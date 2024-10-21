#pragma once

#include <SYSTEM/ADELINE_TYPES.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
void ScaleBox(int32_t xs0, int32_t ys0, int32_t xs1, int32_t ys1, void *ptrs, int32_t xd0, int32_t yd0,
              int32_t xd1, int32_t yd1, void *ptrd);

// =============================================================================
#ifdef __cplusplus
}
#endif
