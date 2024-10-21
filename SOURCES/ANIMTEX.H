#ifndef	ANIMTEX_H
#define	ANIMTEX_H

/*--------------------------------------------------------------------------*/
//				fonctions ASM

#include <cstdint>
#ifdef __cplusplus
extern "C" {
#endif
/*--------------------------------------------------------------------------*/
extern	void	Do_Plasma( uint8_t *PtrEffectStruct ) ;

/*--------------------------------------------------------------------------*/
extern	void	Do_Fire( uint8_t *buff1, uint8_t *buff2, uint8_t *colortable, uint8_t *TileMap ) ;

/*--------------------------------------------------------------------------*/
#ifdef __cplusplus
}
#endif

/*--------------------------------------------------------------------------*/
//				fonctions C (ANIMTEX.CPP)

extern	int32_t     	NbTexEffects ;

/*--------------------------------------------------------------------------*/
extern	void	ScanTextureAnimation( uint8_t *ptrtex, int32_t nbscanlines ) ;
/*--------------------------------------------------------------------------*/
extern	void	InitTextureAnimation( void ) ;
/*--------------------------------------------------------------------------*/
extern	void	DoTextureAnimation() ;
/*--------------------------------------------------------------------------*/
extern	void	InitPlasmaMenu() ;
/*--------------------------------------------------------------------------*/
extern	void	SelectPlasmaBank( uint8_t bank ) ;
/*--------------------------------------------------------------------------*/
extern	void	ClearPlasmaMenu( void ) ;
/*--------------------------------------------------------------------------*/
extern	void	FixePlasmaPtrMap( void ) ;
/*--------------------------------------------------------------------------*/

#endif	// ANIMTEX_H
