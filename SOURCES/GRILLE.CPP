#include	"C_EXTERN.H"
#include "DIRECTORIES.H"

#include <SVGA/SCREEN.H>

/*══════════════════════════════════════════════════════════════════════════*
		      █▀▀▀▀ █▀▀▀█  █    █     █     █▀▀▀▀
		      ██ ▀█ ██▀█▀  ██   ██    ██    ██▀▀
		      ▀▀▀▀▀ ▀▀  ▀  ▀▀   ▀▀▀▀▀ ▀▀▀▀▀ ▀▀▀▀▀
 *══════════════════════════════════════════════════════════════════════════*/
/*──────────────────────────────────────────────────────────────────────────*/

#define	HEADER_BLOCK	3

#define	DXBLOCK		0
#define	DYBLOCK		1
#define	DZBLOCK		2

extern	int32_t	XS0,YS0,XS1,YS1,XS2,YS2,XS3,YS3 ;	// bezier.c

/*-------------------------------------------------------------------------*/

int32_t	XpOrgw ;
int32_t	YpOrgw ;

#define	NB_COLON	28
#define	MAX_BRICK	150

int16_t	NbBrickColon[NB_COLON] ;

typedef	struct
{
	int16_t	Xm ;
	int16_t	Ym ;
	int16_t	Zm ;
	int16_t	Ys ;
	int16_t	Brick ;
	int16_t	Col ;

}	T_COLONB ;

T_COLONB	ListBrickColon[NB_COLON][MAX_BRICK] ;

uint8_t	*BufferMaskBrick ;
int32_t	NbBlock			;
int32_t	DxBlock, DyBlock, DzBlock;

int32_t	ForbidenBrick = 0 ;

extern	int32_t	Nxw, Nyw, Nzw ;
//void	ReajustPos( uint8_t col ) ;
/*--------------------------------------------------------------------------*/
typedef	struct
{
	uint16_t	Gri_Start		;//	Index of GRI
	uint16_t	Grm_Start		;//	Index of GRM
	uint16_t	Bll_Start		;//	Index of BLL
	uint16_t	Brk_Start		;//	Index of BRK
	uint16_t	Max_Brk			;//	Nb Brk
	uint16_t	ForbidenBrick		;//	NEW : Brick Interdite
	uint32_t	Max_Size_Gri		;//	Max Size Gri
	uint32_t	Max_Size_Bll		;//	Max Size Bll
	uint32_t	Max_Size_Brick_Cube	;//	Max Ideal Style Size
	uint32_t	Max_Size_Mask_Brick_Cube;//	Max Size Mask

} T_BKG_HEADER	;

T_BKG_HEADER	BkgHeader	;

typedef	struct
{
	uint8_t	My_Bll		;//	Index Style ( + Bll_Start )
	uint8_t	My_Grm		;//	Index Grm ( + Grm_Start )
	uint8_t	UsedBlock[32]	;//	Bluck Used in Bll ( Bits )

} T_GRI_HEADER	;

T_GRI_HEADER	*GriHeader	;
/*--------------------------------------------------------------------------*/
/*══════════════════════════════════════════════════════════════════════════*
	     █   █ █▀▀▀█ █▀▀▀█       █▀▀█  █▀▀▀█  █    █▀▀▀▀ █  ▄▀
	     ██▀▀█ ██ ▄█ ██▀█▀       ██▀▀█ ██▀█▀  ██   ██    ██▀▄
	     ▀▀  ▀ ▀▀▀▀  ▀▀  ▀ ▀▀▀▀▀ ▀▀▀▀▀ ▀▀  ▀  ▀▀   ▀▀▀▀▀ ▀▀  ▀
 *══════════════════════════════════════════════════════════════════════════*/
#define	MAX_BRICK_GAME		20000L
#define	OFFSET_BUFFER_FLAG	153800L

