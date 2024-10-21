#ifndef	INCRUST_H
#define	INCRUST_H

/*--------------------------------------------------------------------------*/
extern int32_t  InitIncrustDisp(int16_t type,int16_t num,int32_t x,int32_t y,int16_t info,int16_t move,int32_t timeout);
/*--------------------------------------------------------------------------*/
extern void PosObjIncrust( T_INCRUST_DISP *ptrdisp, int32_t num ) ;
/*--------------------------------------------------------------------------*/
extern void ChangeIncrustPos(int32_t xp0,int32_t yp0,int32_t xp1,int32_t yp1);
/*--------------------------------------------------------------------------*/
extern void ClearIncrusts( int32_t type ) ;
/*--------------------------------------------------------------------------*/
extern void DrawBulle(int32_t numobj);
/*--------------------------------------------------------------------------*/

#endif	// INCRUST_H
