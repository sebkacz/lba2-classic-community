#pragma once

#include <SYSTEM/ADELINE_TYPES.H>
#include <cstdint>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
// Init:
//
// BoxInit( ... );
//
// processing loop:
//
// for( ...
// {
//    BoxMovingAdd( ... ) ;
//    AND/OR
//    BoxStaticAdd( ... ) ;
// }
//
// BoxUpdate() ;
//

// -----------------------------------------------------------------------------
extern int32_t BoxClipXMin, BoxClipXMax, BoxClipYMin, BoxClipYMax;
extern int32_t BoxCleanClip;

extern BOX_FUNC *BoxOneBlit, *BoxOneClean;
extern VOID_FUNC *BoxScreenGet, *BoxScreenRelease, *BoxScreenFlip;

// -----------------------------------------------------------------------------
int32_t BoxInit(int32_t nbBox);
void BoxMovingAdd(int32_t x0, int32_t y0, int32_t x1, int32_t y1);
void BoxStaticAdd(int32_t x0, int32_t y0, int32_t x1, int32_t y1);
void BoxUnstaticAdd(int32_t x0, int32_t y0, int32_t x1, int32_t y1);
void BoxCls(int32_t x0, int32_t y0, int32_t x1, int32_t y1);
void BoxStaticFullflip();
void BoxBlitStaticListToScreen();
void BoxBlit();
void BoxClean();
void BoxUpdate();
void BoxReset();
void BoxChangeClip(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t clean);

extern void DefaultBoxOneBlit(T_BOX *pbox);
extern void DefaultBoxOneClean(T_BOX *pbox);
extern void DefaultBoxOneClear(T_BOX *pbox);

// -----------------------------------------------------------------------------
#define Flip BoxStaticFullflip

#define Cls() BoxCls(BoxClipXMin, BoxClipYMin, BoxClipXMax - 1, BoxClipYMax - 1)

#define SetBoxScreenGet(boxscreenget)                                          \
  BoxScreenGet = ((boxscreenget) ? (boxscreenget) : LockPrimary)

#define SetBoxScreenRelease(boxscreenrelease)                                  \
  BoxScreenRelease = ((boxscreenrelease) ? (boxscreenrelease) : UnlockPrimary)

#define SetBoxScreenFlip(boxscreenflip) BoxScreenFlip = (boxscreenflip)

#define SetBoxOneBlit(boxoneblit)                                              \
  BoxOneBlit = ((boxoneblit) ? (boxoneblit) : DefaultBoxOneBlit)

#define SetBoxOneClean(boxoneclean)                                            \
  BoxOneClean = ((boxoneclean) ? (boxoneclean) : DefaultBoxOneClean)

// =============================================================================
#ifdef __cplusplus
}
#endif
