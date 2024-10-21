/*-------------------------------------------------------------------------*/
//────────────────────────────────────────────────────────────────────────────


//#define	MAX_TRI	25
//#define	ONE_DIR		1	//	all datas in current directory...
#define	P_TWINSUN	0
#define	P_MOON		1
#define	P_ZEELICH	2
#define	P_SUN_0		3
#define	P_SUN_1		4
#define	P_SUN_Z		5

#define	MAX_PLANET	7
#define	RAYON_PLANET	1000
#define	ZOOM_PLANET		8000
#define	ZOOM_PLANET_SOUSGAZ	12000
#define	ZOOM_INIT_PLANET	3000

#define	X_CENTRE_TRAJ_HOLO	320+80
#define	Y_CENTRE_TRAJ_HOLO	240

#define	ZOOM_TWINSUN		8000		//9500
#define	ZOOM_MOON		2000		//1250
#define	ZOOM_ZEELICH		6000
#define	ZOOM_SUN		2000

#define	STEP_ANGLE	(32*4)
#define	SLIG  		(((4096/STEP_ANGLE)+1) * 2)
#define	SIZE_TEXT_GLOBE	(((4096/STEP_ANGLE)+1) * ((2048/STEP_ANGLE)+1) * 2 * 2)
#define	SIZE_COOR_GLOBE	(((4096/STEP_ANGLE)+1) * ((2048/STEP_ANGLE)+1) * 3 * 2)
#define	SIZE_ALT_GLOBE	544
#define	DISTANCE_EXT	(512*10)	//	5 Metres


#define	MAX_ARROW	(10*10)	//	10 fleches par 10 iles
#define	SCE		32768	//	SizeXZ Cube Exterieur

#define	MAX_OBJECTIF	50
#define	MAX_ISLAND	12
#define	MAX_CUBE	255


#define	SIZE_ARROW_ISLAND	10000
#define	SIZE_SMALL_ARROW_ISLAND	2000	//	1621 real size

#define	SCALE_OBJ_GLOBE		8
#define	SCALE_BODY_GLOBE	64
#define	SIZE_ARROW_PLANET	100	//	After Scale

#define	SCALE_BODY_PLAN		2048
#define	SCALE_BUGGY_PLAN	1024
#define	SCALE_DYNO_PLAN		(1024+256)

#define	PLANET			128
#define	UFO			256

#define	HQR_COORMAPP_HMM	0
#define	HQR_TWINSUN_HMT		1
#define	HQR_TWINSUN_HMG		2
#define	HQR_MOON_HMT		3
#define	HQR_MOON_HMG		4
#define	HQR_ZEELICH_HMT		5
#define	HQR_ZEELICH_HMG		6
#define	HQR_SOUSGAZ_HMT		7
#define	HQR_SOUSGAZ_HMG		8
#define	HQR_SUN_HMG		9

#define	HQR_FLECHE		10


#define	HQR_LOFLECHE		11
#define	HQR_ARROWBIN		12
#define	HQR_BUGGY		13
#define	HQR_DYNO		14

#define	HQR_BEGIN_MAP		18

#define	START_ZOOM      9500

#define	CENTERX		320
#define	CENTERY		220
#define	SX		6
#define	SY		6

#define	MAX_STARS	200	//Attention au DEFINE dans FlipBox.c


typedef	struct
{
	int32_t	X	;//	Position Island X Y Z
	int32_t	Y	;
	int32_t	Z	;
	int32_t	Alpha	;//	Position Planet Alpha, Beta et Altitude
	int32_t	Beta	;
	int32_t	Alt	;
	int32_t	Mess	;//	Message sur Island ou Planet
	int8_t	ObjFix	;//	Eventual Obj Inventory 3D (FREE NOT USED!)
	uint8_t	FlagHolo;//	Flag for Planet display, active, etc.
	uint8_t	Planet	;
	uint8_t	Island	;

} T_ARROW	;

extern	T_ARROW	TabArrow[MAX_OBJECTIF+MAX_CUBE]		;

extern	uint32_t	DecalTimerRef[MAX_OBJECTIF+MAX_CUBE] 	;

/*-------------------------------------------------------------------------*/

extern	Struc_Point Tab_Points[]	;


extern	uint32_t	AlphaL, BetaL, GammaL	;
extern	int32_t	HoloAlpha, HoloBeta, HoloGamma	;
extern	int32_t	NumObjectif		;
extern	int32_t	OldObjectif		;

extern	uint16_t	PtrTri[]		;//	For 1 Planet
extern	int32_t	ListTriPlanet[]		;//	For 6 Planets
extern	int32_t	NbTri			;//	Nb Planet(s) in ListTri
extern	int32_t	ModeAuto 		;
extern	int32_t	XPos, YPos, ZPos	;
extern	int32_t	XDest, YDest, ZDest	;
extern	int32_t	ZoomDest		;
extern	int32_t	Destination		;
extern	uint32_t	MyTimerRef		;
extern	uint32_t	RayonPlanet		;
extern	int32_t	DialStatHolo 		;
extern	int32_t	SizeRet		;
extern	uint8_t	RotPal[]	;

