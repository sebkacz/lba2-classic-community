#include	"C_EXTERN.H"

int32_t	MyKey	;

uint8_t	PtrPalNormal[768+RECOVER_AREA] ;
uint8_t	*PtrPal	;

#define	BCL_FADE	50

//──────────────────────────────────────────────────────────────────────────
void	FadePal( uint8_t r, uint8_t v, uint8_t b, uint8_t *ptrpal, int32_t percent )
{
	uint8_t	workpal[768] ;
	int32_t	n ;

	for( n=0; n<256; n++ )
	{
		workpal[n*3+0] = (uint8_t)RegleTrois( r, ptrpal[n*3+0], BCL_FADE, percent ) ;
		workpal[n*3+1] = (uint8_t)RegleTrois( v, ptrpal[n*3+1], BCL_FADE, percent ) ;
		workpal[n*3+2] = (uint8_t)RegleTrois( b, ptrpal[n*3+2], BCL_FADE, percent ) ;
	}

	Palette( workpal ) ;
}

//──────────────────────────────────────────────────────────────────────────
void	FadeToBlack( uint8_t *ptrpal )
{
	int32_t	n ;

	SaveTimer() ;

	for( n=BCL_FADE; n>=0; n-=2 )
	{
		FadePal( 0,0,0, ptrpal, n ) ;
	}

	RestoreTimer() ;
}

//──────────────────────────────────────────────────────────────────────────
void	FadeToPal( uint8_t *ptrpal )
{
	int32_t	n ;

	SaveTimer() ;

	for( n=0; n<=BCL_FADE; n+=2 )
	{
		FadePal( 0,0,0, ptrpal, n ) ;
	}

	RestoreTimer() ;
}

//──────────────────────────────────────────────────────────────────────────
void	SetBlackPal()
{
	int32_t	n ;

	SaveTimer() ;

	for( n=0; n<256; n++ )
	{
		PalOne( n, 0,0,0 ) ;
	}

	RestoreTimer() ;
}

//──────────────────────────────────────────────────────────────────────────
void	Beep()
{
	sound(500)	;
	delay(100)	;
	nosound()	;
}

//──────────────────────────────────────────────────────────────────────────

char	*End_Error = "Ok" ;

//-------------------------------------------------------------------------
void	TheEnd( char *err )
{
	End_Error = err ;
	exit( 0 ) ;
}

//-------------------------------------------------------------------------
void	TheEndInfo( void )
{
	LogPrintf( End_Error ) ;
}

//-------------------------------------------------------------------------
void    main( int argc, char *argv[] )
{
	atexit(TheEndInfo)      ;

	#define ibuffer Screen
	#define ibuffersize     (640*480+RECOVER_AREA)
	#define inits   INIT_DEFFILE|INIT_LOG|INIT_TIMER|INIT_SVGA|INIT_KEYB
	#include <initadel.c>

	BoxInit( MAX_BOXES ) 	;

	Cls() ;

	if( !Load( "palette.pal", PtrPalNormal ) )	TheEnd( "palette.pal not found !" ) ;

	PtrPal = PtrPalNormal ;

	SetBlackPal() ;

	ReadInputConfig() 	;
	MenuConfig() 		;
	WriteInputConfig() 	;
}
