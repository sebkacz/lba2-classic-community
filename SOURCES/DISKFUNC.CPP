#include	"C_EXTERN.H"
#include "DIRECTORIES.H"

#include <SYSTEM/ADELINE.H>

#include <errno.h>

uint8_t	*PtrSce ;
uint8_t	*PtrScene ;
int32_t	CubeMode = 0 ; // 0-->Intérieur - 1-->Extérieur
int32_t	LastCubeMode = 0 ; // 0-->Intérieur - 1-->Extérieur

#define	GET_int8_t	(*PtrSce++)
#define	GET_int16_t	(*(int16_t*)PtrSce) ; PtrSce+=2
#define	GET_uint32_t	(*(uint32_t*)PtrSce) ; PtrSce+=4

/*══════════════════════════════════════════════════════════════════════════*
	     █▀▀▀▄  █    ██▀▀▀ █  ▄▀       █▀▀▀▀ █   █ ██▄ █ █▀▀▀▀
	     ██  █  ██   ▀▀▀▀█ ██▀▄        ██▀▀  ██  █ ██▀██ ██
	     ▀▀▀▀   ▀▀   ▀▀▀▀▀ ▀▀  ▀ ▀▀▀▀▀ ▀▀    ▀▀▀▀▀ ▀▀  ▀ ▀▀▀▀▀
 *══════════════════════════════════════════════════════════════════════════*/
/*──────────────────────────────────────────────────────────────────────────*/
/*
void	GetDiskEnv( char *progpath )
{
	_splitpath( (char*)progpath, ProgDrive, ProgDir, Name, Ext ) ;
	getcwd( OrgDir, _MAX_DIR ) ;
	_dos_getdrive( &OrgDrive ) ;
}

void	RestoreDiskEnv()
{
	unsigned total ;

	_dos_setdrive( OrgDrive, &total ) ;
	chdir( OrgDir ) ;
}
*/

/*══════════════════════════════════════════════════════════════════════════*
	  ██▀▀▀ █▀▀▀▀ █▀▀▀▀ ██▄ █ █▀▀▀▀       █▀▀▀▀  █    █     █▀▀▀▀
	  ▀▀▀▀█ ██    ██▀▀  ██▀██ ██▀▀        ██▀▀   ██   ██    ██▀▀
	  ▀▀▀▀▀ ▀▀▀▀▀ ▀▀▀▀▀ ▀▀  ▀ ▀▀▀▀▀ ▀▀▀▀▀ ▀▀     ▀▀   ▀▀▀▀▀ ▀▀▀▀▀
 *══════════════════════════════════════════════════════════════════════════*/
