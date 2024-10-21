#include "DEFINES.H"

/*--------- divers ---------------------------------------------*/
extern int32_t BodyComportement;

extern int32_t DebugFps;

extern int32_t DistribVersion;

extern char MessageNoCD[50];

extern uint16_t GameOptionMenu[];
extern int32_t FlecheForcee;
extern uint16_t *BufOrder;
extern uint8_t *BufText;

extern int32_t DemoSlide; // Mode démo non jouable
extern int32_t RestartMusic;

extern uint8_t FlagRain;
extern uint8_t FlagDrawHorizon;
extern uint8_t SavingEnable;
extern uint8_t FlagPlayAcf;
extern uint8_t RainEnable;

extern char NewGameTxt[20]; // ATTENTION: max 19 chars

#ifdef DEMO
extern uint8_t FlagSlideShow;
#endif

extern "C" uint8_t *BufSpeak;

extern char GamePathname[];
extern char OldGamePathname[];
extern char PlayerName[MAX_SIZE_PLAYER_NAME + 1];

extern uint8_t *PtrScene;

extern uint8_t *LbaFont;
extern uint8_t PalettePcx[];
extern uint8_t *PtrPal;
extern uint8_t *PtrPalNormal;
extern uint8_t *PtrPalCurrent;
extern uint8_t *PtrPalEclair;
extern uint8_t *PtrPalBlack;
extern uint8_t *PtrTransPal;
extern uint8_t *PtrXplPalette;
extern XPL_HEADER *PtrXplHeader;

extern int32_t IdxPalette;     // numéro de palette dans le HQR
extern int32_t LastIdxPalette; // numéro de la palette précédente dans le HQR

extern int32_t MyKey;

extern int32_t LastJoyFlag;
extern int32_t Jumping;
extern int32_t Pushing;
extern int32_t LastMyJoy;
extern int32_t LastMyFire;

extern char String[];
extern int32_t Value;

extern int32_t Nxw, Nyw, Nzw;
extern int32_t SaveNxw, SaveNyw, SaveNzw;
extern int32_t OldX, OldY, OldZ;

extern uint8_t AnimNumObj;
extern T_OBJET *APtObj;

//------------ Mode Cinema = 2 bandes noires de 40 pixels en haut et en bas de
//			     l'ecran

extern uint8_t CinemaMode;
extern int32_t TimerCinema;
extern int32_t LastYCinema;
extern int32_t DebCycleCinema;   // en pixels Y
extern int32_t DureeCycleCinema; // en TimerRefHR

//---------------------------------------------------------------------------

extern int32_t TimerProto;

extern int32_t SampleVolume;
extern int32_t VoiceVolume;
extern int32_t MasterVolume;

extern int32_t SamplesEnable;

extern uint32_t ParmSampleVolume; // a sauver dans les sauvegardes
extern uint32_t ParmSampleDecalage;
extern uint32_t ParmSampleFrequence;

extern int32_t DetailLevel;
extern int32_t VideoFullScreen;

extern int32_t FlecheForcee;

extern int32_t FlagPalettePcx;
extern int32_t FlagFade;
extern int32_t FlagPal;
extern int32_t FadeMenu;
extern int32_t FlagMessageShade;
extern int32_t FlagBlackPal;

extern int32_t FlagShadeMenu;

#ifdef DEBUG_TOOLS
extern int32_t DrawZVObjets;
#endif

extern int32_t FlaFromCD;
extern char PathFla[];

extern int32_t Version_US;

/*-------------------------- memoire ---------------------------*/

extern uint32_t SpriteMem;
extern uint32_t SpriteRawMem;
extern uint32_t Anim3DSMem;
extern uint32_t SampleMem;
extern uint32_t AnimMem;
extern uint32_t BodyMem;
extern uint32_t ObjFixMem;
extern uint32_t IsleObjMem;
extern uint32_t CubeInfosMem;
extern uint32_t ListDecorsMem;
extern uint32_t MapPGroundMem;
extern uint32_t ListTexDefMem;
extern uint32_t MapSommetYMem;
extern uint32_t MapIntensityMem;
extern uint32_t SCCMem; // Calculé dynamiquement

