#pragma once

#include <3D/DATAMAT.H>
#include <SYSTEM/ADELINE_TYPES.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
typedef void(Func_LongRotatePoint)(TYPE_MAT *Mat, int32_t x, int32_t y, int32_t z);

// -----------------------------------------------------------------------------
void LongRotatePoint_C(TYPE_MAT *Mat, int32_t x, int32_t y, int32_t z);
#define LongRotatePoint LongRotatePoint_C

// -----------------------------------------------------------------------------
#define LongWorldRotatePoint(x, y, z) LongRotatePoint(&MatriceWorld, x, y, z)

// =============================================================================
#ifdef __cplusplus
}
#endif
