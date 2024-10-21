#ifndef	PATCH_H
#define	PATCH_H

typedef struct {
	int16_t	Size	;
	int16_t	Offset	;
	} T_PATCH ;

#define	MAX_PATCHES        500

#ifdef	COMPILATOR
extern	int32_t	MaxPatches  	;
extern	T_PATCH	ListPatches[MAX_PATCHES] ;
#else
extern	T_PATCH *ListPatches ;
#endif

extern	int32_t	NbPatches  ;

#ifdef	COMPILATOR
//─────────────────────────────────────────────────────────────────────────────
extern	void	AddPatch( int16_t size, int16_t offset ) ;
#else
//─────────────────────────────────────────────────────────────────────────────
extern	void	SetPatches( void ) ;
#endif	// COMPILATOR

#endif	// PATCH_H
