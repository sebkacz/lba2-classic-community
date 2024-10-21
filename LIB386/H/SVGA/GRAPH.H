#pragma once

#include <SYSTEM/ADELINE_TYPES.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
int32_t AffGraph(int32_t numgraph, int32_t x, int32_t y, const void *bankgraph);
int32_t GetDxDyGraph(int32_t numgraph, int32_t *x, int32_t *y, const void *bankgraph);
int32_t GetBoxGraph(int32_t numgraph, int32_t *x0, int32_t *y0, int32_t *x1, int32_t *y1,
                const void *bankgraph);

// =============================================================================
#ifdef __cplusplus
}
#endif
