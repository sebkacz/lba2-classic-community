#pragma once

#include <SYSTEM/ADELINE_TYPES.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
extern int32_t LFactorX;
extern int32_t LFactorY;

extern int32_t CameraAlpha;
extern int32_t CameraBeta;
extern int32_t CameraGamma;

extern int32_t CameraX;
extern int32_t CameraY;
extern int32_t CameraZ;

extern int32_t CameraXr;
extern int32_t CameraYr;
extern int32_t CameraZr;

extern int32_t CameraZrClip;

extern int32_t NearClip;

extern int32_t XCentre;
extern int32_t YCentre;

extern int32_t Xp;
extern int32_t Yp;

extern int32_t X0;
extern int32_t Y0;
extern int32_t Z0;

extern int32_t TypeProj;

extern float FRatioX;
extern float FRatioY;

extern uint64_t MMX_DEMI;
extern uint64_t MMX_DEMI2;

// -----------------------------------------------------------------------------
void SetCamera(int32_t x, int32_t y, int32_t z);
void SetTargetCamera(int32_t x, int32_t y, int32_t z, int32_t gamma);
void SetAngleCamera(int32_t alpha, int32_t beta, int32_t gamma);
void SetPosCamera(int32_t x, int32_t y, int32_t z);
void SetFollowCamera(int32_t targetx, int32_t targety, int32_t targetz, int32_t alpha, int32_t beta,
                     int32_t gamma, int32_t camzoom);

// =============================================================================
#ifdef __cplusplus
}
#endif
