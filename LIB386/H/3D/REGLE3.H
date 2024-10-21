#pragma once

#include <SYSTEM/ADELINE_TYPES.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
int32_t RegleTrois(int32_t Val1, int32_t Val2, int32_t NbSteps, int32_t CurrentStep);
int32_t BoundRegleTrois(int32_t Val1, int32_t Val2, int32_t NbSteps, int32_t CurrentStep);

// =============================================================================
#ifdef __cplusplus
}
#endif
