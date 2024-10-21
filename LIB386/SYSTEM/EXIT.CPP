#include <SYSTEM/EXIT.H>

#include <stdlib.h>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
char PathConfigFile[ADELINE_MAX_PATH];

// --- Private state -----------------------------------------------------------
static uint32_t NbFuncs = 0;

// -----------------------------------------------------------------------------
uint32_t RegisterInitClear(PTR_VOID_FUNC init, PTR_VOID_FUNC clear) {
  if (NbFuncs == 32) {
    return 1;
  }

  NbFuncs++;

  return clear ? atexit(clear) : 0;
}

// =============================================================================
#ifdef __cplusplus
}
#endif
