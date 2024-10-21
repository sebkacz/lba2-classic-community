#pragma once

#include <3D/DATAMAT.H>
#include <SYSTEM/ADELINE_TYPES.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
typedef void(Func_RotateMatrix)(TYPE_MAT *MatDst, TYPE_MAT *MatSrc, int32_t x,
                                int32_t y, int32_t z);

// -----------------------------------------------------------------------------
extern Func_RotateMatrix *RotateMatrix; ///< Do Not call from C

// =============================================================================
#ifdef __cplusplus
}
#endif
