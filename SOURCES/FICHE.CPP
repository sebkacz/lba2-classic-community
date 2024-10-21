#include	"C_EXTERN.H"

/*══════════════════════════════════════════════════════════════════════════*
		      ██▀▀▀ █▀▀▀▀ █▀▀▀█  █    █▀▀▀█ ▀▀█▀▀
		      ▀▀▀▀█ ██    ██▀█▀  ██   ██▀▀▀   ██
		      ▀▀▀▀▀ ▀▀▀▀▀ ▀▀  ▀  ▀▀   ▀▀      ▀▀
 *══════════════════════════════════════════════════════════════════════════*/
/*──────────────────────────────────────────────────────────────────────────*/

int32_t	SearchBonusKey() ;

uint8_t	*SearchPtrAnimAction ;

int16_t	M_XMin = -32000 ;
int16_t	M_XMax, M_YMin, M_YMax, M_ZMin, M_ZMax ;

uint8_t	MagicHitForce[] = {
	DEGATS_HAND_LVL_0,
	DEGATS_HAND_LVL_1,
	DEGATS_HAND_LVL_2,
	DEGATS_HAND_LVL_3,
	DEGATS_HAND_LVL_4	} ;

uint8_t	MagicBallHitForce[] = {
	DEGATS_BALLE_LVL_01,
	DEGATS_BALLE_LVL_01,
	DEGATS_BALLE_LVL_2,
	DEGATS_BALLE_LVL_3,
	DEGATS_BALLE_LVL_4	} ;

uint8_t	MagicBallSprite[] = {
	SPRITE_BALLE_LVL_01,
	SPRITE_BALLE_LVL_01,
	SPRITE_BALLE_LVL_2,
	SPRITE_BALLE_LVL_3,
	SPRITE_BALLE_LVL_4
	} ;

uint8_t	BaseLeftStepSound[2] = {
		60,	// Interieur
		30,	// Exterieur
		} ;

uint8_t	BaseRightStepSound[2] = {
		75,	// Interieur
		45,	// Exterieur
		} ;


/*══════════════════════════════════════════════════════════════════════════*/
/*══════════════════════════════════════════════════════════════════════════*/
/*══════════════════════════════════════════════════════════════════════════*/

void	ThrowMagicBall(	int32_t x, int32_t y, int32_t z,
			int32_t alpha, int32_t beta,
			int32_t vitesse, uint8_t poids )
{
	int32_t	search, spr ;
	int16_t	n ;
	uint8_t	sprite ;
	uint8_t	force ;

	/* ici on determine le type de tir et la force */

	force = MagicBallHitForce[MagicLevel] ;
	sprite = MagicBallSprite[MagicLevel] 	;

	MagicBallType = (uint8_t)(((MagicPoint-1) / 20) + 1) ;
	if( MagicPoint == 0 )	MagicBallType  = 0 ;

	// si clef trouvée
	if( (search = SearchBonusKey()) != -1 )
	{
		MagicBallType = 5 ;
	}

	switch( MagicBallType )
	{
	case 0:	// balle normale directe
		MagicBall =
		ThrowExtra(	NUM_PERSO, x,y,z,
				sprite,
				alpha, beta,
				vitesse, poids,
				force ) ;
		break ;

	case 1: // balle qui rebondit
		MagicBallCount = 4 ;
		MagicBall =
		ThrowExtra(	NUM_PERSO, x,y,z,
				sprite,
				alpha, beta,
				vitesse, poids,
				force ) ;
		break ;

	case 2: // balle qui rebondit
		MagicBallType = 1 ;
		MagicBallCount = 4 ;
		MagicBall =
		ThrowExtra(	NUM_PERSO, x,y,z,
				sprite,
				alpha, beta,
				vitesse, poids,
				force ) ;
		break ;

	case 3: // balle qui rebondit
		MagicBallType = 1 ;
		MagicBallCount = 4 ;
		MagicBall =
		ThrowExtra(	NUM_PERSO, x,y,z,
				sprite,
				alpha, beta,
				vitesse, poids,
				force ) ;
		break ;

	case 4: // balle qui rebondit
		MagicBallType = 1 ;
		MagicBallCount = 4 ;
		MagicBall =
		ThrowExtra(	NUM_PERSO, x,y,z,
				sprite,
				alpha, beta,
				vitesse, poids,
				force ) ;
		break ;

	case 5:	// cherche Key
		MagicBall = ExtraSearchKey(	NUM_PERSO, x,y,z,
						(int16_t)sprite, (uint8_t)search ) ;
		break ;
	}

	if( MagicBall!=-1 )
	{
		ListExtra[MagicBall].Flags |= EXTRA_MAGIC_BALL ;

		if( MagicLevel==4 )
		{
			ListExtra[MagicBall].Flags |= EXTRA_TRANSPARENT ;

			// integre la trainee de la balle de feu
			for( n=0; n<3; n++ )
			{
				spr = ThrowExtra( NUM_PERSO, x,y,z,
					(int16_t)(SPRITE_TRAINEE_BALLE_1+n),
					alpha, beta,
					vitesse, poids,
					force ) ;

				if( spr!=-1 )
				{
					ListExtra[spr].Scale = 75 + 15 * n ;
					ListExtra[spr].Flags = EXTRA_WAIT|EXTRA_TRAINEE|EXTRA_TRANSPARENT ;
					ListExtra[spr].Timer = TimerRefHR + n*20 ;
					ListExtra[spr].Body  = n ; // numero trainee
				}
			}
		}
	}

	// la balle magique coute 1 point de magie
	if( MagicPoint > 0 )	MagicPoint-- ;
}

