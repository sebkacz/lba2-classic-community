#include	"C_EXTERN.H"

#include "DIRECTORIES.H"

/*══════════════════════════════════════════════════════════════════════════*
				  █▀▀▀▀ █▀▀▀▄
				  ██    ██  █
				  ▀▀▀▀▀ ▀▀▀▀
 *══════════════════════════════════════════════════════════════════════════*/
/*──────────────────────────────────────────────────────────────────────────*/

#ifdef	CDROM
const char*		CDDrive = "Z"	;// Z by default
uint32_t		CDVolume     = DEF_CD_VOLUME	;

#ifndef	LBA_EDITOR
void	InitTabTracks( void ) ;// voir plus bas...
#endif

/*──────────────────────────────────────────────────────────────────────────*/

int32_t	InitCD( char *name )
{
#ifndef	LBA_EDITOR
	InitTabTracks() ;
#endif
	CDDrive = OpenCD( name ) ;

	if( CDDrive )
	{
		SetVolumeCD( CDVolume ) ;

		return TRUE ;
	}

	return FALSE ;
}
#endif	// CDROM

 /*══════════════════════════════════════════════════════════════════════════*
			  █  █    ██▄ █ █▀▀▀▀ █     █▀▀▀▀
		      ▄▄  █  ██   ██▀██ ██ ▀█ ██    ██▀▀
		      ▀▀▀▀▀  ▀▀   ▀▀  ▀ ▀▀▀▀▀ ▀▀▀▀▀ ▀▀▀▀▀
 *══════════════════════════════════════════════════════════════════════════*/
/*──────────────────────────────────────────────────────────────────────────*/

uint32_t	JingleVolume = DEF_JINGLE_VOLUME ;

#define	FIRST_JINGLE	2
#define	LAST_JINGLE	26

#define	NB_JINGLE	26

char	ListJingle[NB_JINGLE][9] = {
	"",		// pour interfacer avec la music CD (car Track 0 == NO_TRACK)
	"TADPCM1",
	"TADPCM2",
	"TADPCM3",
	"TADPCM4",
	"TADPCM5",
	"JADPCM01",
	"",	// Track6.wav
	"JADPCM02",
	"JADPCM03",
	"JADPCM04",
	"JADPCM05",
	"JADPCM06",
	"JADPCM07",
	"JADPCM08",
	"JADPCM09",
	"JADPCM10",
	"JADPCM11",
	"JADPCM12",
	"JADPCM13",
	"JADPCM14",
	"JADPCM15",
	"JADPCM16",
	"JADPCM17",
	"JADPCM18",
	"LOGADPCM",
	} ;

/*──────────────────────────────────────────────────────────────────────────*/

void InitJingle(void) {
        OpenStream(); // init Stream System
        SetVolumeJingle(JingleVolume);
}

/*──────────────────────────────────────────────────────────────────────────*/

int32_t	GetNumJingle( char *name )
{
	char	filename[9] ;
	int32_t	n ;

	if( name AND strcmp(name,"") )
	{
		strcpy( filename, GetFileName(name) ) ;

		for( n=1; n<NB_JINGLE; n++ )
		{
			if( !strcasecmp(ListJingle[n],filename) )
			{
				return (n+FIRST_JINGLE-1) ;// -1 car 0==NO_TRACK
			}
		}
	}

	return 0 ;
}

/*──────────────────────────────────────────────────────────────────────────*/

void PlayJingle(int32_t num) {
  if (num >= FIRST_JINGLE AND num <= LAST_JINGLE AND JingleVolume > 0) {
    LockTimer();

    num -= FIRST_JINGLE;
    num++; // car track 0 == NO_TRACK

    char jingleFilename[ADELINE_MAX_PATH];
    snprintf(jingleFilename, ADELINE_MAX_PATH, "%s.WAV", ListJingle[num]);

    char jinglePath[ADELINE_MAX_PATH];
    GetJinglePath(jinglePath, ADELINE_MAX_PATH, jingleFilename);

    const bool playingTheSame = (strcasecmp(jinglePath, StreamName()) == 0);
    if (!playingTheSame) {
      PlayStream(jinglePath);
    }

    UnlockTimer();
  }
}

/*══════════════════════════════════════════════════════════════════════════*
			 █▄ ▄█ █   █ ██▀▀▀  █    █▀▀▀▀
			 ██▀ █ ██  █ ▀▀▀▀█  ██   ██
			 ▀▀  ▀ ▀▀▀▀▀ ▀▀▀▀▀  ▀▀   ▀▀▀▀▀
 *══════════════════════════════════════════════════════════════════════════*/
/*──────────────────────────────────────────────────────────────────────────*/


// Tableau d'indirection au cas où l'ordre change sur le CD après la saisie
// dans l'outil

#define	JINGLE	0x80	// flag indiquant une track streamée
#define	MUSIC	0x7F	// pour avoir le numero de musique

#define	FIRST_CD_TRACK		6
#define	FIRST_CD_TRACK_US	0

