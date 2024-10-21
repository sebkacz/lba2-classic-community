#ifndef	EXTRA_H
#define	EXTRA_H

/*--------------------------------------------------------------------------*/
extern void InitFly(T_EXTRA *ptrextra,int32_t alpha,int32_t beta,int32_t vitesse,uint8_t poids);
/*--------------------------------------------------------------------------*/
extern void BounceExtra(T_EXTRA *ptrextra,int32_t oldx,int32_t oldy,int32_t oldz);
/*--------------------------------------------------------------------------*/
extern int32_t  ExtraBonus(int32_t x,int32_t y,int32_t z,int32_t alpha,int32_t beta,int16_t num,int16_t nb);
/*--------------------------------------------------------------------------*/
extern int32_t  ExtraLabyrinthe(int32_t x,int32_t y,int32_t z);
/*--------------------------------------------------------------------------*/
extern void MagicBallExplo(int32_t x,int32_t y,int32_t z,int32_t beta);
/*--------------------------------------------------------------------------*/
extern int32_t  SearchBonusKey(void);
/*--------------------------------------------------------------------------*/
extern int32_t  ExtraSearch(uint8_t owner,int32_t x,int32_t y,int32_t z,int16_t num,uint8_t numobj,int32_t speed,uint8_t hitforce);
/*--------------------------------------------------------------------------*/
extern int32_t  ExtraSearchKey(uint8_t owner,int32_t x,int32_t y,int32_t z,int16_t num,uint8_t numobj);
/*--------------------------------------------------------------------------*/
extern void GetExtraZV(T_EXTRA *ptrextra,int32_t *xmin,int32_t *ymin,int32_t *zmin,int32_t *xmax,int32_t *ymax,int32_t *zmax);
/*--------------------------------------------------------------------------*/
extern uint8_t   ExtraCheckObjCol(T_EXTRA *ptrextra,uint8_t owner);
/*--------------------------------------------------------------------------*/
extern uint8_t   ExtraCheckExtraCol(T_EXTRA *ptrextra,int32_t oldx, int32_t oldy, int32_t oldz,uint8_t owner);
/*--------------------------------------------------------------------------*/
extern Func_FullWorldColBrick FullWorldColBrick ;
/*--------------------------------------------------------------------------*/
extern void ClearScreenMinMax(void);
/*--------------------------------------------------------------------------*/
extern void AdjustScreenMinMax(void);
/*--------------------------------------------------------------------------*/
extern void Aff2DShape(int16_t *ptr,int32_t xs,int32_t ys,int32_t coul,int32_t angle,int32_t zoom);
/*--------------------------------------------------------------------------*/
extern void AffSpecial(int32_t numextra);
/*--------------------------------------------------------------------------*/
extern int32_t InitExtraPof( int32_t x, int32_t y, int32_t z, int16_t num, int32_t alpha, int32_t beta, int32_t speed, int32_t poids, int32_t scaledeb, int32_t scalefin, int32_t duree, int32_t rotation, int32_t timeout ) ;
/*--------------------------------------------------------------------------*/
extern int32_t InitExtraAnimSprite( uint8_t owner, int32_t x, int32_t y, int32_t z, int16_t deb, int16_t fin, int32_t tempo, int32_t scale, int32_t transparent, uint8_t hitforce ) ;
/*--------------------------------------------------------------------------*/
extern int16_t  CoulRetourBalle(T_EXTRA *ptrextra);
/*--------------------------------------------------------------------------*/
extern void ClearExtra(void);
/*--------------------------------------------------------------------------*/
extern int32_t  ThrowExtra(uint8_t owner,int32_t x,int32_t y,int32_t z,int16_t num,int32_t alpha,int32_t beta,int32_t vitesse,uint8_t poids,uint8_t hitforce);
/*--------------------------------------------------------------------------*/
extern int32_t  ThrowExtraObj(uint8_t owner,int32_t x,int32_t y,int32_t z,int32_t indexfile3d,int32_t alpha,int32_t beta,int32_t vitesse,int16_t alpharot,uint8_t poids,uint8_t hitforce);
/*--------------------------------------------------------------------------*/
extern void ThrowExtraFoudre( uint8_t owner ) ;
/*--------------------------------------------------------------------------*/
extern void InvoqueFoudre( uint8_t owner, int32_t x, int32_t y, int32_t z ) ;
/*--------------------------------------------------------------------------*/
extern void ThrowExtraProtection( uint8_t owner ) ;
/*--------------------------------------------------------------------------*/
extern void AnnuleExtraProtection( void ) ;
/*--------------------------------------------------------------------------*/
extern uint8_t   WhichBonus( int32_t flags ) ;
/*--------------------------------------------------------------------------*/
extern void GiveExtraBonus(T_OBJET *ptrobj);
/*--------------------------------------------------------------------------*/
extern void ZoneGiveExtraBonus(T_ZONE *ptrz);
/*--------------------------------------------------------------------------*/
extern int32_t  PlusProcheExtra( int32_t x, int32_t z, int32_t flags ) ;
/*--------------------------------------------------------------------------*/
// Passe par un pointeur de fonction, donc ne peut pas etre en passage par
// registres
extern Func_ReajustPosExtra ReajustPosExtra ;
/*--------------------------------------------------------------------------*/
extern void InitBackMagicBall(T_EXTRA *ptrextra,int16_t num,int32_t flags);
/*--------------------------------------------------------------------------*/
extern void GereExtras(void);
/*--------------------------------------------------------------------------*/

#endif	// EXTRA_H
