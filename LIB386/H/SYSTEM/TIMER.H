#pragma once

#include <SYSTEM/ADELINE_TYPES.H>
#include <SYSTEM/EVENTS.H> // For ManageEvents()

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// --- Public state ------------------------------------------------------------
extern volatile uint32_t TimerSystemHR;
extern volatile uint32_t TimerRefHR;
extern volatile int32_t CmptFrame;        ///< Frame count
extern volatile int32_t NbFramePerSecond; ///< FPS - Frames per second

// --- Initialization ----------------------------------------------------------
void InitTimer();
void EndTimer();

// --- Interface ---------------------------------------------------------------
void LockTimer();
void UnlockTimer();
void SaveTimer();
void RestoreTimer();
void SetTimerHR(uint32_t time);

void ManageTime();
void HandleEventsTimer(const void *event);

// -----------------------------------------------------------------------------
#define ManageSystem() { ManageEvents(); ManageTime(); }

// =============================================================================
#ifdef __cplusplus
}
#endif