/*──────────────────────────────────────────────────────────────────────────*/
int32_t	LoadScene( int32_t numscene )
{
	T_OBJET	*ptrobj ;
	T_ZONE  *ptrz   ;
	int32_t	sizetoload ;
	int32_t	indexfile3d ;
	uint8_t	n ;
	char tmpFilePath[ADELINE_MAX_PATH];
//        uint8_t	t ;

	// numscene+1 car en 0 se trouve SizeCube.MAX (taille du plus gros .SCC)
	GetResPath(tmpFilePath, ADELINE_MAX_PATH, SCENE_HQR_NAME);
	if( !Load_HQR( tmpFilePath, PtrScene, numscene+1 ) )
	{
		TheEndCheckFile( tmpFilePath ) ;
	}

	ManageSystem() ;// for streaming

	PtrSce = PtrScene ;

// info world: INFO_WORLD

		NewCube = numscene ;

		Island = GET_int8_t ;

		Planet = TabArrow[Island].Planet;

		// Sert uniquement pour la 3DExt
		CurrentCubeX = GET_int8_t ;
		CurrentCubeY = GET_int8_t ;

		ShadowLevel = GET_int8_t ;
		ModeLabyrinthe = GET_int8_t ;

		CubeMode = GET_int8_t ;

		if( !FlagLoadGame
		AND (!FlagDrawHorizon OR (CubeMode+LastCubeMode!=2)) )
		{
			FadeToBlackAndSamples( PtrPal ) ;
			HQ_StopSample() ;

			Cls() ;
			BoxUpdate() ;
		}

		n = GET_int8_t ;

// ambiance: AMBIANCE

		AlphaLight = GET_int16_t ;
		BetaLight = GET_int16_t ;

		SampleAmbiance[0] = GET_int16_t ;
		SampleRepeat[0] = GET_int16_t ;
		SampleRnd[0] = GET_int16_t ;
		SampleFreq[0] = GET_int16_t ;
		SampleVol[0] = GET_int16_t ;
		SampleAmbiance[1] = GET_int16_t ;
		SampleRepeat[1] = GET_int16_t ;
		SampleRnd[1] = GET_int16_t ;
		SampleFreq[1] = GET_int16_t ;
		SampleVol[1] = GET_int16_t ;
		SampleAmbiance[2] = GET_int16_t ;
		SampleRepeat[2] = GET_int16_t ;
		SampleRnd[2] = GET_int16_t ;
		SampleFreq[2] = GET_int16_t ;
		SampleVol[2] = GET_int16_t ;
		SampleAmbiance[3] = GET_int16_t ;
		SampleRepeat[3] = GET_int16_t ;
		SampleRnd[3] = GET_int16_t ;
		SampleFreq[3] = GET_int16_t ;
		SampleVol[3] = GET_int16_t ;
		SecondMin = GET_int16_t ;
		SecondEcart = GET_int16_t ;

		CubeJingle = GET_int8_t ;

// hero inits: HERO_START

		ptrobj = ListObjet ;

		CubeStartX = GET_int16_t ;
		CubeStartY = GET_int16_t ;
		CubeStartZ = GET_int16_t ;

		sizetoload = GET_int16_t ;
		ptrobj->PtrTrack = PtrSce ;
		PtrSce += sizetoload ;

		sizetoload = GET_int16_t ;
		ptrobj->PtrLife = PtrSce ;
		PtrSce += sizetoload ;

		ptrobj++ ;

// objets: OBJECT

		NbObjets = GET_int16_t ;
		for( n=1; n<NbObjets; n++, ptrobj++ )
		{
			InitObject( n ) ;

			ptrobj->Flags  = GET_uint32_t ;

			indexfile3d = GET_int16_t ;

			if( !(ptrobj->Flags & SPRITE_3D) )
			{
				if( !FlagLoadGame )
				{
					ptrobj->PtrFile3D = LoadFile3D( indexfile3d ) ;
				}

				ptrobj->IndexFile3D = indexfile3d ;
			}

			ManageSystem() ;// for streaming

			ptrobj->GenBody = GET_int8_t ;
			ptrobj->GenAnim = GET_int16_t ;
			ptrobj->Sprite = GET_int16_t ;

			ptrobj->OldPosX = ptrobj->Obj.X = GET_int16_t ;
			ptrobj->OldPosY = ptrobj->Obj.Y = GET_int16_t ;
			ptrobj->OldPosZ = ptrobj->Obj.Z = GET_int16_t ;
			ptrobj->HitForce = GET_int8_t ;
			ptrobj->OptionFlags = GET_int16_t ;
			ptrobj->OptionFlags &= ~EXTRA_GIVE_NOTHING ;
			ptrobj->Obj.Beta = GET_int16_t ;
			ptrobj->SRot = GET_int16_t ;
			ptrobj->Move = GET_int8_t ;

			if( !(ptrobj->Flags&SPRITE_3D)
			AND ptrobj->Move!=MOVE_WAGON	// cf TM_SPEED
			AND ptrobj->SRot )
			{
				// A Priori, ce test ne sert à rien ici
				if(ptrobj->SRot==1)
				{
					ptrobj->SRot++ ;
				}

				ptrobj->SRot = (int16_t)(51200 / (int32_t)ptrobj->SRot) ; // 1024*1000/20
			}

			ptrobj->Info  = GET_int16_t ;
			ptrobj->Info1 = GET_int16_t ;
			ptrobj->Info2 = GET_int16_t ;
			ptrobj->Info3 = GET_int16_t ;

			ptrobj->NbBonus = GET_int16_t ;
			ptrobj->CoulObj = GET_int8_t ;

			if( ptrobj->Flags & ANIM_3DS )
			{
				// num anim 3DS
				ptrobj->Coord.A3DS.Num = GET_uint32_t ;
				// NbFps
				ptrobj->Info3 = ptrobj->SizeSHit = GET_int16_t ;
			}

			ptrobj->Armure = GET_int8_t ;
			ptrobj->LifePoint = GET_int8_t ;

			// Message chapter (a virer)
/*			for( t=0; t<MAX_CHAPTER; t++ )
			{
				ptrobj->MessageChapter[t] = GET_int16_t ;
			}
*/
			sizetoload = GET_int16_t ;
			ptrobj->PtrTrack = PtrSce ;
			PtrSce = PtrSce + sizetoload ;

			sizetoload = GET_int16_t ;
			ptrobj->PtrLife = PtrSce ;
			PtrSce = PtrSce + sizetoload ;
		}

		Checksum = GET_uint32_t ;

// zone declechement: ZONE

		NbZones = GET_int16_t ;
		ListZone = (T_ZONE*)PtrSce ;
		PtrSce += NbZones * sizeof(T_ZONE) ;

		ptrz = ListZone ;

		for( n=0; n<NbZones; n++, ptrz++ )
		{
			switch( ptrz->Type )
			{
				case 0: // change cube
					if( ptrz->Info5&1 )
						ptrz->Info5 |= ZONE_TEST_BRICK ;
					else	ptrz->Info5 &= ~(ZONE_TEST_BRICK) ;

					if( ptrz->Info6&1 )
						ptrz->Info6 |= ZONE_DONT_REAJUST_POS_TWINSEN ;
					else	ptrz->Info6 &= ~(ZONE_DONT_REAJUST_POS_TWINSEN) ;
				case 1:	// camera
					if( ptrz->Info7&1 )
						ptrz->Info7 |= ZONE_ON ;
					else	ptrz->Info7 &= ~(ZONE_ON) ;

					ptrz->Info7 &= ~(ZONE_ACTIVE) ;
					break ;

				case 3:	// zone grm
					ptrz->Info1 = 0 ;
					break ;

				case 4:	/* zone giver */
					ptrz->Info2 = 0 ;	/* pas encore pris */
					break ;

				case 6: // echelle
				case 9: // Rail
					ptrz->Info1 = ptrz->Info0 ;
					break ;

				case 8: // zone Hit
					ptrz->Info3 = 0 ; // init TimerRef
					break ;
			}
		}

// point track: TRACK

		NbBrickTrack = GET_int16_t ;
		ListBrickTrack = (T_TRACK*)PtrSce ;
		PtrSce += NbBrickTrack * sizeof(T_TRACK) ;

		//--------- PATCHES ----------
		NbPatches   = GET_uint32_t ;
		ListPatches = (T_PATCH *)PtrSce ;
		//----------------------------

		if( NumCube==NUM_CUBE_PHANTOM )
		{
			Island = PhantomIsland ;
			CurrentCubeX = PhantomX ;
			CurrentCubeY = PhantomY ;
		}

		ManageSystem() ;// for streaming

		ChoicePalette() ;

//		FlagFade = TRUE ;

		// Init suivant type de cube
		PtrInit3DGame() ;

		return TRUE ;
}

