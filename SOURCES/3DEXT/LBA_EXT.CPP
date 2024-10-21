#include "LBA_EXT.H"

#include <SYSTEM/ADELINE.H>

int32_t Min3(int32_t a, int32_t b, int32_t c) {
  int32_t tmp = ade_min(a, b);
  return ade_min(tmp, c);
}

int32_t Max3(int32_t a, int32_t b, int32_t c) {
  int32_t tmp = ade_max(a, b);
  return ade_max(tmp, c);
}
