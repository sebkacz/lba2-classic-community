#ifndef	PTRFUNC_H
#define	PTRFUNC_H

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
//
//		     Definition des types de pointeurs de fonction
//
//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
typedef	void	(Func_ReajustPos)( uint8_t col ) ;
/*
#pragma	aux	Arg_ReajustPos	"*"	\
		parm caller []		\
		modify [eax ecx edx]

#pragma	aux	(Arg_ReajustPos)	Func_ReajustPos
		*/
//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
typedef	void	(Func_GetShadow)( int32_t, int32_t, int32_t ) ;
/*
#pragma	aux	Arg_GetShadow	"*"	\
		parm caller []		\
		modify [eax ecx edx]

#pragma	aux	(Arg_GetShadow)		Func_GetShadow
		*/

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
typedef	void	(Func_DoAnim)( uint8_t ) ;
/*
#pragma	aux	Arg_DoAnim	"*"	\
		parm caller []		\
		modify [eax ecx edx]

#pragma	aux	(Arg_DoAnim)		Func_DoAnim
*/

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
typedef	uint8_t	(Func_WorldColBrick)( int32_t, int32_t, int32_t ) ;
/*
#pragma	aux	Arg_WorldColBrick	"*"	\
		parm caller []			\
		modify [eax ecx edx]

#pragma	aux	(Arg_WorldColBrick)		Func_WorldColBrick
		*/

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
typedef	uint8_t	(Func_WorldColBrickVisible)( int32_t, int32_t, int32_t, int32_t, int32_t, int32_t ) ;
/*
#pragma	aux	Arg_WorldColBrickVisible	"*"	\
		parm caller []				\
		modify [eax ecx edx]

#pragma	aux	(Arg_WorldColBrickVisible)	Func_WorldColBrickVisible
		*/

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
typedef	void	(Func_ReajustPosExtra)( T_EXTRA *, uint8_t, int16_t * ) ;
/*
#pragma	aux	Arg_ReajustPosExtra	"*"	\
		parm caller []			\
		modify [eax ecx edx]

#pragma	aux	(Arg_ReajustPosExtra)	Func_ReajustPosExtra
		*/

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
typedef	int32_t	(Func_TreeInsert)( int16_t numtype, int32_t posx, int32_t posy, int32_t posz,
				   int32_t txmin, int32_t tymin, int32_t tzmin,
				   int32_t txmax, int32_t tymax, int32_t tzmax ) ;
/*
#pragma	aux	Arg_TreeInsert		"*"	\
		parm caller []			\
		modify [eax ecx edx]

#pragma	aux	(Arg_TreeInsert)	Func_TreeInsert
		*/

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
typedef	void	(Func_Init3DView)( void ) ;
/*
#pragma	aux	Arg_Init3DView		"*"	\
		parm caller []			\
		modify [eax ecx edx]

#pragma	aux	(Arg_Init3DView)	Func_Init3DView
		*/

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
#ifdef	LBA_EDITOR
typedef	void	(Func_InitGrille)( char * ) ;
#else	// LBA_EDITOR
typedef	void	(Func_InitGrille)( uint32_t ) ;
#endif	// LBA_EDITOR
/*
#pragma	aux	Arg_InitGrille		"*"	\
		parm caller []			\
		modify [eax ecx edx]

#pragma	aux	(Arg_InitGrille)	Func_InitGrille
		*/

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
#ifndef	LBA_EDITOR
typedef	uint8_t	(Func_FullWorldColBrick)(int32_t,int32_t,int32_t,int32_t,int32_t,int32_t) ;
/*
#pragma	aux	Arg_FullWorldColBrick	"*"	\
		parm caller []			\
		modify [eax ecx edx]

#pragma	aux	(Arg_FullWorldColBrick)	Func_FullWorldColBrick
		*/
#endif	// LBA_EDITOR

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀

#endif	// PTRFUNC_H