/*══════════════════════════════════════════════════════════════════════════*/
void	SampleMagicBall( int32_t x, int32_t y, int32_t z )
{
	int32_t	sample = SAMPLE_MAGIC_BALL ;

	if( MagicLevel==4 )	sample = SAMPLE_MAGIC_BALL_FIRE ;

	HQ_3D_MixSample( sample, 0x1000, 0, 1, x, y , z ) ;
}

/*══════════════════════════════════════════════════════════════════════════*/
int32_t	ThrowDart(	int32_t x, int32_t y, int32_t z,
			int32_t alpha, int32_t beta,
			int32_t vitesse, uint8_t poids )
{
	int32_t	n ;

	n = ThrowExtraObj(	NUM_PERSO,
			x,y,z,
			BODY_3D_DART,
			alpha, beta, vitesse,
			-1, // alpharot suivant la trajectoire du throw
			poids, DEGATS_DART ) ;

	if( n!=-1 )
	{
		ListExtra[n].Flags |= EXTRA_DART ;

		if( ListVarGame[FLAG_DART] )
			ListVarGame[FLAG_DART]-- ;
	}

	return n ;
}

/*══════════════════════════════════════════════════════════════════════════*/
// Lancement de coeurs par la conque
void	ThrowConque( T_OBJET *ptrobj, int32_t x, int32_t y, int32_t z, int16_t  nb )
{
	int32_t n ;
	int16_t NbBonus = (int16_t)TabInv[FLAG_CONQUE].PtMagie ;

	if( NbBonus>0 )
	{
		if( NbBonus>nb )	NbBonus = nb ;

		if( (n = ExtraBonus(	x, y, z,
				(100*MUL_ANGLE),
				ptrobj->Obj.Beta,
				SPRITE_COEUR,
				NbBonus ))
				!= -1 )
		{
			// C'est crade car deja fait dans ExtraBonus
			InitFly( &ListExtra[n], (100*MUL_ANGLE), ptrobj->Obj.Beta, 50, 16 ) ;
			TabInv[FLAG_CONQUE].PtMagie -= NbBonus ;

			// Cliquetis conque vide
			HQ_3D_MixSample( SAMPLE_BONUS, 0x1000, 0, 1, x, y , z ) ;
		}
	}
	else
	{
		// Cliquetis conque vide
		HQ_3D_MixSample( SAMPLE_CONQUE_VIDE, 0x1000, 0, 1, x, y , z ) ;
	}
}

/*══════════════════════════════════════════════════════════════════════════*/
uint16_t	ChoiceAnimGant( void )
{
	T_OBJET	*ptrobj = &ListObjet[NUM_PERSO] ;
	T_EXTRA *ptrextra ;
	int32_t	num ;
	int32_t	x, z ;
	int32_t	angle, value ;

	x = ptrobj->Obj.X ;
	z = ptrobj->Obj.Z ;

	num = PlusProcheExtra( x, z, EXTRA_RENVOYABLE ) ;

	if( num!=-1 )
	{
		ptrextra = &ListExtra[num] ;

		angle = GetAngle2D( x, z, ptrextra->PosX, ptrextra->PosZ ) ;

		value = (ptrobj->Obj.Beta-angle) & (MAX_ANGLE-1) ;

		if( value>2048 )	return( GEN_ANIM_GANT_DROIT ) ;
		else			return( GEN_ANIM_GANT_GAUCHE ) ;
	}

	// si pas d'extra, brasse dans le vide en anim gant droit
	return( GEN_ANIM_GANT_DROIT ) ;
}
/*══════════════════════════════════════════════════════════════════════════*/

