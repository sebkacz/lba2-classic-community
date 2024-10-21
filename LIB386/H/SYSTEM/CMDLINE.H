#pragma once

#include <SYSTEM/ADELINE_TYPES.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
extern int32_t ArgC;
extern char *ArgV[];

// -----------------------------------------------------------------------------
void RemoveParam(int32_t param);
int32_t FindAndRemoveParam(const char *str);
void GetCmdLine(int32_t argc, char *argv[]);

// =============================================================================
#ifdef __cplusplus
}
#endif
