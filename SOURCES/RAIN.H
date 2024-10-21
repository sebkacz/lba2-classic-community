#ifndef	RAIN_H
#define	RAIN_H

typedef	struct
{
	int32_t	XRain	;
	int32_t	YRain	;
	int32_t	ZRain	;
	int32_t	Timer	;
}	T_RAIN	;

/*--------------------------------------------------------------------------*/
extern void InitOneRain(T_RAIN *pt);
/*--------------------------------------------------------------------------*/
extern void InitRain(void);
/*--------------------------------------------------------------------------*/
extern void GereRain(void);
/*--------------------------------------------------------------------------*/
extern void ClearImpactRain(void) ;
/*--------------------------------------------------------------------------*/
extern void AffRain(void);
/*--------------------------------------------------------------------------*/

extern	int32_t	OldRealTime		;
extern	int32_t	DeltaRain		;
extern	uint32_t	RealTime		;
extern	int32_t	LastTimer		;

#endif	// RAIN_H
