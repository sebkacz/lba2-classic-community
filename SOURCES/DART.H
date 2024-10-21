/*══════════════════════════════════════════════════════════════════════════*
	  █▀▀▀▀ █     █▀▀▀▀ █▀▀▀▀ █   █ █▀▀▀▀ ▀▀█▀▀ ▀▀█▀▀ █▀▀▀▀ ██▀▀▀
	  ██▀▀  ██    ██▀▀  ██    ██▀▀█ ██▀▀    ██    ██  ██▀▀  ▀▀▀▀█
	  ▀▀    ▀▀▀▀▀ ▀▀▀▀▀ ▀▀▀▀▀ ▀▀  ▀ ▀▀▀▀▀   ▀▀    ▀▀  ▀▀▀▀▀ ▀▀▀▀▀
 *══════════════════════════════════════════════════════════════════════════*/
/*──────────────────────────────────────────────────────────────────────────*/

#ifndef	COMPILATOR

#ifndef	DART_H
#define	DART_H

#define	MAX_DARTS	3

#ifdef	LBA_EDITOR
//#define	BODY_3D_DART    "F:\\projet\\lba2\\graphn\\3D\\throw\\dart.O4D"
#define	BODY_3D_DART    "F:\\projet\\lba2\\graph\\3D\\throw\\dart.O4D"
#else
#define	BODY_3D_DART	61	// f:\projet\lba2\graph\3d\objfix.lst
#endif

typedef struct
{
//	T_OBJ_3D	Obj ;		// Structure de l'objet
	int32_t		PosX;
	int32_t		PosY ;
	int32_t		PosZ ;
	int32_t		Alpha ;
	int32_t		Beta ;
	int32_t		Body ;
	int32_t		NumCube ;	// Numéro du cube dans lequel se trouve la fléchette
	uint32_t		Flags	;

	int32_t		XMin	;	// ZV des flechettes
	int32_t		YMin	;
	int32_t		ZMin	;
	int32_t		XMax	;
	int32_t		YMax	;
	int32_t		ZMax	;
} T_DART ;

// Flags des flechettes
#define	DART_TAKEN      (1<<0)

// Fonctions des flechettes (DART.CPP)
/*--------------------------------------------------------------------------*/
extern	void	InitDarts( void ) 	;
/*--------------------------------------------------------------------------*/
extern	int32_t	GetDart( void )		;
/*--------------------------------------------------------------------------*/
extern	void	TakeAllDarts( void )	;
/*--------------------------------------------------------------------------*/
extern	void	CheckDartCol( T_OBJET *ptrobj )	;
/*--------------------------------------------------------------------------*/
#ifdef	LBA_EDITOR
extern	void	DrawZVDart( T_DART *ptrd ) ;
#endif
/*--------------------------------------------------------------------------*/

#endif	// DART_H

#endif	// COMPILATOR