/*──────────────────────────────────────────────────────────────────────────*/
// Pour le buggy pour recupérer les coordonnées 2D d'un cube extérieur dans
// la map
int32_t	LoadSceneCubeXY( int32_t numcube, int32_t *cubex, int32_t *cubey )
{
	int32_t	x, y 	;
	uint8_t	island, shadowlvl, modelaby, cubemode ;
	char tmpFilePath[ADELINE_MAX_PATH];

	// ATTENTION: chargée dans ScreenAux car normalement appelée dans le
	//	      comportement d'init du buggy

	// numscene+1 car en 0 se trouve SizeCube.MAX (taille du plus gros .SCC)
	GetResPath(tmpFilePath, ADELINE_MAX_PATH, SCENE_HQR_NAME);
	if( !Load_HQR( tmpFilePath, ScreenAux, numcube+1 ) )
	{
		TheEndCheckFile( tmpFilePath ) ;
	}

	*cubex = *cubey = 0 ;

	PtrSce = ScreenAux ;

// info world: INFO_WORLD

	island = GET_int8_t ;

	// Sert uniquement pour la 3DExt
	x = GET_int8_t ;
	y = GET_int8_t ;

	shadowlvl = GET_int8_t ;
	modelaby  = GET_int8_t ;
	cubemode  = GET_int8_t ;

	if( cubemode==CUBE_EXTERIEUR
	AND island==Island
	AND abs(x-CurrentCubeX)<=1
	AND abs(y-CurrentCubeY)<=1
	)
	{
		*cubex = x ;
		*cubey = y ;

		return TRUE ;
	}
	else	return FALSE ;
}

/*──────────────────────────────────────────────────────────────────────────*/

uint8_t AddDirIfNot( const char *path ) {
  if (ExistsFileOrDir(path)) {
    return IsDirectory(path);
  }

  char *copypath = strdup(path);

  { // If path ends in separator, remove it
    size_t copyLen = strlen(copypath);
    if ((copyLen > 0) && (copypath[copyLen - 1] == ADELINE_PATH_SEP_CHAR)) {
      copypath[copyLen - 1] = '\0';
    }
  }

  int status = 0;
  char *pp = copypath;
  char *sp;
  while ((status == 0 || errno == EEXIST) &&
         ((sp = strchr(pp, ADELINE_PATH_SEP_CHAR)) != NULL)) {
    if (sp != pp) {
      *sp = '\0';
      status = ADELINE_MKDIR(copypath);
      *sp = ADELINE_PATH_SEP_CHAR;
    }
    pp = sp + 1;
  }

  if (status == 0) {
    status = ADELINE_MKDIR(path);
  }

  free(copypath);

  return (status == 0);
}

/*──────────────────────────────────────────────────────────────────────────*/

void	CreateLbaDirectories( void )
{
	char tmpDirPath[ADELINE_MAX_PATH];

#ifndef	DEMO
	GetVoicePath(tmpDirPath, ADELINE_MAX_PATH, NULL);
	AddDirIfNot( tmpDirPath ) ;
#endif

	GetSavePath(tmpDirPath, ADELINE_MAX_PATH, NULL);
	AddDirIfNot( tmpDirPath ) ;

	GetShootPath(tmpDirPath, ADELINE_MAX_PATH, NULL);
	AddDirIfNot( tmpDirPath ) ;

	GetLogPath(tmpDirPath, ADELINE_MAX_PATH, NULL);
	AddDirIfNot( tmpDirPath ) ;
}

/*══════════════════════════════════════════════════════════════════════════*/
/*══════════════════════════════════════════════════════════════════════════*/

