#include "C_EXTERN.H"
#include "DIRECTORIES.H"

/*══════════════════════════════════════════════════════════════════════════*
	     █▀▀▀█ █▀▀▀█ █▀▀▀█ ▀▀█▀▀  █    █▀▀▀▀ █     █▀▀▀▀ ██▀▀▀
	     ██▀▀▀ ██▀▀█ ██▀█▀   ██   ██   ██    ██    ██▀▀  ▀▀▀▀█
	     ▀▀    ▀▀  ▀ ▀▀  ▀   ▀▀   ▀▀   ▀▀▀▀▀ ▀▀▀▀▀ ▀▀▀▀▀ ▀▀▀▀▀
 *══════════════════════════════════════════════════════════════════════════*/
/*──────────────────────────────────────────────────────────────────────────*/

// type de point
#define	DOT_DEAD	0	// point mort, on ne le gere plus
#define	DOT_DISPLAY	1	// point vivant et visible
#define	DOT_WAIT	2	// point vivant mais attendant d'etre lancé

#ifdef	LBA_EDITOR
extern	int32_t	FlagInfos ;

#define	MAX_PART_FLOW	100
#else
//T_HQR_HEADER	*HQR_Flows ;
#endif

T_FLOW	*TabPartFlow ;

S_PART_FLOW	ListPartFlow[MAX_FLOWS] ;
S_ONE_DOT	*ListFlowDots ;

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
void	RazListPartFlow( )
{
	S_PART_FLOW	*ptrf = ListPartFlow ;
	int32_t n;

	for( n=0; n<MAX_FLOWS; n++, ptrf++ )
	{
		ptrf->NbDot = 0 ;
	}
}

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
uint32_t	InitPartFlow()
{
	S_ONE_DOT	*ptrd ;
	S_PART_FLOW	*ptrf = ListPartFlow ;
	int32_t n;
        char tmpFilePath[ADELINE_MAX_PATH];

#ifdef	LBA_EDITOR
	char	filename[ADELINE_MAX_PATH] ;
	int32_t	handle ;
	int32_t	flag = FALSE ;
	T_FLOW	*flow ;
	char	*ptr ;
	char	*com ;	// pointeur sur le commentaire

	Message( "Chargement des flots de pixels...", FALSE ) ;
	BoxUpdate() ;

	TabPartFlow = (T_FLOW *)Malloc( sizeof(T_FLOW)*MAX_PART_FLOW ) ;
	if( !TabPartFlow )	return( FALSE ) ;

	flow = TabPartFlow ;

	n = 0 ;

	while( !flag AND n<MAX_PART_FLOW )
	{
		strcpy( filename, PATH_FLOW )	;

		InitDefFile( PATH_FLOW"flow.def" ) ;
		ptr = DefFileBufferReadString( Itoa( n ) ) ;

		if( ptr )
		{
			// Vire commentaire
			com = (char *) strchr( ptr, ';' ) ;
			if( com )	*com = '\0' ;

			strcat( filename, ptr ) ;
			AddExt( filename, ".FLW" ) ;

			handle = OpenRead( filename ) ;

			if( handle )
			{
				Read( handle, flow, sizeof(T_FLOW) ) ;
				Close( handle ) ;
				flow->Bank *= 16 ;

				// protec par rapport à l'outil
				if( flow->NbDot>MAX_FLOW_DOTS )
				{
					flow->NbDot = MAX_FLOW_DOTS ;
					Beep() ;
					MessageF( TRUE, "Warning: Flow %s : NbDots>%d", filename, MAX_FLOW_DOTS ) ;
				}
			}
			else
			{
				strcat( filename, " introuvable (InitPartFlow())." ) ;
				Message( filename, TRUE ) ;
			}

			n++ ;
			flow++ ;
		}
		else	flag = TRUE ;
	}

	if( n>=MAX_PART_FLOW )
	{
		Message( "Warning: Tableau de flows trop petit !", TRUE ) ;
	}

	Cls() ;		// Efface message
	BoxUpdate() ;
#else
	GetResPath(tmpFilePath, ADELINE_MAX_PATH, RESS_HQR_NAME);
	Load_HQR( tmpFilePath, TabPartFlow, RESS_FLOW ) ;
#endif

#ifdef	LBA_EDITOR
	ListFlowDots = (S_ONE_DOT *)Malloc( sizeof(S_ONE_DOT)*MAX_FLOW_DOTS*MAX_FLOWS ) ;
	if( !ListFlowDots )	return FALSE ;
#endif

	ptrd = ListFlowDots ;

	for( n=0; n<MAX_FLOWS; n++, ptrf++ )
	{
		ptrf->PtrListDot = ptrd ;
		ptrd += MAX_FLOW_DOTS ;
		ptrf->NbDot = 0 ;
	}

	return( TRUE ) ;
}

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
#ifdef	LBA_EDITOR
void	FreePartFlow( )
{
	if( TabPartFlow )	Free( TabPartFlow ) ;

	if( ListFlowDots )
	{
		Free( ListFlowDots ) ;
		ListFlowDots = NULL ;
	}
}
#endif

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀

