//****************************************************************************
#ifndef	LIB_3D_ROT3D
#define	LIB_3D_ROT3D

//****************************************************************************
#include	"LROT3D.H"

//****************************************************************************
#ifdef	__cplusplus
extern	"C"	{
#endif

//****************************************************************************
typedef	void (Func_RotatePoint)(TYPE_MAT *Mat, int32_t x, int32_t y, int32_t z) ;

#pragma aux Arg_RotatePoint	"*"	       	\
	parm caller	[esi] [eax] [ebx] [ecx]	\
	modify exact	[eax ebx ecx edx edi]

#pragma	aux (Arg_RotatePoint)	Func_RotatePoint

//****************************************************************************
//extern	Func_RotatePoint	*RotatePoint	;
extern	Func_RotatePoint	*RotatePointNoMMX;

#define RotatePoint RotatePoint_C
void RotatePoint_C(TYPE_MAT *Mat, int32_t x, int32_t y, int32_t z) ;

//****************************************************************************
#define	WorldRotatePoint(x, y, z) RotatePoint(&MatriceWorld, x, y, z)

//****************************************************************************
// These functions should not be called directly but through the above pointer
// which auto-initalize to point to the right routine at runtime.
extern	Func_RotatePoint RotatePointI	;
//#define			 RotatePointF(mat, x, y, z)	LongRotatePointF(mat, x, y, z)
extern	Func_RotatePoint RotatePointM	;

//****************************************************************************
#ifdef	__cplusplus
}
#endif

//****************************************************************************
#endif//LIB_3D_ROT3D

//****************************************************************************

