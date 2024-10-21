#ifndef	FICHE_H
#define	FICHE_H

/*--------------------------------------------------------------------------*/
extern void ThrowMagicBall(int32_t x,int32_t y,int32_t z,int32_t alpha,int32_t beta,int32_t vitesse,uint8_t poids);
/*--------------------------------------------------------------------------*/
extern void SampleMagicBall(int32_t x,int32_t y,int32_t z);
/*--------------------------------------------------------------------------*/
extern int32_t ThrowDart(int32_t x,int32_t y,int32_t z,int32_t alpha,int32_t beta,int32_t vitesse,uint8_t poids);
/*--------------------------------------------------------------------------*/
extern void ThrowConque(T_OBJET *ptrobj,int32_t x,int32_t y,int32_t z,int16_t nb);
/*--------------------------------------------------------------------------*/
extern uint16_t  ChoiceAnimGant( void ) ;
/*--------------------------------------------------------------------------*/
extern void InitBodyZV( T_OBJET *ptrobj ) ;
/*--------------------------------------------------------------------------*/
extern void GereAnimAction(T_OBJET *ptrobj,uint8_t numobj);
/*--------------------------------------------------------------------------*/
extern int32_t  SearchAnim(uint16_t numanim,int32_t numobj);
/*--------------------------------------------------------------------------*/
extern int32_t  SearchBody(uint8_t numbody,int32_t numobj);
/*--------------------------------------------------------------------------*/

#endif	// FICHE_H
