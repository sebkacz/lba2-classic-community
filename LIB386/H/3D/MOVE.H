#pragma once

#include <SYSTEM/ADELINE_TYPES.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
#pragma pack(push, 4)
typedef struct {
  int32_t Speed;
  int32_t Acc;
  uint32_t LastTimer;
} MOVE;
#pragma pack(pop)

#pragma pack(push, 4)
typedef struct {
  MOVE Move;
  int32_t Cur;
  int32_t End;
} BOUND_MOVE;
#pragma pack(pop)

// -----------------------------------------------------------------------------
int32_t GetDeltaAccMove(int32_t *acc);
int32_t AdjustSpeedAngle(int32_t speed, int32_t start, int32_t end);
void InitMove(MOVE *pmove, int32_t speed);
void ChangeSpeedMove(MOVE *pmove, int32_t speed);
void ChangeSpeedAngleMove(MOVE *pmove, int32_t speed, int32_t start, int32_t end);
void InitAngleMove(MOVE *pmove, int32_t speed, int32_t start, int32_t end);
void ChangeSpeedBoundAngleMove(BOUND_MOVE *pbmove, int32_t speed, int32_t end);
void InitBoundMove(BOUND_MOVE *pbmove, int32_t speed, int32_t start, int32_t end);
void InitBoundAngleMove(BOUND_MOVE *pbmove, int32_t speed, int32_t start, int32_t end);
int32_t GetDeltaMove(MOVE *pmove);
int32_t GetBoundMove(BOUND_MOVE *pbmove);
int32_t GetBoundAngleMove(BOUND_MOVE *pbmove);

// -----------------------------------------------------------------------------
#define GetSpeedMove(pmove) (pmove)->Speed

#define RestartMove(pmove)                                                     \
  {                                                                            \
    (pmove)->Acc = 500;                                                        \
    (pmove)->LastTimer = TimerRefHR;                                           \
  }

// =============================================================================
#ifdef __cplusplus
}
#endif
