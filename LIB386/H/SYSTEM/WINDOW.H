#pragma once

#include <SYSTEM/ADELINE_TYPES.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// --- Public state ------------------------------------------------------------
extern bool AppActive; ///< Application running and in focus status

// --- Initialization ----------------------------------------------------------
bool InitWindow(const char *title);
void EndWindow();
bool IsWindowInitialized();

// --- Interface ---------------------------------------------------------------
bool CreateWindowSurface(uint32_t resX, uint32_t resY);
void *WindowSurface();
void DestroyWindowSurface();
void UpdateWindowSurface();
void UpdateWindowSurfaceArea(const T_BOX area[], uint32_t areaCount);

void ManageWindow();
void HandleEventsWindow(const void *event);

// =============================================================================
#ifdef __cplusplus
}
#endif
