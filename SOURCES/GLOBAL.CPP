#include	"C_EXTERN.H"

/*══════════════════════════════════════════════════════════════════════════*
			 █▀▀▀█ █▀▀▀▀ █▀▀▀█ ██▀▀▀ █▀▀▀█
			 ██▀▀▀ ██▀▀  ██▀█▀ ▀▀▀▀█ ██  █
			 ▀▀    ▀▀▀▀▀ ▀▀  ▀ ▀▀▀▀▀ ▀▀▀▀▀
 *══════════════════════════════════════════════════════════════════════════*/
/*──────────────────────────────────────────────────────────────────────────*/

/*--------- divers ---------------------------*/
#ifdef	ONE_GAME_DIRECTORY
int32_t	DebugFps = FALSE ;
#else
int32_t	DebugFps = TRUE ;
#endif

int32_t	DistribVersion = ACTIVISION_VERSION ;

char	MessageNoCD[50] ;

int32_t	DemoSlide = FALSE ;	// Mode démo non jouable
int32_t	RestartMusic = FALSE ;

uint8_t	FlagRain = FALSE ;
uint8_t	FlagDrawHorizon=TRUE;
uint8_t	SavingEnable = TRUE ;
uint8_t	FlagPlayAcf = FALSE ;
uint8_t	RainEnable  = FALSE ;

#ifdef	DEMO
uint8_t	FlagSlideShow = FALSE ;
#endif

uint8_t	*BufSpeak ;
//uint8_t	*BufTempo ;

uint8_t	*LbaFont ;
uint8_t	PalettePcx[768+500] ;
int32_t	MyKey = 0 ;
uint8_t	*PtrPal ;
uint8_t	*PtrPalNormal ;
uint8_t	*PtrPalCurrent ;
uint8_t	*PtrPalEclair  ;
uint8_t	*PtrPalBlack   ;
uint8_t	*PtrTransPal   ;
uint8_t	*PtrXplPalette ;
XPL_HEADER	*PtrXplHeader ;

int32_t	IdxPalette = 0 ;	// numéro de palette dans le HQR
int32_t	LastIdxPalette = 0 ;	// numéro de la palette précédente dans le HQR

char	String[256] ;
int32_t	Value ;

//------------ Mode Cinema = 2 bandes noires de 40 pixels en haut et en bas de
//			     l'ecran

uint8_t	CinemaMode = FALSE ;
int32_t	TimerCinema = 0 ;
int32_t	LastYCinema = 0 ;
int32_t	DebCycleCinema = 0 ;		// en pixels Y
int32_t	DureeCycleCinema = 500 ;	// en TimerRefHR

//---------------------------------------------------------------------------

int32_t	TimerProto ;

int32_t	SampleVolume = DEF_SAMPLE_VOLUME;
int32_t	VoiceVolume  = DEF_VOICE_VOLUME	;
int32_t	MasterVolume = DEF_MASTER_VOLUME;

uint32_t	ParmSampleVolume    = 127 ; // a sauver dans les sauvegardes
uint32_t	ParmSampleDecalage  = 0	  ;
uint32_t	ParmSampleFrequence = 0	  ;

int32_t	SamplesEnable = FALSE ;

int32_t	DetailLevel = MAX_DETAIL_LEVEL	;

int32_t	VideoFullScreen = TRUE ;

//int32_t	FlagPalettePcx = FALSE ;
int32_t	FlagFade = FALSE ;
int32_t	FlagPal  = FALSE ;
int32_t	FadeMenu = FALSE ;
int32_t	FlagBlackPal = FALSE ;

int32_t	FlagShadeMenu = FALSE ;

#ifdef	DEBUG_TOOLS
int32_t	DrawZVObjets = FALSE ;
#endif

char	PathFla[ADELINE_MAX_PATH] ;

int32_t	Version_US = TRUE ;

/*-------------------------- memoire ---------------------------*/

uint32_t	SpriteMem	= MIN_SPRITES_MEM ;
uint32_t	SpriteRawMem	= MIN_SPRITES_RAW_MEM ;
uint32_t	Anim3DSMem	= MIN_ANIM_3DS_MEM ;
uint32_t	SampleMem	= MIN_SAMPLES_MEM ;
uint32_t	AnimMem		= MIN_ANIMS_MEM ;
uint32_t	BodyMem		= MIN_BODYS_MEM ;
uint32_t	ObjFixMem	= MIN_OBJFIX_MEM ;
uint32_t	IsleObjMem	= MIN_ISLE_OBJ_MEM ;
uint32_t	CubeInfosMem	= MIN_CUBE_INFOS_MEM ;
uint32_t	ListDecorsMem	= MIN_LIST_DECORS_MEM ;
uint32_t	MapPGroundMem	= MIN_MAP_PGROUND_MEM ;
uint32_t	ListTexDefMem	= MIN_LIST_TEXDEF_MEM ;
uint32_t	MapSommetYMem	= MIN_MAP_SOMMETY_MEM ;
uint32_t	MapIntensityMem	= MIN_MAP_INTENSITY_MEM ;
uint32_t	SCCMem = 0	;	// Calculé dynamiquement (contient le scenar)

