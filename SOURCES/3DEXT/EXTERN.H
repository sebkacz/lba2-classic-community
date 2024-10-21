// extern.h

#ifndef	EXT_EXTERN_H
#define	EXT_EXTERN_H

// vars terrain game
#include	"LBA_EXT.H"
#include	"VAR_EXT.H"


#define	SIZE_Z_BUFFER	(640*480*2)


#ifdef __cplusplus
extern "C" {
#endif

int32_t	LineRain(int32_t x0, int32_t y0, int32_t z0, int32_t x1, int32_t y1, int32_t z1, int32_t coul );
/*
#pragma aux LineRain	"*"				\
	parm caller [eax] [ebx] [edi] [ecx] [edx] [esi]
*/
#ifdef __cplusplus
}
#endif

#define	DISTANCE_VISEE	2500

extern	char	IslandName[ADELINE_MAX_PATH] ;

extern	int32_t	PalLevel	;

extern	int32_t	CurrentCubeX	;
extern	int32_t	CurrentCubeY	;

extern	int32_t	DrawTerrain 	;

extern	uint8_t	*ScreenAux 	;
extern	uint8_t	*ScreenTempo 	;

#ifdef	MOUNFRAC
extern	int32_t	MyKey ;
extern	int32_t	MyJoy ;
extern	int32_t	MyFire ;
extern	int32_t	MyClick ;

extern	uint8_t	CurrentPalette[768] ;
#endif

#ifndef	LBA_GAME
extern	int32_t	MyMouseX ;
extern	int32_t	MyMouseY ;
#endif


// vars edition terrain
#ifndef	LBA_GAME
extern	int32_t	IndXPolySelected ;
extern	int32_t	IndZPolySelected ;
#endif

extern	int32_t	LastTriangle ;

// test obj animé dans decors

#ifdef	MOUNFRAC
extern	T_OBJET	Objet ;
#endif

#ifdef __cplusplus
extern "C" {
#endif

typedef struct
{
	int32_t	Pt_XObs;
	int32_t	Pt_YObs;
	int32_t	Pt_ZObs;
	int32_t	Pt_UObs;
	int32_t	Pt_VObs;
}	Struc_Point3D;


#ifdef __cplusplus
}
#endif


// Prototypes des fonctions de la 3DExt

#include	"DECORS.H"
#include	"LOADISLE.H"
#include	"MAPTOOLS.H"
#include	"SELECT.H"
#include	"TERRAIN.H"
#include	"BOXZBUF.H"

#endif	// EXT_EXTERN_H
