#include	<system/adeline.h>
#include	<system/logprint.h>

#ifdef	_WIN32
#include	<ail/mssw.h>
#else
#include	<ail/mss.h>
#endif

#include	<ail/common.h>

#include	<system.h>

#include	<smacker/smack.h>
#include	<smacker/smacker.h>

//████████████████████████████████████████████████████████████████████████████

#define	MAX_BLOCKS	10

//████████████████████████████████████████████████████████████████████████████

#define	FLAG_LAST	1
#define	FLAG_FREE	2

//████████████████████████████████████████████████████████████████████████████

typedef	struct
	{
		uint32_t	Size	;
		uint32_t	Flags	;
		uint32_t	Dummy[2];
	}	MALLOC_BLOCK	;

typedef	struct
	{
		MALLOC_BLOCK	*Ptr	;
		uint32_t		Size	;
	}	MEMORY_BLOCK	;

//████████████████████████████████████████████████████████████████████████████

static	MEMORY_BLOCK	Block[MAX_BLOCKS];
static	int32_t		NbBlock = 0	;

//████████████████████████████████████████████████████████████████████████████

extern HDIGDRIVER	DigDriver;	// Handle to digital audio driver

//████████████████████████████████████████████████████████████████████████████

RCFUNC void * RADLINK radmalloc(uint32_t size)
{
	MALLOC_BLOCK	*ptr		;
	MALLOC_BLOCK	*next		;
	int32_t		i, found	;
	uint32_t		left		;

	if (!size || (size==0xffffffff))	return NULL;

	found = FALSE			;
	size = (size+15)&~15		;

	for(i=0; i<NbBlock; i++)
	{
		ptr = Block[i].Ptr	;

		while(TRUE)
		{
			if((ptr->Flags&FLAG_FREE)&&(ptr->Size>=size))
			{
				found = TRUE	;
				goto end 	;
			}
			if(ptr->Flags&FLAG_LAST)
			{
				break	;
			}
			ptr = (MALLOC_BLOCK*)((uint8_t*)ptr+sizeof(MALLOC_BLOCK)+ptr->Size) ;
		}
	}
end:
	if(!found)
	{
		LogPuts("Not Enough memory for Smacker!");
		return SmartMalloc(size);
	}

	ptr->Flags &= ~FLAG_FREE	;

	left = ptr->Size-size		;

	if(left<sizeof(MALLOC_BLOCK)+16)
	{
		return	(void *)(ptr+1)	;
	}

	ptr->Size = size		;

	next = (MALLOC_BLOCK*)((uint8_t*)ptr+sizeof(MALLOC_BLOCK)+size)	;

	next->Size = left		;
	next->Flags= ptr->Flags|FLAG_FREE;
	ptr->Flags &= ~FLAG_LAST	;

	return	(void *)(ptr+1)		;
}

//████████████████████████████████████████████████████████████████████████████

RCFUNC void RADLINK radfree(void *ptr)
{
	int32_t		i, found		;
	MALLOC_BLOCK	*prev, *block, *next	;

	if (!ptr)	return	;

	found = FALSE	;

	for(i=0; i<NbBlock; i++)
	{
		prev  = NULL		;
		block = Block[i].Ptr	;

		while(TRUE)
		{
			if(block->Flags&FLAG_LAST)
			{
				next = NULL	;
			}
			else
			{
				next  = (MALLOC_BLOCK*)((uint8_t*)block+sizeof(MALLOC_BLOCK)+block->Size) ;
			}

			if(block+1==(MALLOC_BLOCK*)ptr)
			{
				found = TRUE	;
				goto end 	;
			}

			if(!next)
			{
				break	;
			}
			prev  = block	;
			block = next 	;
		}
	}
end:
	if(!found)
	{
		Free(ptr)	;
		return		;
	}

	block->Flags |= FLAG_FREE ;

	if(prev&&(prev->Flags&FLAG_FREE))
	{
		prev->Size += block->Size + sizeof(MALLOC_BLOCK);
		prev->Flags |= block->Flags;
		block = prev;
	}

	if(next&&(next->Flags&FLAG_FREE))
	{
		block->Size += next->Size + sizeof(MALLOC_BLOCK);
		block->Flags |= next->Flags;
	}
}

//████████████████████████████████████████████████████████████████████████████

void	SmackRegisterMemory(void *ptr, uint32_t size)
{
	if(NbBlock>=MAX_BLOCKS)	return	;

	Block[NbBlock].Ptr	= (MALLOC_BLOCK*)ptr	;
	Block[NbBlock].Size	= size&~15		;

	NbBlock++	;
}

//████████████████████████████████████████████████████████████████████████████

void	SmackResetMemory()
{
	int32_t	i ;

	for(i=0; i<NbBlock; i++)
	{
		Block[i].Ptr->Size = Block[i].Size-sizeof(MALLOC_BLOCK)	;
		Block[i].Ptr->Flags= FLAG_FREE|FLAG_LAST		;
	}
}

//████████████████████████████████████████████████████████████████████████████

void	InitSmacker()
{
	SmackSoundUseMSS(DigDriver);

	if(DigDriver)
	{
		LogPuts("Digital Sound Driver linked to Smacker.");
	}
	else
	{
		LogPuts("No Digital Sound Driver. Smacker will not playback soundtracks.");
	}
}

//████████████████████████████████████████████████████████████████████████████
