//──────────────────────────────────────────────────────────────────────────
#ifndef	LIB_SYSTEM_HQ_MEM
#define LIB_SYSTEM_HQ_MEM

#include <SYSTEM/ADELINE_TYPES.H>

//──────────────────────────────────────────────────────────────────────────
#ifdef	__cplusplus
extern	"C"	{
#endif

//──────────────────────────────────────────────────────────────────────────
// Init le buffer global
extern	int32_t	HQM_Init_Memory(uint32_t size)		;

//──────────────────────────────────────────────────────────────────────────
// free le buffer global
extern	void	HQM_Clear_Memory()			;

//──────────────────────────────────────────────────────────────────────────
// alloue un bloc de memoire
extern	int32_t	HQM_Alloc(uint32_t size, void **ptr)		;

//──────────────────────────────────────────────────────────────────────────
// free tous les blocs dans le buffer global
extern	void	HQM_Free_All()				;

//──────────────────────────────────────────────────────────────────────────
// resize le dernier bloc de memoire
extern	void	HQM_Shrink_Last(void *ptr, uint32_t newsize)	;

//──────────────────────────────────────────────────────────────────────────
// libere un bloc de memoire et bouche le trou (remap les ptrs)
extern	void	HQM_Free(void *ptr)			;

//──────────────────────────────────────────────────────────────────────────
// test la cohérence du buffer global
extern	int32_t	HQM_Check()				;

//──────────────────────────────────────────────────────────────────────────
#ifdef	__cplusplus
}
#endif

//──────────────────────────────────────────────────────────────────────────
#endif//LIB_SYSTEM_HQ_MEM

//──────────────────────────────────────────────────────────────────────────
