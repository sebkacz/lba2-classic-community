;----------------------------------------------------------------------------
;				S_LINE.ASM 386
;			      (c) Adeline 1993-96
;----------------------------------------------------------------------------
			.386
			.MODEL FLAT, C


			INCLUDE	FILLER.INC


;----------------------------------------------------------------------------
			.DATA

;----------------------------------------------------------------------------
RAIN_RANGE		=	200

;----------------------------------------------------------------------------
			extrn	C	ScreenXMin:	DWORD
			extrn	C	ScreenYMin:	DWORD
			extrn	C	ScreenXMax:	DWORD
			extrn	C	ScreenYMax:	DWORD

;----------------------------------------------------------------------------
extrn	C 	ClipXMin		:	DWORD
extrn	C 	ClipYMin		:	DWORD
extrn	C 	ClipXMax		:	DWORD
extrn	C 	ClipYMax		:	DWORD
extrn	C 	Log			:	DWORD
extrn	C 	PtrZBuffer		:	DWORD
extrn	C 	PTR_TabOffLine		:	DWORD
extrn	C 	ScreenPitch		:	DWORD
Extrn	C		Fill_Flag_Fog		:	BYTE
Extrn	C		Fill_Flag_ZBuffer	:	BYTE
Extrn	C	  	Fill_Logical_Palette	:	BYTE

;----------------------------------------------------------------------------
CurrentZ1		dd	0			; For the ZBuffer
CurrentZ2		dd	0
DZ	       		dd	0
Color	       		db	0

; Runtime code patch refactor, uses memory instead of instruction substitution
YPtrZBuf    DWORD 12345678h
YPtrLog     DWORD 12345678h
PtrLog      DWORD 12345678h
PtrZBuf     DWORD 12345678h
DELTA_Y     DWORD 12345678h
DELTA_X     DWORD 12345678h
DELTA_X1    DWORD 12345678h
Line        DWORD 12345678h
Col         DWORD 12345678h
DELTA_Z     DWORD 12345678h
IZ          DWORD 12345678h
YDELTA_X    DWORD 12345678h
YDELTA_Y    DWORD 12345678h
YDELTA_Y1   DWORD 12345678h
Col2        DWORD 12345678h
Line2       DWORD 12345678h
YDELTA_Z    DWORD 12345678h
YIZ         DWORD 12345678h

;----------------------------------------------------------------------------
			.CODE

;----------------------------------------------------------------------------
			public	C	LineRain

;----------------------------------------------------------------------------
; ╔════════════════════════════════════════════════════════════════════════╗
; ║   Trace de droite Zbuffer (methode toute con (Lucas)) No ZBuf write    ║
; ╟────────────────────────────────────────────────────────────────────────╢
; ║ Appel : (EAX,EBX), (ECX,EDX) : points extremes                         ║
; ║         STACK= Color                                                   ║
; ║         EDI  = CurrentZ1                                               ║
; ║         ESI  = CurrentZ2                                               ║
; ║			; Return value: bit field                          ║
; ║			;		0 : line not displayed             ║
; ║			;		1 : line at least partially visible║
; ║			;		2 : line intersects the background ║
; ╚════════════════════════════════════════════════════════════════════════╝

;int32_t	LineRain(int32_t x0, int32_t y0, int32_t z0, int32_t x1, int32_t y1, int32_t z1, int32_t coul );

;#pragma aux LineRain	"*"				\
;	parm caller [eax] [ebx] [edi] [ecx] [edx] [esi]

			ALIGN	4
LineRain		PROC \
			uses ebx ecx edx edi esi ebp\
			x0: DWORD, y0: DWORD, z0: DWORD, x1: DWORD, y1: DWORD, z1: DWORD, coul:DWORD

			mov eax, x0
			mov ebx, y0
			mov edi, z0
			mov ecx, x1
			mov edx, y1
			mov esi, z1

x:
			shl	esi,16
			push	ebp
			shl	edi,16
			mov	ebp, coul

			mov	[CurrentZ2],esi
			mov	[CurrentZ1],edi
			push	eax
			mov	eax,ebp
			and	ebp,0FFh
			cmp	[Fill_Flag_Fog],TRUE
			jne	Pas_Coul_Convert
			mov	al,[Fill_Logical_Palette+ebp]
