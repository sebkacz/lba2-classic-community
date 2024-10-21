#include	"C_EXTERN.H"

int32_t	NbTriObj = 0	;

/*══════════════════════════════════════════════════════════════════════════*

	 █    ██▄ █ ▀▀█▀▀	   ██▀▀▀ █▀▀▀█ █▀▀▀█ ▀▀█▀▀
	 ██   ██▀██   ██	   ▀▀▀▀█ ██  █ ██▀█▀   ██
	 ▀▀   ▀▀  ▀   ▀▀	   ▀▀▀▀▀ ▀▀▀▀▀ ▀▀  ▀   ▀▀

			Tri Intérieur

 *══════════════════════════════════════════════════════════════════════════*/
/*──────────────────────────────────────────────────────────────────────────*/

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
#define	BitAfter(n)		(1<<(n&31))
#define	IndexAfter(n)		(n/32)

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
#define	MAX_INDEX		((MAX_TRI+31)/32)

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
typedef struct {
	uint32_t	after[MAX_INDEX] ;
	int32_t	x0  ;
	int32_t	y0  ;
	int32_t	x1  ;
	int32_t	y1  ;
	int32_t	present ;
} Elem ;

typedef struct {
	Elem		aElem[MAX_TRI] ;
	int32_t		cElem ;
} tDatabase ;

