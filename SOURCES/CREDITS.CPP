/*══════════════════════════════════════════════════════════════════════════*

	    ██████┐ ██████┐ ██████┐ █████┐  ██████┐ ██████┐ ██████┐
	    ██┌───┘ ██┌─██│ ██┌───┘ ██┌─██┐ └─██┌─┘ └─██┌─┘ ██┌───┘
	    ██│     ██████│ █████┐  ██│ ██│   ██│     ██│   ██████┐
	    ██│     ██┌██┌┘ ██┌──┘  ██│ ██│   ██│     ██│   └───██│
	    ██████┐ ██│└██┐ ██████┐ █████┌┘ ██████┐   ██│   ██████│
	    └─────┘ └─┘ └─┘ └─────┘ └────┘  └─────┘   └─┘   └─────┘

 *══════════════════════════════════════════════════════════════════════════*/
/*──────────────────────────────────────────────────────────────────────────*/

#include	"C_EXTERN.H"

#include <SVGA/SCREEN.H>
#include <SYSTEM/KEYBOARD.H>

#define	GridSizeX  40000
#define	GridSizeZ  40000

#define	SPEED_ROT	1100

uint8_t	*PalCredits ;

/*══════════════════════════════════════════════════════════════════════════*/

uint8_t	*NextLine( uint8_t *ptr )
{
	while( *ptr >= 32 ) ptr++ ;
	while( *ptr <  32 ) ptr++ ;

	return ptr ;
}

/*──────────────────────────────────────────────────────────────────────────*/
void	InitXplPalette( uint8_t *ptrxpl )
{
	XPL_HEADER	*xplh ;

	xplh = (XPL_HEADER*)ptrxpl ;

	PalCredits 	= ptrxpl + xplh->OffsetPalette	;
	PtrCLUTFog  	= ptrxpl + xplh->OffsetFog 	;
	PtrCLUTGouraud 	= PtrCLUTFog 			;
	PtrTransPal     = ptrxpl + xplh->OffsetTransp   ;
	PalLevel	= xplh->ShadeNormalLevel 	;
	FogCoul		= xplh->FogCoul 		;
}

//----------------------------------------------------------------------------

int	sub_qsort( const void *a, const void *b )
{
	T_SORT *pta = (T_SORT *)a ;
	T_SORT *ptb = (T_SORT *)b ;

	return( ptb->Z - pta->Z ) ;
}

//----------------------------------------------------------------------------

#define	InitTri()	{NbTriObj = 0;}

//----------------------------------------------------------------------------

void	AddTri( int32_t type, int32_t num )
{
	// mettre une protection depassement list
	T_SORT	*ptrtri = &ListTri[NbTriObj] ;

	ptrtri->NumObj 	= type 	;
	ptrtri->Z    	= Z0 	;
	ptrtri->Num  	= num 	;
	NbTriObj++ 		;
}

//----------------------------------------------------------------------------

#define	DoTri()	qsort( ListTri, NbTriObj, sizeof(T_SORT), sub_qsort ) ;

/*──────────────────────────────────────────────────────────────────────────*/

#define	PtrCredits	((uint8_t*)ScreenAux)

