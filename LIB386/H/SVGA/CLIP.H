#pragma once

#include <SYSTEM/ADELINE_TYPES.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
extern int32_t ClipXMin;
extern int32_t ClipYMin;
extern int32_t ClipXMax;
extern int32_t ClipYMax;

extern int32_t ClipWindowXMin;
extern int32_t ClipWindowYMin;
extern int32_t ClipWindowXMax;
extern int32_t ClipWindowYMax;

extern int32_t MemoClipXMin;
extern int32_t MemoClipYMin;
extern int32_t MemoClipXMax;
extern int32_t MemoClipYMax;

extern int32_t MemoClipWindowXMin;
extern int32_t MemoClipWindowYMin;
extern int32_t MemoClipWindowXMax;
extern int32_t MemoClipWindowYMax;

// -----------------------------------------------------------------------------
void MemoClip();
void RestoreClip();
void SetClip(int32_t x0, int32_t y0, int32_t x1, int32_t y1);
void UnsetClip();

void MemoClipWindow();
void RestoreClipWindow();
void SetClipWindow(int32_t x0, int32_t y0, int32_t x1, int32_t y1);
void UnsetClipWindow();

// =============================================================================
#ifdef __cplusplus
}
#endif
