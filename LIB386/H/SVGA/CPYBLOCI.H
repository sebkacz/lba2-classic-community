#pragma once

#include <SYSTEM/ADELINE_TYPES.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
void CopyBlockIncrust(int32_t x0, int32_t y0, int32_t x1, int32_t y1, void *src, int32_t xd, int32_t yd,
                      void *dst);

// =============================================================================
#ifdef __cplusplus
}
#endif
