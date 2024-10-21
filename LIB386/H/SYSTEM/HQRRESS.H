//──────────────────────────────────────────────────────────────────────────
#ifndef	LIB_SYSTEM_HQRRESS
#define LIB_SYSTEM_HQRRESS

//──────────────────────────────────────────────────────────────────────────
#include <SYSTEM/LIMITS.H>

#include	<stdlib.h>

//──────────────────────────────────────────────────────────────────────────
#ifdef	__cplusplus
extern	"C"	{
#endif

//──────────────────────────────────────────────────────────────────────────
#pragma	pack(push, 4)

//──────────────────────────────────────────────────────────────────────────
typedef struct  {
                        int32_t		MaxSize	;
                        int32_t		FreeSize;
                        int32_t		MaxIndex;
                        int32_t		NbIndex	;
                        void		*Buffer	;
                        char		Name[ADELINE_MAX_PATH];
		}	T_HQR_HEADER 		;

//──────────────────────────────────────────────────────────────────────────
#pragma	pack(pop)

//──────────────────────────────────────────────────────────────────────────
typedef	void	(HQR_GET_CALLBACK)(char *hqrname, int32_t index);

//──────────────────────────────────────────────────────────────────────────
extern	HQR_GET_CALLBACK	*HQRGetErrorFunc;

#pragma	aux	HqrGetErrorFunc	"*"

//──────────────────────────────────────────────────────────────────────────
extern	HQR_GET_CALLBACK	*HQRGetDelFunc	;

#pragma	aux	HqrGetDelFunc	"*"

//──────────────────────────────────────────────────────────────────────────
extern	int32_t	HQR_Flag ;

//──────────────────────────────────────────────────────────────────────────
extern	T_HQR_HEADER	*HQR_Init_Ressource(	const char	*hqrname,
 						int32_t	maxsize,
						int32_t	maxrsrc		);

//──────────────────────────────────────────────────────────────────────────
#define			HQR_Lock_Ressource(header)

//──────────────────────────────────────────────────────────────────────────
extern	void		HQR_Reset_Ressource(	T_HQR_HEADER *header	);

//──────────────────────────────────────────────────────────────────────────
extern	int32_t		HQR_Change_Ressource(	T_HQR_HEADER *header,
						const char *newhqrname	);

//──────────────────────────────────────────────────────────────────────────
extern	void		HQR_Free_Ressource(	T_HQR_HEADER *header	);

//──────────────────────────────────────────────────────────────────────────
extern	void		*HQR_Get(		T_HQR_HEADER *header,
						int32_t index		);

//──────────────────────────────────────────────────────────────────────────
#ifdef	__cplusplus
}
#endif

//──────────────────────────────────────────────────────────────────────────
#endif//LIB_SYSTEM_HQRRESS

//──────────────────────────────────────────────────────────────────────────
