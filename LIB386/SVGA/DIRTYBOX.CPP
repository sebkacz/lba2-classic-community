#include <SVGA/DIRTYBOX.H>

#include <SVGA/CLIP.H>
#include <SVGA/CLRBOX.H>
#include <SVGA/GRAPH.H>
#include <SVGA/RESBLOCK.H>
#include <SVGA/SAVBLOCK.H>
#include <SVGA/SCREEN.H>
#include <SVGA/VIDEO.H>
#include <SYSTEM/ADELINE.H>
#include <SYSTEM/CPU.H>
#include <SYSTEM/EVENTS.H>
#include <SYSTEM/MOUSE.H>
#include <SYSTEM/N_MALLOC.H>

#include <limits.h>
#include <stdlib.h>
#include <string.h>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// --- Public state ------------------------------------------------------------
int32_t BoxClipXMin, BoxClipXMax, BoxClipYMin, BoxClipYMax;
int32_t BoxCleanClip;
BOX_FUNC *BoxOneBlit, *BoxOneClean;
VOID_FUNC *BoxScreenGet, *BoxScreenRelease, *BoxScreenFlip;

// --- Private state -----------------------------------------------------------
static uint8_t BufferSprite[48 * 48];

static int32_t BoxMask = ~7;
static int32_t BoxAlign = 7;

static T_BOX *pBoxMalloc = NULL;
static T_BOX *pBoxFree = NULL;

static T_BOX *pBoxStaticList = NULL;
static T_BOX *pBoxOptList = NULL;
static T_BOX *pBoxMovingList = NULL;

// --- Private functions -------------------------------------------------------
void NewBox(T_BOX **boxlist, int32_t x0, int32_t y0, int32_t x1, int32_t y1);

void CollapseList(T_BOX **boxlist) {
  T_BOX *pbox;

  pbox = *boxlist;

  if (pbox) {
    T_BOX *pbox2;
    int32_t x0, y0, x1, y1;

    x0 = y0 = INT_MAX;
    x1 = y1 = INT_MIN;

    do // compute bounding box
    {
      x0 = ade_min(x0, pbox->x0);
      y0 = ade_min(y0, pbox->y0);
      x1 = ade_max(x1, pbox->x1);
      y1 = ade_max(y1, pbox->y1);

      pbox2 = pbox;
      pbox = pbox->pBoxNext;
    } while (pbox);

    pbox = *boxlist;

    pbox2->pBoxNext = pBoxFree; // link list with free list
    pBoxFree = pbox->pBoxNext;

    pbox->x0 = (int16_t)x0;
    pbox->y0 = (int16_t)y0;
    pbox->x1 = (int16_t)x1;
    pbox->y1 = (int16_t)y1;

    pbox->pBoxNext = NULL;
  }
}

void CollapseAllLists() {
  CollapseList(&pBoxMovingList);
  CollapseList(&pBoxStaticList);
  CollapseList(&pBoxOptList);
}

void DelBox(T_BOX **ppbox) {
  T_BOX *pbox;

  pbox = *ppbox;

  *ppbox = pbox->pBoxNext;

  pbox->pBoxNext = pBoxFree;
  pBoxFree = pbox;
}

void AddSortBox(T_BOX **boxlist, T_BOX *pbox, int32_t y0) {
  while (*boxlist) {
    if ((*boxlist)->y0 >= y0) {
      break;
    }
    boxlist = &((*boxlist)->pBoxNext);
  }

  pbox->pBoxNext = *boxlist;
  *boxlist = pbox;
}

void EmptyList(T_BOX **boxlist) {
  // This method free the whole chain at once at the end

  T_BOX **ppBox;

  ppBox = boxlist;

  while (*ppBox) // find end of list
  {
    ppBox = &((*ppBox)->pBoxNext);
  }

  *ppBox = pBoxFree;   // end of list linked to free list
  pBoxFree = *boxlist; // free list = list

  *boxlist = NULL; // list is empty
}

void MergeLists(T_BOX **boxlistdst, T_BOX *pboxsrc) {
  while (pboxsrc) {
    NewBox(boxlistdst, pboxsrc->x0, pboxsrc->y0, pboxsrc->x1, pboxsrc->y1);
    pboxsrc = pboxsrc->pBoxNext;
  }
}

void BltListAndEmpty(T_BOX **boxlist) {
  // This method free the whole chain at once at the end because
  // we don't need new boxes during processing.

  T_BOX **ppBox;

  ppBox = boxlist;

  while (*ppBox) // walk the list
  {
    BoxOneBlit(*ppBox);
    ppBox = &((*ppBox)->pBoxNext);
  }

  *ppBox = pBoxFree;   // end of list linked to free list
  pBoxFree = *boxlist; // free list = list

  *boxlist = NULL; // list is empty
}

