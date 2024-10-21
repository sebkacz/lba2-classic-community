#pragma once

#include <SYSTEM/ADELINE_TYPES.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
#define TABKEYS_NUM_KEYS (256 + (16 * 8))

// --- Public state ------------------------------------------------------------
extern int32_t AsciiMode;
extern int32_t Key;
extern uint8_t  TabKeys[TABKEYS_NUM_KEYS]; ///< Keyboard and Joysticks state

// --- Initialization ----------------------------------------------------------
void InitKeyboard();
void EndKeyboard();

// --- Interface ---------------------------------------------------------------
int32_t GetAscii();
int32_t CheckKey(uint32_t key);
void GetKeyScancodeName(char *string, uint8_t strMaxLen, uint32_t scanCode);

void ManageKeyboard();
void HandleEventsKeyboard(const void *event);

// =============================================================================
#ifdef __cplusplus
}
#endif
