//──────────────────────────────────────────────────────────────────────────
#ifdef	__cplusplus
extern	"C"	{
#endif

//──────────────────────────────────────────────────────────────────────────
extern	uint32_t	Old_PM15_Off	;
extern	uint32_t	Old_PM15_Sel	;

extern  uint32_t	Int15DataStart	;
extern  uint32_t	Int15DataEnd	;

extern  uint32_t	Int15CodeStart	;
extern  uint32_t	Int15CodeEnd	;

extern  volatile uint32_t	Int15Trans	;

//──────────────────────────────────────────────────────────────────────────
//extern	void	__interrupt	Int15Handler(void)	;

//#pragma	aux	Int15Handler	"*"

//──────────────────────────────────────────────────────────────────────────
extern	void	keyboard_cmd(uint8_t cmd)	;
/*
#pragma aux	keyboard_cmd	"*"	\
	parm	[ebx]			\
	modify	[eax ecx]
	*/
//──────────────────────────────────────────────────────────────────────────
extern	void	keyboard_write(uint8_t cmd)	;
/*
#pragma aux	keyboard_write	"*"	\
	parm	[ebx]			\
	modify	[eax ecx]*/

//──────────────────────────────────────────────────────────────────────────
extern	int32_t	keyboard_read()	;
/*
#pragma aux	keyboard_read	"*"	\
	modify	[eax ecx]*/

//──────────────────────────────────────────────────────────────────────────
#ifdef	__cplusplus
}
#endif

//──────────────────────────────────────────────────────────────────────────
