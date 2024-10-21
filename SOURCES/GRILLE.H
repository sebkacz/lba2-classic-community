#ifndef	GRILLE_H
#define	GRILLE_H

#ifdef __cplusplus
extern "C" {
#endif

// GRILLE_A.ASM

extern	uint8_t	CodeJeu			;
extern	int32_t	XMap, YMap, ZMap 	;
extern	int32_t	XScreen, YScreen	;
extern	PTR_uint8_t	BufCube       		;
extern	PTR_uint8_t	BufferMaskBrick 	;
extern	PTR_uint8_t	BufMap			;
extern	PTR_uint8_t	TabBlock		;
extern	PTR_uint8_t	BufferBrick	       	;

//-------------------------------------------------------------------
extern Func_WorldColBrick	WorldColBrick ;

//-------------------------------------------------------------------
extern uint8_t	WorldColBrickFull( int32_t xw, int32_t yw, int32_t zw, int32_t ymax ) ;

#pragma	aux     WorldColBrickFull	"*"	\
		parm caller []			\
		modify [eax ebx ecx edx]

//-------------------------------------------------------------------
extern uint8_t	WorldCodeBrick(    int32_t xw, int32_t yw, int32_t zw ) ;

#pragma aux	WorldCodeBrick	"*"			\
		parm caller	[eax] [ebx] [ecx]	\
		modify [edx]

//-------------------------------------------------------------------
extern uint8_t	GetBlockBrick(     int32_t xw, int32_t yw, int32_t zw ) ;

#pragma	aux	GetBlockBrick	"*"	\
		parm caller [] 		\
		modify [eax ecx edx]

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	uint8_t	GetWorldColBrickVisible( int32_t x, int32_t y, int32_t z ) ;

#pragma	aux     GetWorldColBrickVisible	"*"	\
		parm caller []			\
		modify [eax ecx edx]

//-------------------------------------------------------------------
extern	void	DecompColonne( uint8_t *pts, uint8_t *ptd  ) ;

#pragma	aux 	DecompColonne	"*"		\
		parm caller	[esi] [edi]	\
		modify [eax ecx edx]

//-------------------------------------------------------------------
extern	void	Map2Screen( int32_t x, int32_t y, int32_t z ) ;

#pragma	aux	Map2Screen	"*"			\
		parm caller	[eax] [ecx] [edx]	\
		modify exact [eax ebx edx]

//-------------------------------------------------------------------
extern	uint8_t	*GetAdrBlock( int32_t numblock ) ;

#pragma	aux 	GetAdrBlock	"*"	\
		parm caller	[ecx]	\
		modify exact [eax]

//-------------------------------------------------------------------

#ifdef __cplusplus
}
#endif

//-------------------------------------------------------------------
extern int32_t  LoadUsedBrick(void);

//-------------------------------------------------------------------
extern Func_InitGrille InitGrille ;

//-------------------------------------------------------------------
extern void FreeGrille(void);

//-------------------------------------------------------------------
extern uint8_t   *GetAdrColonneMap(int32_t x,int32_t z);
//-------------------------------------------------------------------
extern uint8_t   *GetAdrColonneCube(int32_t x,int32_t z);
//-------------------------------------------------------------------
extern Func_WorldColBrickVisible WorldColBrickVisible ;
//-------------------------------------------------------------------
extern Func_GetShadow GetShadow ;

//-------------------------------------------------------------------
extern Func_ProjectShadow ProjectShadow ;

//-------------------------------------------------------------------
extern uint32_t  CreateMaskGph(uint8_t *ptsrc,uint8_t *ptdst);

//-------------------------------------------------------------------
extern void CopyMapToCube(void);

//-------------------------------------------------------------------
extern void InitBufferCube(void);

//-------------------------------------------------------------------
extern void DrawOverBrick(int32_t xm,int32_t ym,int32_t zm);

//-------------------------------------------------------------------
extern void DrawOverBrick3(int32_t xm,int32_t ym,int32_t zm,int32_t ymax);

//-------------------------------------------------------------------
extern void DrawOverBrickCage(int32_t xm,int32_t ym,int32_t zm);

//-------------------------------------------------------------------
extern void AffBrickBlock(int32_t block,int32_t brick,int16_t x,int16_t y,int16_t z);

//-------------------------------------------------------------------
extern void AffGrille(void);

//-------------------------------------------------------------------
extern void AffBrickBlockColon(int32_t block,int32_t brick,int16_t x,int16_t y,int16_t z);

//-------------------------------------------------------------------
extern void AffGrilleOnly(void);

//-------------------------------------------------------------------
extern void AffBrickBlockOnly(int32_t block,int32_t brick,int16_t x,int16_t y,int16_t z);

//-------------------------------------------------------------------
extern void AffGrilleLabyrinthe(void);

//-------------------------------------------------------------------
extern void AffOneBrick(int32_t x,int32_t y,int32_t z);

//-------------------------------------------------------------------
extern void IncrustGrm(T_ZONE *ptrz);

//-------------------------------------------------------------------
extern void DesIncrustGrm(T_ZONE *ptrz);

//-------------------------------------------------------------------
extern void RedrawGRMs( void ) ;

//-------------------------------------------------------------------

#endif	// GRILLE_H
