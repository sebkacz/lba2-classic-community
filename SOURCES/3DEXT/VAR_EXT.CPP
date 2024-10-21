/*══════════════════════════════════════════════════════════════════════════*
             █   █ █▀▀▀█ █▀▀▀█       █▀▀▀▀ ▀▄ ▄▀ ▀▀█▀▀       █▀▀▀▀
             ██ ▄▀ ██▀▀█ ██▀█▀       ██▀▀   ▄▀▄    ██   ▄▄   ██
             ▀▀▀   ▀▀  ▀ ▀▀  ▀ ▀▀▀▀▀ ▀▀▀▀▀ ▀   ▀   ▀▀   ▀▀   ▀▀▀▀▀
 *══════════════════════════════════════════════════════════════════════════*/
/*──────────────────────────────────────────────────────────────────────────*/

#ifndef	LBA_GAME
int16_t	FillFeuille= 1 ;
#endif

int32_t	ClipZFar ;
int32_t	StartZFog ;

//camera

int32_t	CamPosX	;
int32_t	CamPosY	;
int32_t	CamPosZ	;

int32_t	AlphaCam	= 60*4;
int32_t	BetaCam		= -64*4;
int32_t	GammaCam	= 0;
int32_t	ChampX		= 600;
int32_t	ChampZ		= 600;

int32_t	VueDistance	= 30000;
int32_t	VueOffsetX = 512*32 , VueOffsetY = 0 , VueOffsetZ = 512*32 ;

int32_t	WorldLightAlpha ;
int32_t	WorldLightBeta ;

#ifdef	LBA_EDITOR
int32_t	ZBuffer = FALSE ;
#else
int32_t	ZBuffer = TRUE ;
#endif

// terrain

int32_t		*ListCubeInfos ;	// size ok file stored in hqr

uint8_t		*IsleMapIndex ;

T_HALF_POLY	*MapPolyGround ;
T_HALF_TEX	*ListTexDef ;


int16_t		*MapSommetY ;
uint8_t		*MapIntensity ;
T_SOMMET_ROT	SommetRot[65][65] ;
uint8_t		SommetAffichable[65][65] ;

int32_t		FogCoul ;
int32_t		PalLevel ;

uint8_t		*SkySeaTexture ;
uint8_t		*ObjTexture ;
uint8_t		*GroundTexture ;

Struc_Point	Tab_Points[8] ;
//Struc_Point	MemoTab_Points[8] ;

// decors

int32_t		NbObjDecors ;
T_DECORS	*ListDecors ;

T_HQR_HEADER	*HQR_Isle_Obj ;
T_HQR_HEADER	*HQR_CubeInfos ;
T_HQR_HEADER	*HQR_ListDecors ;
T_HQR_HEADER	*HQR_MapPGround ;
T_HQR_HEADER	*HQR_ListTexDef ;
T_HQR_HEADER	*HQR_MapSommetY ;
T_HQR_HEADER	*HQR_MapIntensity ;

int32_t		NbObjScreen = 0;
uint16_t		CubeBitField ;

T_LIST_TRI	*ListTriExt ;

// collision avec le terrain
int32_t	IndexMapPolyTested = 0 ;	// liaison avec perso

//--------------------------------------------------------------------
// Animation de l'eau

int32_t		TimerAniPoly = 0 ;
int32_t		CntAniPoly8 = 0 ;		// anim 0-7
int32_t		CntAniPoly6 = 0 ;		// anim 0-5

S_ANI_POLY	*PtrPolySea	;		// buffer stockage
int32_t		MaxPolySea = MAX_POLY_SEA ;

S_ANI_POLY	*PtrAniPoly ;			// pointeur poly en cours
int32_t		NbAniPoly  = 0 	;

int32_t		OffsetAniPoly1 ;
int32_t		OffsetAniPoly2 ;
int32_t		OffsetAniPoly3 ;
int32_t		OffsetAniPoly4 ;

/*──────────────────────────────────────────────────────────────────────────*/