void CleanList(T_BOX *pboxlist) {
  while (pboxlist) {
    BoxOneClean(pboxlist);
    pboxlist = pboxlist->pBoxNext;
  }
}

void MergeListsAndEmpty(T_BOX **boxlistdst, T_BOX **boxlistsrc) {
  // This method free the block as it walks up the chain.
  // This is slower than freeing the whole list at once at the end
  // but is ensure that we don't run out of boxes while processing
  // (NewBox MAY require a new box every call).

  T_BOX *pbox, *pbox2;

  pbox = *boxlistsrc;

  while (pbox) {
    pbox2 = pbox->pBoxNext; // backup ptr to next block

    pbox->pBoxNext = pBoxFree; // free block
    pBoxFree = pbox;

    NewBox(boxlistdst, pbox->x0, pbox->y0, pbox->x1, pbox->y1);

    pbox = pbox2; // next block
  }

  *boxlistsrc = NULL; // list is empty
}

void BoxPhysClear(int32_t x0, int32_t y0, int32_t x1, int32_t y1) {
  T_BOX box;

  x0 &= BoxMask;
  x1 = (x1 + BoxAlign + 1) & BoxMask;
  y1++;

  box.x0 = (int16_t)x0;
  box.y0 = (int16_t)y0;
  box.x1 = (int16_t)x1;
  box.y1 = (int16_t)y1;
  box.pBoxNext = NULL;

  ClearBox(Phys, TabOffPhysLine, &box);
}

static void BoxClear() {
  BoxReset();

  if (!pBoxMalloc) {
    return;
  }

  Free((void *)pBoxMalloc);
  pBoxMalloc = NULL;
}

// --- Private macros ----------------------------------------------------------
#define CheckClip()                                                            \
  x1++;                                                                        \
  y1++;                                                                        \
  if (x0 < 0)                                                                  \
    x0 = 0;                                                                    \
  if (y0 < 0)                                                                  \
    y0 = 0;                                                                    \
  if (x1 > ModeDesiredX)                                                       \
    x1 = ModeDesiredX;                                                         \
  if (y1 > ModeDesiredY)                                                       \
    y1 = ModeDesiredY;                                                         \
  if ((x1 <= x0) || (y1 <= y0))                                                \
  return

// --- Public interface --------------------------------------------------------
void NewBox(T_BOX **boxlist, int32_t x0, int32_t y0, int32_t x1, int32_t y1) {
  int32_t bx0, by0, bx1, by1;
  int32_t restart;
  int32_t testsurf, bestsurf;
  T_BOX **ppboxbest, *pbox, **ppbox;

  x0 &= BoxMask;
  x1 = (x1 + BoxAlign) & BoxMask;

  testsurf = (x1 - x0) * (y1 - y0);
again:
  bestsurf = INT_MAX;
  do {
    restart = FALSE;
    ppbox = boxlist;
    for (pbox = *ppbox; pbox; pbox = pbox->pBoxNext) {
      int32_t comsurf, totalsurf;
      int32_t cx0, cy0, cx1, cy1;

      cx0 = pbox->x0;
      cx1 = pbox->x1;
      cy0 = pbox->y0;
      cy1 = pbox->y1;

      if ((cx0 <= x0) && (cy0 <= y0) && (cx1 >= x1) && (cy1 >= y1)) {
        return; // box included in another one
      }

      cx0 = ade_min(cx0, x0);
      cx1 = ade_max(cx1, x1);
      cy0 = ade_min(cy0, y0);
      cy1 = ade_max(cy1, y1);

      comsurf = (cx1 - cx0) * (cy1 - cy0);
      totalsurf = testsurf + (pbox->x1 - pbox->x0) * (pbox->y1 - pbox->y0);

      if (comsurf <= totalsurf) {
        x0 = cx0;
        y0 = cy0;
        x1 = cx1;
        y1 = cy1;
        testsurf = comsurf;

        DelBox(ppbox);

        restart = TRUE;
        break;
      }
      if (comsurf < bestsurf) {
        bx0 = cx0;
        by0 = cy0;
        bx1 = cx1;
        by1 = cy1;
        bestsurf = comsurf;

        ppboxbest = ppbox;
      }
      ppbox = &(pbox->pBoxNext);
    }
  } while (restart);

  pbox = pBoxFree;

  if (pbox == NULL) // no more free boxes
  {
    if (bestsurf == INT_MAX) // list is empty
    {
      CollapseAllLists(); // A REVOIR !!!!
      pbox = pBoxFree;
      if (pbox == NULL) {
        return;
      }
    } else {
      DelBox(ppboxbest); // Delete best merge

      x0 = bx0; // new box = common surface
      y0 = by0;
      x1 = bx1;
      y1 = by1;
      testsurf = bestsurf;

      goto again; // reinject in the list
    }
  }

  pBoxFree = pbox->pBoxNext;

  pbox->x0 = (int16_t)x0;
  pbox->y0 = (int16_t)y0;
  pbox->x1 = (int16_t)x1;
  pbox->y1 = (int16_t)y1;

  AddSortBox(boxlist, pbox, y0);
}