#define	LoadPartFlow(num_flow)	(TabPartFlow+num_flow)

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
S_PART_FLOW	*GetFirstFlowDispo( void )
{
	int32_t	n ;
	S_PART_FLOW	*ptrf = ListPartFlow ;
	// cherche slot

	for( n=0; n<MAX_FLOWS; n++, ptrf++ )
	{
		if( ptrf->NbDot == 0 )	return ptrf ;
	}

	return NULL ;
}

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
uint32_t	CreateParticleFlow(	int32_t flag, int32_t owner, int32_t num_point,
				int32_t orgx, int32_t orgy, int32_t orgz,
				int32_t beta, int32_t num_flow  )
{
	int32_t		n ;
	S_PART_FLOW	*ptrf ;
	S_ONE_DOT	*ptrd ;
	T_FLOW		*flow ;
	int32_t		vitesse ;
	int32_t		demi_speed ;
	int32_t		demi_weight ;
	int32_t		demi_ouvalpha ;
	int32_t		demi_ouvbeta ;
	int32_t		bank ;

	// cherche slot
	ptrf = GetFirstFlowDispo() ;
	if( !ptrf )	return( FALSE ) ;		// pas de place

	flow = LoadPartFlow( num_flow ) ;
	if( !flow )	return( FALSE ) ;

	bank = flow->Bank ;

#ifndef	LBA_EDITOR	// Dans l'outil, c'est fait dans InitPartFlow
	bank *= 16 ;

	// protec par rapport à l'outil makeflow
	if( flow->NbDot>MAX_FLOW_DOTS )
	{
		flow->NbDot = MAX_FLOW_DOTS ;
	}
#endif

	if( flow->NbDot<=MAX_FLOW_DOTS )
	{
		ptrf->NbDot = flow->NbDot ;
	}
	else
	{
		ptrf->NbDot = MAX_FLOW_DOTS ;
	}

	ptrf->Flag = flag ;

	// copie zv particule
	ptrf->XMin = flow->XMin ;
	ptrf->YMin = flow->YMin ;
	ptrf->ZMin = flow->ZMin ;
	ptrf->XMax = flow->XMax ;
	ptrf->YMax = flow->YMax ;
	ptrf->ZMax = flow->ZMax ;

	ptrf->FlowTimerStart = TimerRefHR ;

	// est-ce un flow qui va attendre des coor
	if( !(flag & FLOW_WAIT_COOR) )
	{
		ptrf->OrgX = orgx ;
		ptrf->OrgY = orgy ;
		ptrf->OrgZ = orgz ;
	}
	else
	{
		ptrf->Owner = owner;
		ptrf->NumPoint = num_point;
	}

	demi_speed = (flow->Speed>>1) ;
	if( !demi_speed )	demi_speed=1 ;

	demi_weight = (flow->Weight>>1) ;
	if( !demi_weight )	demi_weight=1 ;

	demi_ouvalpha = (flow->OuvertureAlpha>>1) ;
	demi_ouvbeta = (flow->OuvertureBeta>>1) ;

	beta += flow->Beta ;

	ptrd =	ptrf->PtrListDot ;

	for( n=0; n<ptrf->NbDot; n++, ptrd++ )
	{
		if( !(flag & FLOW_WAIT_COOR) )
		{
			ptrd->X = orgx ;
			ptrd->Y = orgy ;
			ptrd->Z = orgz ;
		}

		vitesse = (MyRnd(demi_speed) + flow->Speed) ;

		ptrd->Poids = MyRnd(demi_weight) + flow->Weight ;

		Rotate( vitesse,0, flow->Alpha + MyRnd(flow->OuvertureAlpha) - demi_ouvalpha ) ;
		ptrd->Vy = -Z0 ;

		Rotate( 0, X0, beta + MyRnd(flow->OuvertureBeta) - demi_ouvbeta ) ;
		ptrd->Vx = X0 ;
		ptrd->Vz = Z0 ;

		if( flow->Delay )	ptrd->Delay = MyRnd( flow->Delay ) ;
		else		ptrd->Delay = 0 ;
		ptrd->Couleur = bank + MyRnd(flow->Range)+flow->Coul ;

		ptrd->Mode = DOT_WAIT ;
	}

	return( TRUE ) ;
}

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
// Générateur d'extras à partir du moteur de flows

