;*══════════════════════════════════════════════════════════════════════════*

		.386p

		.model SMALL, C

		include MAT.INC

;*══════════════════════════════════════════════════════════════════════════*
		.DATA

		public	C	InitMatrixTrans

		InitMatrixTrans	dd	offset InitMatrixTransF

;*══════════════════════════════════════════════════════════════════════════*

		.CODE

		public	C	InitMatrixTransF

;*══════════════════════════════════════════════════════════════════════════*
;void	InitMatrixTransF(int32_t *MatDst, int32_t tx, int32_t ty, int32_t tz) ;

;#pragma aux InitMatrixTransF	"*"		\
;	parm		[edi] [eax] [ebx] [ecx]	\
;	modify exact	[]

InitMatrixTransF	PROC

		push	eax
		push	ebx

		push	ecx

		fild	dword ptr[esp]		; Z

		fild	dword ptr[esp+4]	; Y Z

		fild	dword ptr[esp+8]	; X Y Z

		add	esp, 4*3

		fstp	[edi].Struc_MatriceMAT.MAT_MTX

		fstp	[edi].Struc_MatriceMAT.MAT_MTY

		fstp	[edi].Struc_MatriceMAT.MAT_MTZ

		ret

InitMatrixTransF	ENDP

;*══════════════════════════════════════════════════════════════════════════*
;		The
		END
