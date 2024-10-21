/*══════════════════════════════════════════════════════════════════════════*
             █   █ █▀▀▀█ █▀▀▀█       █▀▀▀▀ ▀▄ ▄▀ ▀▀█▀▀       █   █
             ██ ▄▀ ██▀▀█ ██▀█▀       ██▀▀   ▄▀▄    ██   ▄▄   ██▀▀█
             ▀▀▀   ▀▀  ▀ ▀▀  ▀ ▀▀▀▀▀ ▀▀▀▀▀ ▀   ▀   ▀▀   ▀▀   ▀▀  ▀
 *══════════════════════════════════════════════════════════════════════════*/

#ifndef	LBA_GAME
extern	int16_t	FillFeuille ;
#endif

extern	int32_t	ClipZFar  ;
extern	int32_t	StartZFog ;

//camera

extern	int32_t	CamPosX	;
extern	int32_t	CamPosY	;
extern	int32_t	CamPosZ	;

extern	int32_t	AlphaCam ;
extern	int32_t	BetaCam	;
extern	int32_t	GammaCam ;
extern	int32_t	ChampX ;
extern	int32_t	ChampZ ;

extern	int32_t	VueDistance ;
extern	int32_t	VueOffsetX, VueOffsetY, VueOffsetZ ;

extern	int32_t	WorldLightAlpha ;
extern	int32_t	WorldLightBeta ;

// terrain

//extern	int32_t		ListCubeInfos[] ;
extern	int32_t		*ListCubeInfos ;



extern	uint8_t		*IsleMapIndex ;
extern	T_HALF_POLY	*MapPolyGround ;

//extern	char		IsleMapIndex[16][16] ;
//extern	T_HALF_POLY	MapPolyGround[64][64][2] ;
extern	T_HALF_TEX	*ListTexDef ;


extern	int16_t		*MapSommetY ;
extern	uint8_t		*MapIntensity ;
extern	T_SOMMET_ROT	SommetRot[65][65] ;
extern	uint8_t		SommetAffichable[65][65] ;

/*
extern	int16_t		MapSommetY[65][65] ;
extern	uint8_t		MapIntensity[65][65] ;
extern	T_SOMMET_ROT	SommetRot[65][65] ;
*/

extern	int32_t		PalLevel ;

#ifdef __cplusplus
extern "C" int32_t		FogCoul  ;
#else
extern int32_t		FogCoul  ;
#endif

extern	uint8_t		*SkySeaTexture ;
extern	uint8_t		*ObjTexture ;
extern	uint8_t		*GroundTexture ;

extern	Struc_Point	Tab_Points[] ;
//extern	Struc_Point	MemoTab_Points[] ;

// decors

extern	int32_t		NbObjDecors ;
extern	T_DECORS	*ListDecors ;
//extern	T_HQR_HEADER	*HQR_Isle ;
extern	T_HQR_HEADER	*HQR_Isle_Obj ;
extern	T_HQR_HEADER	*HQR_CubeInfos ;
extern	T_HQR_HEADER	*HQR_ListDecors ;
extern	T_HQR_HEADER	*HQR_MapPGround ;
extern	T_HQR_HEADER	*HQR_ListTexDef ;
extern	T_HQR_HEADER	*HQR_MapSommetY ;
extern	T_HQR_HEADER	*HQR_MapIntensity ;

extern	int32_t		NbObjScreen ;
extern	T_LIST_TRI	*ListTriExt ;

// collision avec le terrain
extern	int32_t		IndexMapPolyTested ;
extern	uint16_t		CubeBitField ;

//--------------------------------------------------------------------
// Animation de l'eau

#define	SIZE_BUFFER_POLY_SEA	100000L
#define	MAX_POLY_SEA		(SIZE_BUFFER_POLY_SEA/sizeof(S_ANI_POLY))

extern	int32_t		TimerAniPoly ;
extern	int32_t		CntAniPoly8 ;		// anim 0-7
extern	int32_t		CntAniPoly6 ;		// anim 0-5

extern	S_ANI_POLY	*PtrPolySea ; 		// buffer stockage
extern	int32_t		MaxPolySea ;

extern	S_ANI_POLY	*PtrAniPoly ;			// pointeur poly en cours
extern	int32_t		NbAniPoly ;

extern	int32_t		OffsetAniPoly1 ;
extern	int32_t		OffsetAniPoly2 ;
extern	int32_t		OffsetAniPoly3 ;
extern	int32_t		OffsetAniPoly4 ;
