#include <3D/DISTANCE.H>

#include <math.h>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
uint32_t Distance2D(int32_t x0, int32_t y0, int32_t x1, int32_t y1) {
  int32_t dx = x0 - x1;
  int32_t dy = y0 - y1;

  return sqrtl(dx * dx + dy * dy);
}

uint32_t Distance3D(int32_t x0, int32_t y0, int32_t z0, int32_t x1, int32_t y1, int32_t z1) {
  int32_t dx = x0 - x1;
  int32_t dy = y0 - y1;
  int32_t dz = z0 - z1;

  return sqrtl(dx * dx + dy * dy + dz * dz);
}

// =============================================================================
#ifdef __cplusplus
}
#endif
