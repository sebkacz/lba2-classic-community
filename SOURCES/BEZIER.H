#ifndef	BEZIER_H
#define	BEZIER_H

#define ALTITUDE_MAX	200

#define FTOW(x) (int16_t)(((x)+32767) >> 16)
#define WTOF(x) (int32_t)((int32_t)(x) << 16)

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
typedef	int32_t	(Func_ProjectShadow)( T_SORT *,int32_t ) ;

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀


extern	int32_t	XS0,YS0,XS1,YS1,XS2,YS2,XS3,YS3 ;
extern	int32_t	ShadowTestObject ;

/*--------------------------------------------------------------------------*/
void 	CalculeLigneOmbre( int32_t x1, int32_t y1, int32_t x2, int32_t y2 ) ;
/*--------------------------------------------------------------------------*/
void	DrawOmbre(int32_t x0,int32_t y0,int32_t x1,int32_t y1,int32_t x2,int32_t y2,int32_t x3,int32_t y3) ;
/*--------------------------------------------------------------------------*/
void	DrawLineShade(	int32_t x0, int32_t z0, int32_t x1, int32_t z1, int32_t x2, int32_t z2, int32_t x3, int32_t z3 ) ;
/*--------------------------------------------------------------------------*/
int32_t	TestZVDecorsXZFull( int32_t xw, int32_t zw, int32_t y0, int32_t y1, T_DECORS *objet ) ;
/*--------------------------------------------------------------------------*/
int32_t	TestZVObjectsXZFull( int32_t xw, int32_t zw, int32_t y0, int32_t y1, T_OBJET *objet ) ;
/*--------------------------------------------------------------------------*/
int32_t	AdjustShadowDecors( int32_t xw, int32_t zw, int32_t y0, int32_t y1 ) ;
/*--------------------------------------------------------------------------*/
int32_t	AdjustShadowObjects( int32_t xw, int32_t zw, int32_t y0, int32_t y1 ) ;
/*--------------------------------------------------------------------------*/
extern	Func_ProjectShadow	ProjectShadowExt ;
/*--------------------------------------------------------------------------*/
void	DrawShadow( void ) ;
/*--------------------------------------------------------------------------*/

#endif	// BEZIER_H
