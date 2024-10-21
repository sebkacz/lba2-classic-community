#include	"C_EXTERN.H"

/*══════════════════════════════════════════════════════════════════════════*
     █    ██▄ █ █▀▀▀▀ █▀▀▀█ █   █ ██▀▀▀ ▀▀█▀▀       █▀▀▀▄  █    ██▀▀▀ █▀▀▀█
     ██   ██▀██ ██    ██▀█▀ ██  █ ▀▀▀▀█   ██        ██  █  ██   ▀▀▀▀█ ██▀▀▀
     ▀▀   ▀▀  ▀ ▀▀▀▀▀ ▀▀  ▀ ▀▀▀▀▀ ▀▀▀▀▀   ▀▀  ▀▀▀▀▀ ▀▀▀▀   ▀▀   ▀▀▀▀▀ ▀▀
 *══════════════════════════════════════════════════════════════════════════*/
/*──────────────────────────────────────────────────────────────────────────*/

int32_t	InitIncrustDisp(	int16_t type,
				int16_t num,
				int32_t x, int32_t y,
				int16_t info,
				int16_t move,
				int32_t timeout	)
{
	T_INCRUST_DISP	*ptrdisp ;
	int32_t	n ;

	// Liés aux objets de l'inventaire changeant d'état
	if( (type&0xFF)==INCRUST_INVENTORY )
	{
		num = TabInv[num].TabObj3D[ TabInv[num].IdObj3D ] ;
	}

	ptrdisp = ListIncrustDisp ;

	for( n=0; n<MAX_INCRUST_DISP; n++, ptrdisp++ )
	{
		if( ptrdisp->Num == -1	/* slot libre */
		OR  (ptrdisp->Num==num AND ptrdisp->Type==type) )// same object
		{
			if( ptrdisp->Num==-1
			OR  ptrdisp->Type!=type )
			{
				ptrdisp->X = (int16_t)x ;
				ptrdisp->Y = (int16_t)y ;
			}

			if( (type&0xff)==INCRUST_CMPT )
			{
				// ATTENTION: Grosse Magouille: les compteurs sont tjs affichés
				// en y=20, ceci permet d'utiliser le Y pour memoriser la
				// valeur courante du compteur (cf FlagAnimWhoSpeak)
				ptrdisp->Y = num ;
			}

			ptrdisp->Type = type ;
			ptrdisp->Info = info ;

			ptrdisp->Move = move ;

			ptrdisp->TimerEnd = TimerRefHR + 1000 * timeout ;

			ptrdisp->Num = num ;
			PosObjIncrust( ptrdisp, n ) ;

			return n ;
		}
	}

	return -1 ;
}

/*──────────────────────────────────────────────────────────────────────────*/

void	PosObjIncrust( T_INCRUST_DISP *ptrdisp, int32_t num )
{
	// au cas ou on ait plusieurs objets 3D tournant en même temps !
	int32_t	x = 10 ;
	int32_t	n ;
	int32_t	type ;
	T_INCRUST_DISP *listdisp = ListIncrustDisp ;

	type = (ptrdisp->Type&0xFF) ;

	if( type==INCRUST_INVENTORY
	OR  type==INCRUST_OBJ )
	{
		for( n=0; n<MAX_INCRUST_DISP; n++, listdisp++ )
		{
			if( n != num
			AND listdisp->Num != -1 )
			{
				type = (listdisp->Type&0xFF) ;

				if( type==INCRUST_INVENTORY
				OR  type==INCRUST_OBJ )
				{
					x += 70 ;
				}
			}
		}

		ptrdisp->Y = 10 	;
		ptrdisp->X = (int16_t)x 	;
	}
}

/*──────────────────────────────────────────────────────────────────────────*/

void	ChangeIncrustPos( int32_t xp0, int32_t yp0, int32_t xp1, int32_t yp1 )
{
	T_INCRUST_DISP	*ptrdisp ;
	int32_t	n ;
	int32_t	dx, dy ;

	dx = xp1 - xp0 ;
	dy = yp1 - yp0 ;

	ptrdisp = ListIncrustDisp ;

	for( n=0; n<MAX_INCRUST_DISP; n++, ptrdisp++ )
	{
		if( ptrdisp->Type == INCRUST_NUM )
		{
			ptrdisp->X += dx ;
			ptrdisp->Y += dy ;
		}
	}
}

/*──────────────────────────────────────────────────────────────────────────*/

void	ClearIncrusts( int32_t type )
{
	T_INCRUST_DISP	*ptrdisp ;
	int32_t	n ;

	ptrdisp = ListIncrustDisp ;

	for( n=0; n<MAX_INCRUST_DISP; n++, ptrdisp++ )
	{
		if( ptrdisp->Type==type )
		{
			ptrdisp->Num = -1 ;// libère slot
		}
	}
}

/*──────────────────────────────────────────────────────────────────────────*/

int32_t	LastNumBulle = -1 ;
int32_t	SpriteBulle = SPRITE_BULLE_RIGHT ;

#define	DX_BULLE	45	// Valeur saisie dans Volgraf

void	DrawBulle( int32_t numobj )
{
	PtrProjectPoint(	ListObjet[numobj].Obj.X,
				ListObjet[numobj].Obj.Y + ListObjet[numobj].YMax,
				ListObjet[numobj].Obj.Z ) ;

	if( LastNumBulle != numobj )
	{
		SpriteBulle ^= 1 ;
		LastNumBulle = numobj ;
	}

	if( SpriteBulle == SPRITE_BULLE_LEFT )	SpriteX = Xp + 10 ;
	else			SpriteX = Xp - 10 - DX_BULLE ;

	SpriteY = Yp - 20 ;

	PtrAffGraph( SpriteX, SpriteY, SpriteBulle ) ;
	SetClip( ScreenXMin, ScreenYMin, ScreenXMax, ScreenYMax ) ;

	if( ClipXMin <= ClipXMax
	AND ClipYMin <= ClipYMax )
	{
		if ( FlagDisplayText )
			BoxStaticAdd( ClipXMin, ClipYMin, ClipXMax, ClipYMax ) ;
		else    BoxMovingAdd( ClipXMin, ClipYMin, ClipXMax, ClipYMax ) ;
	}

	UnsetClip() ;
}

/*──────────────────────────────────────────────────────────────────────────*/