/*--------------------------------------------------------------------------*/
int32_t	LoadUsedBrick()
{
	uint32_t	i, j, b	;
	uint8_t	*pt	;
	uint8_t	*ptb	;
	uint16_t	*ptw	;
	uint32_t	*ptoff	;
	uint8_t	*ptdata	;
	uint32_t	offset	;
	uint32_t	maxbrk	;
	uint32_t	brick	;
	uint32_t	offseek	;
	uint32_t	*ptseek	;
	uint32_t	handle	;
	uint16_t	*tabflag;
	uint16_t	*ptflag	;
	uint32_t	min, max;
	uint8_t 	*ptdecomp ;
	COMPRESSED_HEADER header	;
	int32_t	nbbrick	;
        char tmpFilePath[ADELINE_MAX_PATH];

	tabflag = (uint16_t*)((uint8_t*)Screen+OFFSET_BUFFER_FLAG) ;

	memset( tabflag, 0, MAX_BRICK_GAME*2L )	;/* Table de uint16_t pour NewNumBrick */

	min = 60000			;
	max = 0				;

//-------------------------------------- Premiere Passe, Préparation ptflag

	pt = GriHeader->UsedBlock	;/* Debut de Used Block */

	nbbrick = 0			;

	for ( i = 1 ; i < 256 ; i++ )
	{
		b = pt[i>>3] & (1<<(7-(i&7)))	;/*	Recup Bit Block	*/
		if ( !b )	continue	;

		ptb = TabBlock + *(uint32_t *)(TabBlock+((i-1)<<2));
		ptw = (uint16_t *)(ptb + 5)	;/* Jump dx dy dz et collis */
		maxbrk = *ptb * *(ptb+1) * *(ptb+2)	;/* dx*dy*dz*/

		for ( j = 0 ; j < maxbrk ; j++, ptw += 2 )
		{
			brick = *ptw	;

			if ( brick )
			{
				brick--					;

				if ( brick < min )	min = brick	;
				if ( brick > max )	max = brick	;

				if ( tabflag[brick] == 0 )
				{
					nbbrick++		;
					tabflag[brick] = 1	;
				}
			}
		}
	}

//-------------------------------------- Deuxieme Passe, Load Brick

        GetResPath(tmpFilePath, ADELINE_MAX_PATH, BKG_HQR_NAME);
	handle = OpenRead( tmpFilePath )			;
	if ( !handle )	return(0L)			;

	Seek( handle, BkgHeader.Brk_Start<<2, SEEK_FROM_START);// Begin offsets Brk

	Read( handle, Screen, BkgHeader.Max_Brk<<2 )	;// Read Offsets Brk

	ptflag = tabflag+min		;

	ptoff = (uint32_t *)BufferBrick	;

	offset = (nbbrick+1)*4L		;

	*ptoff++ = offset		;/* First Offset        */

	ptdata = BufferBrick+offset	 ;/* Jump nbbrick+1 Offset	*/

	nbbrick = 0			;

	ptseek = (uint32_t *)Screen	;

	for ( i = min ; i <= max ; i++, ptflag++ )
	{
		if ( *ptflag )
		{
			nbbrick++		;/*	One More*/
			*ptflag = (int16_t)nbbrick	;/*	Brick+1, for BLL */
			offseek = *(ptseek+i)	;
			Seek( handle, offseek, SEEK_FROM_START ) 	;
			Read( handle, &header, sizeof(header))	;
			switch( header.CompressMethod )
			{
				case 0://	No compression
					Read( handle, ptdata, header.SizeFile )	;
					break			;
				case 1://	Compression LZSS
					ptdecomp = ptdata+header.SizeFile-header.CompressedSizeFile+500 ;
					Read( handle, ptdecomp, header.CompressedSizeFile )	;
//					ExpandLZSS( ptdecomp, ptdata, header.SizeFile )	;
					ExpandLZ( ptdata, ptdecomp, header.SizeFile, 2 )	;
					break		;
			}
			ptdata += header.SizeFile	;
			offset += header.SizeFile	;
			*ptoff++ = offset		;
		}
	}

//-------------------------------------- Troisieme passe, Rename Block

	pt = GriHeader->UsedBlock		;/* Debut de Used Block */

	for ( i = 1 ; i < 256 ; i++ )
	{
		b = pt[i>>3] & (1<<(7-(i&7)))	;/*	Recup Bit Block	*/
		if ( !b )	continue	;

		ptb = TabBlock + *(uint32_t *)(TabBlock+((i-1)<<2));
		ptw = (uint16_t *)(ptb + 5)			;/* Jump dx dy dz et collis */
		maxbrk = *ptb * *(ptb+1) * *(ptb+2)		;/* dx*dy*dz*/

		for ( j = 0 ; j < maxbrk ; j++, ptw += 2 )
		{
			if ( *ptw )	*ptw = tabflag[(*ptw)-1]	;
		}
	}

	Close(handle)	;

	ForbidenBrick = tabflag[BkgHeader.ForbidenBrick]	;

	return(offset)	;
}
/*-------------------------------------------------------------------------*/
void	InitGrille( uint32_t numcube )
{
	uint32_t	id_gri	;
	uint32_t	id_bll	;
        char tmpFilePath[ADELINE_MAX_PATH];

	numcube = TabAllCube[numcube].Num	;//	Indirection

	id_gri = BkgHeader.Gri_Start+numcube			;

	GriHeader = (T_GRI_HEADER *)BufMap			;

        GetResPath(tmpFilePath, ADELINE_MAX_PATH, BKG_HQR_NAME);
	Load_HQR( tmpFilePath, BufMap, id_gri )			;

	ManageSystem() ;// for streaming

	id_bll = BkgHeader.Bll_Start+GriHeader->My_Bll		;//+numcube

	Load_HQR( tmpFilePath, TabBlock, id_bll )		;

//----------------------------------------------	NEW
	if( !LoadUsedBrick() )	return 		;
//----------------------------------------------

	ManageSystem() ;// for streaming

	CreateMaskGph( BufferBrick, BufferMaskBrick ) ;

	ManageSystem() ;// for streaming

	NbBlock = (*(uint32_t*)TabBlock)/4		;

	CopyMapToCube()				;

	ManageSystem() ;// for streaming

	RedrawGRMs() ;// au cas ou il y ait des GRMs actives

	return	;
}

/*--------------------------------------------------------------------------*/
void	FreeGrille(){}
/*-------------------------------------------------------------------------*/
/*══════════════════════════════════════════════════════════════════════════*
		   █▀▀▀▀ ██▄ █ █▀▀▀▄       █   █ █▀▀▀█ █▀▀▀█
		   ██▀▀  ██▀██ ██  █       ██▀▀█ ██ ▄█ ██▀█▀
		   ▀▀▀▀▀ ▀▀  ▀ ▀▀▀▀        ▀▀  ▀ ▀▀▀▀  ▀▀  ▀
 *══════════════════════════════════════════════════════════════════════════*/
