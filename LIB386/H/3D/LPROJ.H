#pragma once

#include <3D/DATAMAT.H>
#include <SYSTEM/ADELINE_TYPES.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
typedef int32_t(Func_LongProjectPoint)(int32_t x, int32_t y, int32_t z);

// -----------------------------------------------------------------------------
int32_t LongProjectPoint_C(int32_t x, int32_t y, int32_t z);
#define LongProjectPoint LongProjectPoint_C

extern Func_LongProjectPoint LongProjectPointIso; ///< Do Not call from C
extern Func_LongProjectPoint *LongProjectPoint3D; ///< Do Not call from C

// -----------------------------------------------------------------------------
typedef int32_t(Func_ProjectList)(TYPE_PT *Dst, TYPE_VT16 *Src, int32_t NbPt, int32_t OrgX,
                              int32_t OrgY, int32_t OrgZ);

// -----------------------------------------------------------------------------
extern Func_ProjectList *ProjectList;   ///< Do Not call from C
extern Func_ProjectList ProjectListIso; ///< Do Not call from C
extern Func_ProjectList *ProjectList3D; ///< Do Not call from C

// =============================================================================
#ifdef __cplusplus
}
#endif
