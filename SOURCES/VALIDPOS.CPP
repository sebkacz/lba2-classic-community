#include 	"C_EXTERN.H"

int32_t	ValideCube		;

int32_t	ValidePos     = TRUE 	;
int32_t	LastValidePos = TRUE 	;

T_OBJET	ValideHero ;
uint32_t	SizeOfBufferValidePos	;
uint8_t	*BufferValidePos	;

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
void	SaveValidePos( void )
{
	T_OBJET	memoobj ;
	int32_t	timerrefhr = TimerRefHR ;
	T_OBJET	*ptrobj = &ListObjet[NUM_PERSO] ;

	if( ptrobj->LifePoint<=0 )	return ;

	ValideCube = NumCube  ;

	memcpy( &memoobj, ptrobj, sizeof(T_OBJET) ) ;
	memcpy( ptrobj, &ValideHero, sizeof(T_OBJET) ) ;

	PtrSave = BufferValidePos ;

	SaveContexte( timerrefhr ) ;

	SizeOfBufferValidePos = (uint32_t)(PtrSave-BufferValidePos) ;

	memcpy( ptrobj, &memoobj, sizeof(T_OBJET) ) ;

#ifdef	DEBUG_TOOLS
	if( SizeOfBufferValidePos>=SIZE_BUFFER_VALIDE_POS )
	{
		Message( "Warning: BufferValidePos trop petit (ça a dû patché) !", TRUE ) ;
	}
#endif
}

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
void	RestartValidePos( void )
{
	int32_t	flagload ;
	int32_t	savetimerrefhr ;

	PtrSave = BufferValidePos ;

	flagload = LoadContexte( &savetimerrefhr ) ;

	if( !flagload )	InitLoadedGame( ) ;
	else		LoadFile3dObjects() ;

	NewCube = -1 ;

	ChoicePalette() ;
	CameraCenter( 0 ) ;
	RestoreTimer() ;
	SetTimerHR( savetimerrefhr ) ;
	SaveTimer() ;
}
