#ifdef __cplusplus
extern "C" {
#endif

extern	uint8_t	*BaseOldScr	;
extern	uint8_t	*BaseNewScr	;
extern	uint8_t	*BaseData	;

extern	uint8_t	Patch_MaxLine[]	;
extern	uint8_t	Patch_CodeLen[]	;

#define	Dec_MaxLine	Patch_MaxLine[1]
#define	Dec_CodeLen	*(uint32_t *)(&Patch_CodeLen[2])

#define DecompressorHeight(a)					\
{                                                               \
	Dec_MaxLine = (uint8_t)(a/8-1)                  ;		\
	Dec_CodeLen = ((a/8)*(MAX_WIDTH/8)*6)/8+4  ;		\
}

void	Decompressor( void )		;
void	InitDecompressor( void )	;

#ifdef __cplusplus
}
#endif