int32_t     GamePlayCredits( const char *file_name, int32_t mode )
{
	int32_t     flagexit = FALSE ;
	int32_t     flag = 1 ;
	int32_t     n ;
	int32_t     x0, y0, x1, y1 ;
	int32_t     xc ;
	uint8_t      *ptrlist ;
	uint8_t      *ptrl ;
	uint8_t      *ptr ;
	int32_t     nbl ;
	int32_t	dx, xf, yf ;
	int32_t     y ;
	int32_t	timer ;
	int32_t     i ;
	int32_t     flagframe ;
	int32_t     finished ;
	int32_t     angle ;
	int32_t     player_stop;

	int32_t	type ;
	int32_t	NbMovingObj ;
	int32_t	nextobj ;
	int32_t	a ;
	int32_t	scrolltimer ;

	int32_t     NbObjects ;

//	uint8_t      *LbaFont ;
	int32_t     FontBoxY0 ;
	int32_t     FontBoxY1 ;
//	int32_t     FontTab ;
	int32_t     FontHeight ;
	int32_t	distance ;
	T_SORT	*ptrtri ;

	S_CRED_INFOS_2            *ptrinfos ;
	S_CRED_OBJ_2              *ptrcrdobj ;
	S_CRED_OBJ_2              *ptrobj ;

	// chargement de la ressource
	if( (HQF_ResSize(file_name,0)+RECOVER_AREA) > (ModeDesiredX*ModeDesiredY+RECOVER_AREA)*2 )
	{
#if defined(DEBUG_TOOLS)||defined(TEST_TOOLS)
		PalOne( 255, 255, 255, 255 ) ;
		PalOne( 0, 0, 0, 0 ) ;
		CoulText( 255, 0 ) ;
		Message( "Erreur: lba2.hqr trop grand !", TRUE ) ;
#endif
		return TRUE ;
	}

	// chargement de la ressource
	if( !Load_HQR( file_name, PtrCredits, 0 ) )
	{
		return FALSE ;
	}

	ptr = PtrCredits ;

	ptrinfos = (S_CRED_INFOS_2*)ptr ;
	ptr += sizeof( S_CRED_INFOS_2 ) ;

	NbObjects = ptrinfos->NbObjects ;

	ptrcrdobj = (S_CRED_OBJ_2*)ptr ;
	ptr += sizeof( S_CRED_OBJ_2 ) * NbObjects ;

	InitObjects( BufferAnim, SIZE_BUFFER_ANIM, NULL, NULL ) ;


/*	char tmpFilePath[ADELINE_MAX_PATH];
	GetResPath(tmpFilePath, ADELINE_MAX_PATH, RESS_HQR_NAME);
	if( !Load_HQR( tmpFilePath, PtrXplPalette, RESS_XPL0 ) )
		TheEnd( ERROR_NOT_FOUND_FILE, tmpFilePath ) ;
	LastIdxPalette = RESS_XPL0 ;
*/
	LastIdxPalette = -1 ;

	InitXplPalette( PtrCredits + ptrinfos->OffXpl ) ;
//	Palette( PalCredits ) ;
	FadeToBlackAndSamples( PtrPal ) ;
	HQ_StopSample() ;

	x0 = 0 ;
	y0 = 0 ;
	x1 = ModeDesiredX-1 ;
	y1 = ModeDesiredY-1 ;

	xc = ((x0+x1)+1)/2 ;

	SetProjection( (x0+x1)/2, (y0+y1)/2, 1000, 600/(ModeDesiredX/(x1+1)), 600/(ModeDesiredY/(y1+1)) );
//	SetPosCamera( 26790, 2122, 16583 ) ;
//	SetTargetCamera( 23552, 1536, 20480, 0 ) ;
	SetFollowCamera( 23552, 1536, 20480, 75, 2500, 0, 5000 ) ;
	SetLightVector( 600, 1500, 0 ) ;

	ClipZFar = 14000 ;
	StartZFog = 5000 ;
	SetFog( StartZFog, ClipZFar ) ;

/*	LbaFont = PtrCredits + ptrinfos->OffBigFont ;
	FontTab = 20 ;
	SetFont( LbaFont, 2, 8 ) ;
*/
//	FontBoxY0 = 6 ;
	FontBoxY0 = 0 ;
	FontBoxY1 = 35 ;
	FontHeight = 40 ;

//	ColorFont( LBAWHITE ) ;

	BoxReset() ;
	SetClearColor( (uint8_t)FogCoul ) ;
	Cls() ;
	CopyScreen( Log, Screen ) ;

// test fade game screen (mettre new shadebox en lib
//	LoadPCX( "f:\\projet\\lba2\\tools\\credits\\lba2_end.pcx", Log, NULL, NULL, Screen /* paldummy */ ) ;
//	CopyScreen( Log, Screen ) ;
//	FullFlip() ;

	memset(PtrZBuffer, 255, ModeDesiredX*ModeDesiredY*2);	// Clear ZBuffer

	if( mode )	// happy end
	{
		// Twinsen
		ptrobj = ptrcrdobj ;
		ObjectClear( &ptrobj->Obj ) ;
		ptrobj->Obj.X = 24248 ;
		ptrobj->Obj.Y = 331 ;
		ptrobj->Obj.Z = 20336 ;
		ptrobj->Obj.Beta = 2990 ;
		ObjectInitBody( &ptrobj->Obj, PtrCredits + ptrobj->OffBody ) ;
		ObjectInitAnim( &ptrobj->Obj, PtrCredits + ptrobj->OffAnim[0] ) ;
		ObjectInitTexture( &ptrobj->Obj, BufferTexture ) ;
		ptrobj->Flag = 99 ;

		// set further frame

		// Zoe + babycar
		ptrobj++ ;
		ObjectClear( &ptrobj->Obj ) ;
		ptrobj->Obj.X = 23802 ;
		ptrobj->Obj.Y = 500 ;
		ptrobj->Obj.Z = 20320 ;
		ptrobj->Obj.Beta = 1024 ;
		ObjectInitBody( &ptrobj->Obj, PtrCredits + ptrobj->OffBody ) ;
		ObjectInitAnim( &ptrobj->Obj, PtrCredits + ptrobj->OffAnim[0] ) ;
		ObjectSetFrame( &ptrobj->Obj, 6 ) ;
		ObjectInitTexture( &ptrobj->Obj, BufferTexture ) ;
		ptrobj->Flag = 99 ;

		// fade background
/*		scrolltimer = TimerRefHR ;
		while( TimerRefHR-scrolltimer < 1000 * 2 + 200 )
		{
			CopyScreen( Screen, Log ) ;
			ShadeBoxBlk( 0,0, ModeDesiredX-1, ModeDesiredY-1,
				BoundRegleTrois( 0, PalLevel, 1000*2, TimerRefHR-scrolltimer ) ) ;
			BoxStaticAdd( 0,0, ModeDesiredX-1, ModeDesiredY-1 ) ;
*/
			Switch_Fillers( FILL_POLY_FOG_NZW ) ;
			SetCLUT( PalLevel ) ;

			// display Zoe + babycar
			ptrobj = ptrcrdobj + 1 ;
			ObjectSetInterAnim( &ptrobj->Obj ) ;
			if( ObjectDisplay( &ptrobj->Obj ) )
			{
				BoxMovingAdd( ScreenXMin,ScreenYMin,ScreenXMax,ScreenYMax ) ;
			}

			// display twinsen
			ptrobj = ptrcrdobj ;
			ObjectSetInterAnim( &ptrobj->Obj ) ;
			if( ObjectDisplay( &ptrobj->Obj ) )
			{
				BoxMovingAdd( ScreenXMin,ScreenYMin,ScreenXMax,ScreenYMax ) ;
			}

//		}
	}
/*	else		// rolling demo credits
	{
		FadeToBlack( PtrPal ) ;
	}
*/

	BoxUpdate() ;

	FadeToPal( PalCredits ) ;

/*	SetClearColor( (uint8_t)FogCoul ) ;
	Cls() ;
	CopyScreen( Log, Screen ) ;
	BoxStaticFullflip() ;
	Palette( PalCredits ) ;
*/
//	BoxReset();

	ptr = ptrl = ptrlist = PtrCredits + ptrinfos->OffTxt ;

	nbl = ((y1-y0)+1)/FontHeight ;

/*        // test si vsync valide
	timer = 0 ;
//        VSync() ;
	ManageSystem()  ;
	for( n=0; n<10; n++ )
	{
		i = TimerRefHR          ;
//                VSync()                 ;
		ManageSystem()          ;
		timer += TimerRefHR - i ;
	}
	timer /= 10 ;
	vsync = FALSE ;
	if( (timer >= (1000/101)) AND (timer <= (1000/55)) )    vsync = TRUE ;
	//
*/

	y = y1 ;

	flagexit = FALSE ;

	player_stop = FALSE;


	NbMovingObj = 0 ;
	nextobj = 2 ;

	timer = TimerRefHR ;
	scrolltimer = TimerRefHR ;

	ManageSystem()		;

	Switch_Fillers( FILL_POLY_FOG_NZW ) ;

	while( !flagexit )
	{

		ManageSystem()	;

		MyKey = Key;
		GetInput(0);

		if( MyKey OR Input )
		{
			player_stop = TRUE;
			goto end_credits;
		}

// check music
		if( Sample_Driver_Enabled
		AND (TimerRefHR>NextMusicTimer) )
		{
			PlayMusic( CD_TRACK_CREDITS, FALSE ) ;
		}

// animated characters

		InitTri() ;

		if( NbMovingObj < 4 )
		{
			ptrobj = ptrcrdobj + nextobj ;
			ptrobj->Flag = 1 ;
			NbMovingObj++ ;

			nextobj++ ;
			if( nextobj >= NbObjects )
			{
				nextobj = 2 ;
			}
		}

		finished = TRUE ;

		ptrobj = ptrcrdobj ;

		for( n=0; n<NbObjects; n++, ptrobj++ )
		{
			type = -1 ;

			switch( ptrobj->Flag )
			{
			case 0:	// attends
				break ;

			case 1:	// init
				ObjectClear( &ptrobj->Obj ) ;

				a = (Rnd( 2048 ) + 2600 ) & 4095 ;

				// mettre rayon dest avec temps
				Rotate( 0,
					800
					+ (TimerRefHR-timer)/20
					+ Rnd( 1100 ),
					a ) ;
				ptrobj->DestX = 24000 + X0 ;
				ptrobj->DestZ = 20320 + Z0 ;

				Rotate( 0, 7000, a ) ;

				ptrobj->Obj.X = 24000 + X0 ;
				ptrobj->Obj.Z = 20320 + Z0 ;

				ptrobj->Obj.Y = 300 ;

				ptrobj->Obj.Beta = a ;

				ptrobj->Flag++ ;

				ObjectInitBody( &ptrobj->Obj, PtrCredits + ptrobj->OffBody ) ;
				ObjectInitAnim( &ptrobj->Obj, PtrCredits + ptrobj->OffAnim[0] ) ;
				ObjectInitTexture( &ptrobj->Obj, BufferTexture ) ;
				InitBoundAngleMove( &ptrobj->RealAngle, 0, 0,0 ) ;
				ObjectSetInterDep( &ptrobj->Obj ) ;
				// pas de break ;

			case 2:	// marche ->Hello pos
				angle = GetAngle2D(	ptrobj->Obj.X,
							ptrobj->Obj.Z,
							ptrobj->DestX,
							ptrobj->DestZ ) ;

				// mettre test si beta se retourne target missed
				ChangeSpeedBoundAngleMove( &ptrobj->RealAngle, SPEED_ROT, angle ) ;
				ptrobj->Obj.Beta = GetBoundAngleMove( &ptrobj->RealAngle ) ;

				distance = Distance2D(	ptrobj->Obj.X,
							ptrobj->Obj.Z,
							ptrobj->DestX,
							ptrobj->DestZ ) ;
				if( distance <= 550 )
				{
					ptrobj->Flag++ ;
					ObjectInitAnim( &ptrobj->Obj, PtrCredits + ptrobj->OffAnim[1] ) ;
				}
				ObjectSetInterDep( &ptrobj->Obj ) ;
				finished = FALSE ;
				type = 0 ;
				break ;

			case 3: // attends bouclage anim hello
				flagframe = ObjectSetInterDep( &ptrobj->Obj ) ;
				if( flagframe & FLAG_LAST_FRAME )
				{
					type = 1 ;
					ptrobj->Flag = 0 ;
					NbMovingObj-- ;
				}
				else
				{
					type = 0 ;
				}
				finished = FALSE ;
				break ;

			case 98: // init premiere anim
				ObjectInitBody( &ptrobj->Obj, PtrCredits + ptrobj->OffBody ) ;
				ObjectInitAnim( &ptrobj->Obj, PtrCredits + ptrobj->OffAnim[0] ) ;
				ObjectInitTexture( &ptrobj->Obj, BufferTexture ) ;
				InitBoundAngleMove( &ptrobj->RealAngle, 0, 0,0 ) ;
				ptrobj->Flag = 99 ;

			case 99: // boucle forever
				ObjectSetInterDep( &ptrobj->Obj ) ;
				type = 0 ;
				break ;

			}

			if( type != -1 )
			{
				LongWorldRotatePoint( ptrobj->Obj.X, ptrobj->Obj.Y, ptrobj->Obj.Z ) ;

				// un test de pre clip serait bienvenu
				if( LongProjectPoint( X0, Y0, Z0 ) )
				{
					Z0 = CameraZr - Z0 ; // repere ecran standard
					if( Z0 < ClipZFar - 2000 )
					{
						// set body animation only if seen
						ObjectSetInterFrame( &ptrobj->Obj ) ;

						// addtri
						if( type != 1 )	// 0
						{
							AddTri( type, n ) ;
						}
						else
						{
							// incruste dans fond
							SetCLUT( PalLevel +
									16 * BoundRegleTrois(0,15,
									ClipZFar - StartZFog,
									Z0 - StartZFog )
								) ;

							Switch_Fillers( FILL_POLY_FOG_ZBUFFER ) ;
							if( ObjectDisplay( &ptrobj->Obj ) )
							{
								SetClip( ScreenXMin, ScreenYMin, ScreenXMax, ScreenYMax ) ;
								if( (ClipXMin <= ClipXMax) AND (ClipYMin <= ClipYMax) )
								{
									BoxStaticAdd( ClipXMin, ClipYMin, ClipXMax, ClipYMax ) ;
									CopyBlock( ClipXMin, ClipYMin, ClipXMax, ClipYMax, Log, ClipXMin, ClipYMin, Screen ) ;
								}
								UnsetClip() ;
							}
							Switch_Fillers( FILL_POLY_FOG_NZW ) ;
						}
					}
				}
			}
		}

		DoTri() ;

		// display sorted objs

		ptrtri = ListTri ;
		for( n=0; n<NbTriObj; n++, ptrtri++ )
		{
			switch( ptrtri->NumObj )
			{
			case 0: // obj
				i = ptrtri->Num ;
				ptrobj = ptrcrdobj+i ;
	//			ObjPtrMap = PtrCredits + ptrobj->OffTexture ;

				SetCLUT( PalLevel +
					16 * BoundRegleTrois(0,15,
						ClipZFar - StartZFog,
						ptrtri->Z - StartZFog )
					) ;

				if( ObjectDisplay( &ptrobj->Obj ) )
				{
					BoxMovingAdd( ScreenXMin,ScreenYMin,ScreenXMax,ScreenYMax ) ;
				}
				break ;

#ifdef	PLUS_BESOIN
			case 1: // obj incrust
				i = ptrtri->Num ;
				ptrobj = ptrcrdobj+i ;

				SetCLUT( PalLevel +
					16 * BoundRegleTrois(0,15,
						ClipZFar - StartZFog,
						ptrtri->Z - StartZFog )
					) ;

				Switch_Fillers( FILL_POLY_FOG_ZBUFFER ) ;
				if( ObjectDisplay( &ptrobj->Obj ) )
				{
					SetClip( ScreenXMin, ScreenYMin, ScreenXMax, ScreenYMax ) ;
					if( (ClipXMin <= ClipXMax) AND (ClipYMin <= ClipYMax) )
					{
						BoxStaticAdd( ClipXMin, ClipYMin, ClipXMax, ClipYMax ) ;
						CopyBlock( ClipXMin, ClipYMin, ClipXMax, ClipYMax, Log, ClipXMin, ClipYMin, Screen ) ;
					}
					UnsetClip() ;
				}
				break ;
#endif
			}
		}


// scrolling credits

		// scroll speed regulation by fixed_timer/frame_rate
/*		y-- ;
		if( y <= -FontHeight )
		{
			y = 0 ;
			ptrl = NextLine( ptrl ) ;
		}
*/
		// scroll y regulated by timer
		y = ModeDesiredY - (TimerRefHR - scrolltimer)/20 ;
		if( y <= -FontHeight )
		{
			y = y + FontHeight ;
			ptrl = NextLine( ptrl ) ;
			scrolltimer = TimerRefHR - (ModeDesiredY-y)*20 ;
		}

		ptr = ptrl ;
		for( n=0; n<=nbl; n++ )
		{
			yf = y+FontHeight*n ;

			switch( ptr[0] )
			{
//                      case '*':       // line feed
//                              break ;

			case '.':
				flagexit = TRUE ;
                                break ;

                        case '+':
				ColorFont( LBAWHITE ) ;
                                break ;

                        case '-':
				ColorFont( LBAWHITE ) ;
                                break ;

                        case '>':
                                ColorFont( 189 ) ;
                                break ;
			}

			if( *((char*)ptr+2) )
			{
				dx = SizeFont( (char*)ptr + 2 ) ;
				xf = xc-dx/2 ;
				Font( xf, yf, (char*)ptr + 2 ) ;

				// Magouille pour optimiser mais pour voir les lettres
				// entièrement
				if( strpbrk((char*)ptr,"'$/\"") )	FontBoxY0 = 0 ;
				else	FontBoxY0 = 6 ;

				BoxMovingAdd( xf, yf+FontBoxY0, xf+dx, yf+FontBoxY1 ) ;
			}

			ptr = NextLine( ptr ) ;
                }

		ManageSystem()  ;

#if defined(DEBUG_TOOLS)||defined(TEST_TOOLS)
		CoulText( LBAWHITE, 0 ) ;
		GraphPrintf( 0, 610,470, "%d", NbFramePerSecond ) ;
#endif
		BoxUpdate() ;
		CmptFrame++ ;
	}

end_credits:

	InitObjects( BufferAnim, SIZE_BUFFER_ANIM, GivePtrBody, GivePtrAnim )   ;

	SetClearColor( 0 ) ;
	FlagBlackPal = FALSE ;
	FadeToBlack( PalCredits ) ;
	ChoicePalette() ;
	SetFog( StartZFog, ClipZFar ) ;
	SetCLUT( PalLevel ) ;
	Switch_Fillers( FILL_POLY_TEXTURES ) ;

	return( !player_stop ) ;
}

