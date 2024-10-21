/*
				IMPACT.H

		   Gestion des impacts des projectiles

*/

#ifndef	IMPACT_H
#define	IMPACT_H

#ifdef	LBA_EDITOR
#define	PATH_IMPACT	"f:\\projet\\lba2\\datas\\impact\\"
#endif

#define	MAX_IMPACT_ENTITIES	20
#define	MAX_IMPACT		100

// Types d'entité

#define	IMP_NOP		-1
#define	IMP_END		0
#define	IMP_REM		1
#define	IMP_SAMPLE	2
#define	IMP_FLOW	3
#define	IMP_THROW	4
#define	IMP_THROW_POF	5
#define	IMP_THROW_OBJ	6
#define	IMP_SPRITE	7
#define	IMP_FLOW_SPRITE	8
#define	IMP_FLOW_OBJ	9
#define	IMP_FLOW_POF	10

#define	NB_IMP_COMMAND	11


#ifdef	LBA_EDITOR
// Pour précompiler les impacts

typedef struct {
	char name[10] ;
	uint8_t   *buf     ;
	} T_IMPACT ;

extern	uint32_t		NbImpacts ;
extern	T_IMPACT	ListImpact[MAX_IMPACT] ;
#else
//extern	T_HQR_HEADER	*HQR_Impact ;
extern	uint8_t	*BufferImpact ;
#endif

#ifdef	LBA_EDITOR
extern	int8_t	GetImpCommand( void ) ;
extern	int32_t	GetNumDef( char *pathdef, char *name ) ;
extern	int32_t	GetNumDefAddIfNot( char *pathdef, char *name, char *rem ) ;
extern	int32_t	CompileImpact( uint8_t *buffer ) ;
extern	uint8_t	*SearchImpact( char *name ) ;

#ifndef	COMPILATOR
extern	void	DoImpact( char *name, int32_t x, int32_t y, int32_t z, uint8_t owner ) ;
#endif
#else
extern	void   	DoImpact( int32_t num, int32_t x, int32_t y, int32_t z, uint8_t owner ) ;
#endif

#endif	// IMPACT_H
