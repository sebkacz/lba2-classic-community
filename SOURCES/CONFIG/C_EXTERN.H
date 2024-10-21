#include	<dos.h>
#include	<direct.h>
#include	<ctype.h>

#include	<system.h>
#include	<svga.h>
#include	<3d.h>

#include	<fileio.h>

#include	"AddKeys.h"
#include	"Input.h"
#include	"Config.h"

#define		MAX_BOXES	200

extern	int32_t	MyKey	;
extern	uint8_t	PtrPalNormal[768+RECOVER_AREA] ;
extern	uint8_t	*PtrPal	;


extern 	void	FadePal( uint8_t r, uint8_t v, uint8_t b, uint8_t *ptrpal, int32_t percent ) ;
extern 	void	FadeToBlack( uint8_t *ptrpal ) ;
extern	void	FadeToPal( uint8_t *ptrpal ) ;
extern	void	SetBlackPal() ;

extern	void	Beep() ;


#define	FadeToBlackAndSamples	FadeToBlack
#define	FadeToPalAndSamples	FadeToPal
