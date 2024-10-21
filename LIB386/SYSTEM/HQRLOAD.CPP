/*──────────────────────────────────────────────────────────────────────────*/
#include	<SYSTEM/ADELINE.H>
#include	<SYSTEM/N_MALLOC.H>
#include	<SYSTEM/LOADMALL.H>
#include	<SYSTEM/LZ.H>
#include	<SYSTEM/HQFILE.H>
#include	<SYSTEM/HQRLOAD.H>

#include <stddef.h>

//──────────────────────────────────────────────────────────────────────────
// alloue la memoire necessaire
// et charge une fiche(index) d'une ressource .HQR
void	*LoadMalloc_HQR(const char *name, int32_t index)
{
	void	*ptr	;

	LoadMallocFileSize = HQF_Init(name, index);
	if(!LoadMallocFileSize)
	{
		return NULL		;
	}

	ptr = Malloc(LoadMallocFileSize+RECOVER_AREA);
	if( !ptr )
	{
		HQF_Close()		;
		LoadMallocFileSize = 0	;
		return NULL		;
	}

	LoadMallocFileSize = HQF_LoadClose(ptr);
	if(!LoadMallocFileSize)
	{
		Free(ptr)		;
		return NULL		;
	}

	Mshrink(ptr, LoadMallocFileSize);

	return ptr 			;
}

//──────────────────────────────────────────────────────────────────────────
// charge une fiche(index) à l'adresse voulue (ptrdest) depuis une ressource
uint32_t	Load_HQR(const char *name, void *ptr, int32_t index)
{
	HQF_Init(name, index)		;
	return HQF_LoadClose(ptr)	;
}

//──────────────────────────────────────────────────────────────────────────
