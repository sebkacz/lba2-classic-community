#include	"C_EXTERN.H"

#include "DIRECTORIES.H"

char		PathAcf[ADELINE_MAX_PATH] ;

char		*ListAcf ;
char		*EndListAcf ;

#ifdef	LBA_EDITOR
#define	SIZE_BUFFER_SMACK	1000000L
uint8_t  	*BufferSmack ;
#else
uint8_t  	*BufferSmack ;// initialisé dans MEM.CPP
#endif

//---------------------------------------------------------------------------

/***************************************************************************\
|*									   *|
|*				INITS					   *|
|*									   *|
\***************************************************************************/

//---------------------------------------------------------------------------
void InitAcf(void) {
  char tmpFilePath[ADELINE_MAX_PATH];

  GetMoviePath(PathAcf, ADELINE_MAX_PATH, VIDEO_HQR_NAME);
  if (!ExistsFileOrDir(PathAcf)) {
    TheEndCheckFile(PathAcf);
  }

  GetResPath(tmpFilePath, ADELINE_MAX_PATH, RESS_HQR_NAME);
  ListAcf = (char *)LoadMalloc_HQR(tmpFilePath, RESS_ACFLIST);
  if (!ListAcf) {
    TheEndCheckFile(tmpFilePath);
  }

  EndListAcf = ListAcf + LoadMallocFileSize;

#ifdef LBA_EDITOR
  // dispo Screen,ScreenAux,BufSpeak
  SmackRegisterMemory(Screen, (ModeDesiredX * ModeDesiredY + RECOVER_AREA) * 3);

  BufferSmack = (uint8_t *)Malloc(SIZE_BUFFER_SMACK);
  if (!BufferSmack)
    TheEnd(NOT_ENOUGH_MEM, "BufferSmack (InitAcf())");

  SmackRegisterMemory((void *)BufferSmack, SIZE_BUFFER_SMACK);
#else
  // TODO: Check if still useful when movie playback implemented
  // SmackRegisterMemory( MainBuffer, SizeOfMemAllocated ) ;
#endif
}

//---------------------------------------------------------------------------

char	*PtrAcf ;

char	*GetAcfName( char *name )
{
	char	*ptr = name ;
	char	c ;

	do	/* saute cr/lf espace */
	{
		if( PtrAcf>EndListAcf )
		{
			PtrAcf--  ;
			return 0L ;
		}

		c = *PtrAcf++ ;
	}
	while( c <= 32 ) ;

	do
	{
		*ptr++ = c ;
		c = *PtrAcf++ ;
	}
	while( c > 32 ) ;

	if( PtrAcf>EndListAcf )
	{
		PtrAcf--  ;
		return 0L ;
	}

	if( c == 26 )	PtrAcf-- ;

	*ptr++ = 0 ;
	return name ;
}

//---------------------------------------------------------------------------
// TODO: New implementation was not tested yet
int32_t GetNumAcf(const char *name) {
  int32_t n = 0;

  const char *nameDotAt = strchr(name, '.');
  const size_t nameNoDotLen = (nameDotAt)
                                  ? (nameDotAt - name)
                                  : strlen(name);

  char getname[15];
  PtrAcf = ListAcf;
  while (GetAcfName(getname)) {
    const char *getNameDotAt = strchr(getname, '.');
    const size_t getNameNoDotLen = (getNameDotAt)
                                       ? (getNameDotAt - getname)
                                       : strlen(getname);

    const bool sameLen = (nameNoDotLen == getNameNoDotLen);
    if (sameLen && !strncasecmp(name, getname, nameNoDotLen)) {
      return n;
    }

    n++;
  }

  return -1;
}

//---------------------------------------------------------------------------

