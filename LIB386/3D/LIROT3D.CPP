#include <3D/LIROT3D.H>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
#undef LongInverseRotatePoint
extern Func_LongInverseRotatePoint *LongInverseRotatePoint;

void LongInverseRotatePoint_C(TYPE_MAT *Mat, int32_t x, int32_t y, int32_t z) {
#ifdef __MSC_VER
  __asm {
		pusha
		mov esi, Mat
		mov eax, x
		mov ebx, y
		mov ecx, z
		call LongInverseRotatePoint
		popa
  }
#elif __GNUC__
  __asm__ __volatile__("pusha\n\t"
                       "movl %0, %%esi\n\t"
                       "movl %1, %%eax\n\t"
                       "movl %2, %%ebx\n\t"
                       "movl %3, %%ecx\n\t"
                       "call *%4\n\t"
                       "popa\n\t"
                       :
                       : "m"(Mat), "m"(x), "m"(y), "m"(z),
                         "m"(LongInverseRotatePoint)
                       : "%esi", "%eax", "%ebx", "%ecx");
#else
#error "Unsupported compiler!"
#endif
}

// =============================================================================
#ifdef __cplusplus
}
#endif
