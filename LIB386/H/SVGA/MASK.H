#pragma once

#include <SVGA/GRAPH.H>
#include <SYSTEM/ADELINE_TYPES.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
extern uint8_t ColMask;

// -----------------------------------------------------------------------------
int32_t AffMask(int32_t nummask, int32_t x, int32_t y, void *bankmask);

// -----------------------------------------------------------------------------
#define ColorMask(color) ColMask = (uint8_t)(color)

#define GetDxDyMask(nummask, px, py, bankmask)                                 \
  GetDxDyGraph(nummask, px, py, bankmask)

// =============================================================================
#ifdef __cplusplus
}
#endif