/*----------------------------------------------------------------------*/
void	InitBodyZV( T_OBJET *ptrobj )
{
	T_BODY_HEADER	*ptr ;
	int32_t	size ;
	int32_t	x0,x1,z0,z1 ;

	ptr = (T_BODY_HEADER*)GivePtrBody(ptrobj->Obj.Body.Num) ;

	x0 =  ptr->XMin ;
	x1 =  ptr->XMax ;
	ptrobj->YMin =  (int16_t)ptr->YMin ;
	ptrobj->YMax =  (int16_t)ptr->YMax ;
	z0 =  ptr->ZMin ;
	z1 =  ptr->ZMax ;

	if( ptrobj->Flags & MINI_ZV )
	{
		// plus petit
		if( x1 - x0  <  z1 - z0 )
			size = (x1-x0)/2 ;
		else
			size = (z1-z0)/2 ;
	}
	else
	{
		// moyenne
		size = ((x1-x0)+(z1-z0))/4 ;
	}

	ptrobj->XMin =  (int16_t)-size ;
	ptrobj->XMax =  (int16_t)+size ;
	ptrobj->ZMin =  (int16_t)-size ;
	ptrobj->ZMax =  (int16_t)+size ;
}

/*----------------------------------------------------------------------*/
/* recherche des options d'anims */

#define	GET_int8_t	(*ptrc++)
#define	GET_int16_t	(*(int16_t*)ptrc) ; ptrc+=2
#define	GET_int32_t	(*(int32_t*)ptrc) ; ptrc+=4

