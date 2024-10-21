#include <SYSTEM/FILES.H>

#include <assert.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <utime.h>
#include <unistd.h>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// --- Private definitions -----------------------------------------------------
#ifndef _WIN32 // Portability - O_BINARY exists only on Windows platform
#define O_BINARY 0
#endif // _WIN32

#define MODE_READ  (O_RDONLY | O_BINARY)
#define MODE_WRITE (O_WRONLY | O_BINARY | O_CREAT | O_TRUNC)
#define MODE_RW    (O_RDWR   | O_BINARY | O_CREAT)

// --- Private functions -------------------------------------------------------
int32_t OpenMode(const char *filename, int mode) {
  assert(filename != NULL);
  int32_t handle = open(filename, mode, (S_IRUSR | S_IWUSR));
  return (handle == -1) ? 0 : handle;
}

// --- Public functions --------------------------------------------------------
int32_t OpenRead(const char *filename) { return OpenMode(filename, MODE_READ); }
int32_t OpenWrite(const char *filename) { return OpenMode(filename, MODE_WRITE); }
int32_t OpenReadWrite(const char *filename) { return OpenMode(filename, MODE_RW); }

int32_t Close(int32_t handle) {
  assert(handle > 0);
  return close(handle);
}

int32_t Read(int32_t handle, void *buffer, uint32_t maxReadBytes) {
  assert(handle > 0);
  assert(buffer != NULL);
  return read(handle, buffer, maxReadBytes);
}

int32_t Write(int32_t handle, const void *buffer, uint32_t maxWriteBytes) {
  assert(handle > 0);
  assert(buffer != NULL);
  return write(handle, buffer, maxWriteBytes);
}

int32_t Seek(int32_t handle, int32_t offset, ESeekOrigin origin) {
  assert(handle > 0);

  int stdOrigin;
  switch (origin) {
  case SEEK_FROM_START:
    stdOrigin = SEEK_SET;
    break;
  case SEEK_FROM_CURRENT:
    stdOrigin = SEEK_CUR;
    break;
  case SEEK_FROM_END:
    stdOrigin = SEEK_END;
    break;
  default:
    assert(false);
    break;
  }

  return lseek(handle, offset, stdOrigin);
}

uint32_t Delete(const char *filename) {
  assert(filename != NULL);
  int32_t result = unlink(filename);
  return (result != -1);
}

int32_t Touch(const char *filename) {
  assert(filename != NULL);
  return utime(filename, NULL);
}

uint32_t FileSize(const char *filename) {
  assert(filename != NULL);

  int32_t handle = OpenRead(filename);
  if (!handle) {
    return 0;
  }

  int32_t fsize = lseek(handle, 0, SEEK_END);
  Close(handle);

  return (uint32_t)((fsize == -1) ? 0 : fsize);
}

bool ExistsFileOrDir(const char* path) {
  assert(path != NULL);

  struct stat status = {};
  return (stat(path, &status) == 0);
}

bool IsDirectory(const char* path) {
  assert(path != NULL);

  struct stat status = {};
  return ((stat(path, &status) == 0) && ((status.st_mode & S_IFMT) == S_IFDIR));
}

// =============================================================================
#ifdef __cplusplus
}
#endif
