//****************************************************************************
#ifndef	LIB_SYSTEM_DEFFILE
#define	LIB_SYSTEM_DEFFILE

//****************************************************************************
#include	<SYSTEM/ITOA.H>

//****************************************************************************
#ifdef	__cplusplus
extern	"C"	{
#endif


//****************************************************************************
extern	char	*OrgPtrDef		;
extern	char	*EndPtrDef		;

//****************************************************************************
extern	int32_t	DefFileReadSkipComments	;

//****************************************************************************
int32_t	DefFileBufferInit(char *file, void *buffer, int32_t maxsize)	;

//****************************************************************************
char	*DefFileBufferReadString(const char *ident)				;

//****************************************************************************
const char *DefFileBufferReadStringDefault(const char *ident, const char *def)  ;

//****************************************************************************
int32_t	DefFileBufferReadValue(const char *ident)				;

//****************************************************************************
int32_t	DefFileBufferReadValueDefault(const char *ident, int32_t def)		;

//****************************************************************************
int32_t	DefFileBufferReadValue2(const char *ident, int32_t *result)		;

//****************************************************************************
int32_t	DefFileBufferWriteString(const char *ident, const char *string)		;

//****************************************************************************
#define	DefFileBufferWriteValue(ident, value)			\
	DefFileBufferWriteString(ident, Itoa(value))

//****************************************************************************
#ifdef	__cplusplus
}
#endif

//****************************************************************************
#endif//LIB_SYSTEM_DEFFILE

//****************************************************************************

