#ifndef	LBA_GAME

#ifndef	SELECT_H
#define	SELECT_H

/*--------------------------------------------------------------------------*/
extern void BigLine(int32_t x0,int32_t y0,int32_t x1,int32_t y1,int32_t coul);
/*--------------------------------------------------------------------------*/
extern void DrawColFeuille3D(int32_t x0,int32_t z0,int32_t x1,int32_t z1,int32_t x2,int32_t z2,int32_t x3,int32_t z3,int32_t type,int32_t color,int32_t col0,int32_t col1);
/*--------------------------------------------------------------------------*/
extern void DrawFeuille3D(int32_t x1,int32_t z1,int32_t x2,int32_t z2,int32_t x3,int32_t z3,int32_t x4,int32_t z4,int32_t type,int32_t color,int32_t bigline);
/*--------------------------------------------------------------------------*/
extern int32_t TestCroise(int32_t xA,int32_t yA,int32_t xB,int32_t yB,int32_t xC,int32_t yC,int32_t xD,int32_t yD);
/*--------------------------------------------------------------------------*/
extern int32_t SelectPoly(int32_t x,int32_t y);
/*--------------------------------------------------------------------------*/

#endif	// SELECT_H

#endif
