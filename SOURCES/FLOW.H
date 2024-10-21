/*══════════════════════════════════════════════════════════════════════════*
             █▀▀▀█ █▀▀▀█ █▀▀▀█ ▀▀█▀▀  █    █▀▀▀▀ █     █▀▀▀▀ ██▀▀▀
             ██▀▀▀ ██▀▀█ ██▀█▀   ██   ██   ██    ██    ██▀▀  ▀▀▀▀█
	     ▀▀    ▀▀  ▀ ▀▀  ▀   ▀▀   ▀▀   ▀▀▀▀▀ ▀▀▀▀▀ ▀▀▀▀▀ ▀▀▀▀▀
 *══════════════════════════════════════════════════════════════════════════*/
/*──────────────────────────────────────────────────────────────────────────*/

#ifndef	FLOW_H
#define	FLOW_H

typedef	struct
	{
		int16_t	Alpha;
		int16_t	Beta;
		int16_t	OuvertureAlpha;
		int16_t	OuvertureBeta;
		int16_t	XMin;
		int16_t	YMin;
		int16_t	ZMin;
		int16_t	XMax;
		int16_t	YMax;
		int16_t	ZMax;

		int16_t	Delay;
		int16_t	Speed;
		int16_t	Weight;
		int16_t	NbDot;

		int16_t	Bank;
		uint8_t	Coul;
		uint8_t	Range;
		uint32_t	Flags;
	}	T_FLOW;	// Sert uniquement au chargement des flows


typedef	struct {	int32_t	X ;
			int32_t	Y ;
			int32_t	Z ;
			int32_t	Vx ;
			int32_t	Vy ;
			int32_t	Vz ;
			int32_t	Delay ;
			int32_t	Poids ;
			int32_t	Couleur ;
			int32_t	Mode ;		}	S_ONE_DOT ;

typedef struct {
			int32_t		Flag ;
			int32_t		Owner;
			int32_t		NumPoint;
			int32_t		NbDot ;
			int32_t		OrgX ;
			int32_t		OrgY ;
			int32_t		OrgZ ;
			int32_t		XMin ;
			int32_t		YMin ;
			int32_t		ZMin ;
			int32_t		XMax ;
			int32_t		YMax ;
			int32_t		ZMax ;
			uint32_t		FlowTimerStart ;
			S_ONE_DOT	*PtrListDot ;	}	S_PART_FLOW ;

/*──────────────────────────────────────────────────────────────────────────*/

#ifdef	LBA_EDITOR
#define	PATH_FLOW	"f:\\projet\\lba2\\datas\\flow\\"
#endif

#define	FLOW_WAIT_COOR		1
#define	FLOW_EXTRA_SPRITE	2
#define	FLOW_EXTRA_OBJ		4
#define	FLOW_EXTRA_POF		8

#define	MAX_FLOWS	10
#define	MAX_FLOW_DOTS	100
#define	MAX_FLOW_EXTRA_DOTS	10

extern	S_PART_FLOW	ListPartFlow[MAX_FLOWS] ;
extern	S_ONE_DOT	*ListFlowDots ;

#ifndef	LBA_EDITOR
//extern T_HQR_HEADER	*HQR_Flows ;
//extern	uint32_t	FlowMem ;
#endif

extern	T_FLOW	*TabPartFlow	;

/*──────────────────────────────────────────────────────────────────────────*/

/*--------------------------------------------------------------------------*/
extern	S_PART_FLOW	*GetFirstFlowDispo( void ) ;
/*--------------------------------------------------------------------------*/
extern	void	RazListPartFlow( ) ;
/*--------------------------------------------------------------------------*/
extern	uint32_t	InitPartFlow( ) ;
/*--------------------------------------------------------------------------*/
extern	void	FreePartFlow( ) ;
/*--------------------------------------------------------------------------*/
extern	uint32_t	CreateParticleFlow(	int32_t flag, int32_t owner, int32_t num_point,
				int32_t orgx, int32_t orgy, int32_t orgz,
				int32_t beta,
				int32_t num_flow  );

/*--------------------------------------------------------------------------*/
extern	uint32_t	CreateExtraParticleFlow(int32_t type, int32_t owner, int32_t num, int32_t num2,
				int32_t orgx, int32_t orgy, int32_t orgz,
				int32_t beta, int32_t num_flow, int32_t hitforce,
				int32_t scale, int32_t transparent, int32_t tempo ) ;

/*--------------------------------------------------------------------------*/
extern	int32_t	AffParticleFlow( S_PART_FLOW *ptrf ) ;

/*--------------------------------------------------------------------------*/
extern	int32_t	AnimParticleFlow( S_PART_FLOW *ptrf ) ;

/*--------------------------------------------------------------------------*/
extern	void	AnimAllFlow( ) ;
/*--------------------------------------------------------------------------*/
extern	void	AfficheAllFlow( ) ;
/*--------------------------------------------------------------------------*/

//-------------	FLOW_A.ASM

#ifdef __cplusplus
extern "C" {
#endif

/*──────────────────────────────────────────────────────────────────────────*/
extern	void	BoxFlow( int32_t x, int32_t y, int32_t coul ) ;

#pragma	aux	BoxFlow	"*"	\
		parm caller	[eax] [ebx] [ecx]

/*──────────────────────────────────────────────────────────────────────────*/
extern	void	ShadeBoxBlk(int32_t X0, int32_t Y0, int32_t X1, int32_t Y1, int32_t deccoul);

#pragma	aux	ShadeBoxBlk	"*"	\
		parm caller	[]	\
		modify [eax ecx edx]

/*──────────────────────────────────────────────────────────────────────────*/
extern	void	CopyBlockShade( int32_t x0, int32_t y0, int32_t x1, int32_t y1, uint8_t *src,
				int32_t xd, int32_t yd, uint8_t *dst, int32_t shade ) ;

#pragma	aux	CopyBlockShade	"*"	\
		parm caller	[edx] [ecx] [ebx] [eax] [esi] \
		modify		[edi]

/*──────────────────────────────────────────────────────────────────────────*/
#ifdef __cplusplus
}
#endif

#endif	// FLOW_H
/*──────────────────────────────────────────────────────────────────────────*/
