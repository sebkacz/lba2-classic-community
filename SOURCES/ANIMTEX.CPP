#include "C_EXTERN.H"

/*══════════════════════════════════════════════════════════════════════════*/
#define DEF_EFFECT 1
#define MAX_TEX_EFFECTS 10

/*══════════════════════════════════════════════════════════════════════════*/
typedef struct {
  int32_t Type;
  void *PtrStruct;
} T_TEX_EFFECT;

int32_t NbTexEffects = 0;
static T_TEX_EFFECT TexEffectList[MAX_TEX_EFFECTS];
static int32_t LastAnimationTimer;

/*══════════════════════════════════════════════════════════════════════════*/
// plasma struct

typedef struct {

  int16_t *TabVirgule;
  int16_t *TabSpeed;
  int32_t *TabAcc;
  uint8_t *TabColors;

  uint8_t *TexOffset; // devenu ptr sur effet dans tex

  uint8_t Interleave;
  uint8_t NbActivePoints;
  uint8_t NbColors;
  uint8_t Speed;

  uint8_t data_start;

} T_PLASMA;

/*══════════════════════════════════════════════════════════════════════════*/

void ScanTextureAnimation(uint8_t *ptrtex, int32_t nbscanlines) {
  int32_t x;

  nbscanlines *= 256;
  for (x = 0; x < nbscanlines; x++, ptrtex++) {
    if (ptrtex[0] == DEF_EFFECT) {
      uint8_t *ptr;
      int32_t width;
      int32_t effectnum;
      int32_t x1, x2;
      int32_t n;

      // effet trouvé
      effectnum = ptrtex[1 + 2 * 256];

      TexEffectList[NbTexEffects].Type = effectnum;

      // width scan
      ptr = &ptrtex[1 + 256];
      x1 = x2 = x & 0xFF;
      while (*ptr++ == 0) {
        x2++;
        if (x2 == 256)
          break;
      }
      width = 2 + x2 - x1;

      if (width & (width - 1)) {
        // erreur taille texture animee pas exposant de 2
        return;
      }

      switch (effectnum) {
        //------------------------------------------------------------------
      case 0: // plasma
      {
        T_PLASMA *PtrPlasma;
        uint8_t *ptrcol;
        uint8_t *ptrc; // tabcouls
        int16_t *ptrv; // tabvirgule
        int16_t *ptrs; // tabspeed
        int32_t *ptra; // tabacc
        int32_t speed;
        int32_t nbactivepoints;
        int32_t interleave;
        int32_t delta;
        int32_t nbcols;
        int32_t os, ov;

        // lecture des parametres

        // nb colors
        nbcols = 0;
        ptrcol = &ptrtex[1 + 3 * 256];
        while (ptrcol[nbcols] != DEF_EFFECT)
          nbcols++;

        nbactivepoints = ptrtex[2 + 2 * 256];
        if (!nbactivepoints)
          nbactivepoints = 4;

        speed = ptrtex[3 + 2 * 256];
        if (!speed)
          speed = 5;

        delta = width / nbactivepoints;
        interleave = 1;
        while (!((delta >>= 1) & 1))
          interleave++;
        delta = 1 << interleave;

        // init structures
        PtrPlasma = (T_PLASMA *)Malloc(
            sizeof(T_PLASMA) + (nbactivepoints * nbactivepoints * delta * 2) +
            (nbactivepoints * nbactivepoints * 2) +
            (nbactivepoints * nbactivepoints * 4) + nbcols);

        if (!PtrPlasma)
          return;

        TexEffectList[NbTexEffects].PtrStruct = (uint8_t *)PtrPlasma;

        PtrPlasma->TexOffset = ptrtex;
        PtrPlasma->Interleave = (uint8_t)interleave;
        PtrPlasma->NbActivePoints = (uint8_t)nbactivepoints;
        PtrPlasma->NbColors = (uint8_t)nbcols;
        PtrPlasma->Speed = 0;

        ptrv = (int16_t *)&PtrPlasma->data_start;
        ptrs = ptrv + (nbactivepoints * nbactivepoints * delta);
        ptra = (int32_t *)(ptrs + (nbactivepoints * nbactivepoints));
        ptrc = (uint8_t *)(ptra + (nbactivepoints * nbactivepoints));

        PtrPlasma->TabVirgule = ptrv;
        PtrPlasma->TabSpeed = ptrs;
        PtrPlasma->TabAcc = ptra;
        PtrPlasma->TabColors = ptrc;

        // generation des sommets aleatoires
        nbactivepoints *= nbactivepoints;

        for (os = 0, ov = 0; os < nbactivepoints; os++, ov += delta) {
          int32_t va;

          // generation des sommets aleatoires
          ptrv[ov] = (int16_t)MyRnd((nbcols - 1) * 256);
          // generation des vitesses aleatoires
          va = (int16_t)(speed * 512 + MyRnd(speed * 512));
          if (Rnd(2))
            va = -va;

          ptrs[os] = (int16_t)va;
          ptra[os] = 500;
        }

        // color table
        ptrcol = &ptrtex[1 + 3 * 256];
        for (os = 0; os < nbcols; os++) {
          ptrc[os] = ptrcol[os];
        }
      } break;
        //------------------------------------------------------------------
      case 1: // fire
      {
        uint8_t *PtrFire;
        uint8_t *ptrcol;

        // init structures
        PtrFire = (uint8_t *)Malloc(+4 // tex ptr
                                    + 32 * 36 + 32 * 36 + 32);

        if (!PtrFire)
          return;

        TexEffectList[NbTexEffects].PtrStruct = PtrFire;

        // nb colors = 16
        ptrcol = &ptrtex[1 + 3 * 256];

        *((uint8_t **)PtrFire) = ptrtex;

        // color table
        for (n = 0; n < 16; n++) {
          PtrFire[4 + 32 * 36 * 2 + n] = 0;
        }
        for (n = 0; n < 16; n++) {
          PtrFire[4 + 32 * 36 * 2 + n + 16] = *ptrcol++;
        }
      } break;
        //------------------------------------------------------------------
      }

      // clear box effect (connue ou pas)
      ptr = ptrtex;
      for (n = 0; n < width; n++, ptr += 256) {
        memset(ptr, 0, width);
      }

      NbTexEffects++;
    }
  }
}

