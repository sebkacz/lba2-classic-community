//──────────────────────────────────────────────────────────────────────────
#include	<SYSTEM/ADELINE.H>
#include	<SYSTEM/HQMEM.H>
#include	<SYSTEM/HQFILE.H>
#include	<SYSTEM/HQRMLOAD.H>

//──────────────────────────────────────────────────────────────────────────
int32_t	HQRM_Load(char *name, int32_t index, void **handle)
{
	uint32_t	size	;

	size = HQF_Init(name, index)	;
	if(!size)
	{
		return FALSE		;
	}

	if(!HQM_Alloc(size, handle))	// il y a deja 500 de plus
	{
		HQF_Close()		;
		return FALSE		;
	}

	if(!HQF_LoadClose(*handle))
	{
		HQM_Free(*handle)	;
		return FALSE		;
	}

	return TRUE			;
}

//──────────────────────────────────────────────────────────────────────────
