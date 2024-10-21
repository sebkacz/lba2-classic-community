#ifndef	HERCULE_H
#define	HERCULE_H

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀

#define	BASEH	0xB0000L	// Adresse de base carte Hercule
#define	ADRH(x,y)	((char *)(HTabY[y]+x*2))

// Modes de rectangles

#define	HBOX_SIMPLE	0
#define	HBOX_DOUBLE	1

typedef	struct
	{
		char sg ;	// superieur gauche
		char sd ;	// superieur droit
		char ig ;	// inferieur gauche
		char id ;	// inferieur droit
		char h  ;	// horizontal
		char v  ;	// vertical
	} HBoxStyle ;

// Attributs de couleurs

#define	HNORM	0x07
#define	HUNDER	0x01	// Souligne
#define	HINV	0x70	// Video inverse
#define	HBLIND	0x80	// Clignotant

// defines pour la capture d'ecran

#define	SIZE_LINE_MAX	(80*2+2)
#define	SIZE_SCREEN_MAX	(SIZE_LINE_MAX*25)

// Flags pour la capture d'ecran

#define PICK_ATTR	1	// Capture également les attributs des caracteres
#define	PICK_CRLF	2	// Ajoute des cr/lf à la fin de chaque ligne
				// (a utiliser generalement sans PICK_ATTR)

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀

#ifdef __cplusplus
extern "C" {
#endif

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	int32_t		HTabY[25] ;	// Adresses Y de la carte hercule

//#pragma	aux	HTabY	"*"

extern	HBoxStyle       HBStyles[] ;

extern	int32_t	HCurX ;
extern	int32_t	HCurY ;

extern	int32_t	ModeHercule ;

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	int32_t	TestHercule( void ) ;

/*#pragma	aux	TestHercule	"*"	\
		parm caller []		\
		modify exact [eax ebx]
		*/
//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀

#ifdef __cplusplus
}
#endif


/*══════════════════════════════════════════════════════════════════════════*
	    ██████┐ ██┐ ██┐ ██████┐ ██████┐ ██┐ ██┐ ██████┐ ██████┐
	    ██┌───┘ ██│ ██│ ██┌─██│ └─██┌─┘ ███┐██│ ██┌───┘ ██┌───┘
	    ██│     ██████│ ██████│   ██│   ██████│ █████┐  ██████┐
	    ██│     ██┌─██│ ██┌─██│   ██│   ██┌███│ ██┌──┘  └───██│
	    ██████┐ ██│ ██│ ██│ ██│ ██████┐ ██│└██│ ██████┐ ██████│
	    └─────┘ └─┘ └─┘ └─┘ └─┘ └─────┘ └─┘ └─┘ └─────┘ └─────┘
 *══════════════════════════════════════════════════════════════════════════*/

// ATTENTION: Toutes ces Fonctions ne sont pas clippées, donc méfie !

// 0<x<79
// 0<y<24

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀

#ifdef __cplusplus
extern "C" {
#endif

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
void	HCls( void ) ;


//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
void	HPrintCar( int32_t x, int32_t y, char car ) ;


//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
void	HPrintCarC( int32_t x, int32_t y, uint8_t attr, char car ) ;


//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	void	HString( int32_t x, int32_t y, char *string ) ;


//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	void	HStringC( int32_t x, int32_t y, uint8_t attr, char *string ) ;


//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	void	HScrollUp( void ) ;


//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	void	HScrollDown( void ) ;


//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
#ifdef __cplusplus
}
#endif

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	void 	HCentre( int32_t y, char *texte ) ;
//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	void 	HCentreC( int32_t y, uint8_t attr, char *texte ) ;
//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	void	HStringf( int32_t x, int32_t y, char *format, ... ) ;
//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	void	HStringfC( int32_t x, int32_t y, uint8_t attr, char *format, ... ) ;
//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	void	HPrintf( char *format, ... ) ;
//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	void	HPrintfC( uint8_t attr, char *format, ... ) ;
//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	void	HGotoXY( int32_t x, int32_t y ) ;
//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀

/*══════════════════════════════════════════════════════════════════════════*
	██████┐ ██████┐ ██████┐ ██████┐ ██┐ ██┐ ██████┐ ██████┐ ██████┐
	██┌───┘ ██┌─██│ ██┌─██│ ██┌─██│ ██│ ██│ └─██┌─┘ ██┌───┘ ██┌───┘
	██│███┐ ██████│ ██████│ ██████│ ██████│   ██│   ██│     ██████┐
	██│└██│ ██┌██┌┘ ██┌─██│ ██┌───┘ ██┌─██│   ██│   ██│     └───██│
	██████│ ██│└██┐ ██│ ██│ ██│     ██│ ██│ ██████┐ ██████┐ ██████│
	└─────┘ └─┘ └─┘ └─┘ └─┘ └─┘     └─┘ └─┘ └─────┘ └─────┘ └─────┘
 *══════════════════════════════════════════════════════════════════════════*/

// ATTENTION: Toutes ces Fonctions ne sont pas clippées, donc méfie !

// 0<x<79
// 0<y<24

#ifdef __cplusplus
extern "C" {
#endif

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	void	HLineH( int32_t y, int32_t x0, int32_t x1, char car ) ;

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	void	HLineV( int32_t x, int32_t y0, int32_t y1, char car ) ;


#ifdef __cplusplus
}
#endif

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	void	HRect( int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint8_t style ) ;

#ifdef __cplusplus
extern "C" {
#endif

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	void	HColor( int32_t y, int32_t x0, int32_t x1, uint8_t attr ) ;

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	void	HColorBox( int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint8_t attr ) ;


//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	void	HClsBox( int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint8_t attr ) ;

#ifdef __cplusplus
}
#endif

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern 	void	HBox( int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint8_t attr, uint8_t style ) ;

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀

/*══════════════════════════════════════════════════════════════════════════*
	    ██████┐ ██████┐ ██████┐ ██████┐ ██┐ ██┐ ██████┐ ██████┐
	    ██┌───┘ ██┌─██│ ██┌─██│ └─██┌─┘ ██│ ██│ ██┌─██│ ██┌───┘
	    ██│     ██████│ ██████│   ██│   ██│ ██│ ██████│ █████┐
	    ██│     ██┌─██│ ██┌───┘   ██│   ██│ ██│ ██┌██┌┘ ██┌──┘
	    ██████┐ ██│ ██│ ██│       ██│   ██████│ ██│└██┐ ██████┐
	    └─────┘ └─┘ └─┘ └─┘       └─┘   └─────┘ └─┘ └─┘ └─────┘
 *══════════════════════════════════════════════════════════════════════════*/

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	void	CaptureHerculeScreen( char *filename, uint32_t flags ) ;

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀

#endif	// HERCULE_H