uint8_t	FirstCDTrack = FIRST_CD_TRACK ;

uint8_t	TrackCD[] = {
JINGLE| 2,	// Track01.wav
JINGLE| 3,	// Track02.wav
JINGLE| 4,	// Track03.wav
JINGLE| 5,	// Track04.wav
JINGLE| 6,	// Track05.wav
JINGLE| 7,	// Jingle01.wav
	8,	// Track06.wav
JINGLE| 9,	// Jingle02.wav
JINGLE|10,	// Jingle03.wav
JINGLE|11,	// Jingle04.wav
JINGLE|12,	// Jingle05.wav
JINGLE|13,	// Jingle06.wav
JINGLE|14,	// Jingle07.wav
JINGLE|15,	// Jingle08.wav
JINGLE|16,	// Jingle09.wav
JINGLE|17,	// Jingle10.wav
JINGLE|18,	// Jingle11.wav
JINGLE|19,	// Jingle12.wav
JINGLE|20,	// Jingle13.wav
JINGLE|21,	// Jingle14.wav
JINGLE|22,	// Jingle15.wav
JINGLE|23,	// Jingle16.wav
JINGLE|24,	// Jingle17.wav
JINGLE|25,	// Jingle18.wav
JINGLE|26,	// LogAdpcm.wav
	} ;

uint8_t	TrackCDUS[] = {
	2,	// Track01.wav
	3,	// Track02.wav
	4,	// Track03.wav
	5,	// Track04.wav
	6,	// Track05.wav
	7,	// Jingle01.wav
	8,	// Track06.wav
JINGLE| 9,	// Jingle02.wav
JINGLE|10,	// Jingle03.wav
JINGLE|11,	// Jingle04.wav
JINGLE|12,	// Jingle05.wav
JINGLE|13,	// Jingle06.wav
JINGLE|14,	// Jingle07.wav
JINGLE|15,	// Jingle08.wav
JINGLE|16,	// Jingle09.wav
JINGLE|17,	// Jingle10.wav
JINGLE|18,	// Jingle11.wav
JINGLE|19,	// Jingle12.wav
JINGLE|20,	// Jingle13.wav
JINGLE|21,	// Jingle14.wav
JINGLE|22,	// Jingle15.wav
JINGLE|23,	// Jingle16.wav
JINGLE|24,	// Jingle17.wav
JINGLE|25,	// Jingle18.wav
JINGLE|26,	// LogAdpcm.wav
	} ;

uint8_t	*PtrTrackCD ;

#define	TEST_MUSIC_TEMPO	(2*1000)	// 2s

int32_t	NextMusic = -1 ;
int32_t	StopLastMusic = FALSE ;
int32_t	NextMusicTimer ;

/*──────────────────────────────────────────────────────────────────────────*/
#if defined(CDROM)&&!defined(LBA_EDITOR)
void	InitTabTracks( void )
{
	switch( DistribVersion )
	{
		case UNKNOWN_VERSION:
		case EA_VERSION:
			PtrTrackCD = TrackCD ;
			FirstCDTrack = FIRST_CD_TRACK ;
			break ;

		default:
			PtrTrackCD = TrackCDUS ;
			FirstCDTrack = FIRST_CD_TRACK_US ;
	}
}
#endif

/*──────────────────────────────────────────────────────────────────────────*/
// Cette fonction doit orienter la musique soit sur une Track Audio, soit
// sur du Streaming ADPCM

void	PlayMusic( int32_t num, int32_t playit )
{
	NextMusic = -1 ;

	if( num!=-1 )
	{
		int32_t cur ;

		LockTimer() ;

		if( playit OR StopLastMusic )	cur = 0 ;
		else				cur = GetMusic() ;

		StopLastMusic = playit ;

		if( cur==0 )
		{
			if( !playit
			OR  GetMusic()!=(PtrTrackCD[num]&MUSIC) )
			{
				StopMusic() ;

				if( PtrTrackCD[num]&JINGLE )
				{
					PlayJingle( PtrTrackCD[num]&MUSIC ) ;
				}
#ifdef	CDROM
				else
				{
					if( CDVolume>0 )
					{
						PlayCD( (PtrTrackCD[num]&MUSIC)-FirstCDTrack ) ;
					}
				}
#endif
			}
		}
		else
		{
//			if( PtrTrackCD[cur-1]&JINGLE )// on n'empile pas sur une track
			if( cur!=(PtrTrackCD[num]&MUSIC) )// on n'empile pas sur la meme
			{
				NextMusic = num ;// empile musique à jouer +tard
//				NextMusicTimer = TimerRefHR+TEST_MUSIC_TEMPO ;
			}
		}

		NextMusicTimer = TimerRefHR+TEST_MUSIC_TEMPO ;

		UnlockTimer() ;
	}
}

/*──────────────────────────────────────────────────────────────────────────*/