/*-------- RESSOURCES ---------------------------------------------*/

extern T_HQR_HEADER *HQR_Samples;

/*-------- DISKFUNC.C ---------------------------------------------*/

extern int32_t CubeMode;
extern int32_t LastCubeMode;
extern int32_t ModeLabyrinthe;

extern char PleaseWait[];

// extern  char   	ProgDrive[] ;
// extern  char   	ProgDir[] ;

// extern  unsigned OrgDrive 	;
// extern  char   	 OrgDir[] ;

// extern  char   	Name[] ;
// extern  char   	Ext[] ;

/*-------- LIB_SVGA ---------------------------------------------*/
extern int16_t NbPolyPoints;

/*-------- life tool ---------------------------------------------*/
extern T_TRACK *ListBrickTrack;
extern int32_t NbBrickTrack;

/*--------- menus -----------------------------*/
extern uint16_t GameChoice;
extern uint16_t GameNbChoices;
extern int16_t GameListChoice[];

/*--------- perso ----------------------------*/
extern int32_t FlagTheEnd;

extern T_COMPORTEMENT ListComportement[MAX_COMPORTEMENTS];
extern T_COMPORTEMENT *PtrComportement; // Comportement courant

extern int32_t Shadow;
extern int32_t ShadowX, ShadowY, ShadowZ;
extern uint8_t ShadowCol;
extern uint32_t ShadowLevel;

extern int32_t FlagChgCube, NumCube;
extern bool
    FlagReajustPosTwinsen; // Reajustment of Twinsen during a cube change
extern int32_t PhantomX;   // offset du cube ext pour aller mourir
extern int32_t PhantomY;   // offset du cube ext pour aller mourir
extern int32_t PhantomIsland;
extern int32_t FlagLoadGame;
extern int32_t NewPosX, NewPosY, NewPosZ;
extern int32_t CubeStartX, CubeStartY, CubeStartZ;
extern int32_t Island;
extern int32_t Planet;

extern int32_t AllCameras;
extern int32_t ReverseStereo;

extern int32_t ScaleFactorSprite;

extern int32_t SpriteX; // Coordonnees d'affichage des sprites
extern int32_t SpriteY;

extern int32_t FlagWater;

// perso sauvegarde entrée cube
extern uint8_t SaveComportement;

/*--------- Extra objs ----------------------------*/
extern T_HQR_HEADER *HQRPtrSprite;
extern T_HQR_HEADER *HQRPtrSpriteRaw;
extern T_HQR_HEADER *HQRPtrAnim3DS;
extern int16_t *PtrZvExtra;
extern int16_t *PtrZvExtraRaw;
extern int16_t *PtrZvAnim3DS;

/*-------- Moteur 3D ---------------------------------------------*/
extern uint8_t *BufferTexture;
extern uint8_t AnimateTexture;
extern uint8_t *BufferAnim;

/*--------- Ardoise ---------------------------*/
extern int8 _tListArdoise[MAX_ARDOISE];

extern uint8_t CurrentArdoise;
extern uint8_t NbArdoise;

/*-------------------- Animations 3DS  ---------------------------*/

extern T_ANIM_3DS *ListAnim3DS;

extern T_HQR_HEADER *HQR_Anims;
extern T_HQR_HEADER *HQR_Bodys;
extern T_HQR_HEADER *HQR_ObjFix;

extern uint8_t *BufferPof;
extern uint8_t *BufferFile3D;

extern T_SORT ListTri[];

/*--------- ambiance ----------------------------*/
extern int16_t SampleAmbiance[];
extern int16_t SampleRepeat[];
extern int16_t SampleRnd[];
extern int16_t SampleFreq[];
extern int16_t SampleVol[];
extern int32_t SamplePlayed;
extern uint32_t TimerNextAmbiance;
extern int32_t SecondEcart;
extern int32_t SecondMin;
extern int32_t CubeJingle;

