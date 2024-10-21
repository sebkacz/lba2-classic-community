#include <SVGA/PLOT.H>

#include <SVGA/CLIP.H>
#include <SVGA/SCREEN.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
void Plot(int32_t x0, int32_t y0, int32_t coul) {
  if ((x0 < ClipXMin) || (x0 > ClipXMax) || (y0 < ClipYMin) ||
      (y0 > ClipYMax)) {
    return;
  }

  ((uint8_t *)Log)[y0 * ModeDesiredX + x0] = (uint8_t)coul;
}

int32_t GetPlot(int32_t x0, int32_t y0) {
  if ((x0 < ClipXMin) || (x0 > ClipXMax) || (y0 < ClipYMin) ||
      (y0 > ClipYMax)) {
    return 0;
  }

  return ((uint8_t *)Log)[y0 * ModeDesiredX + x0];
}

// =============================================================================
#ifdef __cplusplus
}
#endif
