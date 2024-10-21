#pragma once

#include <SYSTEM/ADELINE_TYPES.H>
#include <cstdint>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
enum ESeekOrigin {
  SEEK_FROM_START,
  SEEK_FROM_CURRENT,
  SEEK_FROM_END
};

// -----------------------------------------------------------------------------
int32_t OpenRead(const char *filename);
int32_t OpenWrite(const char *filename);
int32_t OpenReadWrite(const char *filename);
int32_t Close(int32_t handle);

int32_t Read(int32_t handle, void* buffer, uint32_t maxReadBytes);
int32_t Write(int32_t handle, const void* buffer, uint32_t maxWriteBytes);
int32_t Seek(int32_t handle, int32_t offset, ESeekOrigin origin);

uint32_t Delete(const char* filename);
int32_t Touch(const char* filename);
uint32_t FileSize(const char* filename);

/// Check if file or directory \p path exists.
bool ExistsFileOrDir(const char* path);
bool IsDirectory(const char* path);

// =============================================================================
#ifdef __cplusplus
}
#endif
