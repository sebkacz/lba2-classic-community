#pragma once

#include <SVGA/MASK.H>
#include <SYSTEM/ADELINE_TYPES.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
extern void *PtrFont;
extern int32_t InterLeave;
extern int32_t InterSpace;

// -----------------------------------------------------------------------------
extern int32_t SizeFont(char *str);
extern int32_t CarFont(int32_t x, int32_t y, char c);
extern int32_t Font(int32_t x, int32_t y, const char *str);

// -----------------------------------------------------------------------------
#define ColorFont(color) ColorMask(color)

#define SetFont(ptrfont, interleave, interspace)                               \
  {                                                                            \
    PtrFont = (ptrfont);                                                       \
    InterLeave = (interleave);                                                 \
    InterSpace = (interspace);                                                 \
  }

// =============================================================================
#ifdef __cplusplus
}
#endif
