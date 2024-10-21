#pragma once

#include <SYSTEM/ADELINE_TYPES.H>
#include <SYSTEM/LIMITS.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// --- Public state ------------------------------------------------------------
extern void *Phys;
extern uint32_t ModeResX; ///< X resolution for Phys
extern uint32_t ModeResY; ///< Y resolution for Phys
extern uint32_t TabOffPhysLine[ADELINE_MAX_Y_RES]; ///< Line offsets for Phys

// --- Initialization ----------------------------------------------------------
bool InitVideo();
void EndVideo();

// --- Interface ---------------------------------------------------------------
bool CreateVideoSurface(uint32_t resX, uint32_t resY);
uint32_t VideoSurfacePitch();
void LockVideoSurface();
void UnlockVideoSurface();
void WaitVideoSync();
void SetVideoPalette(const uint8_t src[], int32_t startIdx, int32_t count);
void SetVideoPaletteCol(int32_t colorIdx, uint8_t r, uint8_t g, uint8_t b);
void SetVideoPaletteSync(const uint8_t src[]);
void CopyVideoArea(void *dst, const void *src, const uint32_t tabOffDst[],
                   const T_BOX *area);

void HandleEventsVideo(const void *event);

// -----------------------------------------------------------------------------
#define Palette(Pal) SetVideoPalette(Pal, 0, 256)
#define PalOne(col, r, g, b) SetVideoPaletteCol(col, r, g, b)

// =============================================================================
#ifdef __cplusplus
}
#endif
