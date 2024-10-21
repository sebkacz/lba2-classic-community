#include <3D/CAMERA.H>

#include <3D/DATAMAT.H>
#include <3D/GETANG3D.H>
#include <3D/IMATSTD.H>
#include <3D/LIGHT.H>
#include <3D/LIROT3D.H>
#include <3D/LROT3D.H>
#include <3D/PROJ.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
int32_t LFactorX = 0;
int32_t LFactorY = 0;

int32_t CameraAlpha = 0;
int32_t CameraBeta = 0;
int32_t CameraGamma = 0;

int32_t CameraX = 0;
int32_t CameraY = 0;
int32_t CameraZ = 0;

int32_t CameraXr = 0;
int32_t CameraYr = 0;
int32_t CameraZr = 0;

int32_t CameraZrClip = 0;

int32_t NearClip = 1;

int32_t XCentre = 0;
int32_t YCentre = 0;

int32_t Xp = 0;
int32_t Yp = 0;

int32_t X0 = 0;
int32_t Y0 = 0;
int32_t Z0 = 0;

int32_t TypeProj = TYPE_3D;

float FRatioX = 0.0f;
float FRatioY = 0.0f;

uint64_t MMX_DEMI = (8192LL << 32) | 8192LL;
uint64_t MMX_DEMI2 = (4096LL << 32) | 4096LL;

// -----------------------------------------------------------------------------
void SetCamera(int32_t x, int32_t y, int32_t z) {
  if (TypeProj != TYPE_3D) {
    // iso:
    CameraXr = x;
    CameraYr = y;
    CameraZr = z;
    CameraZrClip = z;
    NearClip = 0;
  } else {
    LongRotatePoint(&MatriceWorld, x, y, z);
    CameraXr = X0;
    CameraYr = Y0;
    CameraZr = Z0;
    CameraZrClip = Z0 - NearClip;
  }
}

void SetTargetCamera(int32_t x, int32_t y, int32_t z, int32_t gamma) {
  y -= CameraZ;
  z -= CameraY;
  x -= CameraX;

  GetAngleVector3D(x, y, z);
  SetAngleCamera(X0, Y0, gamma);
}

void SetAngleCamera(int32_t alpha, int32_t beta, int32_t gamma) {
  if (TypeProj != TYPE_3D) {
    // tiso:
    alpha = 0;
    beta = 0;
    gamma = 0;
  } else {
    // Guarantee values on interval [0, 4095]
    alpha %= 4096;
    beta %= 4096;
    gamma %= 4096;
  }

  // tback:
  CameraAlpha = alpha;
  CameraBeta = beta;
  CameraGamma = gamma;
  InitMatrixStd(&MatriceWorld, alpha, beta, gamma);
  RecomputeLight();

  SetCamera(CameraX, CameraY, CameraZ);
}

void SetPosCamera(int32_t x, int32_t y, int32_t z) {
  CameraX = x;
  CameraY = y;
  CameraZ = z;
  SetCamera(x, y, z);
}

void SetFollowCamera(int32_t targetx, int32_t targety, int32_t targetz, int32_t alpha, int32_t beta,
                     int32_t gamma, int32_t camzoom) {
  CameraX = targetx;
  CameraY = targety;
  CameraZ = targetz;

  SetAngleCamera(alpha, beta, gamma);

  if (TypeProj == TYPE_3D) {
    CameraZr = CameraZr + camzoom;
    CameraZrClip = CameraZrClip + camzoom;

    LongInverseRotatePoint(&MatriceWorld, CameraXr, CameraYr, CameraZr);
    CameraX = X0;
    CameraY = Y0;
    CameraZ = Z0;
  }
}

// =============================================================================
#ifdef __cplusplus
}
#endif
