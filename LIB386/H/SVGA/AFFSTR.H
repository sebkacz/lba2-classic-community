#pragma once

#include <SYSTEM/ADELINE_TYPES.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
extern uint32_t SizeChar;
extern uint8_t TextInk;
extern uint8_t TextPaper;

// -----------------------------------------------------------------------------
extern void AffString(int32_t x, int32_t y, char *str);

// -----------------------------------------------------------------------------
#define CoulText(ink, paper)                                                   \
  {                                                                            \
    TextInk = (uint8_t)(ink);                                                       \
    TextPaper = (uint8_t)(paper);                                                   \
  }

// =============================================================================
#ifdef __cplusplus
}
#endif
