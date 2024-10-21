#pragma once

#include <stdint.h>

//------------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

//------------------------------------------------------------------------------
typedef uint8_t  uint8_t;
typedef int8_t   int8_t;
typedef uint16_t uint16_t;
typedef int16_t  int16_t;
typedef uint32_t uint32_t;
typedef int32_t  int32_t;
typedef uint64_t uint64_t;
typedef int64_t  int64_t;
//typedef int32_t  LONG;

//------------------------------------------------------------------------------
typedef void  *PTR_VOID;
typedef uint64_t   *PTR_uint64_t;
typedef int64_t   *PTR_int64_t;
typedef uint32_t   *PTR_uint32_t;
typedef int32_t   *PTR_int32_t;
typedef uint16_t   *PTR_uint16_t;
typedef int16_t   *PTR_int16_t;
typedef uint8_t    *PTR_uint8_t;
typedef int8_t    *PTR_int8_t;

typedef void(VOID_FUNC)();
typedef VOID_FUNC *PTR_VOID_FUNC;

//------------------------------------------------------------------------------
#pragma pack(push, 1)
typedef struct STR_T_BOX {
  int16_t x0;
  int16_t y0;
  int16_t x1;
  int16_t y1;
  struct STR_T_BOX *pBoxNext;
} T_BOX;
#pragma pack(pop)

typedef void (BOX_FUNC)(T_BOX *pbox);

//------------------------------------------------------------------------------
#define AND &&
#define OR ||

#define TRUE 1
#define FALSE 0

// =============================================================================
#ifdef __cplusplus
}
#endif