/*--------------------------------------------------------------------------*/
/*══════════════════════════════════════════════════════════════════════════*
	     █▀▀▀▀ █   █ ██▄ █ █▀▀▀▀ ▀▀█▀▀  █    █▀▀▀█ ██▄ █ ██▀▀▀
	     ██▀▀  ██  █ ██▀██ ██      ██   ██   ██  █ ██▀██ ▀▀▀▀█
	     ▀▀    ▀▀▀▀▀ ▀▀  ▀ ▀▀▀▀▀   ▀▀   ▀▀   ▀▀▀▀▀ ▀▀  ▀ ▀▀▀▀▀
 *══════════════════════════════════════════════════════════════════════════*/
/*──────────────────────────────────────────────────────────────────────────*/

/*--------------------------------------------------------------------------*/
uint8_t	*GetAdrColonneMap( int32_t x, int32_t z )
{
	uint32_t	offset	;

	offset = *(uint16_t*)(BufMap+sizeof(T_GRI_HEADER)+(x+(z*SIZE_CUBE_Z))*2);

	return(BufMap+sizeof(T_GRI_HEADER)+offset )	;
}
/*--------------------------------------------------------------------------*/
uint8_t	*GetAdrColonneCube( int32_t x, int32_t z )
{
	uint32_t	offset	;

	offset = (x*SIZE_CUBE_Y*2)+(z*SIZE_CUBE_Z*SIZE_CUBE_Y*2);

	return(BufCube+offset)			;
}

/*--------------------------------------------------------------------------*/
uint8_t	WorldColBrickVisible( 	int32_t oldx, int32_t oldy, int32_t oldz,
				int32_t xw, int32_t yw, int32_t zw )
{
	uint8_t col = GetWorldColBrickVisible( xw, yw, zw ) ;

	if( col )	return( col ) ;

	if( abs(xw-oldx)>=SIZE_BRICK_XZ
	OR  abs(yw-oldy)>=SIZE_BRICK_Y
	OR  abs(zw-oldz)>=SIZE_BRICK_XZ )
	{
		return( WorldColBrickVisible( 	oldx, oldy, oldz,
					oldx+(xw-oldx)/2,
					oldy+(yw-oldy)/2,
					oldz+(zw-oldz)/2 ) ) ;
	}

	return( 0 ) ;// Ok, cette fois, on est sûr !:)
}

/*--------------------------------------------------------------------------*/
/*uint8_t	WorldColBrickVisible( int32_t xw, int32_t yw, int32_t zw )
{
	if( GetBlockBrick( xw, yw, zw ) )
	{
		return( WorldColBrick( xw, yw, zw ) ) ;
	}
	else	return 0 ;
}
*/

/*--------------------------------------------------------------------------*/

void	GetShadow( int32_t xw, int32_t yw, int32_t zw )
{
	int32_t	xm, ym, zm ;
	uint8_t	*ptc ;
	int32_t	y ;
	uint8_t	*adr ;
	int32_t	block ;

	xm = xw/SIZE_BRICK_XZ ;
	ym = yw/SIZE_BRICK_Y ;
	zm = zw/SIZE_BRICK_XZ ;

	ShadowX = Nxw = xw ;
	ShadowZ = Nzw = zw ;

	if( ym>=SIZE_CUBE_Y )	// au-dessus du plafond de la map
	{
		ym = SIZE_CUBE_Y-1 ;
	}

	ptc = BufCube + ym*2 + (xm*SIZE_CUBE_Y*2) + (zm*SIZE_CUBE_X*SIZE_CUBE_Y*2) ;

	for( y = ym; y>0; y-- )
	{
		if( *ptc != 0 )	break ;
		ptc -= 2 ;
	}

	XMap = xm ;
	YMap = y ;
	ZMap = zm ;

	Nyw = (y+1) * SIZE_BRICK_Y ;

	ShadowCol = 0 ;

	if( *ptc != 0 )
	{
		block = (*ptc++) - 1 ;
		adr = GetAdrBlock( block )	;
		adr += HEADER_BLOCK		;
		adr += (*ptc)<<2 		;/* 4 Bytes to Jump	*/
		ShadowCol = *adr ;
		ReajustPos( ShadowCol ) ;
	}

	ShadowY = AdjustShadowObjects( xw, zw, Nyw, yw ) ;
}

