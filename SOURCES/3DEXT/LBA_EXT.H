/*══════════════════════════════════════════════════════════════════════════*/

// lbaext.h

/*──────────────────────────────────────────────────────────────────────────*/

#include <POLYGON/POLY.H>

int32_t	Min3( int32_t a, int32_t b, int32_t c ) ;
/*
#pragma aux	Min3=					\
		"cmp	eax, edx"			\
		"jge	m0"				\
		"cmp	eax, ecx"			\
		"jl	mex"				\
		"jmp	m1"				\
	"m0:"						\
		"mov	eax, edx"			\
		"cmp	eax, ecx"			\
		"jl	mex"				\
	"m1:"						\
		"mov	eax, ecx"			\
	"mex:"						\
		parm caller [eax] [edx] [ecx]		\
		modify exact [eax]
*/
int32_t	Max3( int32_t a, int32_t b, int32_t c ) ;
/*
#pragma aux	Max3=					\
		"cmp	eax, edx"			\
		"jle	m0"				\
		"cmp	eax, ecx"			\
		"jg	mex"				\
		"jmp	m1"				\
	"m0:"						\
		"mov	eax, edx"			\
		"cmp	eax, ecx"			\
		"jg	mex"				\
	"m1:"						\
		"mov	eax, ecx"			\
	"mex:"						\
		parm caller [eax] [edx] [ecx]		\
		modify exact [eax]
*/
// maxima

#define	MAX_OBJ_DECORS		200

#define	NB_COTE		 	64
#define	SIZE_MAIN_MAP		16

#define	MAX_CUBES_PER_ISLE	20	// desert

// cube infos
#define		INFO_ALPHA_LIGHT	0
#define		INFO_BETA_LIGHT		1
#define		INFO_NB_DECORS		2
#define		INFO_SKY_Y		3
#define		INFO_START_Z_FOG	4
#define		INFO_CLIP_Z_FAR		5
#define		INFO_OFFSET_ANI_POLY_1	6
#define		INFO_OFFSET_ANI_POLY_2	7
#define		INFO_OFFSET_ANI_POLY_3	8
#define		INFO_OFFSET_ANI_POLY_4	9

#define		SIZE_CUBE_INFOS		10

/*──────────────────────────────────────────────────────────────────────────*/
//                              CODES JEU

#define CJ_WATER                1       // eau
#define CJ_ELECTRIC             2       // Pseudo électrifié (mort instantanée)
#define CJ_ESCALATOR_OUEST      3       // Tapis roulant OUEST
#define CJ_ESCALATOR_EST        4       // Tapis roulant EST
#define CJ_ESCALATOR_NORD       5       // Tapis roulant NORD
#define CJ_ESCALATOR_SUD        6       // Tapis roulant SUD
#define	CJ_LABYRINTHE		7	// Pseudo visible seulement sous
					// les pieds de l'objet
#define	CJ_POS_INVALID		8	// Position non valide
#define	CJ_LAVE			9	// psshhht !
#define	CJ_GAZ			11	// prout !
#define	CJ_FOOT_WATER		12	// Eau où l'on a pied
#define	CJ_ANIMATED_LAVE	13
#define	CJ_ANIMATED_GAZ		14

/*──────────────────────────────────────────────────────────────────────────*/

// structure d'un element du decors
typedef struct {

		int32_t	Body	;		//
		int32_t	Xworld	;		//
		int32_t	Yworld	;        	// position dans le monde
		int32_t	Zworld	;	      	//
		int32_t	CodeJeu	;	      	// CodeJeu uint8_t
		int32_t	Beta	;		// direction de l'objet

		int32_t	XMin ;			// ZV
		int32_t	YMin ;
		int32_t	ZMin ;
		int32_t	XMax ;
		int32_t	YMax ;
		int32_t	ZMax ;

		}	T_DECORS ;

// structure d'un masque
// ATTENTION : Structure utilisée en ASM dans MASQUE_A.ASM (donc à modifier
// 	       aussi !)

// structure tempo de rotation/tri
typedef struct {

		int32_t	Zrot;
		int16_t	X2D;	// old int32_t
		int16_t	Y2D;	// old int32_t

		} 	T_SOMMET_ROT;

//========== Flags pour les objets du decors (champ Body&0xFFFF0000 )

#define	DEC_INVISIBLE	(1<<16)	// objet invisible (sorte de GRM)
#define	DEC_DRAWN	(1<<17)	// objet affiché à l'ecran

typedef struct {
		int32_t	Zrot ;

		T_DECORS *PtrDec ;	// ca prend la meme place que Num
					// et c'est plus rapide dans les
					// boucles !
		int32_t	Num ;

		int32_t	NumMasque ;		// numero eventuel d'un masque écran

		}	T_LIST_TRI ;

//****************************************************************************
// structure map poly mode jeu ( 32 Bits)
typedef	struct	{

		uint32_t	Bank		:4 ;	// coul bank poly
		uint32_t	TexFlag		:2 ;	// flag texture 00 rien 01 triste 10 flat 11 gouraud
		uint32_t	PolyFlag	:2 ;	// flag poly 00 rien 01 flat 10 gouraud 11 dither
		uint32_t	SampleStep	:4 ;	// sample pas twinsen
		uint32_t	CodeJeu		:4 ;	// code jeu
		uint32_t	Sens		:1 ;	// sens diagonale
		uint32_t	Col		:1 ;
		uint32_t	Dummy		:1 ;
		uint32_t	IndexTex	:13 ;	// index texture 8192

		}	T_HALF_POLY ;		// 1 long

typedef struct	{

		uint16_t	Tx0 ;
		uint16_t	Ty0 ;
		uint16_t	Tx1 ;
		uint16_t	Ty1 ;
		uint16_t	Tx2 ;
		uint16_t	Ty2 ;

		}	T_HALF_TEX ;		// 2 Longs


//****************************************************************************
// animated sea

typedef	struct	{

		Struc_Point	Tab_Points[3] ;

		uint8_t	Type ;
		uint8_t	Color ;

		int16_t	Fog ;

		int16_t	X0 ;
		int16_t	Y0 ;

		int16_t	X1 ;
		int16_t	Y1 ;


		}	S_ANI_POLY ;


//****************************************************************************
