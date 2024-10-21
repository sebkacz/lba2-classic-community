#include <SVGA/CLIP.H>

#include <SVGA/VIDEO.H>
#include <SYSTEM/ADELINE.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
int32_t ClipXMin = 0;
int32_t ClipYMin = 0;
int32_t ClipXMax = 0;
int32_t ClipYMax = 0;

int32_t ClipWindowXMin = 0;
int32_t ClipWindowYMin = 0;
int32_t ClipWindowXMax = 0;
int32_t ClipWindowYMax = 0;

int32_t MemoClipXMin = 0;
int32_t MemoClipYMin = 0;
int32_t MemoClipXMax = 0;
int32_t MemoClipYMax = 0;

int32_t MemoClipWindowXMin = 0;
int32_t MemoClipWindowYMin = 0;
int32_t MemoClipWindowXMax = 0;
int32_t MemoClipWindowYMax = 0;

// -----------------------------------------------------------------------------
void MemoClip() {
  MemoClipXMin = ClipXMin;
  MemoClipXMax = ClipXMax;
  MemoClipYMin = ClipYMin;
  MemoClipYMax = ClipYMax;
}

void RestoreClip() {
  SetClip(MemoClipXMin, MemoClipYMin, MemoClipXMax, MemoClipYMax);
}

void SetClip(int32_t x0, int32_t y0, int32_t x1, int32_t y1) {
  ClipXMin = ade_max(x0, ClipWindowXMin);
  ClipXMax = ade_min(x1, ClipWindowXMax);
  ClipYMin = ade_max(y0, ClipWindowYMin);
  ClipYMax = ade_min(y1, ClipWindowYMax);
}

void UnsetClip() {
  ClipXMin = ClipWindowXMin;
  ClipXMax = ClipWindowXMax;
  ClipYMin = ClipWindowYMin;
  ClipYMax = ClipWindowYMax;
}

void MemoClipWindow() {
  MemoClipWindowXMin = ClipWindowXMin;
  MemoClipWindowXMax = ClipWindowXMax;
  MemoClipWindowYMin = ClipWindowYMin;
  MemoClipWindowYMax = ClipWindowYMax;
}

void RestoreClipWindow() {
  SetClipWindow(MemoClipWindowXMin, MemoClipWindowYMin,
                MemoClipWindowXMax, MemoClipWindowYMax);
}

void SetClipWindow(int32_t x0, int32_t y0, int32_t x1, int32_t y1) {
  ClipWindowXMin = ade_max(0, x0);
  ClipWindowXMax = ade_min(x1, ModeResX - 1);
  ClipWindowYMin = ade_max(0, y0);
  ClipWindowYMax = ade_min(y1, ModeResY - 1);

  SetClip(ClipXMin, ClipYMin, ClipXMax, ClipYMax);
}

void UnsetClipWindow() {
  ClipWindowXMax = ModeResX - 1;
  ClipXMax = ClipWindowXMax;
  ClipWindowXMin = 0;
  ClipXMin = 0;

  ClipWindowYMax = ModeResY - 1;
  ClipYMax = ClipWindowYMax;
  ClipWindowYMin = 0;
  ClipYMin = 0;
}

// =============================================================================
#ifdef __cplusplus
}
#endif