void	GereAnimAction( T_OBJET *ptrobj, uint8_t numobj )
{
	T_EXTRA	*ptrextra = NULL ;
	int32_t	sample ;
	int32_t	decal ;
	int32_t	anim ;
	int32_t	point ;
	int32_t	x,y,z ;
	int32_t	alpha ;
	int32_t	beta ;
	int32_t	vitesse ;
	int32_t	repeat ;
	int32_t	dist ;
	int32_t	testframe ;
	int32_t	last_extra = -1 ;
	uint8_t	*ptrc ;
	int32_t	n, nb ;
	int16_t	sprite ;
	uint8_t	poids ;
	uint8_t	force ;
	uint8_t	search ;

	anim = ptrobj->Obj.Anim.Num ;

	ptrc = ptrobj->PtrAnimAction ;

	testframe = ptrobj->Obj.LastFrame+1 ;

	nb = *ptrc++ ;
	for( n=0; n<nb; n++ )
	{
		if( last_extra!=-1 )
		{
			ptrextra = &ListExtra[last_extra] ;
			last_extra = -1 ;
		}

		switch( *ptrc++ )
		{
		case F_ZV:
			if( testframe == *ptrc++ )
			{
				ptrobj->XMin = GET_int16_t ;
				ptrobj->YMin = GET_int16_t ;
				ptrobj->ZMin = GET_int16_t ;
				ptrobj->XMax = GET_int16_t ;
				ptrobj->YMax = GET_int16_t ;
				ptrobj->ZMax = GET_int16_t ;
			}
			else	ptrc += 12 ; // 6 int16_t
			break ;

		case F_ZV_ANIMIT:
			if( testframe == *ptrc++ )
			{
				InitBodyZV( ptrobj ) ;
			}
			break ;

		case F_SUPER_HIT:
			if( testframe == *ptrc++
			AND !(ptrobj->WorkFlags&WAIT_SUPER_HIT) )
			{
				ptrobj->HitForce = GET_int8_t ;
				ptrobj->WorkFlags |= OK_SUPER_HIT ;

				ptrobj->Coord.SHit.SHitX = GET_int16_t ;
				ptrobj->Coord.SHit.SHitY = GET_int16_t ;
				ptrobj->Coord.SHit.SHitZ = GET_int16_t ;

				ptrobj->SizeSHit = GET_int16_t ;

				Rotate( ptrobj->Coord.SHit.SHitX,
					ptrobj->Coord.SHit.SHitZ,
					ptrobj->Obj.Beta ) ;

				ptrobj->Coord.SHit.SHitX = X0 + ptrobj->Obj.X ;
				ptrobj->Coord.SHit.SHitY += ptrobj->Obj.Y ;
				ptrobj->Coord.SHit.SHitZ = Z0 + ptrobj->Obj.Z ;
			}
			else	ptrc += 9 ; // 4 int16_t + 1 int8_t
			break ;

		case F_HIT:
			if( testframe == *ptrc++ )
			{
				ptrobj->HitForce = GET_int8_t ;
				ptrobj->WorkFlags |= OK_HIT ;
			}
			else	ptrc++ ;
			break ;

		case F_SAMPLE:
			if( testframe == *ptrc++ )
			{
				HQ_3D_MixSample( *(int16_t*)ptrc, 0x1000, 0, 1,
					ptrobj->Obj.X, ptrobj->Obj.Y, ptrobj->Obj.Z ) ;
			}
			ptrc += 2 ;
			break ;

		case F_NEW_SAMPLE:
			if( testframe == *ptrc++ )
			{
				sample = GET_int16_t ;
				decal = GET_int16_t ;
				ParmSampleVolume = GET_int8_t ;		// volume
				y = GET_int16_t ;		// frequence

				HQ_3D_MixSample( sample, y, decal, 1,
					ptrobj->Obj.X, ptrobj->Obj.Y, ptrobj->Obj.Z ) ;
			}
			else ptrc += 7 ;
			break ;

		case F_SAMPLE_RND:
			if( testframe == *ptrc++ )
			{
				sample = GET_int16_t ;
				decal = GET_int16_t ;
				HQ_3D_MixSample( sample, 0x1000, decal, 1,
					ptrobj->Obj.X, ptrobj->Obj.Y, ptrobj->Obj.Z ) ;
			}
			else	ptrc += 4 ;
			break ;

		case F_THROW:
			if( testframe == *ptrc++ )
			{
				point = GET_int16_t ;
				sprite = GET_int8_t ;
				alpha = GET_int16_t ;
				beta = ptrobj->Obj.Beta + GET_int16_t ;
				vitesse = GET_int16_t ;
				poids = GET_int8_t ;
				force = GET_int8_t ;

				last_extra = ThrowExtra( 	numobj,
						ptrobj->Obj.X,ptrobj->Obj.Y+point,ptrobj->Obj.Z,
						sprite,
						alpha, beta, vitesse, poids,
						force ) ;
			}
			else	ptrc += 11 ;
			break ;

		case F_THROW_MAGIC:
			if( MagicBall == -1 )	// pas de balle en cours
			{

			if( testframe == *ptrc++ )	// frame ok ?
			{
				point = GET_int16_t ;
				alpha = GET_int16_t ;
				vitesse = GET_int16_t ;
				poids = GET_int8_t ;

				ThrowMagicBall(	ptrobj->Obj.X,
						ptrobj->Obj.Y + point,
						ptrobj->Obj.Z,
						alpha,
						ptrobj->Obj.Beta,
						vitesse,
						poids ) ;

				last_extra = MagicBall ;
			}
			else	ptrc += 7 ;

			}
			else	ptrc += 8 ;

			break ;

		case F_SAMPLE_REPEAT:
			if( testframe == *ptrc++ )
			{
				sample = GET_int16_t ;
				repeat = GET_int16_t ;
				decal = GET_int16_t ;
				ParmSampleVolume = GET_int8_t ; // volume
				y = GET_int16_t ;		// frequence

				if( ptrobj->SampleAlways
				AND ((ptrobj->SampleAlways>>8)&0xFFFF)!=sample )
				{
					HQ_StopOneSample( ptrobj->SampleAlways ) ;
					ptrobj->SampleAlways = 0 ;
				}

				if( !ptrobj->SampleAlways
				OR  !IsSamplePlaying( ptrobj->SampleAlways ) )
				{
					ptrobj->SampleVolume = (uint8_t)ParmSampleVolume ;

					ptrobj->SampleAlways = HQ_3D_MixSample( sample, y, decal, repeat,
						ptrobj->Obj.X, ptrobj->Obj.Y, ptrobj->Obj.Z ) ;
				}
				else
				{
					if( ptrobj->SampleAlways )	sample = ptrobj->SampleAlways ;

					HQ_3D_ChangePanSample( sample,
						ptrobj->Obj.X, ptrobj->Obj.Y, ptrobj->Obj.Z ) ;
				}
			}
			else	ptrc += 9 ;
			break ;

		case F_THROW_SEARCH:
			if( testframe == *ptrc++ )
			{
				point = GET_int16_t ;
				sprite = GET_int8_t ;
				search = GET_int8_t ;
				vitesse = GET_int16_t ;
				force = GET_int8_t ;

				last_extra = ExtraSearch( numobj,
						ptrobj->Obj.X,ptrobj->Obj.Y+point,ptrobj->Obj.Z,
						sprite,
						search, vitesse, force ) ;
			}
			else	ptrc += 7 ;
			break ;

		case F_THROW_ALPHA:
			if( testframe == *ptrc++ )
			{
				dist = Distance2D(ptrobj->Obj.X,
						ptrobj->Obj.Z,
						ListObjet[NUM_PERSO].Obj.X,
						ListObjet[NUM_PERSO].Obj.Z ) ;

				alpha =	GetAngle2D(ptrobj->Obj.Y,0,
						ListObjet[NUM_PERSO].Obj.Y,
						dist  ) ;

				point = GET_int16_t ;
				sprite = GET_int8_t ;
				alpha += GET_int16_t ;
				beta = ptrobj->Obj.Beta + GET_int16_t ;
				vitesse = GET_int16_t ;
				poids = GET_int8_t ;
				force = GET_int8_t ;

				last_extra = ThrowExtra( numobj,
						ptrobj->Obj.X,ptrobj->Obj.Y+point,ptrobj->Obj.Z,
						sprite,
						alpha, beta, vitesse, poids,
						force ) ;
			}
			else	ptrc += 11 ;
			break ;

		case F_SAMPLE_STOP:
			if( testframe == *ptrc++ )
			{
				sample = GET_int16_t ;

				if( ptrobj->SampleAlways
				AND ((ptrobj->SampleAlways>>8)&0xFFFF)==sample )
				{
					sample = ptrobj->SampleAlways ;
					ptrobj->SampleAlways = 0 ;
				}

				HQ_StopOneSample( sample ) 	;
			}
			else	ptrc += 2 ;
			break ;

		case F_LEFT_STEP:
			if( testframe == *ptrc++ )	/* frame */
			{
				sample = ptrobj->CodeJeu ;

				sample &= 0x0F ;

				if( sample )	// rien
				{

					HQ_3D_MixSample( sample + BaseLeftStepSound[CubeMode],
							0x1000, 1000,
							1,
							ptrobj->Obj.X, ptrobj->Obj.Y, ptrobj->Obj.Z ) ;
				}
			}
			break ;

		case F_RIGHT_STEP:
			if( testframe == *ptrc++ )
			{
				sample = ptrobj->CodeJeu ;

				sample &= 0x0F ;

				if( sample )	// rien
				{
					HQ_3D_MixSample( sample + BaseRightStepSound[CubeMode],
							0x1000, 1000,
							1,
							ptrobj->Obj.X, ptrobj->Obj.Y, ptrobj->Obj.Z ) ;
				}
			}
			break ;

		case F_HIT_TWINSEN:
			if( testframe == *ptrc++ )
			{
				ptrobj->HitForce = MagicHitForce[ MagicLevel ] ;
				ptrobj->WorkFlags |= OK_HIT ;

			}
			break ;

		case F_THROW_3D:
			if( testframe == *ptrc++ )
			{
				x = GET_int16_t ;
				y = GET_int16_t ;
				z = GET_int16_t ;

				Rotate( x,z, ptrobj->Obj.Beta ) ;

				x = X0 + ptrobj->Obj.X ;
				y += ptrobj->Obj.Y ;
				z = Z0 + ptrobj->Obj.Z ;

				sprite = GET_int8_t ;
				alpha = GET_int16_t ;
				beta = ptrobj->Obj.Beta + GET_int16_t ;
				vitesse = GET_int16_t ;
				poids = GET_int8_t ;
				force = GET_int8_t ;

				last_extra = ThrowExtra( numobj,
						x,y,z,
						sprite,
						alpha, beta, vitesse, poids,
						force ) ;
			}
			else	ptrc += 15 ;
			break ;

		case F_THROW_3D_ALPHA:
			if( testframe == *ptrc++ )
			{
				dist = Distance2D(ptrobj->Obj.X,
						ptrobj->Obj.Z,
						ListObjet[NUM_PERSO].Obj.X,
						ListObjet[NUM_PERSO].Obj.Z ) ;

				alpha =	GetAngle2D(ptrobj->Obj.Y,0,
						ListObjet[NUM_PERSO].Obj.Y,
						dist  ) ;

				x = GET_int16_t ;
				y = GET_int16_t ;
				z = GET_int16_t ;

				Rotate( x,z, ptrobj->Obj.Beta ) ;

				x = X0 + ptrobj->Obj.X ;
				y += ptrobj->Obj.Y ;
				z = Z0 + ptrobj->Obj.Z ;

				sprite = GET_int8_t ;
				alpha += GET_int16_t ;
				beta = ptrobj->Obj.Beta + GET_int16_t ;
				vitesse = GET_int16_t ;
				poids = GET_int8_t ;
				force = GET_int8_t ;

				last_extra = ThrowExtra( numobj,
						x,y,z,
						sprite,
						alpha, beta, vitesse, poids,
						force ) ;
			}
			else	ptrc += 15 ;
			break ;

		case F_THROW_3D_SEARCH:
			if( testframe == *ptrc++ )
			{
				x = GET_int16_t ;
				y = GET_int16_t ;
				z = GET_int16_t ;

				Rotate( x,z, ptrobj->Obj.Beta ) ;

				x = X0 + ptrobj->Obj.X ;
				y += ptrobj->Obj.Y ;
				z = Z0 + ptrobj->Obj.Z ;

				sprite = GET_int8_t ;
				search = GET_int8_t ;
				vitesse = GET_int16_t ;
				force = GET_int8_t ;

				last_extra = ExtraSearch( numobj,
						x,y,z,
						sprite,
						search, vitesse, force ) ;
			}
			else	ptrc += 11 ;
			break ;

		case F_THROW_3D_MAGIC:
			if( MagicBall == -1 )	// pas de balle en cours
			{

			if( testframe == *ptrc++ )
			{
				x = GET_int16_t ;
				y = GET_int16_t ;
				z = GET_int16_t ;

				Rotate( x,z, ptrobj->Obj.Beta ) ;

				x = X0 + ptrobj->Obj.X ;
				y += ptrobj->Obj.Y ;
				z = Z0 + ptrobj->Obj.Z ;

				alpha = GET_int16_t ;
				vitesse = GET_int16_t ;
				poids = GET_int8_t ;

				ThrowMagicBall(	x,y,z,
						alpha,
						ptrobj->Obj.Beta,
						vitesse,
						poids ) ;

				last_extra = MagicBall ;
			}
			else	ptrc += 11 ;

			}
			else	ptrc += 12 ;
			break ;


		case F_THROW_OBJ_3D:
			if( testframe==*ptrc++ )	// frame
			{
				x = GET_int16_t ;
				y = GET_int16_t ;
				z = GET_int16_t ;

				Rotate( x,z, ptrobj->Obj.Beta ) ;

				x = X0 + ptrobj->Obj.X ;
				y += ptrobj->Obj.Y     ;
				z = Z0 + ptrobj->Obj.Z ;

				sprite = GET_int16_t ; // IndexFile3d
				alpha = GET_int16_t ;
				beta = GET_int16_t ;
				beta += ptrobj->Obj.Beta ;
				vitesse = GET_int16_t ;
				poids = GET_int8_t ;
				force = GET_int8_t ;

				last_extra = ThrowExtraObj( numobj,
						x,y,z,
						sprite, // IndexFile3d
						alpha, beta, vitesse,
						-1, // alpharot suivant la trajectoire du throw
						poids, force ) ;
			}
			else	ptrc += 16 ;
			break ;

		case F_FLOW_3D:
			if( testframe==*ptrc++ )	/* frame */
			{
				x = GET_int16_t ;
				y = GET_int16_t ;
				z = GET_int16_t ;

				Rotate( x,z, ptrobj->Obj.Beta ) ;

				x = X0 + ptrobj->Obj.X ;
				y += ptrobj->Obj.Y ;
				z = Z0 + ptrobj->Obj.Z ;

				sprite = GET_int8_t ;	// Numéro de flow
				CreateParticleFlow( 0, numobj, 0,
						    x, y, z,
						    ptrobj->Obj.Beta,
						    sprite ) ;
			}
			else	ptrc += 7 ;
			break ;

		case F_THROW_DART:
			if( testframe==*ptrc++ )	/* frame */
			{
				point = GET_int16_t ;
				alpha = GET_int16_t ;
				vitesse = GET_int16_t ;
				poids = GET_int8_t ;

				last_extra = ThrowDart(	ptrobj->Obj.X,
						ptrobj->Obj.Y + point,
						ptrobj->Obj.Z,
						alpha,
						ptrobj->Obj.Beta,
						vitesse,
						poids ) ;
			}
			else	ptrc += 8 ;
			break ;

		case F_SHIELD:
			x = *ptrc++ ;	// First Frame
			y = *ptrc++ ;	// Last  Frame

			if( testframe>=x
			AND testframe<=y )
			{
				ptrobj->WorkFlags |= FRAME_SHIELD ;
			}
			break ;

		case F_SAMPLE_MAGIC:
			if( testframe == *ptrc++ )	/* frame */
			{
				SampleMagicBall( ptrobj->Obj.X, ptrobj->Obj.Y, ptrobj->Obj.Z ) ;
			}
			break ;

		case F_THROW_3D_CONQUE:
			if( testframe == *ptrc++ )	/* frame */
			{
				x = GET_int16_t ;
				y = GET_int16_t ;
				z = GET_int16_t ;

				Rotate( x,z, ptrobj->Obj.Beta ) ;

				x = X0 + ptrobj->Obj.X ;
				y += ptrobj->Obj.Y ;
				z = Z0 + ptrobj->Obj.Z ;

				sprite = *ptrc++ ;	// Nb Coeurs

				ThrowConque( ptrobj, x, y, z, sprite ) ;
			}
			else	ptrc += 7 ;
			break ;

		case F_IMPACT:
			if( ptrextra
			AND !(ptrextra->Flags&EXTRA_NEW_IMPACT) )
			{
				ptrextra->Flags |= (EXTRA_IMPACT|EXTRA_NEW_IMPACT) ;
				ptrextra->Impact = GET_int16_t ;
			}
			else	ptrc+=2 ;
			break ;

		case F_RENVOIE:
			if( testframe == *ptrc++ )	/* frame */
			{
				ptrobj->WorkFlags |= OK_RENVOIE ;
			}
			break ;

		case F_RENVOYABLE:
			if( ptrextra
			AND !(ptrextra->Flags&EXTRA_RENVOYABLE) )
			{
				ptrextra->Flags |= EXTRA_RENVOYABLE ;
				ptrextra->NewForce = GET_int8_t ;
			}
			else	ptrc++ ;
			break ;

		case F_TRANSPARENT:
			if( ptrextra
			AND !(ptrextra->Flags&EXTRA_TRANSPARENT) )
			{
				ptrextra->Flags |= EXTRA_TRANSPARENT ;
			}
			break ;

		case F_SCALE:
			if( ptrextra AND !ptrextra->Scale )
			{
				ptrextra->Scale = GET_int32_t ;
			}
			else	ptrc+=4 ;
			break ;

		case F_LEFT_JUMP:
			if( ptrobj->Obj.LastFrame==-1 )// on prend la frame de bouclage
			{
				testframe = ptrobj->Obj.NextFrame ;
			}

			if( testframe == *ptrc++ )	/* frame */
			{
				ptrobj->WorkFlags &= ~(RIGHT_JUMP) ;
				ptrobj->WorkFlags |=  LEFT_JUMP ;
			}
			break ;

		case F_RIGHT_JUMP:
			if( ptrobj->Obj.LastFrame==-1 )// on prend la frame de bouclage
			{
				testframe = ptrobj->Obj.NextFrame ;
			}

			if( testframe == *ptrc++ )	/* frame */
			{
				ptrobj->WorkFlags &= ~(LEFT_JUMP) ;
				ptrobj->WorkFlags |=  RIGHT_JUMP ;
			}
			break ;

		case F_IMPACT_3D:
			if( testframe==*ptrc++ )	/* frame */
			{
				x = GET_int16_t ;
				y = GET_int16_t ;
				z = GET_int16_t ;

				Rotate( x,z, ptrobj->Obj.Beta ) ;

				x = X0 + ptrobj->Obj.X ;
				y += ptrobj->Obj.Y ;
				z = Z0 + ptrobj->Obj.Z ;

				sprite = GET_int16_t ;	// Numéro d'impact

				DoImpact( sprite, x, y, z, numobj ) ;
			}
			else	ptrc += 8 ;
			break ;

		case F_THROW_MAGIC_EXTRA:
			if( testframe == *ptrc++ )
			{
				point = GET_int16_t ;	// numero point 3D

				sprite = GET_int8_t ;
				alpha = GET_int16_t ;
				vitesse = GET_int16_t ;
				poids = GET_int8_t ;

				if( MagicLevel>1 )
				{
					sprite += (int16_t)(MagicLevel-1) ;
				}

				// ATTENTION: cet extra suit l'aplha de l'objet
				//	      (cf buggy)

				last_extra = ThrowExtra( numobj,
						point,0,0,// magouille: x,y,z seront calculés +tard
						sprite,
						alpha-ListBuggy[0].Alpha,// dédié buggy
						ptrobj->Obj.Beta,
						vitesse, poids,
						MagicBallHitForce[MagicLevel] ) ;

				ListBuggy[0].Alpha = 0 ;// au cas où ce soit utilisé par 1 autre obj
						// que le buggy

				if( last_extra!=-1 )// ok
				{
					ptrobj->WorkFlags |= WAIT_COORD ;

					// ATTENTION: cet objet ne peut pas avoir
					// de SuperHit à cette frame
					ptrobj->Coord.A3DS.Num = last_extra ;
				}
			}
			else	ptrc += 8 ;
			break ;

		case F_THROW_FOUDRE:
			if( testframe == *ptrc++ )	// frame ok ?
			{
				ThrowExtraFoudre( numobj ) ;
				MagicPoint = 0 ;	// ?
			}
			break ;

		default:
			return ;
		}
	}
}

