#pragma once

#include <3D/DATAMAT.H>
#include <SYSTEM/ADELINE_TYPES.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
typedef void(Func_InitMatrix)(TYPE_MAT *MatDst, int32_t alpha, int32_t beta, int32_t gamma);

// -----------------------------------------------------------------------------
void InitMatrixStd_C(TYPE_MAT *MatDst, int32_t alpha, int32_t beta, int32_t gamma);
#define InitMatrixStd InitMatrixStd_C

// =============================================================================
#ifdef __cplusplus
}
#endif