/*──────────────────────────────────────────────────────────────────────────*/
/*--------------------------------------------------------------------------*/
int32_t	ProjectShadow( T_SORT *ptrs, int32_t beta )
{
	int32_t	xmin, zmin, xmax, zmax, xw, yw, zw ;
	int32_t	ys, cy		;
	int32_t	altitude_ref	;
	int32_t	demix, demiz 	;

	ClearScreenMinMax();

	xw = ptrs->Xw ;
	yw = ptrs->Yw ;
	zw = ptrs->Zw ;

	xmin = ptrs->XMin - xw ;
	zmin = ptrs->ZMin - zw ;
	xmax = ptrs->XMax - xw ;
	zmax = ptrs->ZMax - zw ;

	demix = (xmin+xmax)/2 ;
	demiz = (zmin+zmax)/2 ;

	// inclure ici la gestion des objets du decors
	altitude_ref = AdjustShadowObjects( xw, zw, yw, yw ) ;

	Rotate( demix, zmin, beta );

	X0 += xw			;
	Z0 += zw			;
	ys  = altitude_ref+SIZE_BRICK_Y	;

	GetShadow(X0, ys, Z0)		;
	cy = AdjustShadowObjects( X0, Z0, ShadowY, yw ) ;

	if( cy < altitude_ref-ALTITUDE_MAX ) cy = altitude_ref-ALTITUDE_MAX;
	else if( cy > altitude_ref+ALTITUDE_MAX ) cy = altitude_ref+ALTITUDE_MAX;

	if( !LongProjectPoint( X0,cy,Z0 ) )	return FALSE ;
	XS0 = Xp ;
	YS0 = Yp ;
	AdjustScreenMinMax();

	Rotate( xmin, demiz, beta );

	X0 += xw	;
	Z0 += zw	;

	GetShadow(X0, ys, Z0)	;
	cy = AdjustShadowObjects( X0, Z0, ShadowY, yw ) ;

	if( cy < altitude_ref-ALTITUDE_MAX ) cy = altitude_ref-ALTITUDE_MAX;
	else if( cy > altitude_ref+ALTITUDE_MAX ) cy = altitude_ref+ALTITUDE_MAX;

	if( !LongProjectPoint( X0,cy,Z0 ) )	return FALSE ;
	XS1 = Xp ;
	YS1 = Yp ;
	AdjustScreenMinMax();

	Rotate( demix, zmax, beta );

	X0 += xw	;
	Z0 += zw	;

	GetShadow(X0, ys, Z0)	;
	cy = AdjustShadowObjects( X0, Z0, ShadowY, yw ) ;

	if( cy < altitude_ref-ALTITUDE_MAX ) cy = altitude_ref-ALTITUDE_MAX;
	else if( cy > altitude_ref+ALTITUDE_MAX ) cy = altitude_ref+ALTITUDE_MAX;

	if( !LongProjectPoint( X0,cy,Z0 ) )	return FALSE ;
	XS2 = Xp ;
	YS2 = Yp ;
	AdjustScreenMinMax();

	Rotate( xmax, demiz, beta );

	X0 += xw	;
	Z0 += zw	;

	GetShadow(X0, ys, Z0)	;
	cy = AdjustShadowObjects( X0, Z0, ShadowY, yw ) ;

	if( cy < altitude_ref-ALTITUDE_MAX ) cy = altitude_ref-ALTITUDE_MAX;
	else if( cy > altitude_ref+ALTITUDE_MAX ) cy = altitude_ref+ALTITUDE_MAX;

	if( !LongProjectPoint( X0,cy,Z0 ) )	return FALSE ;
	XS3 = Xp ;
	YS3 = Yp ;
	AdjustScreenMinMax();

	UnsetClip() ;
	SetClip( ScreenXMin, ScreenYMin, ScreenXMax, ScreenYMax ) ;

	return TRUE ;
}

/*══════════════════════════════════════════════════════════════════════════*
		   █▄ ▄█ █▀▀▀▀ █▄ ▄█ █▀▀▀█  █    █▀▀▀█ █▀▀▀▀
		   ██▀ █ ██▀▀  ██▀ █ ██  █  ██   ██▀█▀ ██▀▀
		   ▀▀  ▀ ▀▀▀▀▀ ▀▀  ▀ ▀▀▀▀▀  ▀▀   ▀▀  ▀ ▀▀▀▀▀
 *══════════════════════════════════════════════════════════════════════════*/
/*──────────────────────────────────────────────────────────────────────────*/

uint32_t	CreateMaskGph( uint8_t *ptsrc, uint8_t *ptdst )
{
	uint8_t	*ptd	;
	uint32_t   nbg, off;
	uint32_t	*ptoff	;
	uint32_t	size, i	;

	ptoff = (uint32_t*)ptdst		;

	off = *(uint32_t *)ptsrc		;/*	First Offset Src	*/

	*ptoff++ = off			;/*	First Offset	*/

	ptd = ptdst+off			;

	nbg = (off-4)>>2		;/*	Nombre de Graph	*/

	for ( i = 0 ; i < nbg ; i++ )
	{
		size = CalcGraphMsk( i, ptsrc, ptd )	;

		off += size			;/*	Maj Offset	*/
		*ptoff++ = off			;/*	Write Offset 	*/
		ptd += size			;/*	Maj Pt Dest	*/
	}
	return(off)	;
}

/*-------------------------------------------------------------------------*/
void	CopyMapToCube()
{
	uint8_t	*pts, *ptd	;
	int32_t	x, z		;

/*-------------- Copy -------------------------*/
	for ( z = 0 ; z < SIZE_CUBE_Z ; z++ )
	{
		for ( x = 0 ; x < SIZE_CUBE_X ; x++ )
		{
			pts = GetAdrColonneMap( x, z )		;
			ptd = GetAdrColonneCube( x, z )		;

			DecompColonne( pts, ptd )		;
		}
	}
}
/*──────────────────────────────────────────────────────────────────────────*/
void	InitBufferCube()
{
	int32_t	intmem ;
        char tmpFilePath[ADELINE_MAX_PATH];

        GetResPath(tmpFilePath, ADELINE_MAX_PATH, BKG_HQR_NAME);

//	pas de RECOVER_AREA car BkgHeader en stored et pas en LZSS
        Load_HQR( tmpFilePath, &BkgHeader, 0 )			;// HEADER

// 	pas de RECOVER_AREA car TabAllCube en stored et pas en LZSS
	Load_HQR( tmpFilePath, (void *)TabAllCube, BkgHeader.Brk_Start+BkgHeader.Max_Brk ) ;

// 	Calcul des tailles nécessaires
	intmem = (BkgHeader.Max_Size_Brick_Cube+RECOVER_AREA)	// BufferBrick
		+(SIZE_CUBE_X*SIZE_CUBE_Y*SIZE_CUBE_Z*2L) ;	// BufCube

//	PtrZvBuffer sert aussi pour les décors intérieurs
	ListMem[MEM_PTR_ZBUFFER].Size = ade_max(intmem,SIZE_Z_BUFFER) ;

	ListMem[MEM_BUFFER_MASK_BRICK].Size 	= BkgHeader.Max_Size_Mask_Brick_Cube ;
	ListMem[MEM_BUF_MAP].Size 		= BkgHeader.Max_Size_Gri + RECOVER_AREA ;
	ListMem[MEM_TAB_BLOCK].Size 		= BkgHeader.Max_Size_Bll + RECOVER_AREA ;
}

