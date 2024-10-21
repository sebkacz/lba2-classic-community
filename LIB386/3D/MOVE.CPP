#include <3D/MOVE.H>
#include <SYSTEM/TIMER.H>

#include <stdlib.h>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
void ChangeSpeedMove(MOVE *pmove, int32_t speed) {
  uint32_t timer, delta;

  timer = TimerRefHR;

  delta = timer - pmove->LastTimer;

  if (delta | pmove->Speed) {
    pmove->Acc += (timer - pmove->LastTimer) * pmove->Speed;
    pmove->LastTimer = timer;
  }

  pmove->Speed = speed;
}

void InitMove(MOVE *pmove, int32_t speed) {
  RestartMove(pmove);
  pmove->Speed = speed;
}

void ChangeSpeedAngleMove(MOVE *pmove, int32_t speed, int32_t start, int32_t end) {
  ChangeSpeedMove(pmove, AdjustSpeedAngle(speed, start, end));
}

void InitAngleMove(MOVE *pmove, int32_t speed, int32_t start, int32_t end) {
  InitMove(pmove, AdjustSpeedAngle(speed, start, end));
}

void ChangeSpeedBoundAngleMove(BOUND_MOVE *pbmove, int32_t speed, int32_t end) {
  ChangeSpeedMove(&(pbmove->Move), AdjustSpeedAngle(speed, pbmove->Cur, end));
  pbmove->End = end & 4095;
}

void InitBoundAngleMove(BOUND_MOVE *pbmove, int32_t speed, int32_t start, int32_t end) {
  InitAngleMove(&(pbmove->Move), speed, start, end);
  pbmove->Cur = start & 4095;
  pbmove->End = end & 4095;
}

void InitBoundMove(BOUND_MOVE *pbmove, int32_t speed, int32_t start, int32_t end) {
  if (start == end) {
    speed = 0;
  } else if (start > end) {
    speed = -speed;
  }

  InitMove(&(pbmove->Move), speed);

  pbmove->Cur = start;
  pbmove->End = end;
}

int32_t GetDeltaMove(MOVE *pmove) {
  uint32_t timer, delta;

  timer = TimerRefHR;

  delta = timer - pmove->LastTimer;

  if (delta | pmove->Speed) {
    pmove->Acc += (timer - pmove->LastTimer) * pmove->Speed;
    pmove->LastTimer = timer;
    return GetDeltaAccMove(&(pmove->Acc));
  } else {
    return 0;
  }
}

int32_t GetBoundMove(BOUND_MOVE *pbmove) {
  int32_t temp, cur;

  temp = GetDeltaMove(&(pbmove->Move));
  cur = pbmove->Cur;

  if (temp) {
    int32_t end;

    end = pbmove->End;

    cur += temp;

    if (pbmove->Move.Speed > 0) {
      if (cur >= end) {
        goto over;
      }
    } else {
      if (cur <= end) {
      over:
        cur = end;
        pbmove->Move.Speed = 0;
      }
    }

    pbmove->Cur = cur;
  }

  return cur;
}

int32_t GetBoundAngleMove(BOUND_MOVE *pbmove) {
  int32_t temp, cur;

  temp = GetDeltaMove(&(pbmove->Move));
  cur = pbmove->Cur;

  if (temp) {
    int32_t end;

    end = pbmove->End;

    if (pbmove->Move.Speed > 0) {
      if (cur > end) {
        end += 4096;
      }

      cur += temp;

      if (cur >= end) {
        goto over;
      }
    } else {
      if (cur < end) {
        end -= 4096;
      }

      cur += temp;

      if (cur <= end) {
      over:
        cur = end;
        pbmove->Move.Speed = 0;
      }
    }

    cur &= 4095;
    pbmove->Cur = cur;
  }

  return cur;
}

int32_t AdjustSpeedAngle(int32_t speed, int32_t start, int32_t end) {
  int32_t diff = (end & 4095) - (start & 4095);
  if (diff == 0) {
    return 0;
  }

  if (diff < 0) {
    diff = -diff;
    speed = -speed;
  }

  return (diff < 2048) ? speed : -speed;
}

int32_t GetDeltaAccMove(int32_t *acc) {
  if (*acc >= 1000 || *acc <= -1000) {
    ldiv_t tmpDivRem = ldiv(*acc, 1000);
    *acc = tmpDivRem.rem;
    return tmpDivRem.quot;
  }

  return 0;
}

// =============================================================================
#ifdef __cplusplus
}
#endif