/*-------- Brick ISO ---------------------------------------------*/

#ifdef BRICK_HQR
extern uint8_t *BufferBrick;
#endif

extern int32_t FirstTime;
extern int32_t FirstLoop;
extern int32_t FirstSave;

extern int32_t WorldXCube;
extern int32_t WorldYCube;
extern int32_t WorldZCube;

extern int32_t XpOrgw;
extern int32_t YpOrgw;

/*--------- Message ---------------------------------------------*/
#ifdef CDROM
extern int32_t NumObjSpeak;
#endif
extern int32_t FlagSpeak;

//-------------------- Message Chapter
// extern int16_t MessChapitreTwinsen[MAX_CHAPTER][5] ;

//-------------------- ExtFunc.c
extern uint8_t *PtrNuances; // Nuances gouraud

extern uint8_t MagicHitForce[];
extern uint8_t MagicBallHitForce[];
extern uint8_t MagicBallSprite[];

/*══════════════════════════════════════════════════════════════════════════*
        Liste des Globales sauvées dans les fichiers de sauvegarde .LBA
 *══════════════════════════════════════════════════════════════════════════*/
/*──────────────────────────────────────────────────────────────────────────*/
extern int32_t NewCube; // change cube demandé
extern uint8_t ListVarCube[];
extern int16_t ListVarGame[];
extern uint8_t Comportement;
extern uint8_t SaveComportementHero;
extern int32_t NbGoldPieces;
extern int32_t NbZlitosPieces;
extern uint8_t NumVersion;
extern uint8_t MagicLevel;
extern uint8_t MagicPoint;
extern uint8_t NbLittleKeys;
extern int16_t NbCloverBox;
extern int32_t SceneStartX, SceneStartY, SceneStartZ;
extern uint8_t Weapon;
// TimerRef en extern sauvé ici
// extern  int32_t    		LastFire ;
extern uint8_t Bulle;
extern uint8_t ActionNormal;
extern int32_t InventoryAction;
extern int32_t MagicBall;
extern uint8_t MagicBallType;
extern uint8_t MagicBallCount;
extern int32_t MagicBallFlags;
extern T_ZONE *PtrZoneClimb; // Zone echelle dans laquelle se trouve Twinsen
extern uint8_t FlagClimbing;
extern int32_t StartYFalling;
extern MOVE RealFalling;
extern int32_t StepFalling;
extern MOVE RealShifting;
extern int32_t StepShifting;
extern uint8_t NumObjFollow;
extern uint8_t CameraZone;
extern int32_t StartXCube;
extern int32_t StartYCube;
extern int32_t StartZCube;
extern T_INV_OBJ TabInv[];
extern T_DART ListDart[];
extern int32_t NbObjets;
extern T_OBJET ListObjet[];
extern T_EXTRA ListExtra[];
extern int32_t NbZones;
extern T_ZONE *ListZone;
extern T_INCRUST_DISP ListIncrustDisp[];
// ListPartFlow en extern sauvé ici

extern MOVE SampleAlwaysMove; // pour repaner les samples always de tps en tps

extern int32_t FlagCameraForcee;
extern int32_t AddBetaCam;

extern int32_t VueCamera;

extern int32_t DefVueDistance[NB_VUE_CAMERA];
extern int32_t DefAlphaCam[NB_VUE_CAMERA];

extern int32_t ExtraConque;   // Numero extra visant Twinsen (avec Conque)
extern uint8_t PingouinActif; // Pingouin en cours d'utilisation

extern T_TABALLCUBE TabAllCube[];
/*──────────────────────────────────────────────────────────────────────────*/

extern uint8_t NumObjDial;
extern int32_t DialNbLine; // pour la version demo le 02/08/96
extern uint8_t SaveBodyHero;
extern uint32_t Checksum;