extern	int16_t	RotPalPos 	;
extern	int32_t	FlagMap		;
extern	int32_t	FlagHoloEnd	;
extern	int32_t	XpObjectif	;
extern	int32_t	YpObjectif	;
extern	uint32_t	MemoTimerRot	;
extern	int32_t	ZoomedIsland	;
extern	int32_t	TwinsenLinkArrow;
extern	int32_t	OrgMX, OrgMZ	;
extern	int32_t	AlphaM, BetaM	;
extern	int32_t	DistanceM	;
extern	uint8_t	*PtCurrentBody	;//	Tempo : Pointeur dans struc Twinsen
extern	uint8_t	*PtCurrentAnim	;//	Tempo : Pointeur dans struc Twinsen
extern	uint32_t	SizeCurrentBody	;//	Tempo : Pointeur dans struc Twinsen
extern	uint32_t	SizeCurrentAnim	;//	Tempo : Pointeur dans struc Twinsen
extern	uint8_t	*BufBodyTempo	;//	Buffer Tempo Traffiquer Body ( scale & rot )
extern	uint8_t	*BufAnimTempo	;//	Buffer Tempo Traffiquer Anim ( scale & rot )
extern	uint16_t	*PtrMapping	;
extern	uint16_t	*PtrGlobe	;
extern	uint8_t	*PtrAlt		;
extern	uint16_t	*PtrCoorGlobe	;
extern	uint8_t	*PtrTextMap	;
extern	T_OBJ_3D ObjTwinsen	;
extern	int32_t	NumOldMess	;
extern	int32_t	HoloMode	;
/*-------------------------------------------------------------------------*/

typedef	struct
{
	int32_t	XStar	;
	int32_t	YStar	;
	int32_t	ZStar	;
	int32_t	ColStar	;
} T_STARS	;

extern	T_STARS	TabStars[];
/*-------------------------------------------------------------------------*/
typedef	struct
{

	uint32_t	XSpace	;
	uint32_t	YSpace	;
	uint32_t	ZSpace	;
	uint16_t	Rayon	;
	uint16_t     Zoom	;

	uint16_t	*PtrCoorGlobe	;
	uint8_t	*PtrTextMap	;
	uint8_t	dummy		;// I don't like to wait after watcom about struct align ;)

}	T_PLANET		;

extern	T_PLANET	TabPlanet[]	;

/*-------------------------------------------------------------------------*/
extern	uint8_t		*PtUfo		;
extern	uint8_t		*PtAnimUfo	;
extern	T_OBJ_3D        Ufo		;
//----------------------------------------------------------------------------
extern	uint8_t	*BufFleche	;
extern	uint8_t	*BufLoFleche	;
extern	uint8_t	*BufBuggy	;
extern	uint8_t	*BufDyno	;
//----------------------------------------------------------------------------

/*-------------------------------------------------------------------------*/

//────────────────────────────────────────────────────────────────────────────
//	Objects Scale factor by planet
extern	int32_t	TabRayon[]	;
extern	int32_t	TabScale[] 	;
extern	int32_t	TabZoom[]	;
//────────────────────────────────────────────────────────────────────────────
//	Functions
extern	int	z_sort( void const *a, void const *b)	;
extern	int	z_sort32( void const *a, void const *b)	;

#ifdef	DEBUG_TOOLS
extern	int32_t	SizeHoloMalloc					;
#endif
extern	void	InitHoloMalloc(void)				;
extern	uint8_t	*HoloMalloc( uint32_t size )				;
extern	uint8_t	*LoadHoloMalloc_HQR( const char *name, int32_t index )	;

extern	void	ScaleRotBody3D( uint8_t *ptbody, int32_t scale, int32_t flagrot )	;
extern	uint32_t	GetSizeBody3D( uint8_t *ptbody )	;
extern	void	ScaleRotAnim3D( uint8_t *ptanim, int32_t scale, int32_t flagrot )	;
extern	uint32_t	GetSizeAnim3D( uint8_t *ptanim )	;
extern	void	InitAngleArrow(void)		;
extern	void	HoloPlan(int32_t numplan)		;

extern	void    AffUpperLeft( int32_t x, int32_t y, int32_t flag )	;
extern	void    AffLowerLeft( int32_t x, int32_t y, int32_t flag )	;
extern	void    AffUpperRight( int32_t x, int32_t y, int32_t flag )	;
extern	void    AffLowerRight( int32_t x, int32_t y, int32_t flag )	;
extern	void	DoAnimHolo(void)		        ;
extern	void	AffReticule(void)			;
extern	void	AffHoloMess(void)			;
extern	void	AdjustScreenMax(void)			;
extern	void	ComputeCoorGlobe(void)			;
extern	void	DrawHolomap(void)			;
extern	void	HoloSpace(void)				;

extern	void	InitHoloMap()				;
extern	void	HoloMap(void)				;
extern	int32_t	SetHoloPos( int32_t num )			;
extern	void	ClrHoloPos( int32_t num )			;