// ATTENTION:

//	FLOW_EXTRA_SPRITE: num et num2 correspondent à sprite_deb et sprite_fin

//	FLOW_EXTRA_OBJ: num correspond au body en mode Jeu, sinon le nom du
//			body doit se trouver dans FicName en mode Outil

//	FLOW_EXTRA_POF: num correspond au numéro de pof dans 'pof.def'
//                      num2 correspond à SpeedRot
//                      scale correspond à scale_deb
//                      transparent correspond à scale_fin

uint32_t	CreateExtraParticleFlow(int32_t type, int32_t owner, int32_t num, int32_t num2,
				int32_t orgx, int32_t orgy, int32_t orgz,
				int32_t beta, int32_t num_flow, int32_t hitforce,
				int32_t scale, int32_t transparent, int32_t tempo )
{
	T_FLOW	*flow ;
	int32_t	n ;
	int32_t	vitesse ;
	int32_t	demi_speed ;
	int32_t	demi_weight ;
	int32_t	demi_ouvalpha ;
	int32_t	demi_ouvbeta ;
	int32_t	num_extra ;
	int32_t	nbdot ;
	int32_t	poids ;
	int32_t	delay ;
	int32_t	speedrot ;
	int32_t	shadow = 0; // yaz

	flow = LoadPartFlow( num_flow ) ;
	if( !flow )	return( FALSE ) ;

	nbdot = flow->NbDot ;

	if( nbdot>MAX_FLOW_EXTRA_DOTS )
	{
		nbdot = MAX_FLOW_EXTRA_DOTS ;
	}

	demi_speed = (flow->Speed>>1) ;
	if( !demi_speed )	demi_speed=1 ;

	demi_weight = (flow->Weight>>1) ;
	if( !demi_weight )	demi_weight=1 ;

	demi_ouvalpha = (flow->OuvertureAlpha>>1) ;
	demi_ouvbeta = (flow->OuvertureBeta>>1) ;

	beta += flow->Beta ;

	for( n=0; n<nbdot; n++ )
	{
		vitesse = MyRnd(demi_speed) + flow->Speed ;

		poids = MyRnd(demi_weight) + flow->Weight ;

		if( flow->Delay )	delay = MyRnd( flow->Delay ) ;
		else			delay = 0 ;

		switch( type )
		{
			case FLOW_EXTRA_OBJ:
				num_extra = ThrowExtraObj( (uint8_t)owner, orgx, orgy, orgz,
#ifdef	LBA_EDITOR
				    FicName,
#else
				    num,
#endif
				    flow->Alpha + MyRnd(flow->OuvertureAlpha) - demi_ouvalpha,
				    beta + MyRnd(flow->OuvertureBeta) - demi_ouvbeta,
				    vitesse,
				    -1, // alpharot suivant la trajectoire du throw
				    (uint8_t)poids, (uint8_t)hitforce ) ;

#ifdef	LBA_EDITOR
				shadow = TRUE ;
#else
				shadow = 2 ;
#endif
				break ;

			case FLOW_EXTRA_SPRITE:
				if( num==num2 )	// Pas une anim
				{
					num_extra = ThrowExtra( (uint8_t)owner, orgx, orgy, orgz,
					    (int16_t)num,
					    flow->Alpha + MyRnd(flow->OuvertureAlpha) - demi_ouvalpha,
					    beta + MyRnd(flow->OuvertureBeta) - demi_ouvbeta,
					    vitesse, (uint8_t)poids, (uint8_t)hitforce ) ;

					if( num_extra!=-1 )
					{
						ListExtra[num_extra].Scale = scale ;
					}
				}
				else	// c'est une anim de sprites
				{
					num_extra = InitExtraAnimSprite( (uint8_t) owner, orgx, orgy, orgz,
							     (int16_t)num, (int16_t)num2,
							     tempo, scale,
							     transparent, (uint8_t)hitforce ) ;

					if( num_extra!=-1 )
					{
						InitFly(&ListExtra[num_extra],
							flow->Alpha + MyRnd(flow->OuvertureAlpha) - demi_ouvalpha,
							beta + MyRnd(flow->OuvertureBeta) - demi_ouvbeta,
							vitesse, (uint8_t)poids ) ;
					}
				}

#ifdef	LBA_EDITOR
				shadow = TRUE ;
#else
				shadow = 3 ;
#endif
				break ;

			case FLOW_EXTRA_POF:
				if( num2==-1 )	speedrot = vitesse	;
				else		speedrot = num2		;

				num_extra = InitExtraPof( orgx, orgy, orgz,
						(int16_t)num,
						flow->Alpha + MyRnd(flow->OuvertureAlpha) - demi_ouvalpha,
						beta + MyRnd(flow->OuvertureBeta) - demi_ouvbeta,
						vitesse, poids,
						scale, transparent, tempo,
						speedrot, 0 ) ;
				break ;

		}

		// ATTENTION: les extras générés par le moteur de flow peuvent
		// également toucher leur propriétaire
		if( num_extra!=-1 )
		{
			ListExtra[num_extra].Flags |= (EXTRA_HIT_ANY|EXTRA_WAIT_NO_COL_OWNER) ;

			if( Shadow<shadow )
			{
				ListExtra[num_extra].Flags |= EXTRA_NO_SHADOW ;
			}

			if( delay )
			{
				ListExtra[num_extra].Flags |= EXTRA_WAIT ;
				ListExtra[num_extra].Timer = TimerRefHR + delay ;
			}
		}
	}

	return( TRUE ) ;
}

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
int32_t	AffParticleFlow( S_PART_FLOW *ptrf )
{
	int32_t	n ;
	int32_t	flag = FALSE ;
	S_ONE_DOT	*ptrd ;

	ClearScreenMinMax() ;
	ptrd =	ptrf->PtrListDot ;
	for( n=0; n<ptrf->NbDot; n++, ptrd++ )
	{
		if( ptrd->Mode==DOT_DISPLAY )
		{
			X0 = ptrd->X ;
			Y0 = ptrd->Y ;
			Z0 = ptrd->Z ;

			LongWorldRotatePoint( X0, Y0, Z0 ) ;
			if( LongProjectPoint( X0, Y0, Z0 ) )
			{
#ifdef	LBA_EDITOR
				if( !(FlagInfos & INFO_BOX_FLOW) )
					Plot( Xp, Yp, ptrd->Couleur ) ;
				else
#endif
					BoxFlow( Xp, Yp, ptrd->Couleur ) ;

				if( Xp < ScreenXMin )	ScreenXMin = Xp ;
				if( Xp+1 > ScreenXMax )	ScreenXMax = Xp+1 ;
				if( Yp < ScreenYMin )	ScreenYMin = Yp ;
				if( Yp+1 > ScreenYMax )	ScreenYMax = Yp+1 ;
				flag = TRUE ;
			}
		}
	}

#ifdef	LBA_EDITOR
	if( FlagInfos & INFO_DRAW_ZV )
	{
		int32_t    x, y, z ;
		int32_t	xmin, ymin, zmin ;
		int32_t	xmax, ymax, zmax ;

		x = ptrf->OrgX ;
		y = ptrf->OrgY ;
		z = ptrf->OrgZ ;

		xmin = x + ptrf->XMin ;
		ymin = y + ptrf->YMin ;
		zmin = z + ptrf->ZMin ;
		xmax = x + ptrf->XMax ;
		ymax = y + ptrf->YMax ;
		zmax = z + ptrf->ZMax ;

		DrawCube( xmin, ymin, zmin, xmax, ymax, zmax, 0 ) ;
//		if( ClipXMin<0 )	ClipXMin = 0 ;
	}
	else if( FlagInfos & INFO_VISU_BOX )
	{
		Rect( ScreenXMin,ScreenYMin,ScreenXMax,ScreenYMax, RED ) ;
	}

#endif

	return flag ;	// si 0 pas besoin aff
}

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
// Anim particule sans l'afficher
int32_t	AnimParticleFlow( S_PART_FLOW *ptrf )
{
	int32_t	n ;
	int32_t	time ;
	int32_t	timew ;
	int32_t	flag = FALSE ;
	int32_t    x, y, z ;
	int32_t	xmin, ymin, zmin ;
	int32_t	xmax, ymax, zmax ;

	S_ONE_DOT	*ptrd ;

	time = TimerRefHR - ptrf->FlowTimerStart ;

	x = ptrf->OrgX ;
	y = ptrf->OrgY ;
	z = ptrf->OrgZ ;

	xmin = x + ptrf->XMin ;
	ymin = y + ptrf->YMin ;
	zmin = z + ptrf->ZMin ;
	xmax = x + ptrf->XMax ;
	ymax = y + ptrf->YMax ;
	zmax = z + ptrf->ZMax ;

	ptrd =	ptrf->PtrListDot ;
	for( n=0; n<ptrf->NbDot; n++, ptrd++ )
	{
		if( ptrd->Mode ) // si point vivant
		{
			if( time >= ptrd->Delay )
			{
				timew = (time - ptrd->Delay)/20 ;

				X0 = (ptrd->Vx * timew) + x ;
				Y0 = (ptrd->Vy * timew) + y - (ptrd->Poids*timew*timew)/(20) ;
				Z0 = (ptrd->Vz * timew) + z ;

				// test in ZV
				if( (X0 >= xmin)
				AND (X0 <= xmax)
				AND (Y0 >= ymin)
				AND (Y0 <= ymax)
				AND (Z0 >= zmin)
				AND (Z0 <= zmax) )
				{
					ptrd->X = X0 ;
					ptrd->Y = Y0 ;
					ptrd->Z = Z0 ;
					ptrd->Mode = DOT_DISPLAY ;

					flag = TRUE ;
				}
				else
				{
					ptrd->Mode = DOT_DEAD ;	// end dot
				}
			}
			else
			{
				// si on attends le point le flow vie
				flag = TRUE ;
			}
		}
	}

	if( !flag )
	{
		// au revoir ma jolie
		ptrf->NbDot = 0 ;

	}

	return flag ;	// si 0 pas besoin aff
}

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
void	AnimAllFlow()
{
	int32_t	n;
	S_PART_FLOW	*ptrf = ListPartFlow ;

	for( n=0; n<MAX_FLOWS; n++, ptrf++ )
	{
		if( ptrf->NbDot>0 )
		{
			AnimParticleFlow( ptrf );
		}
	}
}
