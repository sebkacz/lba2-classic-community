//──────────────────────────────────────────────────────────────────────────
#include	<SYSTEM/ADELINE.H>
#include	<SYSTEM/LZ.H>
#include	<SYSTEM/HQRRESS.H>
#include	<SYSTEM/HQRMEM.H>

#include 	<string.h>

//──────────────────────────────────────────────────────────────────────────
// retourne un pointeur sur un bloc demande(index) d'un hqr chargé en mémoire
COMPRESSED_HEADER *GetPtrBlockMemoryHQR(void *ptrhqr, int32_t index)
{
	uint32_t		seekindex 	;

	index	*= 4			;

	// si num bloc demande > num bloc dans hqr exit
	if( index >= *(uint32_t*)ptrhqr )
	{
		return NULL 		;
	}

	// recupere offset bloc
	seekindex	= *(uint32_t*)((uint8_t*)ptrhqr + index)	;

	// saute header
	return	(COMPRESSED_HEADER*)((uint8_t*)ptrhqr + seekindex + sizeof(T_HQR_HEADER));
}

//──────────────────────────────────────────────────────────────────────────
// decompresse un bloc d'un hqr charge en mémoire
// retourne:	taille du bloc(decompressé) si Ok
//		0 si bloc_demande>bloc existant
uint32_t	LoadMemoryHQR( void *ptrhqr, void *ptrdest, int32_t index )
{
	COMPRESSED_HEADER	*header	;

	header	= GetPtrBlockMemoryHQR(ptrhqr, index);

	if(!header)
	{
		return	NULL	;
	}

	switch( header->CompressMethod )
	{
		case 0: 	// Stored
			memmove(ptrdest, (void*)(header+1), header->SizeFile) ;
			break 	;

		case 1:
		case 2: 	// LZSS/LZMIT
			ExpandLZ(ptrdest, (void*)(header+1), header->SizeFile, header->CompressMethod+1) ;
			break 	;

	}
	return header->SizeFile	;
}

//──────────────────────────────────────────────────────────────────────────

