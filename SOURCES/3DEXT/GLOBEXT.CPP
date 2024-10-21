#include	"DEFINES.H"

#include	"VAR_EXT.CPP"	// variables pour le terrain

char	IslandName[ADELINE_MAX_PATH] ;

int32_t	CurrentCubeX = 8 ;
int32_t	CurrentCubeY = 9 ;

int32_t	DrawTerrain = TRUE ;

uint8_t	*ScreenAux ;
//uint8_t	*ScreenTempo ;

#ifdef	MOUNFRAC
uint8_t	*Screen ;

int32_t	MyKey ;
int32_t	MyJoy ;
int32_t	MyFire ;
int32_t	MyClick ;

uint8_t	CurrentPalette[768] ;
#endif

#ifndef	LBA_GAME
int32_t	MyMouseX ;
int32_t	MyMouseY ;
#endif



// vars edition terrain
#ifndef	LBA_GAME
int32_t	IndXPolySelected = 0 ;
int32_t	IndZPolySelected = 0 ;
int32_t	PolySelectTriangle = 0 ;
#endif

int32_t	LastTriangle = 0 ;

// test obj animé dans decors
#ifdef	MOUNFRAC
T_OBJET	Objet ;
#endif
