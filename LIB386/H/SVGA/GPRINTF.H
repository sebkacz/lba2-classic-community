#pragma once

#include <SYSTEM/ADELINE_TYPES.H>
#include <cstdint>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
extern int32_t TextXMin;
extern int32_t TextXMax;
extern int32_t TextYMin;
extern int32_t TextYMax;

// -----------------------------------------------------------------------------
void GraphPrintf(uint32_t flagflip, uint32_t x, uint32_t y, const char *format, ...);

// =============================================================================
#ifdef __cplusplus
}
#endif
