#ifndef	CREDITS_H
#define	CREDITS_H

typedef struct  {

	int32_t             NbObjects ;
	int32_t             OffTxt ;
	int32_t		OffXpl ;

		}       S_CRED_INFOS_2 ;


typedef struct {

						// reserve place pour player
	T_OBJ_3D	Obj ;			// lib struct
	BOUND_MOVE	RealAngle;		// synchro de la rotation

	int32_t		Flag ;
	int32_t		DestX ;
	int32_t		DestZ ;

	int32_t		OffBody ;		// offset
	int32_t		OffAnim[2] ;

	} S_CRED_OBJ_2 ;

extern	int32_t     GamePlayCredits( const char *file_name, int32_t mode ) ;

#endif	// CREDITS_H