/*--------- ressources ---------------------------*/

T_HQR_HEADER	*HQR_Samples ;

uint8_t	*BufferTexture ;
uint8_t	AnimateTexture = FALSE ;

/*--------- Ardoise ---------------------------*/
int8_t	ListArdoise[MAX_ARDOISE] = { -1, -1, -1, -1, -1 } ;

uint8_t	CurrentArdoise = 0 ;
uint8_t	NbArdoise = 0 ;

/*-------------------- Animations 3DS  ---------------------------*/

T_ANIM_3DS	*ListAnim3DS	;

/*--------- disk ---------------------------*/

char	PleaseWait[60] ;

//char	ProgDrive[_MAX_DRIVE] ;
//char	ProgDir[_MAX_DIR] ;

//unsigned	OrgDrive ;
//char	OrgDir[_MAX_DIR] ;

//char	Name[_MAX_FNAME] ;
//char	Ext[_MAX_EXT] ;


T_TRACK	*ListBrickTrack ;
int32_t	NbBrickTrack = 0 ;

/*--------- menus -----------------------------*/
uint16_t	GameChoice ;
uint16_t	GameNbChoices ;
int16_t	GameListChoice[10] ; // max 7 (normally)

/*--------- perso ----------------------------*/
int32_t	FlagTheEnd = FALSE ;

/*
int32_t	AnimRienNormal, AnimRienSportif, AnimRienAgressif, AnimRienDiscret, AnimRienProtopack ;

uint8_t	*PtrFile3dNormal ;
uint8_t	*PtrFile3dSportif ;
uint8_t	*PtrFile3dAgressif ;
uint8_t	*PtrFile3dDiscret ;
uint8_t	*PtrFile3dProtopack ;
*/

extern	T_COMPORTEMENT	ListComportement[MAX_COMPORTEMENTS] ;

T_COMPORTEMENT	*PtrComportement = ListComportement ; // Normal

int32_t	Shadow = 3 ;	// full
int32_t	ShadowX, ShadowY, ShadowZ ;
uint8_t	ShadowCol ;
uint32_t	ShadowLevel = SHADOW_LEVEL ;

/*int32_t	ValidePosX, ValidePosY, ValidePosZ ;
int32_t	ValideCube ;
int32_t	ValideBeta ;
int16_t	ValideOffsetLife, ValideOffsetTrack ;
*/

int32_t	NumCube = 0 ;			// num cube en cours
int32_t	FlagChgCube = 0 ;
int32_t	FlagReajustPosTwinsen = TRUE ;	// Reajustement de twinsen lors d'un
					// changement de cube

int32_t	PhantomX = 0 ;	// offset du cube ext pour aller mourir
int32_t	PhantomY = 0 ;	// offset du cube ext pour aller mourir
int32_t	PhantomIsland ;

int32_t	FlagLoadGame = 0 ;
int32_t	NewPosX, NewPosY, NewPosZ ;
int32_t	CubeStartX, CubeStartY, CubeStartZ ;

int32_t	ExtraConque = -1 ;	// Numero extra visant Twinsen (avec Conque)

int32_t	AllCameras = TRUE ;
int32_t	ReverseStereo = FALSE ;
int32_t	Island = 0	;
int32_t	Planet = 0	;

int32_t	FlagWater = FALSE ;

int32_t	ScaleFactorSprite = DEF_SCALE_FACTOR ;

int32_t	SpriteX = 0 ;	// Coordonnees d'affichage des sprites
int32_t	SpriteY = 0 ;

uint8_t	SaveComportement = C_NORMAL ;

/*--------- Extra objs ----------------------------*/
T_HQR_HEADER	*HQRPtrSprite ;
T_HQR_HEADER	*HQRPtrSpriteRaw ;
T_HQR_HEADER	*HQRPtrAnim3DS ;
int16_t	*PtrZvExtra ;
int16_t	*PtrZvExtraRaw ;
int16_t	*PtrZvAnim3DS	;