Pas_Coul_Convert:
			mov	[Color],al
			pop	eax

Trace_Still:
			mov	edi,[CurrentZ1]
			mov	esi,[CurrentZ2]

			sub	esi,edi
			mov	edi,ecx

			mov	[DZ],esi
			mov	esi,edx

			sub	edi,eax			; EDI = DELTA_X
			jz	DX_Nul

			sub	esi,ebx			; ESI = DELTA_Y
			jz	DY_Nul

			cmp	eax,[ClipXMin]
			jl	Clip_X0

			cmp	eax,[ClipXMax]
			jg	Clip_X1

			cmp	ecx,[ClipXMin]
			jl	Clip_X2

			cmp	ecx,[ClipXMax]
			jg	Clip_X3

			cmp	ebx,[ClipYMin]
			jl	Clip_Y0

			cmp	ebx,[ClipYMax]
			jg	Clip_Y1

			cmp	edx,[ClipYMin]
			jl	Clip_Y2

			cmp	edx,[ClipYMax]
			jg	Clip_Y3
Draw_Line:
			mov	[ScreenXMin],eax
			mov	[ScreenXMax],ecx

			mov	edi,ecx
			mov	ecx,1			; ECX = Incr_X

			sub	edi,eax
			jns	DeltaX_Pos

			neg	edi
			neg	ecx

			mov	[ScreenXMin],ecx
			mov	[ScreenXMax],eax
DeltaX_Pos:						; EDI = ABS(Delta_X)

			mov	[ScreenYMin],ebx
			mov	[ScreenYMax],edx

			mov	esi,edx
			mov	ebp,[ScreenPitch]	; EBP = Incr_Y

			sub	esi,ebx
			jns	DeltaY_Pos

			neg	esi
			neg	ebp

			mov	[ScreenYMin],edx
			mov	[ScreenYMax],ebx
DeltaY_Pos:						; ESI = ABS(Delta_Y)
			shl	ebx,2
			add	ebx,[PTR_TabOffLine]

			mov	ebx,[ebx]

			add	ebx,eax			; EBX = start offset

			cmp	edi,esi
			jb	Draw_Y

							; Delta_X > Delta_Y
			mov	[DELTA_Y],esi
			mov	[DELTA_X],edi
			mov	[DELTA_X1],edi

			mov	eax,[DZ]

			test	ecx,ecx
			jns	Pos1

			neg	eax
Pos1:
			mov	edx,eax			; compute Z gradient
			sar	edx,31
			idiv	edi

			mov	edx,eax
			shr	edx,31
			add	eax,edx

			mov	edx,eax
			shl	eax,16
			sar	edx,16
			mov	[DELTA_Z],eax
			mov	[IZ],edx

			mov	[Line],ebp
			mov	[Col],ecx

			mov	eax,[Log]
			mov	edx,[PtrZBuffer]
			mov	[PtrLog],eax
			mov	[PtrZBuf],edx


			mov	edx,edi
			mov	ebp,edi
			shr	edx,1

			xor	eax,eax
			mov	esi,[CurrentZ1]
			mov	edi,esi
			shl	esi,16
			mov	al,[Color]
			shr	edi,16

			sub	edi,RAIN_RANGE/2
			xor	ecx,ecx

			jmp	$+2
Do_X:
			push eax
			mov eax,[PtrZBuf]
			mov	cx,[ebx*2+eax]
			pop eax

			sub	ecx,edi
			js	NoDisp

;			cmp	esi,RAIN_RANGE
			cmp	ecx,RAIN_RANGE
			jge	Disp

			or	ah,2
Disp:
			or	ah,1
			push ecx
			mov ecx,[PtrLog]
			mov	[ebx+ecx],al
			pop ecx
NoDisp:
			add	edx,[DELTA_Y]

			cmp	edx,[DELTA_X]
			jb	Plot_X

			sub	edx,[DELTA_X1]
			add	ebx,[Line]
Plot_X:
			add	ebx,[Col]
			xor	ecx,ecx

			add	esi,[DELTA_Z]
			adc	edi,[IZ]

			dec	ebp
			jge	Do_X

			shr	eax,8
			pop	ebp

			ret