/*══════════════════════════════════════════════════════════════════════════*
		   █▀▀▀▄  █    ██▀▀▀ █▀▀▀█ █     █▀▀▀█ █  ▄▀
		   ██  █  ██   ▀▀▀▀█ ██▀▀▀ ██    ██▀▀█ ██▀
		   ▀▀▀▀   ▀▀   ▀▀▀▀▀ ▀▀    ▀▀▀▀▀ ▀▀  ▀ ▀▀
 *══════════════════════════════════════════════════════════════════════════*/
/*──────────────────────────────────────────────────────────────────────────*/

void	DrawOverBrick( int32_t xm, int32_t ym, int32_t zm )
{
	register T_COLONB	*ptrlbc ;
	register int32_t		colscreen ;
	int32_t		col, i ;
	int32_t		startcol, endcol ;
	int32_t		xw, yw, zw ;
	int32_t		recouvre ;

	startcol = (ClipXMin+24)/24-1 ;
	endcol = (ClipXMax+24)/24 ;

	for( col = startcol; col <= endcol; col++ )
	{
		ptrlbc = &ListBrickColon[col][0] ;

		colscreen = col*24-24 ;

		for( i=0; i<NbBrickColon[col]; i++ )
		{
			/* bricks devant */
			if( ptrlbc->Ys+38 > ClipYMin
			AND ptrlbc->Ys <= ClipYMax )
			{
			recouvre = FALSE ;

			// essai correction bugs escaliers
//			if( WorldColBrick(ptrlbc->Xm*SIZE_BRICK_XZ,ptrlbc->Ym*SIZE_BRICK_Y,ptrlbc->Zm*SIZE_BRICK_XZ) > 1 )
			if( ptrlbc->Col > 1 )// collis complexe ?
			{
				if( ptrlbc->Ym >= ym+1 )
				{
					recouvre = TRUE ;
				}
			}
			else if( ptrlbc->Ym >= ym )
			{
				recouvre = TRUE ;
			}

			if( recouvre )
			{
			xw = ptrlbc->Xm*SIZE_BRICK_XZ ;
			yw = ptrlbc->Ym*SIZE_BRICK_Y  ;
			zw = ptrlbc->Zm*SIZE_BRICK_XZ ;

			if( (ptrlbc->Xm>=xm AND ptrlbc->Zm>=zm)
			OR (ptrlbc->Xm>xm
				AND WorldColBrick(xw-SIZE_BRICK_XZ,yw,zw)!=1
//				AND WorldColBrick(xw,yw,zw+SIZE_BRICK_XZ)==1 )
				AND WorldColBrick(xw,yw,zw+SIZE_BRICK_XZ)>=1 )
			OR (ptrlbc->Zm>zm
				AND WorldColBrick(xw,yw,zw-SIZE_BRICK_XZ)!=1
//				AND WorldColBrick(xw+SIZE_BRICK_XZ,yw,zw)==1 ) )
				AND WorldColBrick(xw+SIZE_BRICK_XZ,yw,zw)>=1 ) )
			{
				CopyMask( ptrlbc->Brick, colscreen, ptrlbc->Ys, BufferMaskBrick, Screen ) ;
			}
			}
			}
			ptrlbc++ ;
		}
	}
}

/*--------------------------------------------------------------------------*/
/* recouvrement reel pour obj qui ne depassent pas la ZV */

void	DrawOverBrick3( int32_t xm, int32_t ym, int32_t zm, int32_t ymax )
{
	register T_COLONB	*ptrlbc ;
	register int32_t		colscreen ;
	int32_t		col, i ;
	int32_t		startcol, endcol ;

	startcol = (ClipXMin+24)/24-1 ;
	endcol = (ClipXMax+24)/24 ;

	for( col = startcol; col <= endcol; col++ )
	{
		ptrlbc = &ListBrickColon[col][0] ;

		colscreen = col*24-24 ;

		for( i=0; i<NbBrickColon[col]; i++, ptrlbc++ )
		{
			/* bricks devant */
			if( ptrlbc->Ys+38 > ClipYMin
			AND ptrlbc->Ys <= ClipYMax )
			{
				if( ptrlbc->Ym > ymax )
				{
					if( (ptrlbc->Zm >= zm)
					OR  (ptrlbc->Xm >= xm) )
					{
						CopyMask( ptrlbc->Brick, colscreen, ptrlbc->Ys, BufferMaskBrick, Screen ) ;
					}
				}
				else if( ptrlbc->Ym >= ym )
				{
					if( (ptrlbc->Zm == zm)
					AND (ptrlbc->Xm == xm) )
					{
						CopyMask( ptrlbc->Brick, colscreen, ptrlbc->Ys, BufferMaskBrick, Screen ) ;
					}

					if( (ptrlbc->Zm > zm)
					OR  (ptrlbc->Xm > xm) )
					{
						CopyMask( ptrlbc->Brick, colscreen, ptrlbc->Ys, BufferMaskBrick, Screen ) ;
					}
				}
			}
		}
	}
}

