/*══════════════════════════════════════════════════════════════════════════*

    ██████┐ ██┐ ██┐ ██████┐ ██████┐ ██┐ ██┐ ██┐ ██┐ ██████┐         ██┐ ██┐
    ██┌───┘ ██│ ██│ └─██┌─┘ ██┌───┘ ██│ ██│ ███┐██│ ██┌───┘         ██│ ██│
    █████┐  └████┌┘   ██│   █████┐  ██│ ██│ ██████│ ██│             ██████│
    ██┌──┘  ██┌─██┐   ██│   ██┌──┘  ██│ ██│ ██┌███│ ██│             ██┌─██│
    ██████┐ ██│ ██│   ██│   ██│     ██████│ ██│└██│ ██████┐   ██┐   ██│ ██│
    └─────┘ └─┘ └─┘   └─┘   └─┘     └─────┘ └─┘ └─┘ └─────┘   └─┘   └─┘ └─┘

 *══════════════════════════════════════════════════════════════════════════*/

extern	int32_t	FlagHeroOutX ;	// Twinsen sort du cube en X
extern	int32_t	FlagHeroOutZ ;	// Twinsen sort du cube en Z

/*──────────────────────────────────────────────────────────────────────────*/
// Game
//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	void	Init3DExt( void ) ;

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	void	Clear3dExt( void ) ;

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	Func_Init3DView	Init3DExtView ;

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	void	Init3DExtGame( void ) ;

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
// Map
extern	Func_InitGrille	InitGrilleExt ;

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	void	AffGrilleExt( void ) ;

/*──────────────────────────────────────────────────────────────────────────*/
// Graph
/*--------------------------------------------------------------------------*/
extern	void	CalculeScaleFactorSprite( int32_t x, int32_t y, int32_t z, int32_t scaleorg ) ;

/*--------------------------------------------------------------------------*/
extern	void	AffGraphExt( int32_t xp, int32_t yp, int32_t sprite ) ;

/*--------------------------------------------------------------------------*/

/*──────────────────────────────────────────────────────────────────────────*/
// Objects
/*--------------------------------------------------------------------------*/
extern	Func_GetShadow	GetShadowExt ;

/*--------------------------------------------------------------------------*/
extern	Func_WorldColBrick	WorldColBrickExt ;

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern Func_WorldColBrickVisible	WorldColBrickVisibleExt ;

/*--------------------------------------------------------------------------*/
extern	Func_ReajustPosExtra	ReajustPosExtraExt ;

/*--------------------------------------------------------------------------*/
#ifndef	LBA_EDITOR
extern	Func_FullWorldColBrick	FullWorldColBrickExt ;
#endif

/*--------------------------------------------------------------------------*/
extern	int32_t	TestZVDecorsZV( T_DECORS *objet,
				int32_t xpmin, int32_t ypmin, int32_t zpmin,
				int32_t xpmax, int32_t ypmax, int32_t zpmax
				 ) ;

/*--------------------------------------------------------------------------*/
extern	uint8_t	WorldColBrickDecors( 	int32_t xpmin, int32_t ypmin, int32_t zpmin,
					int32_t xpmax, int32_t ypmax, int32_t zpmax ) ;

/*--------------------------------------------------------------------------*/
extern	int32_t	ReajustPosDecors( int32_t xmin, int32_t zmin,
				  int32_t xmax, int32_t zmax,
				  int32_t y0, int32_t y1 ) ;

/*--------------------------------------------------------------------------*/
extern	uint8_t	WorldColBrickFullExt( int32_t xw, int32_t yw, int32_t zw ) ;

/*--------------------------------------------------------------------------*/
extern	void	InitSkating( void ) ;

/*--------------------------------------------------------------------------*/
extern	Func_ReajustPos	ReajustPosExt ;

/*--------------------------------------------------------------------------*/
extern	int32_t    GetSkateBeta( int32_t nx, int32_t nz ) ;

/*--------------------------------------------------------------------------*/
extern	Func_DoAnim	DoAnimExt ;

/*--------------------------------------------------------------------------*/

/*──────────────────────────────────────────────────────────────────────────*/
// Tools (PERSO)
#ifdef	LBA_EDITOR
extern	void	DrawGrilleFeuille3D( int32_t xi, int32_t zi ) ;
extern	int32_t	GereMouseMovements( int32_t boutons ) ;
#endif

extern	void 	AffPalette( void ) ;

/*--------------------------------------------------------------------------*/
#ifdef	LBA_EDITOR
extern	int32_t	GereExtKeys( uint32_t key, uint32_t flagmenu ) ;
#else
extern	int32_t	GereExtKeys( uint32_t key ) ;
#endif

/*--------------------------------------------------------------------------*/

#ifdef	LBA_EDITOR
extern	void	DrawRepereXYZ( int32_t x0, int32_t y0, int32_t x1, int32_t y1 ) ;
extern	void	DrawCameraInfos( void ) ;
extern	void	MenuCreateExtZones( void ) ;
#endif

/*══════════════════════════════════════════════════════════════════════════*/
