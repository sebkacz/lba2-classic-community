#pragma once

#include <SYSTEM/ADELINE_TYPES.H>
#include <SYSTEM/LIMITS.H>
#include <SYSTEM/FASTCPY.H>
#include <cstdint>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// --- Public state ------------------------------------------------------------
extern void *Log;
extern void *Screen;
extern uint32_t ModeDesiredX; ///< X resolution for Log and Screen
extern uint32_t ModeDesiredY; ///< Y resolution for Log and Screen
extern uint32_t TabOffLine[ADELINE_MAX_Y_RES]; ///< Line offsets for Log and Screen

// --- Initialization ----------------------------------------------------------
bool InitScreen();
void EndScreen();

// --- Interface ---------------------------------------------------------------
bool CreateScreenMemory(uint32_t resX, uint32_t resY);

// -----------------------------------------------------------------------------
#define CopyScreen(src, dst) FastCopy(dst, src, ModeDesiredX *ModeDesiredY)

// =============================================================================
#ifdef __cplusplus
}
#endif
