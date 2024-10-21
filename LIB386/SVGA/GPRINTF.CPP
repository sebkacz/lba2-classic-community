#include <SVGA/GPRINTF.H>

#include <SVGA/AFFSTR.H>
#include <SVGA/CLIP.H>
#include <SVGA/DIRTYBOX.H>

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
int32_t TextXMin = 0;
int32_t TextXMax = 0;
int32_t TextYMin = 0;
int32_t TextYMax = 0;

// -----------------------------------------------------------------------------
void GraphPrintf(uint32_t flagflip, uint32_t x, uint32_t y, const char *format, ...) {
  int32_t len;
  char *ptr;
  char msgbuf[256];
  va_list arglist;

  if ((y < ClipYMin) OR(y > ClipYMax - 7) OR(x > ClipXMax))
    return;

  va_start(arglist, format);
  len = vsnprintf(msgbuf, 256, format, arglist);
  va_end(arglist);

  if (len == -1)
    return;

  ptr = msgbuf;

  if (x + len * 8 - 1 > ClipXMax) {
    len = (ClipXMax - x) / 8;
    ptr[len] = 0;
  }

  if (x < ClipXMin) {
    ptr += (ClipXMin - x) / 8;
    x += ClipXMin - x;
    len = strlen(ptr);
  }

  if (ptr < msgbuf + len) {
    AffString(x, y, ptr);

    TextXMin = x;
    TextXMax = x + len * 8 - 1;
    TextYMin = y;
    TextYMax = y + 7;

    BoxStaticAdd(TextXMin, TextYMin, TextXMax, TextYMax);

    if (flagflip) {
      BoxUpdate();
    }
  } else {
    TextXMin = -1;
    TextXMax = -1;
    TextYMin = -1;
    TextYMax = -1;
  }
}

// =============================================================================
#ifdef __cplusplus
}
#endif
