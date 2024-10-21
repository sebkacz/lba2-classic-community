#include <POLYGON/POLY.H>

#include <limits.h>

// -----------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

// -----------------------------------------------------------------------------
int32_t INV64(int32_t a) { return LONG_MIN / a; }

#undef Fill_Poly
int32_t Fill_Poly_C(int32_t Type_Poly, int32_t Color_Poly, int32_t Nb_Points,
                Struc_Point *Ptr_Points) {
  int32_t returnValue;

#ifdef __MSC_VER
  __asm {
		pusha
		mov eax, Type_Poly
		mov ebx, Color_Poly
		mov ecx, Nb_Points
		mov esi, Ptr_Points
		call Fill_PolyMMX
		mov returnValue, eax
		popa
  }
#elif __GNUC__
  FUNC_FILL_POLY *fn = &Fill_PolyFast;

  __asm__ __volatile__("pusha\n\t"
                       "mov %1, %%eax\n\t"
                       "mov %2, %%ebx\n\t"
                       "mov %3, %%ecx\n\t"
                       "mov %4, %%esi\n\t"
                       "call *%5\n\t"
                       "mov %%eax, %0\n\t"
                       "popa\n\t"
                       : "=m"(returnValue)
                       : "m"(Type_Poly), "m"(Color_Poly), "m"(Nb_Points),
                         "m"(Ptr_Points), "m"(fn)
                       : "%eax", "%ebx", "%ecx", "%esi");
#else
#error "Unsupported compiler!"
#endif

  return returnValue;
}

void Switch_Fillers_C(uint32_t Bank) {
#ifdef __MSC_VER
  __asm {
		pusha
		mov eax, Bank
		call Switch_Fillers_ASM
		popa
  }
#elif __GNUC__
  typedef void(FUNC_SWITCH_FILLERS)(uint32_t);
  FUNC_SWITCH_FILLERS *fn = &Switch_Fillers_ASM;

  __asm__ __volatile__("pusha\n\t"
                       "movl %0, %%eax\n\t"
                       "call *%1\n\t"
                       "popa\n\t"
                       :
                       : "m"(Bank), "m"(fn)
                       : "%eax");
#else
#error "Unsupported compiler!"
#endif
}

// =============================================================================
#ifdef __cplusplus
}
#endif