Draw_Y:
			mov	[YDELTA_X],edi
			mov	[YDELTA_Y],esi
			mov	[YDELTA_Y1],esi

			mov	eax,[DZ]

			test	ebp,ebp
			jns	Pos2

			neg	eax
Pos2:
			mov	edx,eax
			sar	edx,31
			idiv	esi

			mov	edx,eax
			shr	edx,31
			add	eax,edx

			mov	edx,eax
			shl	eax,16
			sar	edx,16
			mov	[YDELTA_Z],eax
			mov	[YIZ],edx

			mov	[Col2],ecx
			mov	[Line2],ebp

			mov	eax,[Log]
			mov	edx,[PtrZBuffer]
			mov	[YPtrLog],eax
			mov	[YPtrZBuf],edx

			mov	edx,esi
			mov	ecx,esi
			shr	edx,1

			mov	esi,[CurrentZ1]
			xor	eax,eax
			mov	edi,esi
			mov	al,[Color]
			shl	esi,16
			shr	edi,16

			sub	edi,RAIN_RANGE/2
			xor	ebp,ebp

			jmp	$+2
Do_Y:
			push eax
			mov eax,[YPtrZBuf]
			mov	bp,[ebx*2+eax]
			pop eax

			sub	ebp,edi
			js	YNoDisp

			cmp	ebp,RAIN_RANGE
			jge	YDisp

			or	ah,2
YDisp:
			or	ah,1
			push ecx
			mov ecx,[YPtrLog]
			mov	[ebx+ecx],al
			pop ecx
YNoDisp:
			add	edx,[YDELTA_X]

			cmp	edx,[YDELTA_Y]
			jb	Plot_Y

			sub	edx,[YDELTA_Y1]
			add	ebx,[Col2]
Plot_Y:
			add	ebx,[Line2]
			xor	ebp,ebp

			add	esi,[YDELTA_Z]
			adc	edi,[YIZ]

			dec	ecx
			jge	Do_Y

			shr	eax,8
			pop	ebp

			ret
Exit:
			mov	ebx,7FFFFFFFh
			xor	eax,eax

			mov	[ScreenXMin],ebx
			mov	[ScreenYMin],ebx

			inc	ebx
			pop	ebp

			mov	[ScreenXMax],ebx
			mov	[ScreenYMax],ebx

			ret

Clip_X0:						; Case X1<XMin
			cmp	ecx,[ClipXMin]
			jl	Exit

			push	edx
			sub	eax,[ClipXMin]

			push	eax

			imul	[DZ]
			idiv	edi

			sub	[CurrentZ1],eax		; z1-=(x1-XMin)*dz/dx
			pop	eax

			imul	esi
			idiv	edi

			sub	ebx,eax			; y1-=(x1-XMin)*dy/dx
			mov	eax,[ClipXMin]		; x1 = ClipXMin

			pop	edx
			jmp	Trace_Still
Clip_X1:						; Case X1>XMax
			cmp	ecx,[ClipXMax]
			jg	Exit

			push	edx
			sub	eax,[ClipXMax]

			push	eax

			imul	[DZ]
			idiv	edi

			sub	[CurrentZ1],eax		; z1-=(x1-XMax)*dz/dx
			pop	eax

			imul	esi
			idiv	edi

			sub	ebx,eax			; y1-=(x1-XMax)*dy/dx
			pop	edx

			mov	eax,[ClipXMax]		; x1 = ClipXMax
			jmp	Trace_Still

Clip_X2:						; Case X2<XMin
			push	eax
			push	edx

			mov	eax,ecx
			sub	eax,[ClipXMin]

			push	eax

			imul	[DZ]
			idiv	edi

			sub	[CurrentZ2],eax		; z2-=(x2-XMin)*dz/dx
			pop	eax

			imul	esi
			idiv	edi

			pop	edx
			mov	ecx,[ClipXMin]		; x2 = ClipXMin

			sub	edx,eax			; y2-=(x2-XMin)*dy/dx
			pop	eax

			jmp	Trace_Still

Clip_X3:						; Case X2>XMax
			push	eax
			mov	eax,ecx

			push	edx
			sub	eax,[ClipXMax]

			push	eax

			imul	[DZ]
			idiv	edi

			sub	[CurrentZ2],eax		; z2-=(x2-XMax)*dz/dx
			pop	eax

			imul	esi
			idiv	edi

			pop	edx
			mov	ecx,[ClipXMax]		; x2 = ClipXMax

			sub	edx,eax			; y2-=(x2-XMax)*dy/dx
			pop	eax

			jmp	Trace_Still

