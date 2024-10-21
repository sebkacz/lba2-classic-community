#include <SVGA/GRAPH.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
int32_t GetDxDyGraph(int32_t numgraph, int32_t *x, int32_t *y, const void *bankgraph) {
  const int32_t *graphMem = (const int32_t *)bankgraph;
  const uint8_t *graphBytes = (const uint8_t *)bankgraph;

  // Don't know if the value is really a signed int, but works for now
  int32_t offset = graphMem[numgraph];

  *x = (graphBytes[offset] & 0xFF);
  *y = (graphBytes[offset + 1] & 0xFF);

  return 0; // TODO: Remove, make void
}

// =============================================================================
#ifdef __cplusplus
}
#endif
