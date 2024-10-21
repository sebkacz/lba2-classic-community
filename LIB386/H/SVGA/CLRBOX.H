#pragma once

#include <SVGA/BOX.H>
#include <SVGA/DIRTYBOX.H>
#include <SYSTEM/ADELINE_TYPES.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
typedef void (Func_ClearBox)(void *dst, uint32_t *TabOffDst, T_BOX *box);

// -----------------------------------------------------------------------------
extern Func_ClearBox *ClearBox;
extern void SetClearColor(uint32_t color);

// =============================================================================
#ifdef __cplusplus
}
#endif