/*══════════════════════════════════════════════════════════════════════════*/
/*══════════════════════════════════════════════════════════════════════════*/

int32_t	SearchAnim( uint16_t numanim, int32_t numobj )
{
	uint8_t	command ;
	T_OBJET	*ptrobj ;
	int32_t	hqranim ;
	uint8_t	*ptrc	;
	uint16_t	numgene ;

	ptrobj = &ListObjet[numobj] ;
	ptrc = ptrobj->PtrFile3D ;

	SearchPtrAnimAction = 0 ;

	while( (command = *ptrc++) != 255 )
	{
		switch( command )
		{
		case F_ANIM:
			numgene = *(uint16_t*)ptrc ; 	// lit num name generique
			ptrc+=2 ;

			if( numanim == numgene )	// ok trouve
			{
				ptrc++ ; // saute size anim

				hqranim = *(int16_t*)ptrc ;

				ptrc += 2 ;

				if( *ptrc++ ) // anim possede action ?
				{
					SearchPtrAnimAction = ptrc-1 ;
				}

				return hqranim ;
			}
			else
			{
				ptrc += *ptrc ;	// next anim
			}
			break ;
		default:
			ptrc++ ;	// gen
			ptrc += *ptrc ;
		}
	}
	return -1 ;
}

/*══════════════════════════════════════════════════════════════════════════*/

