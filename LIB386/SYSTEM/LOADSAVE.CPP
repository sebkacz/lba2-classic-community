//──────────────────────────────────────────────────────────────────────────
#include <SYSTEM/LOADSAVE.H>

#include <SYSTEM/ADELINE.H>
#include <SYSTEM/FILES.H>
#include <SYSTEM/LOGPRINT.H>

#include <stdlib.h>
#include <limits.h>

//──────────────────────────────────────────────────────────────────────────
uint32_t	Load( char *name, void *buffer )
{
	int32_t	handle	;
	uint32_t	size	;

	size = FileSize(name)		;
	if (!size)	return 0	;

	handle = OpenRead(name)		;
	if (handle)
	{
		size = Read(handle, buffer, size) 	;
		Close(handle)				;
		return size				;
	}
	return 0;
}
//──────────────────────────────────────────────────────────────────────────
int32_t	LoadSize( char *name, void *buffer, int32_t size )
{
	int32_t	handle				;
	int32_t	maxsize, sizeread, sizetoread	;

	maxsize = FileSize( name )	;
	if ( !maxsize )	return(0)	;

	handle = OpenRead( name )	;
	if ( handle )
	{
		sizetoread = ade_min(maxsize, size)		;
		sizeread = Read( handle, buffer, sizetoread )	;
		Close( handle )					;
		if(sizeread < sizetoread)
		{
			if(sizeread < maxsize)
			{
				// error reading
				sizeread = LONG_MIN		;
			}
		}
		else
		{
			if(maxsize > size)
			{
				// file too large by...
				sizeread -= maxsize		;
			}
		}
		return( sizeread )				;
	}
	return( 0 )	;
}
//──────────────────────────────────────────────────────────────────────────
uint32_t	Save( char *name, void *buffer, uint32_t size )
{
	int32_t	handle		;
	uint32_t	written = 0	;

	handle = OpenWrite( name )	;
	if( handle )
	{
		written = Write( handle, buffer, size )	;
		Close( handle )				;
	}
	else
	{
		LogPrintf("Warning: Unable to save game to file '%s'\n", name);
	}

	return( written == size )	;
}

//──────────────────────────────────────────────────────────────────────────