Clip_Y0:						; Case Y1<YMin
			cmp	edx,[ClipYMin]
			jl	Exit

			push	edx
			push	eax

			mov	eax,ebx

			sub	eax,[ClipYMin]

			push	eax

			imul	[DZ]
			idiv	esi

			sub	[CurrentZ1],eax		; z1-=(y1-YMin)*dz/dy
			pop	eax

			imul	edi
			idiv	esi

			mov	edx,eax
			pop	eax

			sub	eax,edx			; x1-=(y1-YMin)*dz/dy
			mov	ebx,[ClipYMin]		; y1 = ClipYMin

			pop	edx
			jmp	Trace_Still

Clip_Y1:						; Case Y1>YMax
			cmp	edx,[ClipYMax]
			jg	Exit

			push	edx
			push	eax

			mov	eax,ebx

			sub	eax,[ClipYMax]

			push	eax

			imul	[DZ]
			idiv	esi

			sub	[CurrentZ1],eax		; z1-=(y1-YMax)*dz/dy
			pop	eax

			imul	edi
			idiv	esi

			mov	edx,eax
			pop	eax

			sub	eax,edx			; x1-=(y1-YMax)*dz/dy
			mov	ebx,[ClipYMax]		; y1 = ClipYMax

			pop	edx
			jmp	Trace_Still

Clip_Y2:						; Case Y2<YMin
			push	eax
			mov	eax,edx

			sub	eax,[ClipYMin]

			push	eax

			imul	[DZ]
			idiv	esi

			sub	[CurrentZ2],eax		; z2-=(y2-YMin)*dz/dy
			pop	eax

			imul	edi
			idiv	esi

			sub	ecx,eax			; x2-=(y2-YMin)*dz/dy
			mov	edx,[ClipYMin]		; y2 = ClipYMin

			pop	eax
			jmp	Trace_Still

Clip_Y3:						; Case Y2>YMax
			push	eax
			mov	eax,edx

			sub	eax,[ClipYMax]

			push	eax

			imul	[DZ]
			idiv	esi

			sub	[CurrentZ2],eax		; z2-=(y2-YMax)*dz/dy
			pop	eax

			imul	edi
			idiv	esi

			sub	ecx,eax			; x2-=(y2-YMax)*dz/dy
			mov	edx,[ClipYMax]		; y2 = ClipYMax

			pop	eax
			jmp	Trace_Still

							; *** DeltaX nul ***
DX_Nul:
			cmp	eax,[ClipXMin]
			jl	Exit
			cmp	eax,[ClipXMax]
			jg	Exit

			sub	esi,ebx			; ESI = DELTA_Y
			jz	Plot

			cmp	ebx,[ClipYMin]
			jge	DX_Y1
			cmp	edx,[ClipYMin]
			jl	Exit

			push	edx
			push	eax

			mov	eax,ebx
			sub	eax,[ClipYMin]

			imul	[DZ]
			idiv	esi

			sub	[CurrentZ1],eax		; z1-=(y1-YMin)*dz/dy
			pop	eax

			pop	edx
			mov	ebx,[ClipYMin]		; y1 = YMin

			mov	esi,edx

			sub	esi,ebx			; ESI = DELTA_Y
			jz	Plot

DX_Y1:
			cmp	ebx,[ClipYMax]
			jle	DX_Y1b
			cmp	edx,[ClipYMax]
			jg	Exit

			push	edx
			push	eax

			mov	eax,ebx
			sub	eax,[ClipYMax]

			imul	[DZ]
			idiv	esi

			sub	[CurrentZ1],eax		; z1-=(y1-YMax)*dz/dy
			pop	eax

			pop	edx
			mov	ebx,[ClipYMax]		; y1 = YMax

			mov	esi,edx

			sub	esi,ebx			; ESI = DELTA_Y
			jz	Plot