void BoxMovingAdd(int32_t x0, int32_t y0, int32_t x1, int32_t y1) {
  CheckClip();

  NewBox(&pBoxMovingList, x0, y0, x1, y1);
}

void BoxStaticAdd(int32_t x0, int32_t y0, int32_t x1, int32_t y1) {
  CheckClip();

  NewBox(&pBoxStaticList, x0, y0, x1, y1);
}

void BoxUnstaticAdd(int32_t x0, int32_t y0, int32_t x1, int32_t y1) {
  T_BOX box;

  CheckClip();

  x0 &= BoxMask;
  x1 = (x1 + BoxAlign) & BoxMask;

  box.x0 = (int16_t)x0;
  box.y0 = (int16_t)y0;
  box.x1 = (int16_t)x1;
  box.y1 = (int16_t)y1;
  box.pBoxNext = NULL;

  BoxOneClean(&box); // offscreen buffer cleanup

  NewBox(&pBoxStaticList, x0, y0, x1, y1);
}

void BoxCls(int32_t x0, int32_t y0, int32_t x1, int32_t y1) {
  T_BOX box;

  CheckClip();

  x0 &= BoxMask;
  x1 = (x1 + BoxAlign) & BoxMask;

  box.x0 = (int16_t)x0;
  box.y0 = (int16_t)y0;
  box.x1 = (int16_t)x1;
  box.y1 = (int16_t)y1;
  box.pBoxNext = NULL;

  DefaultBoxOneClear(&box); // offscreen buffer clear

  NewBox(&pBoxStaticList, x0, y0, x1, y1);
}

void BoxReset() {
  EmptyList(&pBoxMovingList);
  EmptyList(&pBoxStaticList);
  EmptyList(&pBoxOptList);
}

void BoxBlitStaticListToScreen() {
  T_BOX *pBox;

  pBox = pBoxStaticList;

  while (pBox) // walk the list
  {
    CopyVideoArea(Screen, Log, TabOffLine, pBox);
    pBox = pBox->pBoxNext;
  }
}

void BoxBlit() {
  int32_t SaveClipXMin, SaveClipYMin, SaveClipXMax, SaveClipYMax;
  int32_t x0, y0, x1, y1;

  ManageEvents();

  MergeLists(&pBoxOptList, pBoxMovingList); // rebuild BoxOptList

  if (pBoxStaticList) {
    MergeListsAndEmpty(&pBoxOptList,
                       &pBoxStaticList); // add static boxes and clear
  }

  if (FlagMouse) // Display mouse
  {
    int32_t sx, sy;

    GetBoxGraph(MouseSpriteGraphicNum, &x0, &y0, &x1, &y1, MouseSpriteGraphic);

    sx = MouseX;
    sy = MouseY;

    x0 += sx;
    y0 += sy;
    x1 += sx + 1;
    y1 += sy + 1;

    if (x0 < 0)
      x0 = 0;
    if (y0 < 0)
      y0 = 0;

    if (x1 > ModeDesiredX)
      x1 = ModeDesiredX;
    if (y1 > ModeDesiredY)
      y1 = ModeDesiredY;

    if ((x1 > x0) && (y1 > y0)) {
      // Save log under mouse
      SaveBlock(Log, BufferSprite, x0, y0, x1 - 1, y1 - 1);

      SaveClipXMin = ClipXMin;
      SaveClipYMin = ClipYMin;
      SaveClipXMax = ClipXMax;
      SaveClipYMax = ClipYMax;

      ClipXMin = 0;
      ClipYMin = 0;
      ClipXMax = ModeDesiredX - 1;
      ClipYMax = ModeDesiredY - 1;

      AffGraph(MouseSpriteGraphicNum, sx, sy, MouseSpriteGraphic);

      // add box in optlist for immediate blit
      NewBox(&pBoxOptList, x0, y0, x1, y1);
    }
  }

  LockVideoSurface(); // Get access to the screen

  BltListAndEmpty(&pBoxOptList); // Blit boxes to screen

  if (BoxCleanClip) {
    if (BoxClipYMin > 0) {
      BoxPhysClear(0, 0, ModeResX - 1, BoxClipYMin - 1);
    }

    if (BoxClipXMin > 0) {
      BoxPhysClear(0, BoxClipYMin, BoxClipXMin - 1, BoxClipYMax - 1);
    }

    if (BoxClipXMax < ModeResX - 1) {
      BoxPhysClear(BoxClipXMax, BoxClipYMin, ModeResX - 1, BoxClipYMax - 1);
    }

    if (BoxClipYMax < ModeResY - 1) {
      BoxPhysClear(0, BoxClipYMax, ModeResX - 1, ModeResY - 1);
    }

    BoxCleanClip = FALSE;
  }

  UnlockVideoSurface(); // Release screen

  if (FlagMouse && (x1 > x0) && (y1 > y0)) // remove sprite from Log
  {
    // Clean Log
    RestoreBlock(Log, BufferSprite, x0, y0, x1 - 1, y1 - 1);

    ClipXMin = SaveClipXMin;
    ClipYMin = SaveClipYMin;
    ClipXMax = SaveClipXMax;
    ClipYMax = SaveClipYMax;

    // Add sprite to static list to get it
    // cleaned in phys at next blit
    NewBox(&pBoxStaticList, x0, y0, x1, y1);
  }
}

