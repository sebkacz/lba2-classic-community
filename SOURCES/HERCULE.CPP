// Mettre le define LOCAL à 1 pour une utilisation hors PERSO.EXE

//#define	LOCAL	1

#ifdef	LOCAL
#include	<stdarg.h>
#include	<i86.h>
#include	<conio.h>

#include	"f:/projet/lib386/lib_sys4/lib_sys.h"
#include	"hercule.h"
#else
#include	"C_EXTERN.H"
#endif

//--------------------------------------------------------------

#define	BASEH	0xB0000L	// Adresse de base carte Hercule
#define	ADRH(x,y)	((char *)(HTabY[y]+x*2))

//--------------------------------------------------------------

int32_t	HTabY[25] =
	{
		BASEH,
		BASEH+160,
		BASEH+160*2,
		BASEH+160*3,
		BASEH+160*4,
		BASEH+160*5,
		BASEH+160*6,
		BASEH+160*7,
		BASEH+160*8,
		BASEH+160*9,
		BASEH+160*10,
		BASEH+160*11,
		BASEH+160*12,
		BASEH+160*13,
		BASEH+160*14,
		BASEH+160*15,
		BASEH+160*16,
		BASEH+160*17,
		BASEH+160*18,
		BASEH+160*19,
		BASEH+160*20,
		BASEH+160*21,
		BASEH+160*22,
		BASEH+160*23,
		BASEH+160*24
	} ;

HBoxStyle       HBStyles[] =
	{
		{ '┌', '┐', '└', '┘', '─', '│' },	// HBOX_SIMPLE
		{ '╔', '╗', '╚', '╝', '═', '║' }	// HBOX_DOUBLE
	} ;


int32_t	ModeHercule = FALSE ;

int32_t	HCurX = 0 ;
int32_t	HCurY = 0 ;

char	MsgBuf[1000] ;

/*══════════════════════════════════════════════════════════════════════════*
	    ██████┐ ██┐ ██┐ ██████┐ ██████┐ ██┐ ██┐ ██████┐ ██████┐
	    ██┌───┘ ██│ ██│ ██┌─██│ └─██┌─┘ ███┐██│ ██┌───┘ ██┌───┘
	    ██│     ██████│ ██████│   ██│   ██████│ █████┐  ██████┐
	    ██│     ██┌─██│ ██┌─██│   ██│   ██┌███│ ██┌──┘  └───██│
	    ██████┐ ██│ ██│ ██│ ██│ ██████┐ ██│└██│ ██████┐ ██████│
	    └─────┘ └─┘ └─┘ └─┘ └─┘ └─────┘ └─┘ └─┘ └─────┘ └─────┘
 *══════════════════════════════════════════════════════════════════════════*/

//--------------------------------------------------------------
void HCentre( int32_t y, char *texte )
{
	int32_t x;

	x = (80/2) - ( strlen( texte ) / 2 );

	HString( x, y, texte );
}

//--------------------------------------------------------------
void HCentreC( int32_t y, uint8_t attr, char *texte )
{
	int32_t x;

	x = (80/2) - ( strlen ( texte ) / 2 );

	HStringC( x, y, attr, texte );
}

//--------------------------------------------------------------
void	HStringf( int32_t x, int32_t y, char *format, ... )
{
	int32_t	len ;
	char	MsgBuf[256];
	va_list arglist;

	va_start( arglist, format );
	len = _vbprintf( MsgBuf, 256, format, arglist );
	va_end( arglist );
	if(len==-1)						return ;

	HString( x, y, MsgBuf ) ;
}

//--------------------------------------------------------------
void	HStringfC( int32_t x, int32_t y, uint8_t attr, char *format, ... )
{
	int32_t	len ;
	char	MsgBuf[256];
	va_list arglist;

	va_start( arglist, format );
	len = _vbprintf( MsgBuf, 256, format, arglist );
	va_end( arglist );
	if(len==-1)						return ;

	HStringC( x, y, attr, MsgBuf ) ;
}

// Affichage de texte avec gestion du curseur
//--------------------------------------------------------------

void	HPrintf( char *format, ... )
{
	int32_t	len ;
	char	*ptr ;
	va_list arglist;

	va_start( arglist, format );
	len = _vbprintf( MsgBuf, 256, format, arglist );
	va_end( arglist );
	if(len==-1)						return ;

	ptr = MsgBuf ;

	while( *ptr )
	{
		switch( *ptr )
		{
			case '\r':
				HCurX = 0 ;
				break ;

			case '\t':
				HCurX+=4 ;
				break ;

			case '\n':
				HCurX = 0 ;
				HCurY++ ;
				break ;

			default:
				HPrintCar( HCurX++, HCurY, *ptr ) ;
		}

		ptr++ ;

		if( HCurX>79 )
		{
			HCurX = 0 ;
			HCurY++   ;
		}

		if( HCurY>24 )
		{
			HCurY = 24 ;
			HScrollUp() ;
		}
	}
}

