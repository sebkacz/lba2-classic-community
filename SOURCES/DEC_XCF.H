#ifdef __cplusplus
extern "C" {
#endif

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
extern	PTR_VOID	XCF_BaseOldScr	;
extern	PTR_VOID	XCF_BaseNewScr	;
extern	PTR_VOID	XCF_BaseData	;

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
void	XCF_InitDecompressor();

#pragma	aux	XCF_InitDecompressor	"*"	\
		parm caller []			\
		modify [eax ecx edx]

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
void	XCF_DecompressorHeight(uint32_t height);

#pragma	aux	XCF_DecompressorHeight	"*"	\
		parm caller []			\
		modify [eax ecx edx]

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
void	XCF_Decompressor();

#pragma	aux	XCF_Decompressor	"*"	\
		parm caller []			\
		modify [eax ecx edx]

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀

typedef	struct
	{
		uint32_t	struct_size	;
		uint32_t	DeltaX		;
		uint32_t	DeltaY		;
		uint32_t	FrameSize	;
		uint32_t	KeySize		;
		uint32_t	KeyRate		;
		uint32_t	PlayRate	;

		uint32_t	SamplingRate	;
		uint32_t	SampleType	;
		uint32_t	SampleFlags	;

		uint32_t	Compressor	;
	}	FORMAT;

#ifdef __cplusplus
}
#endif
