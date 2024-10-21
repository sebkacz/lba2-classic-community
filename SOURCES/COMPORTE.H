#ifndef	COMPORTE_H
#define	COMPORTE_H

/*--------------------------------------------------------------------------*/
extern int32_t GetPreviousMenuComp(void);
/*--------------------------------------------------------------------------*/
extern int32_t GetNextMenuComp(void);
/*--------------------------------------------------------------------------*/
extern void DrawObjComportement(int32_t x0,int32_t y0,int32_t x1,int32_t y1,int32_t y3d,int32_t betaflag,T_OBJ_3D *ptrobj3d);
/*--------------------------------------------------------------------------*/
extern void DrawComportement(int32_t num,int32_t comportement,int32_t beta,int32_t copyblock);
/*--------------------------------------------------------------------------*/
extern void DrawInfoMenu(int32_t x0,int32_t y0);
/*--------------------------------------------------------------------------*/
extern void DrawMenuComportement(int32_t beta);
/*--------------------------------------------------------------------------*/
extern void CalculeDebComportement(T_MENU_COMP *ptrmcomp);
/*--------------------------------------------------------------------------*/
extern void MenuComportement(int32_t affone);
/*--------------------------------------------------------------------------*/
extern void IncrustComportement( uint8_t Comportement ) ;
/*--------------------------------------------------------------------------*/

#endif	// COMPORTE_H
