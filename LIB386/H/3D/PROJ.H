#pragma once

#include <SYSTEM/ADELINE_TYPES.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
enum ProjectionType { TYPE_3D = 0, TYPE_ISO = 1 };

// -----------------------------------------------------------------------------
extern void SetProjection(int32_t xcentre, int32_t ycentre, int32_t clip, int32_t factorx,
                          int32_t factory);
extern void SetIsoProjection(int32_t xcentre, int32_t ycentre);

// =============================================================================
#ifdef __cplusplus
}
#endif