/*--------------------------------------------------------------------------*/
// recouvrement reel pour obj qui ne depassent pas la ZV
// GROSSE RUSTINE: Cage à la fin de LBA2 pour ne pas recouvrir l'objet avec
// les briques du sol en 0

void	DrawOverBrickCage( int32_t xm, int32_t ym, int32_t zm )
{
	register T_COLONB	*ptrlbc ;
	register int32_t		colscreen ;
	int32_t		col, i ;
	int32_t		startcol, endcol ;

	startcol = (ClipXMin+24)/24-1 ;
	endcol = (ClipXMax+24)/24 ;

	for( col = startcol; col <= endcol; col++ )
	{
		ptrlbc = &ListBrickColon[col][0] ;

		colscreen = col*24-24 ;

		for( i=0; i<NbBrickColon[col]; i++, ptrlbc++ )
		{
			/* bricks devant */
			if( ptrlbc->Ys+38 > ClipYMin
			AND ptrlbc->Ys <= ClipYMax )
			{
			if( ptrlbc->Ym > 0 // diff ici avec DrawOverBrick3
			AND ptrlbc->Ym >= ym )
			{

			if( (ptrlbc->Zm == zm)
			AND (ptrlbc->Xm == xm) )
			{
				CopyMask( ptrlbc->Brick, colscreen, ptrlbc->Ys, BufferMaskBrick, Screen ) ;
			}

			if( (ptrlbc->Zm > zm)
			OR  (ptrlbc->Xm > xm) )
			{
				CopyMask( ptrlbc->Brick, colscreen, ptrlbc->Ys, BufferMaskBrick, Screen ) ;
			}

			}
			}
		}
	}
}

/*--------------------------------------------------------------------------*/

void	AffBrickBlock( int32_t block, int32_t brick, int16_t x, int16_t y, int16_t z )
{
	uint8_t	*adr	;
	int32_t	nb, col ;
	register T_COLONB	*ptrlbc ;
	int16_t	numbrick;
	uint8_t      brickcol ;

	adr = GetAdrBlock( block )	;
	adr += HEADER_BLOCK		;

	adr += ( brick<<2 )		;/* 4 Bytes to Jump	*/
	brickcol = *adr			;
	adr += 2			;

	numbrick = *(uint16_t*)adr		;	/* & 32767 */

	if ( numbrick AND numbrick!=ForbidenBrick )
	{
		Map2Screen( x-StartXCube, y-StartYCube, z-StartZCube )	;

		if( XScreen >= -24
		AND XScreen < 640
		AND YScreen >= -38
		AND YScreen < 480 )
		{
			AffGraph( numbrick-1, XScreen, YScreen, BufferBrick ) ;

			col = (XScreen+24)/24 ; /* 48 / 2 colonne intercalée */

			nb = NbBrickColon[col] ;

			ptrlbc = &ListBrickColon[col][nb] ;

			if( nb < MAX_BRICK )
			{
				ptrlbc->Xm   = x ;
				ptrlbc->Ym   = y ;
				ptrlbc->Zm   = z ;
				ptrlbc->Ys    = (int16_t)YScreen ;
				ptrlbc->Brick = (int16_t)(numbrick-1) ;
				ptrlbc->Col  = brickcol ;
				NbBrickColon[ col ]++ ;
			}
			else	Message( "Arg MAX_BRICK Z BUFFER atteint", TRUE ) ;
		}
	}
}

/*--------------------------------------------------------------------------*/
/*ptc = BufCube + y*2 + (x*SIZE_CUBE_Y*2) + (z*SIZE_CUBE_X*SIZE_CUBE_Y*2) ;*/

void	AffGrille()
{
	int32_t	block		;
	uint8_t	*ptc		;
	int16_t	z, y, x		;

	PtrProjectPoint( 0, 0, 0 ) ;
	XpOrgw = Xp ;
	YpOrgw = Yp ;

	memset( NbBrickColon, 0, sizeof(int16_t)*NB_COLON ) ;

	ptc = BufCube		;
	for ( z = 0 ; z < SIZE_CUBE_Z ; z++ )
	{
		for ( x = 0 ; x < SIZE_CUBE_X ; x++ )
		{
			for ( y = 0 ; y < SIZE_CUBE_Y ; y++ )
			{
				block = *ptc++	;

				if( block )
				{
					AffBrickBlock( block-1, *ptc, x, y, z )	;
				}
				ptc++	;
			}
		}
	}
}

/*══════════════════════════════════════════════════════════════════════════*
	  █     █▀▀▀█ █▀▀█  █  ▄▀ █▀▀▀█  █    ██▄ █ ▀▀█▀▀ █   █ █▀▀▀▀
	  ██    ██▀▀█ ██▀▀█ ██▀   ██▀█▀  ██   ██▀██   ██  ██▀▀█ ██▀▀
	  ▀▀▀▀▀ ▀▀  ▀ ▀▀▀▀▀ ▀▀    ▀▀  ▀  ▀▀   ▀▀  ▀   ▀▀  ▀▀  ▀ ▀▀▀▀▀
 *══════════════════════════════════════════════════════════════════════════*/
