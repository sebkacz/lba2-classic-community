#pragma once

#include <SYSTEM/ADELINE_TYPES.H>
#include <cstdint>

// -----------------------------------------------------------------------------

#pragma pack(push, 1)
typedef struct {
  int16_t Type;
  int16_t Alpha;
  int16_t Beta;
  int16_t Gamma;
} T_GROUP_INFO;
#pragma pack(pop)

#pragma pack(push, 1)
typedef union {
  void *Ptr;
  int32_t Num;
} T_PTR_NUM;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
  int32_t X; // world coor
  int32_t Y;
  int32_t Z;

  int32_t Alpha; // local angles
  int32_t Beta;
  int32_t Gamma;

  T_PTR_NUM Body;
  ; // ->.O3D
  T_PTR_NUM NextBody;
  ;               // ->.O3D
  T_PTR_NUM Anim; // ->.A3D

  void *Texture;     //
  void *NextTexture; //

  uint32_t LastOfsIsPtr;

  int32_t LastFrame;
  uint32_t LastOfsFrame;
  uint32_t LastTimer; // last TimerRef
  uint32_t LastNbGroups;

  int32_t NextFrame;
  uint32_t NextOfsFrame;
  uint32_t NextTimer; // TimerRef when frame reached
  uint32_t NextNbGroups;

  int32_t LoopFrame;
  uint32_t LoopOfsFrame;

  uint32_t NbFrames;

  int32_t LastAnimStepX;
  int32_t LastAnimStepY;
  int32_t LastAnimStepZ;

  int32_t LastAnimStepAlpha;
  int32_t LastAnimStepBeta;
  int32_t LastAnimStepGamma;

  uint32_t Interpolator; // lib internal

  uint32_t Time; // TimerRef last modif

  uint32_t Status; // BitField FLAG_*

  uint32_t Master; // BitField ANIM_MASTER_ROT

  uint32_t NbGroups;

  T_GROUP_INFO CurrentFrame[30];
} T_OBJ_3D;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
  int16_t X;
  int16_t Y;
  int16_t Z;
  int16_t Group;
} T_OBJ_POINT;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct {
  int32_t Info;
  int16_t SizeHeader;
  int16_t Dummy;
  int32_t XMin;
  int32_t XMax;
  int32_t YMin;
  int32_t YMax;
  int32_t ZMin;
  int32_t ZMax;
  int32_t NbGroupes;
  int32_t OffGroupes;
  int32_t NbPoints;
  int32_t OffPoints;
  int32_t NbNormales;
  int32_t OffNormales;
  int32_t NbNormFaces;
  int32_t OffNormFaces;
  int32_t NbPolys;
  int32_t OffPolys;
  int32_t NbLines;
  int32_t OffLines;
  int32_t NbSpheres;
  int32_t OffSpheres;
  int32_t NbTextures;
  int32_t OffTextures;
} T_BODY_HEADER;
#pragma pack(pop)

// -----------------------------------------------------------------------------
#define TYPE_ROTATE 0
#define TYPE_TRANSLATE 1
#define MASK_OBJECT_VERSION (0xff) //; Dans Obj_Info
#define MASK_OBJECT_ANIMATED (1 << 8)
#define MASK_OBJECT_NO_SORT (1 << 9)
#define MASK_OBJECT_TRANSPARENT (1 << 10)

// -----------------------------------------------------------------------------
extern uint8_t *ObjPtrMap; // Ptr on the current texture page
extern T_OBJ_POINT Obj_ListRotatedPoints[];

// -----------------------------------------------------------------------------
extern int32_t ObjectDisplay(T_OBJ_3D *obj);
extern int32_t BodyDisplay(int32_t x, int32_t y, int32_t z, int32_t alpha, int32_t beta, int32_t gamma,
                       void *obj);
extern int32_t BodyDisplay_AlphaBeta(int32_t x, int32_t y, int32_t z, int32_t alpha, int32_t beta,
                                 int32_t gamma, void *obj);