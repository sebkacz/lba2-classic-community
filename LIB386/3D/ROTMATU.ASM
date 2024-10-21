;*══════════════════════════════════════════════════════════════════════════*

		.386p

		.model SMALL, C

;*══════════════════════════════════════════════════════════════════════════*

		.DATA

		extrn	C	InitMatrixStd:DWORD
		extrn	C	CopyMatrix:DWORD
		extrn	C	MulMatrix:DWORD

		extrn	C	MatrixLib2:DWORD

		public	C	RotateMatrix

		RotateMatrix	dd	offset RotateMatrixU

		ASSUME  DS:SEG MatrixLib2

;*══════════════════════════════════════════════════════════════════════════*

		.CODE

		public	C	RotateMatrixU

;*══════════════════════════════════════════════════════════════════════════*
;void	RotateMatrixU(int32_t *MatDst, int32_t *MatSrc, int32_t alpha, int32_t beta, int32_t gamma) ;

;#pragma aux RotateMatrixU				\
;	parm		[edi] [esi] [eax] [ebx] [ecx]
;	modify exact	[eax ebx ecx edx esi]

RotateMatrixU	proc

		push	edi
		push	esi

		mov	edi, offset MatrixLib2	; because InitMatrixStd use MatrixLib1
		call	[InitMatrixStd]		; MatrixLib2 = Alpha * Gamma * Beta

		mov	ebx, edi
		pop	esi
		pop	edi

		jmp	[MulMatrix]		; MatDst = MatSrc * Alpha * Gamma * Beta

RotateMatrixU	endp

;*══════════════════════════════════════════════════════════════════════════*
;		The
		END
