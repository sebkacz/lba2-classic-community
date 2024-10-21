/*══════════════════════════════════════════════════════════════════════════*

	██████┐ ██┐ ██┐ ██████┐ ██████┐ ██┐ ██┐ ██████┐         ██┐ ██┐
	└─██┌─┘ ███┐██│ └─██┌─┘ ██┌───┘ ██│ ██│ └─██┌─┘         ██│ ██│
	  ██│   ██████│   ██│   █████┐  └████┌┘   ██│           ██████│
	  ██│   ██┌███│   ██│   ██┌──┘  ██┌─██┐   ██│           ██┌─██│
	██████┐ ██│└██│   ██│   ██████┐ ██│ ██│   ██│     ██┐   ██│ ██│
	└─────┘ └─┘ └─┘   └─┘   └─────┘ └─┘ └─┘   └─┘     └─┘   └─┘ └─┘

	Module commun aux mondes interieurs et exterieurs encapsulant
	certaines fonctions.

 *══════════════════════════════════════════════════════════════════════════*/

extern	int32_t	SaveVueOffsetX, SaveVueOffsetY, SaveVueOffsetZ ;
extern	int32_t	SaveAlphaCam, SaveBetaCam, SaveGammaCam ;
extern	int32_t	SaveVueDistance ;

/*──────────────────────────────────────────────────────────────────────────*/
// Game
extern	void	PtrInit3DGame() ;

/*──────────────────────────────────────────────────────────────────────────*/
// Objects
/*--------------------------------------------------------------------------*/
extern	int32_t	DrawRecover( int32_t xw, int32_t yw, int32_t zw, int32_t ymax, int32_t zvmax ) ;

/*--------------------------------------------------------------------------*/
extern	void	DrawRecover3( int32_t xw, int32_t yw, int32_t zw, int32_t ymax, int32_t zvmax ) ;

/*--------------------------------------------------------------------------*/

/*──────────────────────────────────────────────────────────────────────────*/
// Map
extern	void	RefreshGrille() ;
/*--------------------------------------------------------------------------*/
extern	uint8_t	PtrWorldCodeBrick( int32_t xw, int32_t yw, int32_t zw ) ;

/*--------------------------------------------------------------------------*/

#ifdef	LBA_EDITOR
extern	void	RefreshClippedGrille() ;
extern	void	PtrSearchFirstPseudo() ;
extern	int32_t	PtrGetScreenBrick( int32_t xp, int32_t yp ) ;
#endif

/*──────────────────────────────────────────────────────────────────────────*/
// Graph
/*--------------------------------------------------------------------------*/
extern	void	PtrProjectSprite( int32_t xw, int32_t yw, int32_t zw, int32_t sprite ) ;

/*--------------------------------------------------------------------------*/
extern	void	PtrGetDxDyGraph( int32_t sprite, int32_t *dx, int32_t *dy ) ;

/*--------------------------------------------------------------------------*/
extern	void	PtrAffGraph( int32_t xp, int32_t yp, int32_t sprite ) ;

/*--------------------------------------------------------------------------*/
extern	uint8_t	*GetPtrSprite( int32_t sprite ) ;

/*--------------------------------------------------------------------------*/

/*──────────────────────────────────────────────────────────────────────────*/
// World
/*--------------------------------------------------------------------------*/
extern	int32_t	PtrProjectPoint( int32_t xw, int32_t yw, int32_t zw ) ;

/*--------------------------------------------------------------------------*/
extern	void	CameraCenter( int32_t flagbeta ) ;

/*--------------------------------------------------------------------------*/
extern	void	FlyCamera( 	int32_t offx, int32_t offy, int32_t offz,
				int32_t alpha, int32_t beta, int32_t gamma, int32_t distance,
				int32_t delay ) ;
/*--------------------------------------------------------------------------*/
extern	void	SaveCamera() ;
/*--------------------------------------------------------------------------*/
extern	void	RestoreCamera() ;
/*--------------------------------------------------------------------------*/
extern	int32_t	PtrCalculAltitudeY( int32_t x, int32_t z ) ;

/*--------------------------------------------------------------------------*/

/*──────────────────────────────────────────────────────────────────────────*/
// Tools (PERSO)
#ifdef	LBA_EDITOR
extern	void	GereBrickMouse() ;
extern	int32_t	PtrGereKeys( uint32_t key, uint32_t flagmenu ) ;
#endif

/*──────────────────────────────────────────────────────────────────────────*/
// Pointeurs de fonctions communs au deux mondes et initialisés par PtrInit3DGame
//			(voir PTRFUNC.H)
/*--------------------------------------------------------------------------*/

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	Func_ReajustPos	*PtrReajustPos ;

//#pragma	aux	PtrReajustPos	"*"

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	Func_GetShadow	*PtrGetShadow ;

//#pragma	aux	PtrGetShadow	"*"

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	Func_DoAnim	*PtrDoAnim ;

//#pragma	aux	PtrDoAnim	"*"

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	Func_WorldColBrick	*PtrWorldColBrick ;

//#pragma	aux	PtrWorldColBrick	"*"

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	Func_WorldColBrickVisible	*PtrWorldColBrickVisible ;

//#pragma	aux	PtrWorldColBrickVisible	"*"

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	Func_ProjectShadow	*PtrProjectShadow ;

//#pragma	aux	PtrFunc_ProjectShadow	"*"

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	Func_ReajustPosExtra	*PtrReajustPosExtra ;

//#pragma	aux	PtrReajustPosExtra	"*"

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	Func_Init3DView	*PtrInit3DView ;

//#pragma	aux	PtrInit3DView	"*"

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	Func_InitGrille	*PtrInitGrille ;

//#pragma	aux	PtrInitGrille	"*"

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
#ifndef	LBA_EDITOR
extern	Func_FullWorldColBrick	*PtrFullWorldColBrick ;

//#pragma	aux	PtrFullWorldColBrick	"*"
#endif	// LBA_EDITOR

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀

/*══════════════════════════════════════════════════════════════════════════*/
