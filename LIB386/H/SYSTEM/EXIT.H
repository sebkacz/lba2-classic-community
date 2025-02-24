#pragma once

#include <SYSTEM/ADELINE_TYPES.H>
#include <SYSTEM/LIMITS.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
extern char PathConfigFile[ADELINE_MAX_PATH];

// -----------------------------------------------------------------------------
extern uint32_t RegisterInitClear(PTR_VOID_FUNC init, PTR_VOID_FUNC clear);

// =============================================================================
#ifdef __cplusplus
}
#endif