/*──────────────────────────────────────────────────────────────────────────*/

/*--------------------------------------------------------------------------*/
// Calcule les masques du Z-Buffer pour DrawOverBrick sans dessiner la
// brick
void	AffBrickBlockColon( int32_t block, int32_t brick, int16_t x, int16_t y, int16_t z )
{
	uint8_t	*adr	;
	int32_t	nb, col ;
	register T_COLONB	*ptrlbc ;
	int16_t	numbrick;
	uint8_t      brickcol ;

	adr = GetAdrBlock( block )	;
	adr += HEADER_BLOCK		;

	adr += ( brick<<2 )		;/* 4 Bytes to Jump	*/
	brickcol = *adr			;
	adr += 2			;

	numbrick = *(uint16_t*)adr		;	/* & 32767 */

	if ( numbrick AND numbrick!=ForbidenBrick )
	{
		Map2Screen( x-StartXCube, y-StartYCube, z-StartZCube )	;

		if( XScreen >= -24
		AND XScreen < 640
		AND YScreen >= -38
		AND YScreen < 480 )
		{
			col = (XScreen+24)/24 ; /* 48 / 2 colonne intercalée */

			nb = NbBrickColon[col] ;

			ptrlbc = &ListBrickColon[col][nb] ;

			if( nb < MAX_BRICK )
			{
				ptrlbc->Xm   = x ;
				ptrlbc->Ym   = y ;
				ptrlbc->Zm   = z ;
				ptrlbc->Ys    = (int16_t)YScreen ;
				ptrlbc->Brick = (int16_t)(numbrick-1) ;
				ptrlbc->Col  = brickcol ;
				NbBrickColon[ col ]++ ;

			}
			else	Message( "Arg MAX_BRICK Z BUFFER atteint", TRUE ) ;
		}
	}
}

// Calcule le Z-Buffer pour le DrawOverBrick de toute la grille sans
// afficher les bricks
void	AffGrilleOnly()
{
	int32_t	block		;
	uint8_t	*ptc		;
	uint8_t	*adr ;
	int16_t	z, y, x		;
	uint8_t	codejeu		;

	PtrProjectPoint( 0, 0, 0 ) ;
	XpOrgw = Xp ;
	YpOrgw = Yp ;

	memset( NbBrickColon, 0, sizeof(int16_t)*NB_COLON ) ;

	ptc = BufCube		;

	for ( z = 0 ; z < SIZE_CUBE_Z ; z++ )
	{
		for ( x = 0 ; x < SIZE_CUBE_X ; x++ )
		{
			for ( y = 0 ; y < SIZE_CUBE_Y ; y++ )
			{
				block = *ptc++	;

				if( block )
				{
					block-- ;

					//-------------------
					adr = GetAdrBlock( block )	;
					adr += (HEADER_BLOCK+1)		;

					codejeu = (uint8_t)((*adr)>>4) 	;

					if( codejeu!=CJ_LABYRINTHE )
					//-------------------
					{
						AffBrickBlockColon( block, *ptc, x, y, z )	;
					}
				}
				ptc++	;
			}
		}
	}
}
/*--------------------------------------------------------------------------*/
// Affiche la brick sans calculer le Z-Buffer pour DrawOverBrick
void	AffBrickBlockOnly( int32_t block, int32_t brick, int16_t x, int16_t y, int16_t z )
{
	uint8_t	*adr	;
	int32_t	numbrick;

	adr = GetAdrBlock( block )	;
	adr += HEADER_BLOCK		;

	adr += ( brick<<2 )		;/* 4 Bytes to Jump	*/
	adr += 2			;

	numbrick = *(uint16_t*)adr		;	/* & 32767 */

	if( numbrick AND numbrick!=ForbidenBrick )
	{
		Map2Screen( x-StartXCube, y-StartYCube, z-StartZCube )	;

		if( XScreen >= -24
		AND XScreen < 640
		AND YScreen >= -38
		AND YScreen < 480 )
		{
			AffGraph( numbrick-1, XScreen, YScreen, BufferBrick ) ;
		}
	}
}

// Redessine uniquement les block n'ayant pas le code jeu Invisible
void	AffGrilleLabyrinthe()
{
	int32_t	block		;
	uint8_t	*ptc		;
	uint8_t	*adr ;
	int16_t	z, y, x		;
	uint8_t	codejeu		;

	PtrProjectPoint( 0, 0, 0 ) ;
	XpOrgw = Xp ;
	YpOrgw = Yp ;

	ptc = BufCube		;

	for ( z = 0 ; z < SIZE_CUBE_Z ; z++ )
	{
		for ( x = 0 ; x < SIZE_CUBE_X ; x++ )
		{
			for ( y = 0 ; y < SIZE_CUBE_Y ; y++ )
			{
				block = *ptc++	;

				if( block )
				{
					block-- ;

					adr = GetAdrBlock( block )	;
					adr += (HEADER_BLOCK+1)		;

					codejeu = (uint8_t)((*adr)>>4) ;

					if( codejeu!=CJ_LABYRINTHE )
					{
						AffBrickBlockOnly( block, *ptc, x, y, z )	;
					}
				}
				ptc++	;
			}
		}
	}
}

