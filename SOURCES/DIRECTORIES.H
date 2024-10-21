#pragma once

#include <SYSTEM/ADELINE_TYPES.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// --- Initialization ----------------------------------------------------------
void InitDirectories(const char *userDir, const char *resDir,
                     const char *cfgDir, const char *CDPrefix, int32_t distVersion);
void EndDirectories();

// --- Interface ---------------------------------------------------------------
void GetCurrentRunningDir(char *outDir); ///< Path where application was run
void GetDefaultUserDir(char *outDir);    ///< Path for user writable data
void GetDefaultResDir(char *outDir);     ///< Path for game resources

void GetCfgPath(char *outPath, uint16_t pathMaxSize, const char *cfgFilename);
void GetSavePath(char *outPath, uint16_t pathMaxSize, const char *saveFilename);
void GetShootPath(char *outPath, uint16_t pathMaxSize, const char *shootFilename);
void GetJinglePath(char *outPath, uint16_t pathMaxSize, const char *jingleFilename);
void GetVoicePath(char *outPath, uint16_t pathMaxSize, const char *voiceFilename,
                  bool fromCD = false);
void GetMoviePath(char *outPath, uint16_t pathMaxSize, const char *movieFilename);
void GetResPath(char *outPath, uint16_t pathMaxSize, const char *resFilename);
void GetLogPath(char *outPath, uint16_t pathMaxSize, const char *logFilename);

// =============================================================================
#ifdef __cplusplus
}
#endif
