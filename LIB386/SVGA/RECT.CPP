#include <SVGA/RECT.H>

#include <SVGA/FIL_LINE.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
void Rect(int32_t x0, int32_t y0, int32_t x1, int32_t y1, int32_t coul) {
  Line(x0, y0, x1, y0, coul);
  Line(x0, y1, x1, y1, coul);
  Line(x0, y0, x0, y1, coul);
  Line(x1, y0, x1, y1, coul);
}

// =============================================================================
#ifdef __cplusplus
}
#endif