// Affiche un cube de block (3*3*3) autour du point passe (coordonnees world)
void	AffOneBrick( int32_t x, int32_t y, int32_t z )
{
	int32_t	block		;
	uint8_t	*ptc		;
	uint8_t	*adr	;
	int32_t	xmin, ymin, xmax, ymax ;
	int16_t	xs, ys, zs ;
	int16_t	zdeb ;
	uint8_t	codejeu	;

	xmin = 639 ;
	ymin = 479 ;
	xmax = 0 ;
	ymax = 0 ;

	PtrProjectPoint( 0, 0, 0 ) ;
	XpOrgw = Xp ;
	YpOrgw = Yp ;

	x /= SIZE_BRICK_XZ ;
	y /= SIZE_BRICK_Y  ;
	z /= SIZE_BRICK_XZ ;

	zdeb = (int16_t)(z-1) ;
	if( zdeb<0 )	zdeb = 0 ;

	for( zs=zdeb; zs<=z+1; zs++ )
	{
		for( xs=(int16_t)(x-1); xs<=(int16_t)(x+1); xs++ )
		{
			ptc = GetAdrColonneCube( xs, zs )		;
			ptc += (y-1)*2 ;
			for( ys=(int16_t)(y-1); ys<=(int16_t)(y+1); ys++ )
			{
				block = *ptc++	;
				if( block )
				{
					block-- ;

					adr = GetAdrBlock( block )	;
					adr += (HEADER_BLOCK+1)		;

					codejeu = (uint8_t)((*adr)>>4) ;

					if( codejeu==CJ_LABYRINTHE )
					{
						AffBrickBlockOnly( block, *ptc, xs, ys, zs )	;
						if( ScreenXMin<xmin )	xmin = ScreenXMin ;
						if( ScreenXMax>xmax )	xmax = ScreenXMax ;
						if( ScreenYMin<ymin )	ymin = ScreenYMin ;
						if( ScreenYMax>ymax )	ymax = ScreenYMax ;
					}
				}
				ptc++ ;
			}
		}
	}

	SetClip( xmin, ymin, xmax, ymax ) ;
	DrawRecover( (x+1)*SIZE_BRICK_XZ, y*SIZE_BRICK_Y, (z+1)*SIZE_BRICK_XZ, 0, 0 ) ;
}

// Fin Labyrinthe

/*--------------------------------------------------------------------------*/

void	IncrustGrm( T_ZONE *ptrz )
{
	int32_t numgrm, xo, yo, zo	;
	uint8_t	*pts, *ptd	;
	int32_t	x, z	 	;
	int32_t	dx, dy, dz	;
        char tmpFilePath[ADELINE_MAX_PATH];

	numgrm = ptrz->Info0		;

        GetResPath(tmpFilePath, ADELINE_MAX_PATH, BKG_HQR_NAME);
	Load_HQR( tmpFilePath, Screen,
			BkgHeader.Grm_Start+GriHeader->My_Grm+numgrm ) ;

	xo = ptrz->X0/SIZE_BRICK_XZ	;
	yo = ptrz->Y0/SIZE_BRICK_Y	;
	zo = ptrz->Z0/SIZE_BRICK_XZ	;

	pts = (uint8_t*)Screen	;

	dx = *pts++	;
	dy = *pts++	;
	dz = *pts++	;

	yo <<= 1	;//	Cause int16_t
	dy <<= 1	;//	Cause int16_t

	for ( z = zo ; z < zo+dz ; z++ )
	{
		for ( x = xo ; x < xo+dx ; x++ )
		{
			ptd = GetAdrColonneCube( x, z )	;
			ptd += yo			;
			memcpy( ptd, pts, dy )		;
			pts += dy			;
		}
	}

	FirstTime = AFF_ALL_FLIP ;
}

/*--------------------------------------------------------------------------*/
void	DesIncrustGrm( T_ZONE *ptrz )
{
	uint8_t	*pts, *ptd	;
	uint8_t	col[50]		;//	1 Colonne decompressee
	int32_t	x, y, z, dy	;
	int32_t	z0, z1, x0, x1	;
	int32_t	y0, y1		;

	x0 = ptrz->X0/SIZE_BRICK_XZ	;
	x1 = ptrz->X1/SIZE_BRICK_XZ	;

	y0 = ptrz->Y0/SIZE_BRICK_Y	;
	y1 = ptrz->Y1/SIZE_BRICK_Y	;

	z0 = ptrz->Z0/SIZE_BRICK_XZ	;
	z1 = ptrz->Z1/SIZE_BRICK_XZ	;

	y = y0 << 1			;//	Cause int16_t

	dy = ((y1-y0)+1)<<1		;

/*-------------- Copy -------------------------*/
	for ( z = z0 ; z <= z1  ; z++ )
	{
		for ( x = x0 ; x <= x1 ; x++ )
		{
			pts = GetAdrColonneMap( x, z )	;
			DecompColonne( pts, col )	;

			ptd = GetAdrColonneCube( x, z )	;
			memcpy( ptd+y, col+y, dy )	;

		}
	}

	FirstTime = AFF_ALL_FLIP ;
}

/*--------------------------------------------------------------------------*/
void	RedrawGRMs( void )
{
	int32_t	n ;
	T_ZONE	*ptrz = ListZone ;

	for( n=0; n<NbZones; n++, ptrz++ )
	{
		switch( ptrz->Type )
		{
			case 3:	// GRM
				if( ptrz->Info2 )
				{
					IncrustGrm( ptrz ) ;
				}
				break ;
		}
	}
}
/*--------------------------------------------------------------------------*/