void BoxClean() {
  if (!pBoxOptList) {
    CleanList(pBoxMovingList); // offscreen buffer cleanup

    pBoxOptList = pBoxMovingList; // OptList = BoxMoving
    pBoxMovingList = NULL;        // Clear BoxMoving
  }
}

void BoxUpdate() {
  BoxBlit();
  BoxClean();
}

void BoxStaticFullflip() {
  BoxReset();
  BoxStaticAdd(BoxClipXMin, BoxClipYMin, BoxClipXMax - 1, BoxClipYMax - 1);
  BoxUpdate();
}

void BoxChangeClip(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t clean) {
  x1++;
  y1++;

  if (x0 < 0)
    x0 = 0;
  if (y0 < 0)
    y0 = 0;
  if (x1 > ModeDesiredX)
    x1 = ModeDesiredX;
  if (y1 > ModeDesiredY)
    y1 = ModeDesiredY;

  if ((x1 <= x0) || (y1 <= y0))
    return;

  x0 &= BoxMask;
  x1 = (x1 + BoxAlign) & BoxMask;

  BoxClipXMin = x0;
  BoxClipYMin = y0;
  BoxClipXMax = x1;
  BoxClipYMax = y1;

  BoxCleanClip |= clean;
}

int32_t BoxInit(int32_t nbBox) {
  if ((ProcessorSignature.FPU == 1) &&
      (ProcessorSignature.Family >= 5) // At least Pentium
      && ((ProcessorSignature.Manufacturer == 1) ||
          (ProcessorFeatureFlags.MMX == 1)) // either Intel or MMX
  ) {
    BoxMask = ~7;
    BoxAlign = 7;
  } else {
    BoxMask = ~3;
    BoxAlign = 3;
  }

  if (nbBox < 4) // minimum of one box per list
  {
    nbBox = 4;
  }

  // SetBoxScreenGet(NULL)			;
  // SetBoxScreenRelease(NULL);
  // SetBoxScreenFlip(NULL)			;
  SetBoxOneBlit(NULL);
  SetBoxOneClean(NULL);

  BoxChangeClip(0, 0, ModeDesiredX - 1, ModeDesiredY - 1, TRUE);

  // Allocate chained list of boxes
  pBoxMalloc = (T_BOX *)Malloc(nbBox * sizeof(T_BOX));
  if (!pBoxMalloc) {
    return FALSE;
  } else {
    register T_BOX *pbox;

    pbox = pBoxMalloc;

    for (; nbBox > 1; nbBox--) // link the list
    {
      register T_BOX *pbox2;

      pbox2 = pbox + 1;
      pbox->pBoxNext = pbox2;
      pbox = pbox2;
    }
    pbox->pBoxNext = NULL; // end points to nothing
  }

  pBoxFree = pBoxMalloc; // init the empty list

  atexit(BoxClear);

  return TRUE;
}

void DefaultBoxOneBlit(T_BOX *pbox) {
  if (pbox->x0 < BoxClipXMin)
    pbox->x0 = (int16_t)BoxClipXMin;
  if (pbox->x1 > BoxClipXMax)
    pbox->x1 = (int16_t)BoxClipXMax;
  if (pbox->y0 < BoxClipYMin)
    pbox->y0 = (int16_t)BoxClipYMin;
  if (pbox->y1 > BoxClipYMax)
    pbox->y1 = (int16_t)BoxClipYMax;

  if ((pbox->x1 <= pbox->x0) || (pbox->y1 <= pbox->y0))
    return;

  CopyVideoArea(Phys, Log, TabOffPhysLine, pbox);
}

void DefaultBoxOneClean(T_BOX *pbox) {
  CopyVideoArea(Log, Screen, TabOffLine, pbox);
}
void DefaultBoxOneClear(T_BOX *pbox) { ClearBox(Log, TabOffLine, pbox); }

// =============================================================================
#ifdef __cplusplus
}
#endif