tDatabase Base ;

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
uint32_t	Checked[MAX_INDEX]	;

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
static inline int32_t BaseDistance(int32_t after, int32_t before)
{
	T_SORT	*pt1, *pt2;
	int32_t dxa, dya, dza ;
	int32_t dxb, dyb, dzb ;
	int32_t va ;

	pt1 = &ListTri[after]	;
	pt2 = &ListTri[before]	;

	dxb = pt1->XMin-pt2->XMax	;
	dyb = pt1->YMin-pt2->YMax	;
	dzb = pt1->ZMin-pt2->ZMax	;
	dxa = pt2->XMin-pt1->XMax	;
	dya = pt2->YMin-pt1->YMax	;
	dza = pt2->ZMin-pt1->ZMax	;

	va = ade_max(Max3(dxa, dya, dza), Max3(dxb, dyb, dzb)) ;

	if(va<0)	va = 0	;

	return va ;
}

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
static inline int32_t BaseFindFirst(int32_t after)
{
	int32_t	i	;
	int32_t	best	;
	int32_t	index	;
	int32_t	bafter	;
	int32_t	bi	;
	uint32_t	bit	;

restartall:

	memset(Checked, 0, MAX_INDEX*sizeof(uint32_t))	;

	best = -1	;

restart:

	bit   = BitAfter(after) ;
	index = IndexAfter(after) ;

	if(Checked[index]&bit)	// check Loop
	{
		Base.aElem[bi].after[IndexAfter(bafter)] &= ~BitAfter(bafter) ;
		after = bi	;
		goto restartall ;
	}

	Checked[index] |= bit ;

	for(i=0; i<Base.cElem; i++)
	{
		if(Base.aElem[i].after[index]&bit)
		{
			int32_t temp ;

			temp = BaseDistance(after, i) ;

			if(temp>best)
			{
				best	= temp	;
				bafter	= after	;
				bi	= i	;
			}

			after = i ;

			goto restart ;
		}
	}

	return after ;
}

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
static inline int32_t BaseDisplayFirst( void )
{
	int32_t i ;

	for(i=0; i<Base.cElem; i++)
	{
		if(Base.aElem[i].present) break ;
	}

	i = BaseFindFirst(i);

	memset(&(Base.aElem[i]), 0, sizeof(Elem)) ;

	return( AffOneObject( &ListTri[i] ) ) ;
}

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
int32_t BaseSort( void )
{
	int32_t i ;

	for(i=0; i<Base.cElem; i++)
	{
		if( BaseDisplayFirst() )	return TRUE ;
	}

	return FALSE ;
}

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
void BaseReset( void )
{
	Base.cElem = 0 ;
}

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
#define	BaseAddRelation(a, b)	\
	Base.aElem[b].after[IndexAfter(a)] |= BitAfter(a)

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
int32_t	TreeInsert( int16_t numtype, int32_t posx, int32_t posy, int32_t posz,
		    int32_t txmin, int32_t tymin, int32_t tzmin,
		    int32_t txmax, int32_t tymax, int32_t tzmax )
{
	int32_t	x0, y0, x1, y1	;
	int32_t	i		;
	T_SORT	*pt		;
	Elem	*elem		;
	int32_t	zrot = 0	;

	if(CubeMode==CUBE_INTERIEUR)
	{
		// Serge: a optimiser
		LongProjectPoint(txmin, tymin, tzmax)	;
		x0 = Xp ;
		LongProjectPoint(txmax, tymin, tzmax)	;
		y1 = Yp ;
		LongProjectPoint(txmax, tymin, tzmin)	;
		x1 = Xp ;
		LongProjectPoint(txmin, tymax, tzmin)	;
		y0 = Yp ;
	}
	else
	{
		int32_t	d ;
		int32_t	mx, my, mz ;

		mx = (txmin + txmax)>>1 ;
		my = (tymin + tymax)>>1 ;
		mz = (tzmin + tzmax)>>1 ;

		d = Distance3D(mx, my, mz, txmax, tymax, tzmax) ;

		LongWorldRotatePoint(mx, my, mz) ;

		if(!LongProjectPoint(X0+d, Y0, Z0))
		{
			return FALSE ;
		}

		d = Xp ;

		if(!LongProjectPoint(X0, Y0, Z0))
		{
			return FALSE ;
		}

		d -= Xp ;

		x0 = Xp - d ;
		y0 = Yp - d ;
		x1 = Xp + d ;
		y1 = Yp + d ;

		LongWorldRotatePoint( posx, posy, posz ) ;
		zrot = CameraZrClip-Z0 ;// l'ecran
	}

	// PreClipping
	if( (x1<0) OR (x0>=640)
	OR  (y1<0) OR (y0>=480) )
	{
		if( !(numtype&SORT_NO_PRECLIP) )
		{
			return FALSE ;
		}
	}

	pt = &ListTri[NbTriObj]	;//	Create New Entry/List

	pt->Z = zrot		;// l'ecran
	pt->NumObj = numtype&~(SORT_NO_PRECLIP)	;
	pt->Xw = posx		;
	pt->Yw = posy		;
	pt->Zw = posz		;
	pt->XMin = txmin	;
	pt->YMin = tymin	;
	pt->ZMin = tzmin	;
	pt->XMax = txmax	;
	pt->YMax = tymax	;
	pt->ZMax = tzmax	;

	NbTriObj++ 		;

	Base.aElem[Base.cElem].present= TRUE;

	memset(Base.aElem[Base.cElem].after, 0, sizeof(uint32_t)*MAX_INDEX) ;
	Base.aElem[Base.cElem].x0 = x0 ;
	Base.aElem[Base.cElem].y0 = y0 ;
	Base.aElem[Base.cElem].x1 = x1 ;
	Base.aElem[Base.cElem].y1 = y1 ;

	pt   = ListTri		;
	elem = Base.aElem	;

	for (i=0; i<Base.cElem; i++, pt++, elem++ )
	{
// test d'overlap
//		if((x0<=elem->x1)&&(x1>=elem->x0)&&(y0<=elem->y1)&&(y1>=elem->y0))
		{
			int32_t	dxa, dya, dza	;
			int32_t	dxb, dyb, dzb	;
			int32_t	vb		;

			dxa = txmin-pt->XMax	;
			dya = tymin-pt->YMax	;
			dza = tzmin-pt->ZMax	;
			dxb = pt->XMin-txmax	;
			dyb = pt->YMin-tymax	;
			dzb = pt->ZMin-tzmax	;

			if(CubeMode==CUBE_INTERIEUR)
			{
				vb = Max3( dxb, dyb, dzb ) - Max3( dxa, dya, dza ) ;
			}
			else
			{
				dxb -= dxa ;
				dzb -= dza ;
				dyb -= dya ;

				// new method
				dxb = ((-dxb * SinTab[CameraBeta]) >> 14) * CosTab[CameraAlpha] >> 14 ;
				dzb = ((dzb * CosTab[CameraBeta]) >> 14) * CosTab[CameraAlpha] >> 14  ;
				dyb = (dyb * SinTab[CameraAlpha]) >> 14 ;
/*
				// old method
				if(CameraBeta<2048)
				{
					dxb = - dxb ;
				}

				if(CameraAlpha>2048)
				{
					dyb = - dyb ;
				}

				if((CameraBeta>1024)&&(CameraBeta<3072))
				{
					dzb = - dzb ;
				}
*/
				if(abs(dxb)>abs(dyb))
				{
					vb = dxb ;
				}
				else
				{
					vb = dyb ;
				}

				if(abs(dzb)>abs(vb))
				{
					vb = dzb ;
				}

//				vb = Max3( dxb, dyb, dzb ) - Max3( dxa, dya, dza ) ;
			}

			if(vb)
			{
				if (vb>0)		// 	Before
				{
					BaseAddRelation(i, Base.cElem) ;
				}
				else
				{
					BaseAddRelation(Base.cElem, i) ;
				}
			}
		}
	}

	Base.cElem++ ;

	return TRUE ;
}

