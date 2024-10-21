#pragma once

#include <3D/DATAMAT.H>
#include <SYSTEM/ADELINE_TYPES.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
typedef void(Func_LongInverseRotatePoint)(TYPE_MAT *Mat, int32_t x, int32_t y, int32_t z);

// -----------------------------------------------------------------------------
void LongInverseRotatePoint_C(TYPE_MAT *Mat, int32_t x, int32_t y, int32_t z);
#define LongInverseRotatePoint LongInverseRotatePoint_C

// -----------------------------------------------------------------------------
#define LongWorldInverseRotatePoint(x, y, z)                                   \
  LongInverseRotatePoint(&MatriceWorld, x, y, z)

// =============================================================================
#ifdef __cplusplus
}
#endif
