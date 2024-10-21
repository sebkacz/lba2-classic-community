#pragma once

#include <SYSTEM/ADELINE_TYPES.H>
#include <cstdint>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
extern int32_t AlphaLight, BetaLight, GammaLight;
extern int32_t NormalXLight, NormalYLight, NormalZLight;
extern int32_t CameraXLight, CameraYLight, CameraZLight;
extern int32_t PosXLight, PosYLight, PosZLight;
extern int32_t TargetXLight, TargetYLight, TargetZLight;
extern int32_t LightNormalUnit;
extern float FactorLight;

// -----------------------------------------------------------------------------
void SetLightVector(int32_t alpha, int32_t beta, int32_t gamma);
void RecomputeLight();

// -----------------------------------------------------------------------------
#define SetLightIntensity(intensity) (LightNormalUnit = (intensity))

// =============================================================================
#ifdef __cplusplus
}
#endif