/*--------- moteur 3D ----------------------------*/
uint8_t	*BufferAnim ;

T_HQR_HEADER	*HQR_Anims ;
T_HQR_HEADER	*HQR_Bodys ;
T_HQR_HEADER	*HQR_ObjFix ;

uint8_t	*BufferPof ;
uint8_t	*BufferFile3D ;

T_SORT	ListTri[MAX_TRI] ;

/*--------- ambiance ----------------------------*/
int16_t	SampleAmbiance[4] ;
int16_t	SampleRepeat[4] ;
int16_t	SampleRnd[4] ;
int16_t	SampleFreq[4] ;
int16_t	SampleVol[4] ;
int32_t	SamplePlayed = 0 ;
uint32_t	TimerNextAmbiance = 0 ;
int32_t	SecondEcart = 30 ;
int32_t	SecondMin = 10 ;
int32_t	CubeJingle = 255 ;

/*--------- brick iso ----------------------------*/
int32_t	FirstTime = AFF_ALL_FLIP ;
int32_t	FirstLoop = FALSE ;
int32_t	FirstSave = FALSE ;

/*══════════════════════════════════════════════════════════════════════════*
	Liste des Globales sauvées dans les fichiers de sauvegarde .LBA
 *══════════════════════════════════════════════════════════════════════════*/
/*──────────────────────────────────────────────────────────────────────────*/
int32_t		NewCube	= -1 ;			// change cube demandé
uint8_t		ListVarCube[MAX_VARS_CUBE] ;
int16_t		ListVarGame[MAX_VARS_GAME] ;
uint8_t		Comportement = C_NORMAL ;
uint8_t		SaveComportementHero = C_NORMAL ;
int32_t		NbGoldPieces = 0 ;
int32_t		NbZlitosPieces = 0 ;
uint8_t		NumVersion = NUM_VERSION|SAVE_COMPRESS ;
uint8_t		MagicLevel = 0 ;
uint8_t		MagicPoint = 0 ;
uint8_t		NbLittleKeys = 0 ;
int16_t		NbCloverBox = NB_CLOVER_BOX_DEFAULT ;
int32_t		SceneStartX, SceneStartY, SceneStartZ ;
uint8_t		Weapon = FLAG_BALLE_MAGIQUE ;		// magicball
		// TimerRef en extern sauvé ici
//int32_t		LastFire = 0 ;
uint8_t		Bulle = TRUE ;
uint8_t		ActionNormal = FALSE ;
int32_t		InventoryAction = -1 ;
int32_t		MagicBall = -1 ;
uint8_t		MagicBallType = 1 ;
uint8_t		MagicBallCount = 3 ;
int32_t		MagicBallFlags = 0 ;
T_ZONE		*PtrZoneClimb ;	// Zone echelle dans laquelle se trouve Twinsen
uint8_t		FlagClimbing = FALSE ;
int32_t		StartYFalling = 0 ;
MOVE		RealFalling ;
int32_t		StepFalling = 1 ;
MOVE		RealShifting ;
int32_t		StepShifting = 1 ;
uint8_t		NumObjFollow = NUM_PERSO ;
uint8_t		CameraZone = FALSE ;
int32_t		StartXCube = 0	;
int32_t		StartYCube = 0	;
int32_t		StartZCube = 0	;
T_DART		ListDart[MAX_DARTS] ;
int32_t		NbObjets = 0 ;
T_OBJET		ListObjet[MAX_OBJETS] ;
T_EXTRA		ListExtra[MAX_EXTRAS] ;
int32_t		NbZones = 0 ;
T_ZONE		*ListZone ;
T_INCRUST_DISP	ListIncrustDisp[MAX_INCRUST_DISP] ;
		// ListPartFlow en extern sauvé ici

MOVE	SampleAlwaysMove ;	// pour repaner les samples always de tps en tps

int32_t	FlagCameraForcee = FALSE ;
int32_t	ModeLabyrinthe = FALSE ;

int32_t	VueCamera = 0 ;

int32_t	DefVueDistance[NB_VUE_CAMERA] = { 10500, 17000 } ;
int32_t	DefAlphaCam[NB_VUE_CAMERA] = { 300, 530 } ;

T_TABALLCUBE	TabAllCube[256]	;//	A mettre en define
/*──────────────────────────────────────────────────────────────────────────*/

uint8_t	NumObjDial = 0		;
uint8_t	SaveBodyHero = GEN_BODY_NORMAL  ;

uint32_t	Checksum = 0 ;

