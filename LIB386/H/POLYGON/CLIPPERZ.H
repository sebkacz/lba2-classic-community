#pragma once

#include <POLYGON/POLY.H>
#include <SYSTEM/ADELINE_TYPES.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
#pragma pack(push, 1)
typedef struct {
  int32_t V_X0;
  int32_t V_Y0;
  int32_t V_Z0;
  uint16_t V_MapU;
  uint16_t V_MapV;
  uint16_t V_Light;
  uint16_t V_Dummy;
} STRUC_CLIPVERTEX;
#pragma pack(pop)

// -----------------------------------------------------------------------------
///< @return -1 if negative half-space
extern uint32_t ClipperZ(STRUC_CLIPVERTEX dst[], STRUC_CLIPVERTEX src[],
                    uint32_t nbvertex, int32_t zclip, int32_t flag);

// =============================================================================
#ifdef __cplusplus
}
#endif
