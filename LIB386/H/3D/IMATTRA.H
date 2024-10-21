#pragma once

#include <3D/DATAMAT.H>
#include <SYSTEM/ADELINE_TYPES.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
typedef void(Func_InitMatrixTrans)(TYPE_MAT *MatDst, int32_t tx, int32_t ty, int32_t tz);

// -----------------------------------------------------------------------------
extern Func_InitMatrixTrans *InitMatrixTrans; ///< Do Not call from C

// =============================================================================
#ifdef __cplusplus
}
#endif