/*══════════════════════════════════════════════════════════════════════════*/

// Loop to initialise the plasmas, fire...

void InitTextureAnimation(void) {
  ManageTime();
  LastAnimationTimer = TimerSystemHR; // init 1st DoTextureAnimation() loop

  DoTextureAnimation();
}

/*══════════════════════════════════════════════════════════════════════════*/

void DoTextureAnimation() {
  int32_t n;
  int32_t deltatimer, timer;

  ManageTime();

  timer = TimerSystemHR;
  deltatimer = timer - LastAnimationTimer;

  if (deltatimer < 20)
    return;

  LastAnimationTimer = timer;

  for (n = 0; n < NbTexEffects; n++) {
    switch (TexEffectList[n].Type) {
      //--------------------------------------------------------------------
    case 0: // plasma
    {
      int16_t *ptrs, *ptrv;
      int32_t *ptra;
      T_PLASMA *ptreffect;
      int32_t nbactivepoints, delta;
      int32_t nbcols;
      int32_t ov, os;

      ptreffect = (T_PLASMA *)TexEffectList[n].PtrStruct;

      ptrv = ptreffect->TabVirgule;
      ptrs = ptreffect->TabSpeed;
      ptra = ptreffect->TabAcc;

      delta = 1 << ptreffect->Interleave;
      nbactivepoints = ptreffect->NbActivePoints;
      nbactivepoints *= nbactivepoints;
      nbcols = ptreffect->NbColors << 8;

      // Movements of the plasma tops
      for (os = 0, ov = 0; os < nbactivepoints; os++, ov += delta) {
        int32_t sv;

        ptra[os] += ptrs[os] * deltatimer;

        sv = GetDeltaAccMove(&ptra[os]);

        if (!sv)
          continue;

        sv += ptrv[ov];

        if (sv <= 0) {
          sv = 0;
          ptrs[os] = (int16_t)-ptrs[os];
        } else if (sv >= nbcols) {
          sv = nbcols - 1;
          ptrs[os] = (int16_t)-ptrs[os];
        }

        ptrv[ov] = (int16_t)sv;
      }

      Do_Plasma((uint8_t *)TexEffectList[n].PtrStruct);
    } break;
      //--------------------------------------------------------------------
    case 1: // fire
    {
      uint8_t *ptrb;

      ptrb = (uint8_t *)TexEffectList[n].PtrStruct;
      Do_Fire(ptrb + 4, ptrb + 32 * 36 + 4, ptrb + 32 * 36 * 2 + 4,
              *(uint8_t **)ptrb);
    } break;
      //--------------------------------------------------------------------
    }
  }
}