DX_Y1b:
			cmp	edx,[ClipYMin]
			jge	DX_Y2

			push	eax
			mov	eax,edx

			sub	eax,[ClipYMin]

			imul	[DZ]
			idiv	esi

			sub	[CurrentZ2],eax		; z2-=(y2-YMin)*dz/dy
			mov	edx,[ClipYMin]		; y2 = YMin

			pop	eax
			mov	esi,edx

			sub	esi,ebx			; ESI = DELTA_Y
			jz	Plot
DX_Y2:
			cmp	edx,[ClipYMax]
			jle	Draw_Line

			push	eax
			mov	eax,edx

			sub	eax,[ClipYMax]

			imul	[DZ]
			idiv	esi

			sub	[CurrentZ2],eax		; z2-=(y2-YMax)*dz/dy
			mov	edx,[ClipYMax]		; y2 = YMax

			mov	esi,edx
			pop	eax

			sub	esi,ebx			; ESI = DELTA_Y
			jnz	Draw_Line

			jmp	Plot
							; *** DeltaY nul ***
DY_Nul:
			cmp	ebx,[ClipYMin]
			jl	Exit
			cmp	ebx,[ClipYMax]
			jg	Exit

			cmp	eax,[ClipXMin]
			jge	DY_X1
			cmp	ecx,[ClipXMin]
			jl	Exit

			push	edx
			sub	eax,[ClipXMin]

			imul	[DZ]
			idiv	edi

			sub	[CurrentZ1],eax		; z1-=(x1-XMin)*dz/dx
			mov	edi,ecx

			mov	eax,[ClipXMin]		; x1 = XMin
			pop	edx

			sub	edi,eax
			jz	Plot

DY_X1:
			cmp	eax,[ClipXMax]
			jle	DY_X1b
			cmp	ecx,[ClipXMin]
			jg	Exit

			push	edx
			sub	eax,[ClipXMax]

			imul	[DZ]
			idiv	edi

			sub	[CurrentZ1],eax		; z1-=(x1-XMax)*dz/dx
			mov	edi,ecx

			mov	eax,[ClipXMax]		; x1 = XMax
			pop	edx

			sub	edi,eax
			jz	Plot
DY_X1b:

			cmp	ecx,[ClipXMin]
			jge	DY_X2

			push	eax
			mov	eax,ecx

			push	edx
			sub	eax,[ClipXMin]

			imul	[DZ]
			idiv	edi

			sub	[CurrentZ2],eax		; z2-=(x2-XMin)*dz/dx
			mov	ecx,[ClipXMin]		; x2 = XMin

			pop	edx
			mov	edi,ecx

			pop	eax

			sub	edi,eax
			jz	Plot
DY_X2:
			cmp	ecx,[ClipXMax]
			jle	Draw_Line

			push	eax
			mov	eax,ecx

			push	edx
			sub	eax,[ClipXMax]

			imul	[DZ]
			idiv	edi

			sub	[CurrentZ2],eax		; z2-=(x2-XMax)*dz/dx
			mov	ecx,[ClipXMax]		; x2 = XMax

			pop	edx
			mov	edi,ecx

			pop	eax

			sub	edi,eax
			jnz	Draw_Line
							; *** Plot ***
Plot:
			cmp	ebx,[ClipYMin]
			jl	Exit
			cmp	ebx,[ClipYMax]
			jg	Exit
			cmp	eax,[ClipXMin]
			jl	Exit
			cmp	eax,[ClipXMax]
			jg	Exit

			mov	[ScreenXMin],eax
			mov	[ScreenYMin],ebx
			mov	[ScreenXMax],eax
			mov	[ScreenYMax],ebx

			shl	ebx,2
			mov	edi,[PTR_TabOffLine]

			add	ebx,edi
			mov	edi,[Log]

			mov	edx,[CurrentZ1]
			mov	esi,[PtrZBuffer]

			sar	edx,16
			mov	ebx,[ebx]

			add	ebx,eax			; EBX = start offset
			xor	eax,eax

			xor	ebp,ebp
			mov	al,[Color]

			mov	bp,word ptr[ebx*2+esi]
			sub	edx,RAIN_RANGE/2

			sub	ebp,edx
			js	Exit

			cmp	ebp,RAIN_RANGE
			jge	PlotDisp

			or	ah,2
PlotDisp:		mov	[ebx+edi],al

	        	or	ah,1
			pop	ebp

			shr	eax, 8

			ret

LineRain		ENDP

;			The
			End
