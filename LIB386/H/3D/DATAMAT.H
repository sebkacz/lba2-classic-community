#pragma once

#include <SYSTEM/ADELINE_TYPES.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
#pragma pack(push, 1)
typedef union {
  struct {
    float M11;
    float M12;
    float M13;
    float M21;
    float M22;
    float M23;
    float M31;
    float M32;
    float M33;
    float TX;
    float TY;
    float TZ;
  } F;
  struct {
    int32_t M11;
    int32_t M12;
    int32_t M13;
    int32_t M21;
    int32_t M22;
    int32_t M23;
    int32_t M31;
    int32_t M32;
    int32_t M33;
    int32_t TX;
    int32_t TY;
    int32_t TZ;
  } I;
  struct {
    int16_t M11;
    int16_t M12;
    int16_t M13;
    int16_t M14;
    int16_t M21;
    int16_t M22;
    int16_t M23;
    int16_t M24;
    int16_t M31;
    int16_t M32;
    int16_t M33;
    int16_t M34;
    int16_t TX;
    int16_t TY;
    int16_t TZ;
  } M;
} TYPE_MAT;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
  int16_t X;
  int16_t Y;
  int16_t Z;
  int16_t Grp;
} TYPE_VT16;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
  int32_t X;
  int32_t Y;
  int32_t Z;
} TYPE_VT32;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
  int16_t X;
  int16_t Y;
} TYPE_PT;
#pragma pack(pop)

// -----------------------------------------------------------------------------
extern TYPE_MAT MatriceWorld;
extern TYPE_MAT MatrixLib1;
extern TYPE_MAT MatrixLib2;
extern TYPE_MAT MatriceRot;

// =============================================================================
#ifdef __cplusplus
}
#endif
