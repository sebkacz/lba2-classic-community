//--------------------------------------------------------------------------
#ifndef BOXZBUF
#define BOXZBUF

//--------------------------------------------------------------------------
#ifdef	__cplusplus
extern	"C"	{
#endif

extern	int32_t	ZBufBoxOverWrite2(int32_t z0, int32_t z1,
				  int32_t xmin, int32_t ymin,
				  int32_t xmax, int32_t ymax
				 );
/*
#pragma aux	ZBufBoxOverWrite2	"*"				\
		parm caller	[edi] [esi] [ecx] [edx] [ebx] [eax]
*/
//--------------------------------------------------------------------------
#ifdef	__cplusplus
}
#endif

//--------------------------------------------------------------------------
#endif//BOXZBUF

//--------------------------------------------------------------------------
