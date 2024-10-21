#include	<SYSTEM/LOADMALL.H>

#include	<SYSTEM/FILES.H>
#include	<SYSTEM/N_MALLOC.H>

#include <stddef.h>

//──────────────────────────────────────────────────────────────────────────
uint32_t	LoadMallocFileSize ;

//──────────────────────────────────────────────────────────────────────────
void	*LoadMalloc(char *name)
{
	int32_t	handle	;
	uint32_t	size	;
	void	*ptr	;

	LoadMallocFileSize = FileSize( name )		;
	if ( !LoadMallocFileSize )	goto Error3	;

	ptr = NormMalloc( LoadMallocFileSize );
	if ( !ptr )
	{
		goto Error2		;
	}

	handle = OpenRead( name )	;
	if ( !handle)
	{
		goto Error1		;
	}

	size = Read( handle, ptr, LoadMallocFileSize );
	Close( handle )			;

	if ( size != LoadMallocFileSize )
	{
Error1:		NormFree(ptr)		;
Error2:		LoadMallocFileSize = 0	;
Error3:		ptr = NULL		;
	}

	return ptr 			;
}

//──────────────────────────────────────────────────────────────────────────
