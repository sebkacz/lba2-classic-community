;*══════════════════════════════════════════════════════════════════════════*

		.386p

		.model SMALL, C


;*══════════════════════════════════════════════════════════════════════════*
		.DATA

		extrn	C MatrixLib2:DWORD
		extrn	C InitMatrixStd:DWORD
		extrn	C LongRotatePoint:DWORD

		ASSUME  DS:SEG LongRotatePoint

;*══════════════════════════════════════════════════════════════════════════*
		.CODE

;*══════════════════════════════════════════════════════════════════════════*

		public	C	RotateVector

;*══════════════════════════════════════════════════════════════════════════*

;*══════════════════════════════════════════════════════════════════════════*
;void RotateVector(int32_t norme, int32_t alpha, int32_t beta, int32_t gamma)	;

;#pragma aux RotateVector			\
;	parm		[edx] [eax] [ebx] [ecx]	\
;	modify		[esi edi]

RotateVector	proc

		mov	edi, offset MatrixLib2
		push	edx

		call	[InitMatrixStd]

		pop	ecx
		xor	eax, eax
		xor	ebx, ebx
		mov	esi, offset MatrixLib2

		jmp	[LongRotatePoint]

RotateVector	endp

;*══════════════════════════════════════════════════════════════════════════*
;		The
		END