int32_t	SearchBody( uint8_t numbody, int32_t numobj )
{
	uint8_t	command ;
	T_OBJET	*ptrobj ;
	int32_t	hqrbody ;
	uint8_t	*ptrc	;
	uint8_t	numgene ;

	ptrobj = &ListObjet[numobj] ;
	ptrc = ptrobj->PtrFile3D ;

	SearchPtrAnimAction = 0 ;

	while( (command = *ptrc++) != 255 )
	{
		switch( command )
		{
		case F_BODY:
			numgene = *ptrc++ ; 	// lit num name generique

			if( numbody==numgene )	// ok trouve
			{
				ptrc++ ; // saute size anim

				hqrbody = *(int16_t*)ptrc ;

				ptrc += 2 ;

				M_XMin = -32000 ;

				if( *ptrc++  ) // body possede action ?
				{
					if( *ptrc++ == F_ZV )
					{
						M_XMin = *(int16_t*)ptrc ;
						ptrc += 2 ;
						M_YMin = *(int16_t*)ptrc ;
						ptrc += 2 ;
						M_ZMin = *(int16_t*)ptrc ;
						ptrc += 2 ;
						M_XMax = *(int16_t*)ptrc ;
						ptrc += 2 ;
						M_YMax = *(int16_t*)ptrc ;
						ptrc += 2 ;
						M_ZMax = *(int16_t*)ptrc ;
						ptrc += 2 ;
					}
				}

				return hqrbody;
			}
			else
			{
				ptrc += *ptrc ;	// next anim
			}
			break ;

		case F_ANIM:
			ptrc+=2 ;	// gen sur int16_t
			ptrc += *ptrc ;
			break ;

		default:
			ptrc++ ;	// gen
			ptrc += *ptrc ;
		}
	}
	return -1 ;
}
/*══════════════════════════════════════════════════════════════════════════*/

