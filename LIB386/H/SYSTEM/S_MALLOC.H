#pragma once

#include <SYSTEM/ADELINE_TYPES.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
void SafeErrorMallocMsg();
void SafeFree(void *ptr, char *file, uint32_t line);
void *SafeMshrink(void *ptr, uint32_t taille, char *file, uint32_t line);

// =============================================================================
#ifdef __cplusplus
}
#endif
