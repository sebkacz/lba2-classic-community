#pragma once

#include <3D/DATAMAT.H>
#include <SYSTEM/ADELINE_TYPES.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
typedef void(Func_MulMatrix)(int32_t *MatDst, int32_t *MatSrc1, int32_t *MatSrc2);

// -----------------------------------------------------------------------------
extern Func_MulMatrix *MulMatrix; ///< Do Not call from C

// =============================================================================
#ifdef __cplusplus
}
#endif
