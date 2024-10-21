#pragma once

#include <SYSTEM/ADELINE_TYPES.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
typedef void(Func_LongRotate)(int32_t x, int32_t z, int32_t angle);

// -----------------------------------------------------------------------------
extern Func_LongRotate *LongRotate;

// =============================================================================
#ifdef __cplusplus
}
#endif
