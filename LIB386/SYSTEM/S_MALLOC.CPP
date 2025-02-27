#include <SYSTEM/S_MALLOC.H>

#include <SYSTEM/LOGPRINT.H>
#include <SYSTEM/N_MALLOC.H>

#include <stdlib.h>
#include <string.h>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// --- Private state -----------------------------------------------------------
static char MallocErrorString[256];
static char MallocErrorFile[260];
static uint32_t MallocErrorLine;

// --- Private functions -------------------------------------------------------
void SafeErrorMalloc(const char *msg, char *file, uint32_t line) {
  strcpy(MallocErrorString, msg);
  strcpy(MallocErrorFile, file);
  MallocErrorLine = line;
  exit(1);
}

void CheckPtr(void *ptr, char *file, uint32_t line) {
  if ((int32_t)ptr & (MALLOC_ALIGN - 1)) {
  error:
    SafeErrorMalloc("Trying to Free or Mshrink a block not allocated with "
                    "Malloc/SMartMalloc/DosMalloc",
                    file, line);
    return;
  }
  switch (*((uint8_t *)ptr - 2)) {
  case 0:
    if (*((uint8_t *)ptr - 1) > MALLOC_ALIGN) {
      goto error;
    }
    break;
  default:
    goto error;
  }
}

// -----------------------------------------------------------------------------
void SafeErrorMallocMsg() {
  if (MallocErrorString[0]) {
    LogPrintf("\nMalloc Error: %s in %s at line %d\n", MallocErrorString,
              MallocErrorFile, MallocErrorLine);
  }
}

void SafeFree(void *ptr, char *file, uint32_t line) {
  if (!ptr) {
    SafeErrorMalloc("Trying to Free a NULL ptr", file, line);
  }

  CheckPtr(ptr, file, line); // check if valid block

  NormFree(ptr);
}

void *SafeMshrink(void *ptr, uint32_t taille, char *file, uint32_t line) {
  if (!ptr) {
    SafeErrorMalloc("Trying to Mshrink a NULL ptr", file, line);
  }

  CheckPtr(ptr, file, line); // check if valid block

  ptr = NormMshrink(ptr, taille);

  return ptr;
}

// =============================================================================
#ifdef __cplusplus
}
#endif
