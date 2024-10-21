#include <SYSTEM/N_MALLOC.H>

#include <malloc.h>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
#define MALLOC_MASK (~(MALLOC_ALIGN - 1))

// -----------------------------------------------------------------------------
void *NormMalloc(uint32_t size) {
  int32_t addr, temp;

  temp = (int32_t)malloc(size + MALLOC_ALIGN);

  if (!temp) {
    return NULL;
  }

  addr = (temp + MALLOC_ALIGN) & MALLOC_MASK;

  *((int8_t *)addr - 2) = 0;
  *((int8_t *)addr - 1) = (int8_t)(addr - temp);

  return (void *)addr;
}

void NormFree(void *addr) {
  addr = (void *)((int32_t)addr - *((int8_t *)addr - 1));
  free(addr);
}

void *NormMshrink(void *addr, uint32_t size) {
  // There is no portable equivalent to '_expand' without changing
  //   code that uses this function, making it fail is valid according to
  //   the "contract" of the function
  return NULL;
}

// =============================================================================
#ifdef __cplusplus
}
#endif