//--------------------------------------------------------------
void	HPrintfC( uint8_t attr, char *format, ... )
{
	int32_t	len ;
	char	MsgBuf[1000];
	char	*ptr ;
	va_list arglist;

	va_start( arglist, format );
	len = _vbprintf( MsgBuf, 256, format, arglist );
	va_end( arglist );
	if(len==-1)						return ;

	ptr = MsgBuf ;

	while( *ptr )
	{
		switch( *ptr )
		{
			case '\r':
				HCurX = 0 ;
				break ;

			case '\t':
				HCurX+=4 ;
				break ;

			case '\n':
				HCurX = 0 ;
				HCurY++ ;
				break ;

			default:
				HPrintCarC( HCurX++, HCurY, attr, *ptr ) ;
		}

		ptr++ ;

		if( HCurX>79 )
		{
			HCurX = 0 ;
			HCurY++   ;
		}

		if( HCurY>24 )
		{
			HCurY = 24 ;
			HScrollUp() ;
		}
	}
}

// Gestion de curseur
//--------------------------------------------------------------

void	HGotoXY( int32_t x, int32_t y )
{
	HCurX = x ;
	HCurY = y ;

	// clipping
	if( HCurX<0 )	HCurX = 0 ;
	if( HCurY<0 )	HCurY = 0 ;
	if( HCurX>79 )	HCurX = 79 ;
	if( HCurY>24 )	HCurY = 24 ;
}

/*══════════════════════════════════════════════════════════════════════════*
	██████┐ ██████┐ ██████┐ ██████┐ ██┐ ██┐ ██████┐ ██████┐ ██████┐
	██┌───┘ ██┌─██│ ██┌─██│ ██┌─██│ ██│ ██│ └─██┌─┘ ██┌───┘ ██┌───┘
	██│███┐ ██████│ ██████│ ██████│ ██████│   ██│   ██│     ██████┐
	██│└██│ ██┌██┌┘ ██┌─██│ ██┌───┘ ██┌─██│   ██│   ██│     └───██│
	██████│ ██│└██┐ ██│ ██│ ██│     ██│ ██│ ██████┐ ██████┐ ██████│
	└─────┘ └─┘ └─┘ └─┘ └─┘ └─┘     └─┘ └─┘ └─────┘ └─────┘ └─────┘
 *══════════════════════════════════════════════════════════════════════════*/

//--------------------------------------------------------------
void	HRect( int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint8_t style )
{
	HBoxStyle *ptrs = &HBStyles[style] ;

	HPrintCar( x0, y0, ptrs->sg ) ;
	HPrintCar( x1, y0, ptrs->sd ) ;
	HPrintCar( x0, y1, ptrs->ig ) ;
	HPrintCar( x1, y1, ptrs->id ) ;

	HLineH( y0, x0+1, x1-1, ptrs->h ) ;
	HLineH( y1, x0+1, x1-1, ptrs->h ) ;

	HLineV( x0, y0+1, y1-1, ptrs->v ) ;
	HLineV( x1, y0+1, y1-1, ptrs->v ) ;
}

//--------------------------------------------------------------
void	HBox( int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint8_t attr, uint8_t style )
{
	HClsBox( x0, y0, x1, y1, attr ) ;
	HRect( x0, y0, x1, y1, style ) ;
}

//--------------------------------------------------------------

/*══════════════════════════════════════════════════════════════════════════*
	    ██████┐ ██████┐ ██████┐ ██████┐ ██┐ ██┐ ██████┐ ██████┐
	    ██┌───┘ ██┌─██│ ██┌─██│ └─██┌─┘ ██│ ██│ ██┌─██│ ██┌───┘
	    ██│     ██████│ ██████│   ██│   ██│ ██│ ██████│ █████┐
	    ██│     ██┌─██│ ██┌───┘   ██│   ██│ ██│ ██┌██┌┘ ██┌──┘
	    ██████┐ ██│ ██│ ██│       ██│   ██████│ ██│└██┐ ██████┐
	    └─────┘ └─┘ └─┘ └─┘       └─┘   └─────┘ └─┘ └─┘ └─────┘
 *══════════════════════════════════════════════════════════════════════════*/

//--------------------------------------------------------------

void	CaptureHerculeScreen( char *filename, uint32_t flags )
{
	uint8_t	*ptr = (uint8_t *)BASEH ;
	uint8_t	*buf ;
	int32_t	size = 0 ;

	buf = (uint8_t *) Malloc( SIZE_SCREEN_MAX ) ;

	if( buf )
	{
		if( flags&PICK_ATTR )	// on veut l'ecran brut de pomme
		{
			size = 80*25*2 ;

			memcpy( buf, ptr, size ) ;
		}
		else
		{
			int32_t	n, t ;
			uint8_t	*ptr_buf = buf ;
			uint8_t	c ;

			// traite les 25 lignes
			for( n=0; n<25; n++ )
			{
				// traite les 80 colonnes
				// (on ne veut que les caracteres)
				for( t=0; t<80; t++, ptr+=2, ptr_buf++ )
				{
					c = *ptr ;
					if( !c )	c = ' ' ;
					*ptr_buf = c ;
				}

				if( flags&PICK_CRLF )
				{
					*ptr_buf++ = 0xD ;
					*ptr_buf++ = 0xA ;

					size += 2 ;
				}

				size += 80 ;
			}
		}

		Save( filename, buf, size ) ;
		Free( buf ) ;
	}
}