void	PlayAllAcf( void )
{
	int32_t	firsttime = TRUE ;
	int32_t	n = 0 ;
	int32_t	var = FLAG_ACF ;
	char	getname[13] ;

	PtrAcf = ListAcf ;

#if defined(LBA_EDITOR)||defined(CDROM)
	FadeOutVolumeMusic() ;
#endif

	while( GetAcfName( getname ) )
	{
#ifdef	LBA_EDITOR
		if( (ListVarGame[var].Value & (1<<n))
#else
		if( (ListVarGame[var] & (1<<n))
#endif
		AND (strncasecmp(getname,"INTRO",5)) )// on ne rejoue pas l'intro
		{
			if( !FlagFade )
			{
				if( firsttime )
				{
					FadeToBlackAndSamples( PtrPal ) ;
					firsttime = FALSE ;
				}
				else	FadeToBlack( PtrPal ) ;
			}

			FlagFade = TRUE ;

			PlayAcf( getname ) ;
//			if( PlayAcf( getname ) == K_ESC )	break ;
		}

		n++ ;

		if( n>=16 )
		{
			var++ ;
			n = 0 ;
		}
	}

#if defined(LBA_EDITOR)||defined(CDROM)
	FadeInVolumeMusic() ;
#endif

	FirstTime = AFF_ALL_FLIP ;
}

//---------------------------------------------------------------------------

//extern	void	CopyFrameDoubleXY( uint8_t *ptrsrc ) ;

/***************************************************************************\
|*									   *|
|*				MAIN					   *|
|*									   *|
\***************************************************************************/

// TODO: Implement SMACK video playback
int32_t	PlayAcf( const char *name )
{
  return 0;
//	Smack		*smk	      	;
//	uint32_t		frame	      	;
//	int32_t		n 		;
//	int32_t		ret 		;
//	uint8_t		*decompbuf	;
//	uint32_t		smackflags	;
//#ifdef	LBA_EDITOR
//	char		name_acf[256] 	;
//
//	ShowMouse( false ) ;
//
//	smackflags = SMACKTRACK1|SMACKNEEDVOLUME ;
//#else
//	smackflags = SMACKFILEHANDLE|SMACKTRACK1|SMACKNEEDVOLUME ;
//#endif
//
//	// si c'est l'intro, on joue la track de la langue choisie
//	if( !strncasecmp(name,"INTRO",5) )
//	{
//#ifdef	CDROM
//		if( FlagSpeak )
//		{
//			switch( LanguageCD )
//			{
//				case 0:  // English
//					smackflags |= SMACKTRACK4 ;
//					break ;
//
//				case 1:	// Français
//					smackflags |= SMACKTRACK2 ;
//					break ;
//
//				case 2:	// Deutsch
//					smackflags |= SMACKTRACK3 ;
//					break ;
//
////				default:// other ...
//					// no spoken track
//			}
//		}
//#else
//		smackflags |= SMACKTRACK4 ;// English and other ...
//#endif
//	}
//
//	// Ah ? pas de son ? tiens donc ... gicle-moi les tracks !
///*	if( !Sample_Driver_Enabled )
//	{
//		smackflags &= ~(SMACKTRACKS|SMACKNEEDVOLUME) ;
//	}
//*/
//	n = GetNumAcf( name ) ;
//
//	if( n==-1 )	return 0 ;
//
//	{
//		int32_t	var	;
//		int32_t	bit	;
//
//		var = n/16	;
//		if( n>=32 )
//		{
//			var = FLAG_ACF2 ;
//			bit = 1<<(n-32) ;
//		}
//		else
//		{
//			var = FLAG_ACF 	;
//			bit = 1<<n 	;
//		}
//
//#ifdef	LBA_EDITOR
//		ListVarGame[FLAG_ACF+(n/16)].Value |= (int16_t)(1<<(n&15)) ;
//#else
//		ListVarGame[FLAG_ACF+(n/16)] |= (int16_t)(1<<(n&15)) ;
//#endif
//	}
//
//	StopMusic() ;
//
//	SmackResetMemory() ;
//
//#ifdef	LBA_EDITOR
//	strcpy( name_acf, PathAcf ) ;
//	strcat( name_acf, name ) ;
//	AddExt( name_acf, ".SMK" ) ;
//
//	smk = SmackOpen( name_acf, smackflags, SMACKAUTOEXTRA ) ;
//#else
////	Fd = OpenRead(name_acf)	;// Ouvrir ressource + Seek
//
//	// ouvre la ressource et positionne le handle à l'offet ou se trouve
//	// la sequence
//	if( !HQF_Init( PathAcf, n ) )
//#if defined(DEBUG_TOOLS)||defined(TEST_TOOLS)||!defined(CDROM)
//		return 0 ;
//#else
//		TheEnd( PROGRAM_OK, MessageNoCD ) ;
//#endif
//
//	smk = SmackOpen( (char*)HQF_File, smackflags, SMACKAUTOEXTRA ) ;
//#endif
//
//	if( !smk )
//#if defined(DEBUG_TOOLS)||defined(TEST_TOOLS)||!defined(CDROM)
//		return 0 ;
//#else
//		TheEnd( PROGRAM_OK, MessageNoCD ) ;
//#endif
//
//	decompbuf = (uint8_t*)radmalloc( 320*200 )	;
//
//	if( !decompbuf )
//	{
//		SmackClose( smk ) ;
//#ifndef	LBA_EDITOR
//		HQF_Close() ;
//#endif
//		return 0 ;
//	}
//
//	memset( decompbuf, 0, 320*200 ) ;
//
//	SmackToBuffer( smk, 0, 0, 320, 200, decompbuf, FALSE ) ;
//
////	if( Sample_Driver_Enabled )
//	{
//		int32_t	vol ;
//
//		if( UseWaveMixer )
//		{
//			vol = SampleVolume ;
//		}
//		else
//		{
//#ifdef	LBA_EDITOR
//			vol = SampleVolume ;
//#else
//			vol = BoundRegleTrois( 0, MasterVolume, 127, SampleVolume ) ;
//#endif
//		}
//
//		vol = (vol==0?vol:(vol+1))*512 ;// 0..65536
//
//		SmackVolumePan( smk, SMACKTRACKS, vol, 32768 ) ;
//	}
//
//	SetBlackPal();
//
//	BoxReset()  ;// pour etre sûr de ne pas utiliser Screen !
//	Cls() ;
//	BoxUpdate() ;
//
//	InitWaitNoKey()			;
//	InitWaitNoInput( I_JOY|I_FIRE|I_MENUS ) ;
//
//	for( frame=0; frame<smk->Frames; frame++ )
//	{
//		SmackDoFrame( smk ) ;
//
//#ifndef	LBA_EDITOR
//		if( !VideoFullScreen )
//		{
//			if( smk->NewPalette )
//			{
//#ifndef	LBA_EDITOR
//				FlagBlackPal = FALSE ;
//#endif
//				Palette(smk->Palette) ;
//			}
//			BlitBox( (void*)Phys, (void*)decompbuf ) ;
//		}
//		else
//#endif
//		{
//			CopyFrameDoubleXY( (void*)decompbuf ) ;
//			BoxStaticAdd( 0, 40, 639, 439 ) ;
//		}
//
//#ifdef	LBA_EDITOR
//		if( FlagInfos & INFO_FRAME_SPEED )
//		{
//			GraphPrintf(FALSE, 0,0, "Frame: %d", frame++);
//		}
//#endif
//
//#ifndef	LBA_EDITOR
//		if( VideoFullScreen )
//#endif
//		{
//			if( smk->NewPalette )
//			{
//#ifndef	LBA_EDITOR
//				FlagBlackPal = FALSE ;
//#endif
//				// Pour eviter flash sur frame precedente
////				Cls()  ;
////				BoxUpdate() ;
//
//				Palette(smk->Palette) ;
//			}
//
//			BoxUpdate() ;
//		}
//
//		if( frame!=smk->Frames )
//		{
//			SmackNextFrame( smk ) ;
//		}
//
//		do
//		{
//			MyGetInput() ;
//			ManageTime() ;
//
//#ifndef	LBA_EDITOR
//			CheckSaveLogPcx( smk->Palette ) ;// F9: Sauve Screen
//#endif
//
//			if( (MyKey==K_ESC OR (Input&I_MENUS))
//#ifndef	LBA_EDITOR
//			AND (!FlagPlayAcf OR frame>290)
//#endif
//			)
//			{
//				goto fin_play ;
//			}
//		}
//		while( SmackWait( smk ) ) ;
//	}
//
//fin_play:
//
//	SmackClose( smk ) ;
//
//#ifndef	LBA_EDITOR
//	HQF_Close() ;
//	LastIdxPalette = 0 ;// pour reforcer le chargement du .XPL (cf ChoicePalette())
//#endif
//
//	radfree( decompbuf ) ;
//
//	FadeToBlack( smk->Palette ) ;
//	Cls() ;
//	BoxStaticFullflip() ;
//	SetBlackPal() ;
//
//	ret = MyKey ;
//
//#ifdef	LBA_EDITOR
//	SetMouseBox( 0,0, 639,479 ) ;
//#endif
//
//	InitWaitNoKey()			;
//	InitWaitNoInput( I_MENUS ) ;
//
//#ifdef	LBA_EDITOR
//	ShowMouse( true ) ;
//#endif
//
//	return ret ;
}

//---------------------------------------------------------------------------