int32_t	GetMusic( void )
{
	int32_t	num ;

#ifdef	CDROM
	num = IsCDPlaying() ;
#else
	num = 0 ;
#endif

	if( !num )	// pas de music CD
	{
		num = GetNumJingle( StreamName() ) ;
	}
	else	num += FirstCDTrack ;

	return num ;
}

/*──────────────────────────────────────────────────────────────────────────*/

void	StopMusic( void )
{
#ifdef	CDROM
	StopCD() ;
#endif
	StopStream()  ;
}

/*──────────────────────────────────────────────────────────────────────────*/

void	PauseMusic( int32_t fade )
{
	SaveTimer() ;

	if( fade )	FadeOutVolumeMusic() ;

#ifdef	CDROM
	PauseCD() ;
#endif
	PauseStream() ;

	if( fade )
	{
#ifdef	CDROM
		SetVolumeCD( CDVolume ) ;
#endif
		SetVolumeJingle( JingleVolume ) ;
	}

	RestoreTimer() ;
}

/*──────────────────────────────────────────────────────────────────────────*/

void	ResumeMusic( int32_t fade )
{
	SaveTimer() ;

	if( fade )
	{
#ifdef	CDROM
		SetVolumeCD(0) ;
#endif
		SetVolumeJingle( 0 ) ;
	}

	StopMusic() ;

#ifdef	CDROM
	ResumeCD() ;
#endif
	ResumeStream()  ;

	if( fade )	FadeInVolumeMusic() ;

	StopLastMusic = FALSE ;

	RestoreTimer() ;
}

/*──────────────────────────────────────────────────────────────────────────*/

#define	FADE_MUSIC_TIME		100	// 1/5s

void	FadeOutVolumeMusic( void )
{
	int32_t	timer ;
	uint32_t	startjvol, jvolume, oldjvol ;
#ifdef	CDROM
	uint32_t	startcdvol, cdvolume, oldcdvol ;
#endif

	ManageTime();
	SaveTimer() ;

	timer = TimerRefHR ;

	startjvol = oldjvol = jvolume = GetVolumeStream() ;

#ifdef	CDROM
	startcdvol  = oldcdvol = cdvolume = GetVolumeCD() ;
#endif

	while(
#ifdef	CDROM
	cdvolume>0 OR
#endif
	jvolume>0 )
	{
		ManageTime();
#ifdef	CDROM
		// volume du CD
		cdvolume = BoundRegleTrois( startcdvol, 0, FADE_MUSIC_TIME, TimerRefHR-timer ) ;

		if( cdvolume!=oldcdvol )
		{
			SetVolumeCD( cdvolume ) ;
			oldcdvol = cdvolume ;
		}
#endif
		// volume des Jingles
		jvolume = BoundRegleTrois( startjvol, 0, FADE_MUSIC_TIME, TimerRefHR-timer ) ;

		if( jvolume!=oldjvol )
		{
			SetVolumeJingle( jvolume ) ;
			oldjvol = jvolume ;
		}
	}

#ifdef	CDROM
	SetVolumeCD( 0 ) ;
#endif
	SetVolumeJingle( 0 ) ;

	RestoreTimer() ;
}

/*──────────────────────────────────────────────────────────────────────────*/

void	FadeInVolumeMusic( void )
{
	int32_t	timer ;
	uint32_t	startjvol, jvolume, oldjvol ;
#ifdef	CDROM
	uint32_t	startcdvol, cdvolume, oldcdvol ;
#endif

	ManageTime();
	SaveTimer() ;

	timer = TimerRefHR ;

#ifdef	CDROM
	startcdvol = oldcdvol = cdvolume = GetVolumeCD() ;
#endif

	startjvol = oldjvol = jvolume = GetVolumeStream() ;

	while(
#ifdef	CDROM
	cdvolume<CDVolume OR
#endif
	jvolume<JingleVolume )
	{
		ManageTime();
#ifdef	CDROM
		// volume du CD
		cdvolume = BoundRegleTrois( startcdvol, CDVolume, FADE_MUSIC_TIME, TimerRefHR-timer ) ;

		if( cdvolume!=oldcdvol )
		{
			SetVolumeCD( cdvolume ) ;
			oldcdvol = cdvolume ;
		}
#endif
		// volume des Jingles
		jvolume = BoundRegleTrois( startjvol, JingleVolume, FADE_MUSIC_TIME, TimerRefHR-timer ) ;

		if( jvolume!=oldjvol )
		{
			SetVolumeJingle( jvolume ) ;
			oldjvol = jvolume ;
		}
	}

#ifdef	CDROM
	SetVolumeCD( CDVolume ) ;
#endif
	SetVolumeJingle( JingleVolume ) ;

	RestoreTimer() ;
}
/*──────────────────────────────────────────────────────────────────────────*/

void	CheckNextMusic( void )
{
	if( NextMusic!=-1 )
	{
		if( TimerRefHR>NextMusicTimer )
		{
			PlayMusic( NextMusic, FALSE ) ;
		}
	}
}