/*══════════════════════════════════════════════════════════════════════════*/
//
//      ATTENTION: Routines dedicated to LBA2 menus
//
/*══════════════════════════════════════════════════════════════════════════*/
int32_t PlasmaMenuIndex;

void InitPlasmaMenu(void) {
  int32_t n;
  uint8_t *ptr;
  uint8_t *texdest;
  uint8_t *ptrorg;

  if (!TexEffectList[NbTexEffects].PtrStruct) {
    ptrorg = (uint8_t *)(SkySeaTexture + 256 * (128 + 64));

    texdest = ptrorg;

    memset(ptrorg, 0, 256);

    ////////////////////////////////////////////////////////

    memset(texdest, 1, 64);
    texdest += 256;
    memset(texdest, 0, 64);
    texdest[0] = 1;
    texdest[63] = 1;
    texdest += 256;
    texdest[0] = 1;
    texdest[1] = 0;
    texdest[2] = 4; // nb control point
    texdest[3] = 2; // speed
    ptr = texdest + 256;
    *ptr++ = 1;
    for (n = 10; n >= 0; n--)
      *ptr++ = (uint8_t)(n + 12 * 16);
    for (n = 0; n < 2; n++)
      *ptr++ = 0;
    *ptr++ = 1;
    /*
                    memset( texdest, 1, 32 ) ;
                    texdest += 256 ;
                    memset( texdest, 0, 32 ) ;
                    texdest[0] = 1 ;
                    texdest[31] = 1 ;
                    texdest += 256 ;
                    texdest[0] = 1 ;
                    texdest[1] = 0 ;
                    texdest[2] = 4 ;        // nb control point
                    texdest[3] = 1 ;        // speed
                    ptr = texdest + 256 ;
                    *ptr++ = 1 ;
                    for( n=0; n<6; n++ )    *ptr++ = (uint8_t)(n+12*16) ;
                    *ptr++ = 1 ;
    */

    PlasmaMenuIndex = NbTexEffects;

    ScanTextureAnimation(ptrorg, 1);
    InitTextureAnimation();
  } else {
    NbTexEffects = PlasmaMenuIndex + 1;
  }
}

/*══════════════════════════════════════════════════════════════════════════*/

void SelectPlasmaBank(uint8_t bank) {
  int32_t n;
  uint8_t *ptr;

  ptr = ((T_PLASMA *)TexEffectList[PlasmaMenuIndex].PtrStruct)->TabColors;

  for (n = 10; n >= 0; n--)
    *ptr++ = (uint8_t)(n + bank * 16);
}

/*══════════════════════════════════════════════════════════════════════════*/

void ClearPlasmaMenu(void) { NbTexEffects = PlasmaMenuIndex; }

/*══════════════════════════════════════════════════════════════════════════*/

void FixePlasmaPtrMap(void) {
  PtrMap = ((T_PLASMA *)TexEffectList[PlasmaMenuIndex].PtrStruct)->TexOffset;
}
