;----------------------------------------------------------------------------
			.386P
			.MODEL FLAT, C

;----------------------------------------------------------------------------
			.DATA

;----------------------------------------------------------------------------
			EXTRN	C	TabOffLine:DWORD
			EXTRN	C	ClipXMin:DWORD
			EXTRN	C	ClipXMax:DWORD
			EXTRN	C	ClipYMin:DWORD
			EXTRN	C	ClipYMax:DWORD

;----------------------------------------------------------------------------
			.CODE

;----------------------------------------------------------------------------
			PUBLIC	C	CopyBlockIncrust

;----------------------------------------------------------------------------
;void	CopyBlockIncrust(int32_t x0, int32_t y0, int32_t x1, int32_t y1, void *src, int32_t xd, int32_t yd, void *dst)

;#pragma aux CopyBlockIncrust	"*"				\
;	parm caller	[eax] [ebx] [ecx] [edx] [esi]	\
;	modify		[edi]

CopyBlockIncrust	proc uses ebp,\
			xd:DWORD, yd:DWORD, dst:DWORD

			cmp	eax,[ClipXMax]
			jg	endcopy
			cmp	ebx,[ClipYMax]
			jg	endcopy

			mov	edi,[ClipXMin]

			sub	edi,eax
			jle	@@NoClipXMin

			mov	eax,[ClipXMin]
			add	[xd],edi
@@NoClipXMin:
			mov	edi,[ClipYMin]
			sub	edi,ebx
			jle	@@NoClipYMin

			mov	ebx,[ClipYMin]
			add	[yd],edi
@@NoClipYMin:
			mov	edi,[ClipXMax]
			cmp	ecx,edi
			jle	@@NoClipXMax
			mov	ecx,edi
@@NoClipXMax:
			mov	edi,[ClipYMax]
			cmp	edx,edi
			jle	@@NoClipYMax
			mov	edx,edi
@@NoClipYMax:
			sub	ecx, eax
			js	endcopy

			sub	edx, ebx
			js	endcopy

			mov	edi,[xd]
			cmp	edi,[ClipXMin]
			jl	endcopy
			cmp	edi,[ClipXMax]
			jg	endcopy

			mov	edi,[yd]
			cmp	edi,[ClipYMin]
			jl	endcopy
			cmp	edi,[ClipYMax]
			jg	endcopy


			mov	edi,[xd]
			add	edi,ecx
			sub	edi,[ClipXMax]
			jle	@@NoClipXMaxD
			sub	ecx,edi
			jle	endcopy
@@NoClipXMaxD:

			mov	edi,[yd]
			add	edi,edx
			sub	edi,[ClipYMax]
			jle	@@NoClipYMaxD
			sub	edx,edi
			jle	endcopy
@@NoClipYMaxD:


			add	esi, eax		; Offset Src
			mov	edi, dst

			mov	eax, yd
			add	edi, xd			; Offset Dst

			add	esi, TabOffLine[ebx*4]
			xor	ecx, -1

			add	edi, TabOffLine[eax*4]
			mov	ebp, TabOffLine[1*4]

			mov	ebx, ecx
			inc	edx                     ; Delta Y

			sub	esi, ebx
			sub	edi, ebx
nextline:
			mov	ecx, ebx
nextbyte:
			mov	al, [esi+ecx]

			test	al, al
			jz	skip

			mov	[edi+ecx], al
skip:			inc	ecx

			jnz	nextbyte

			add	esi, ebp
			add	edi, ebp

			dec	edx
			jnz	nextline
endcopy:
			ret

CopyBlockIncrust	endp

;----------------------------------------------------------------------------
;			The
       			End
