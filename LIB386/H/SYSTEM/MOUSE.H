#pragma once

#include <SYSTEM/ADELINE_TYPES.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// --- Public state ------------------------------------------------------------
extern bool FlagMouse;      ///< Display mouse if true
extern volatile int32_t Click;  ///< Mouse button click flags. Left = 1; Right = 2
extern volatile uint32_t MouseX; ///< Mouse X position relative to window
extern volatile uint32_t MouseY; ///< Mouse Y position relative to window
extern int32_t MouseXDep;       ///< Mouse relative motion in the X axis
extern int32_t MouseYDep;       ///< Mouse relative motion in the Y axis

extern int32_t MouseSpriteGraphicNum;      ///< Id of graphic for mouse cursor
extern const void *MouseSpriteGraphic; ///< Memory of graphic for mouse cursor

// --- Initialization ----------------------------------------------------------
void InitMouse();
void EndMouse();

// --- Interface ---------------------------------------------------------------
void ShowMouse(bool show);
void SetMousePos(uint32_t x, uint32_t y);
void SetMouseBox(uint32_t x0, uint32_t y0, uint32_t x1, uint32_t y1); ///< Set mouse position limits
void ClearMouseBox(); ///< Reset mouse position limits to screen size

void ManageMouse();
void HandleEventsMouse(const void *event);

// =============================================================================
#ifdef __cplusplus
}
#endif
