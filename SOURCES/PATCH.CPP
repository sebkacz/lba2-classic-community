#include 	"C_EXTERN.H"

/*══════════════════════════════════════════════════════════════════════════*
		   █▀▀▀█ █▀▀▀█ ▀▀█▀▀ █▀▀▀▀ █   █ █▀▀▀▀ ██▀▀▀
		   ██▀▀▀ ██▀▀█   ██  ██    ██▀▀█ ██▀▀  ▀▀▀▀█
		   ▀▀    ▀▀  ▀   ▀▀  ▀▀▀▀▀ ▀▀  ▀ ▀▀▀▀▀ ▀▀▀▀▀
 *══════════════════════════════════════════════════════════════════════════*/
/*──────────────────────────────────────────────────────────────────────────*/

extern	uint8_t	*PtrCompil 	;	// COMPIL.CPP
extern	uint8_t	*PtrSce 	;	// DISKFUNC.CPP

#ifdef	COMPILATOR
int32_t	MaxPatches = 0 ;
T_PATCH	ListPatches[MAX_PATCHES] ;
#else
T_PATCH *ListPatches ;
#endif

int32_t	NbPatches = 0 ;

#ifdef	COMPILATOR
//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
void	AddPatch( int16_t size, int16_t offset )
{
	T_PATCH *ptrpatch ;

	if( NbPatches>=MAX_PATCHES )
	{
		Message( "Warning: ListPatches trop petit ...", TRUE ) ;
		return ;
	}

	ptrpatch = &ListPatches[NbPatches++] ;

	ptrpatch->Size   = size		;
	ptrpatch->Offset = (int16_t)((PtrSce-StartPtrSce)+(PtrCompil-(uint8_t*)Screen)+offset) ;
}
#endif	// COMPILATOR
