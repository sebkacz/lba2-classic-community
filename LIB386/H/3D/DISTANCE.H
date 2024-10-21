#pragma once

#include <SYSTEM/ADELINE_TYPES.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
uint32_t Distance2D(int32_t x0, int32_t y0, int32_t x1, int32_t y1);
uint32_t Distance3D(int32_t x0, int32_t y0, int32_t z0, int32_t x1, int32_t y1, int32_t z1);

// =============================================================================
#ifdef __cplusplus
}
#endif
