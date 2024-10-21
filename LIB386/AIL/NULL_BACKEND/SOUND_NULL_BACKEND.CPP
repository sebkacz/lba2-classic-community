#include "AIL.H"

#include <SYSTEM/LIMITS.H>

#include <stdlib.h>

// === TIMER ===================================================================
void InitAIL() {}

// === COMMON ==================================================================
int32_t Midi_Driver_Enabled = FALSE;   // Exposed by COMMON.H and MIDI.H
int32_t Sample_Driver_Enabled = FALSE; // Exposed by COMMON.H and SAMPLE.H
int32_t SamplingRate = 22050;          // Exposed by COMMON.H and SAMPLE.H

char SampleDriverName[ADELINE_MAX_PATH] = ""; // Exposed by COMMON.H and SAMPLE.H
char MidiDriverName[ADELINE_MAX_PATH] = "";   // Exposed by COMMON.H and MIDI.H

VOID_FUNC *PauseMidiPtr = NULL;
VOID_FUNC *ResumeMidiPtr = NULL;
VOID_FUNC *PauseSamplesPtr = NULL;
VOID_FUNC *ResumeSamplesPtr = NULL;

void PauseBothMiles() {
  (*PauseSamplesPtr)();
  (*PauseMidiPtr)();
}

void ResumeBothMiles() {
  (*ResumeMidiPtr)();
  (*ResumeSamplesPtr)();
}

// === MIDI ====================================================================
int32_t Midi_Driver_Type = MIDI; // Exposed by MIDI.H

void ClearMidiDriver() { Midi_Driver_Enabled = FALSE; }
void PauseMidi() {}
void ResumeMidi() {}
void ResetMidi() {}
uint32_t PrepareMidi(void *ptrxmi, int32_t seqnum, int32_t volume) { return TRUE; }
void ClearMidi() {}
void PlayBlockMidi(int32_t blocknum) {}
void ChainBlockMidi(int32_t blocknum) {}
void ChangeVolumeMidi(int32_t volume, int32_t delay) {}
void StopChainMidi() {}
void StopMidi() {}
int32_t GetBlockPlayingMidi() { return -1; }

int32_t InitMidiDriver(char *driver_name) {
  if (Midi_Driver_Enabled) {
    return TRUE;
  }

  Midi_Driver_Type = MIDI;
  Midi_Driver_Enabled = TRUE;
  PauseMidiPtr = PauseMidi;
  ResumeMidiPtr = ResumeMidi;

  return TRUE;
}

// === SAMPLE ==================================================================
int32_t SampleOverflow = FALSE; // Exposed by SAMPLE.H
int32_t sampleVolume = 0;

void SetMasterVolumeSample(int32_t volume) { sampleVolume = volume; }
int32_t GetMasterVolumeSample() { return sampleVolume; }
int32_t FadeOutSamples(int32_t delay) { return 0; }
int32_t FadeInSamples(int32_t delay) { return delay; }
void InverseStereoSample(int32_t inverse) {}
uint32_t PlaySample(void *buffer, uint32_t userhandle, int32_t pitchbend, int32_t repeat,
               int32_t volume, int32_t pan) {
  return 0xFFFFFFFF;
}
uint32_t TimerPlaySample(void *ptrsample, uint32_t usernum, int32_t pitchbend, int32_t nbrepeat,
                    int32_t volume, int32_t pan, int32_t period) {
  return Sample_Driver_Enabled ? TRUE : FALSE;
}
void TimerStopSample() {}
void ChangePitchbendSample(uint32_t sample, int32_t pitchbend) {}
void ChangeVolumePanSample(uint32_t sample, int32_t volume, int32_t pan) {}
void *GetSampleMSSHandle(uint32_t sample);
void StopOneSample(uint32_t sample) {}
void StopSamples() {}
void PauseOneSample(uint32_t sample) {}
void ResumeOneSample(uint32_t sample) {}
void PauseSamples() {}
void ResumeSamples() {}
int32_t GetPlayingSamples(SAMPLE_PLAYING tab[], int32_t max) { return 0; }
uint32_t IsSamplePlaying(uint32_t sample) { return FALSE; }
int32_t GetSamplePosition(uint32_t sample) { return -1; }
int32_t GetSamplePoly() { return 0; }
void SetDataSample(uint32_t sample, int32_t index, int32_t value) {}
int32_t GetDataSample(uint32_t sample, int32_t index) { return 0; }

int32_t InitSampleDriver(char *driver_name) {
  if (Sample_Driver_Enabled) {
    return TRUE;
  }

  Sample_Driver_Enabled = TRUE;
  PauseSamplesPtr = PauseSamples;
  ResumeSamplesPtr = ResumeSamples;

  return TRUE;
}

// === STREAM ==================================================================
int32_t streamVolume = 0;

void OpenStream() {}
void PlayStream(char *name) {}
void ChangeVolumeStream(int32_t volume) { streamVolume = volume; }
int32_t GetVolumeStream() { return streamVolume; }
void StopStream() {}
void PauseStream() {}
void ResumeStream() {}
int32_t IsStreamPlaying() { return FALSE; }
char *StreamName() { return ""; }

// === CD ======================================================================
const char* OpenCD(char *volume_name) { return "D"; }
void CloseCD() {}
void PlayCD(int32_t track) {}
void ChangeVolumeCD(int32_t volume) {}
int32_t GetVolumeCD() { return 0; }
void StopCD() {}
void PauseCD() {}
void ResumeCD() {}
int32_t IsCDPlaying() { return FALSE; }

// =============================================================================
