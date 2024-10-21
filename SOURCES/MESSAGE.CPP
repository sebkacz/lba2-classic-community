/*-------------------------------------------------------------------------*/
#ifdef  TITRE
/*-------------------------------------------------------------------------*/

// MESSAGE

/*-------------------------------------------------------------------------*/
#endif

//#define LORAN 1
//#define LBA_EDITOR 1
/*-------------------------------------------------------------------------*/

#include        "C_EXTERN.H"

#include <SVGA/SCREEN.H>
#include <SVGA/VIDEO.H>
#include "DIRECTORIES.H"
#include <SYSTEM/KEYBOARD_KEYS.H>
#include <SYSTEM/STRING.H>

#include <dirent.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

int32_t     FlagRestoreCD = 0               ;

/*-------------------------------------------------------------------------*/
//======================== Issus de Dial 
#define DIAL_DEF        (1<<0)  // Texte normal (defaut)
#define DIAL_BIG        (1<<1)  // Texte affiche en BigMessage
#define DIAL_FUL        (1<<2)  // Texte affiche en BigMessage sans cadre (Full Screen)
#define DIAL_SAY        (1<<3)  // Texte affiche en SayMessage
//#define       DIAL_INT        (1<<4)  // Resonnance de la voix en interieur
//#define       DIAL_EXT        (1<<5)  // Resonnance de la voix en exterieur
//#define       DIAL_CAV        (1<<6)  // Resonnance de la voix en cave
//#define       DIAL_HOL        (1<<4)  // Text affiche en 1 ligne (HOLOMAP)
#define DIAL_RAD        (1<<5)  // Message Radio
#define DIAL_EXP        (1<<6)  // Texte affiche Explain Inventory
#define DIAL_DEM        (1<<7)  // Texte affiche sur PCX pour Demo

int32_t     FlagDial = DIAL_DEF     ;

int32_t     FlagSpeedMessage = FALSE ;// cf MyDial() and NextDialCar()

int32_t     DialNbLine ;    // pour la version demo le 02/08/96

#ifdef  LBA_EDITOR
#define PATH_TXT        "f:\\projet\\lba2\\text\\"
#endif

//extern        Struc_Point Tab_Points[] ;

#ifdef  LORAN
//================================================================= L O R A N
#define PathConfigFile  "c:\\adeline.def"
//#define       CDROM   1

int32_t     Island  ;

/*-------------------------------------------------------------------------*/
void    DrawCadre( int32_t x0, int32_t y0, int32_t x1, int32_t y1 )
{
        Rect( x0, y0, x1, y1, LBAWHITE )      ;
}
/*-------------------------------------------------------------------------*/
void    *LoadTestMalloc( char *name )
{
        return(LoadMalloc(name))        ;
}
/*-------------------------------------------------------------------------*/
int32_t     GetMusicCD()
{
        return(GetMusicCDR())   ;
}
/*-------------------------------------------------------------------------*/
void    StopMusicCD()
{
        StopCDR()       ;
}
/*-------------------------------------------------------------------------*/
uint8_t   *Screen ;
uint8_t   *LbaFont;
uint8_t   *PalOrg ;
//===========================================================================
#endif

//--------------------------------------------------------------
#define NB_LANGUAGES    6
#define MAX_TEXT_LANG   15              // Attention, pour 1 langue seulement!
#define MAX_FILE_VOICE  (MAX_TEXT_LANG*NB_LANGUAGES)    // ( SYS CRE GAM 0 ... 11 ) * MaxLang
#define EXT_VOX         ".VOX"
#define FROM_HD         0
#define FROM_CD         1
#define CDBLOCK         (256L*256L)
//-------------------------------------------------------------- #endif

#define INTER_LINE      38
#define INTER_SPACE     7               //  16/08/94  de 5 a 7 !
#define INTER_LEAVE     2
#define CODE_HARD_SPACE 42              // Space with unchangable size (7)

#define TIME_DELTA_CAR  20

#define MAX_STACK       100             // ex 32!!!
#define MAX_SHADE       14              // ex 32!!!
#define SPEAK_SAMPLE    0x1234
/*-------------------------------------------------------------------------*/
int32_t    Dial_X0=16      ;
int32_t    Dial_Y0=334     ;
int32_t    Dial_X1=639-16  ;
int32_t    Dial_Y1=479-16  ;
static  int32_t    DialMaxSize=((623-8)-(16+8));

static  char    BufLine[256]    ;
static  char    *PtLine         ;
static  int32_t    SizeLine        ;
static  int32_t    NbSpace         ;
static  int32_t    NbBigSpace      ;
static  int32_t    SizeSpace       ;
static  int32_t    LenLine         ;
static  int32_t    SizeWord        ;

/*-------------------------------------------------------------------------*/

static  char    BufferMultiText[256] ;
static  int32_t     FileMultiText = -1 ;
static  int32_t     NumMultiText = -1 ;

int32_t     FlecheForcee = FALSE ;
/*-------------------------------------------------------------------------*/

uint16_t    MaxText          ;

static char     FileText[ADELINE_MAX_PATH]   ;

int32_t     Language = 1    ;               // English
int32_t     LastFileInit=-1 ;

const char    *TabLanguage[] = {
                        //      Ne pas toucher l'ordre cause HQR
        "English",
        "Français",
        "Deutsch",
        "Español",
        "Italiano",
        "Portugues"     }       ;


const char  *ListLanguage[] = {     "EN_", "FR_", "DE_", "SP_", "IT_", "PO_" } ;

const char    *ListFileText[] = {     "sys",
                                      "cre",
                                      "gam",
                                      "000",
                                      "001",
                                      "002",
                                      "003",
                                      "004",
                                      "005",
                                      "006",
                                      "007",
                                      "008",
                                      "009",
                                      "010",
                                      "011"     } ;
// flag de cadre shade

int32_t     FlagMessageShade = TRUE ;

#pragma pack(push,4)

typedef struct
{
        int32_t    x       ;
        int32_t    y       ;
        char   c       ;

} T_STACKCAR    ;

#pragma pack(pop)

static  T_STACKCAR      StackCar[MAX_STACK]       ;

static  int32_t    NbCar           ;

#define NB_DEGRADE      14
static  int32_t    MinDegrade      ;
static  int32_t    MaxDegrade      ;
uint8_t   *BufText=0L        ;
static  uint8_t   *PtText=0L ;
static  int32_t    SizeText        ;

uint16_t   *BufOrder = 0L    ;

int32_t    FlagSpeak=FALSE                  ;//     cf InitLanguage
int32_t     FlagDisplayText=1               ;//     ON par default

//----------------------------------------------------------------------------
#if defined(CDROM)||defined(LBA_EDITOR)
uint32_t     *BufMemoSeek=0                          ;
#endif

#ifdef  CDROM
int32_t     NumObjSpeak = -1                ;
int32_t     FlagVoiceCD=FALSE               ;//     cf InitLanguage

static  int32_t     FlagKeepVoice=0         ;
static  int32_t     FlagNextVoc=FALSE       ;
static  uint32_t     FdNar=0                 ;
//static        uint32_t     FdCd=0                  ;

typedef struct
{
        char    NameHD[13+ADELINE_MAX_PATH]  ;
        uint32_t     SaveTimer                       ;
        uint32_t     SizeFileHD                      ;

} T_FILEONHD    ;

T_FILEONHD      TabFileOnHD[MAX_FILE_VOICE] ;

uint32_t     TotalSizeFileHD = 0             ;
int32_t     LanguageCD = 0                  ;// Français, a changer of course!
int32_t     NbFileOnHD = 0                  ;// No File for the moment
int32_t     MaxVoice=0                      ;

#endif
//-----------------------------------------------------------------------------

char    *PtDial                 ;//     Use by Holomap
int32_t    X_Dial, Y_Dial           ;//     Use by Holomap
static  char    Word[256]       ;
static  char    *PtWord         ;
static  int32_t    NbLineDial      ;
static  int32_t    MaxLineDial=3   ;
static  int32_t    FlagEndPage=FALSE;
static  int32_t    FlagRunningDial=FALSE;
static  int32_t    FlagEndDial=FALSE;
static  int32_t    CurrentDial=0   ;
static  int32_t    LenWord         ;

//------------------------------
// le 03/05/95
#ifndef COMPILATOR
struct ListMessages {
        int32_t     Perso ;         // numero personnage scenarique
        int32_t    Message ;        // numero message
        } ;

struct ListMessages *MessList = NULL ;  // Alloue dynamiquement

int32_t     NbMess = 0 ;            // nombre de messages dans le .txt
#endif

/*-------------------------------------------------------------------------*/
uint32_t     GetHDFreeSize()
{
  // FIXME: Implement in a portable way
  return 10000000;
}

/*-------------------------------------------------------------------------*/
#ifdef  CDROM

#define BAR_X0  16
#define BAR_Y0  400
#define BAR_X1  623
#define BAR_Y1  440

void    TimeBar( uint32_t max, uint32_t val )
{
#ifdef  LBA_EDITOR
        max = max ;
        val = val ;
#else
        uint32_t     x       ;
        uint32_t     dx      ;
        MemoClipWindow()        ;
        MemoClip()              ;
        UnsetClipWindow()       ;

// old way
//      CopyBlock( 16, 400, 623, 440, Log, 16, 400, Screen );
//      PalOne( LBAWHITE, 0,255,255 )   ;
//      Rect( 16, 400, 623, 440, LBAWHITE );

        x = RegleTrois( BAR_X0+1, BAR_X1-1, max, val ) ;//      Lib_3D

        BackupAngles( BAR_X0, BAR_Y0, BAR_X1, BAR_Y1 ) ;
        if( x<BAR_X1-1 )        ShadeBoxBlk( x+1, BAR_Y0+1, BAR_X1-1, BAR_Y1-1, 8 );

//      Box( BAR_X0+1, BAR_Y0+1, x, BAR_Y1-1, 9*16+15 ) ;
        DrawFireBar( BAR_X0+1, BAR_Y0+1, x, BAR_Y1-1, FIRE_SELECT_MENU )        ;

        DrawCadre( BAR_X0, BAR_Y0, BAR_X1, BAR_Y1, ALL_ANGLES ) ;
        RestoreAngles( BAR_X0, BAR_Y0, BAR_X1, BAR_Y1 ) ;

        ColorFont( LBAWHITE )           ;
        dx = SizeFont( PleaseWait )     ;
        Font( 320-dx/2, BAR_Y0, PleaseWait );

        BoxMovingAdd( BAR_X0, BAR_Y0, BAR_X1, BAR_Y1 );
        BoxUpdate() ;

        RestoreClipWindow()     ;
        RestoreClip()           ;
#endif
}
#endif
/*-------------------------------------------------------------------------*/

void    InitLanguage()
{
        char    string[256] ;
        int32_t     n ;

        // Attention: Textes toujours Valides ???
        strcpy( string, DefFileBufferReadStringDefault( "Language", TabLanguage[1] ) ) ;

        for( n=0; n<NB_LANGUAGES; n++ )
        {
                if( !strcasecmp( string, TabLanguage[n] ) )
                {
                        Language = n    ;
                        break           ;
                }
        }

#ifdef  CDROM
        // Attention: Voix toujours Valides !!!
        strcpy( string, DefFileBufferReadStringDefault( "LanguageCD", TabLanguage[1] ) ) ;

        FlagSpeak = FALSE       ;

        for( n=0; n<NB_LANGUAGES; n++ )
        {
                if( !strcasecmp( string, TabLanguage[n] ) )
                {
                        LanguageCD = n  ;
                        FlagSpeak = TRUE;
                        break           ;
                }
        }

        if ( !SamplesEnable ) FlagSpeak = FALSE ;// No Sound PC

        strcpy( string, DefFileBufferReadStringDefault( "FlagKeepVoice", "ON" ) ) ;

        if ( !strcasecmp( string, "ON" ))  FlagKeepVoice = 1       ;// default
        else                            FlagKeepVoice = 0       ;

        if( !FlagSpeak )
        {
                // pas de voix, on force l'affichage des textes
                FlagDisplayText = TRUE ;
        }
#endif
}

/*-------------------------------------------------------------------------*/

int32_t    FindText( int32_t text )
{
        uint16_t *pt       ;
        int32_t i          ;

        pt = BufOrder   ;

        for ( i = 0 ; i < MaxText ; i++ )
        {
                if ( *pt++ == text )    return( i )     ;
        }
        return( -1 )    ;
}
#ifdef  TITRE
/*-------------------------------------------------------------------------*/
CDROM PART
/*-------------------------------------------------------------------------*/
#endif
#ifdef  CDROM
/*-------------------------------------------------------------------------*/
//      Pour prendre en compte les eventuels fichiers déjà sur HD
void InitVoiceFile() {
  char pathname[ADELINE_MAX_PATH];
  char filesDir[ADELINE_MAX_PATH];
  dirent *file;
  DIR *dir;

  GetVoicePath(filesDir, ADELINE_MAX_PATH, NULL);
  dir = opendir(filesDir);
  if (dir != NULL) {
    while ((file = readdir(dir)) != NULL) {
      if (ade_strcasestr(file->d_name, ".VOX") != NULL) {
        GetVoicePath(pathname, ADELINE_MAX_PATH, file->d_name);

        struct stat fileInfo;
        stat(pathname, &fileInfo);
        if (S_ISREG(fileInfo.st_mode)) {
          AddFileNameOnHD(pathname, fileInfo.st_size, fileInfo.st_mtime);
        }
      }
    }
    closedir(dir);
  }
}

/*-------------------------------------------------------------------------*/
void    ClearVoiceFile()
{
#ifndef DEBUG_TOOLS
        T_FILEONHD *pt  ;
        int32_t     i       ;
#endif

        CloseFdNar() ;

        if ( FlagKeepVoice )    return  ;

#ifdef  DEBUG_TOOLS
if(!QuietLog)   LogPrintf("FlagKeepVoice=0 !!!!!");
else            Message("FlagKeepVoice=0 !!!!!", TRUE )  ;
return  ;
#else

        pt = TabFileOnHD;

        for ( i = 0 ; i < NbFileOnHD ; i++, pt++ )
        {
                if ( FileSize( pt->NameHD ))//  On ne sait jamais,
                        Delete( pt->NameHD );// un bug est si vite arrive :-o
        }

        TotalSizeFileHD = 0     ;
#endif
}
/*-------------------------------------------------------------------------*/
void    CalcTotalSizeFileOnHD()
{
        T_FILEONHD *pt  ;
        int32_t     i       ;

        TotalSizeFileHD = 0     ;
        pt = TabFileOnHD        ;

        for ( i = 0 ; i < NbFileOnHD ; i++, pt++ )
                TotalSizeFileHD += pt->SizeFileHD       ;

}
/*-------------------------------------------------------------------------*/
#ifdef  LORAN
void    AffStatusVoiceFile()
{
        T_FILEONHD *pt  ;
        int32_t     i       ;

        Text( 10, 8, "%FStatus des fichiers voix :")    ;

        pt = TabFileOnHD;
        for ( i = 0 ; i < NbFileOnHD ; i++, pt++ )
        {
                Text( 10, i*10+16, "%FName : %s  Size : %L  Time : %L", pt->NameHD, pt->SizeFileHD, pt->SaveTimer ) ;
        }
        while( !Key )   ;
        while( Key )    ;
}
#endif
/*-------------------------------------------------------------------------*/
void    AddFileNameOnHD( char *filename, uint32_t size, uint32_t timer )
{
        T_FILEONHD *pt  ;
        int32_t     i       ;

        // on n'insere pas FR_GAM.VOX dans cette liste
        if( ade_strcasestr(filename,"_GAM.VOX") )       return ;

        pt = TabFileOnHD;

        for ( i = 0 ; i < NbFileOnHD ; i++, pt++ )
        {
                if ( !strcasecmp( pt->NameHD, filename ))   break   ;
        }

        strcpy( pt->NameHD, filename )  ;//     Eventuelle recopie...
        pt->SaveTimer = timer           ;
        pt->SizeFileHD = size           ;

        if ( i == NbFileOnHD )  NbFileOnHD++    ;// Maj ou Add

        CalcTotalSizeFileOnHD()         ;//     Place prise
}
/*-------------------------------------------------------------------------*/
void    DeleteOlderFileHD()
{
        T_FILEONHD *pt, *pt1    ;
        int32_t     i               ;
        uint32_t     min		;

        min = 0xFFFFFFFFL       ;//     le plus récent, non?

        pt = TabFileOnHD        ;

        for ( i = 0 ; i < NbFileOnHD ; i++, pt++ )
        {
                if ( pt->SaveTimer <= min )
                {
                        min = pt->SaveTimer     ;
                        pt1 = pt		;
                }
        }

        if ( FileSize( pt1->NameHD ))   //  cf Del upper
        {
                Delete( pt1->NameHD )   ;
        }

        TotalSizeFileHD -= pt1->SizeFileHD      ;// Maj TotalSizeFileHD

        NbFileOnHD--                            ;// One less

        if(NbFileOnHD)
        {
		pt--    ;//     back to last Entry

	        strcpy( pt1->NameHD, pt->NameHD )       ;// copy Last -> Current
        	pt1->SaveTimer = pt->SaveTimer          ;
	        pt1->SizeFileHD = pt->SizeFileHD 	;
       	}
}
/*-------------------------------------------------------------------------*/
//      Copy File CD On HD
int32_t     CopyFileCD_HD( char *filecd, char *filehd )
{
        uint32_t     fdr     ;
        uint32_t     fdw     ;
        int32_t     size    ;
        int32_t     i       ;
        int32_t     sizefile;
        char    tmpFilePath[ADELINE_MAX_PATH];


        sizefile = FileSize( filecd )   ;
        if (!sizefile)
#if defined(DEBUG_TOOLS)||defined(TEST_TOOLS)
                return(0)       ;
#else
                TheEnd( PROGRAM_OK, MessageNoCD ) ;
#endif

        fdr = OpenRead(  filecd )       ;
        if ( !fdr )     return(0)       ;

        size = GetHDFreeSize()  ;//     HD Free Space

        size -= (1024L*1024L)   ;//     1 megas marge

        if ( sizefile >= size ) goto error;

        fdw = OpenWrite( filehd );
        if ( !fdw )
        {
error:          Close(fdr)      ;
                return(0)       ;
        }

#ifndef LBA_EDITOR
        BoxReset() ;
        Cls() ;// fait le BoxStaticAdd()
        CopyScreen( Log, Screen ) ;

        FadeToBlack( PtrPal ) ;

        GetResPath(tmpFilePath, ADELINE_MAX_PATH, SCREEN_HQR_NAME);
        Load_HQR( tmpFilePath, Log, PCR_CDROM ) ;
        BoxUpdate() ;

        FadeToPal( PtrPalNormal) ;
        PalOne( LBAWHITE, 255, 255, 255 ) ;

        InitPlasmaMenu() ;
//      BackupScreen( TRUE ) ;
#endif

//------------------------------------------------ 64Ko fast copy   :-)
        size = sizefile         ;

        for ( i = 0 ; i < sizefile/CDBLOCK ; i++ )
        {
                if (Read( fdr, BufSpeak, CDBLOCK ) != CDBLOCK)
                {
                        Close(fdr)      ;
                        Close(fdw)      ;
                        Delete( filehd );
                        return(0)       ;
                }

                if ( Write( fdw, BufSpeak, CDBLOCK ) != CDBLOCK )
                {
                        Close(fdr)      ;
                        Close(fdw)      ;
                        Delete( filehd );
                        return(0)       ;
                }
                size -= (CDBLOCK)       ;
                TimeBar( sizefile, sizefile-size );
        }
//------------------------------------------------ Copy left Bytes

        if ( size>0 )
        {
                if (Read( fdr, BufSpeak, size ) != size)
                {
                        Close(fdr)      ;
                        Close(fdw)      ;
                        Delete( filehd );
                        return(0)       ;
                }

                if ( Write( fdw, BufSpeak, size ) != size )
                {
                        Close(fdr)      ;
                        Close(fdw)      ;
                        Delete( filehd );
                        return(0)       ;
                }
        }

        TimeBar( sizefile, sizefile );
        BoxBlit() ;
        BoxReset() ;

/*      CopyScreen( ScreenAux, Screen ) ;
        CopyScreen( ScreenAux, Log )    ;
        BoxStaticAdd( 0, 0, ModeDesiredX-1, ModeDesiredY-1 ) ;
*/
        Close(fdr)      ;
        Close(fdw)      ;

#ifndef LBA_EDITOR
        FadeToBlack( PtrPalNormal )     ;
        Cls()                           ;
        BoxUpdate()                     ;// fait le Cls()
#endif

        return(1)       ;
}
/*-------------------------------------------------------------------------*/
int32_t     TryCopyFileCD_HD( char *filecd, char *filehd )
{
        int32_t     ret = 0 ;
        uint32_t     freesize, size, verif   ;

        PauseMusic( FALSE ) ;

        freesize = GetHDFreeSize()-(1024L*1024L) ;//    1 Mega de marge

        size = FileSize( filecd )       ;

        if ( !size )    goto endtry     ;// Ne doit Jamais Arriver!

        if ( freesize > size )          // Y a la place :-)
        {
                ret = CopyFileCD_HD( filecd, filehd )   ;
                goto endtry ;
        }

//------------------------------ Ok, y a pas la place for the moment :-(

        if ( !NbFileOnHD )      goto endtry     ;// Nothing to delete :-<

        if ( TotalSizeFileHD+freesize < size )
                                goto endtry     ;// We can't do nothing :-[


        do
        {
                DeleteOlderFileHD()                     ;
                verif = freesize                        ;
                freesize = GetHDFreeSize()-(1024L*1024L);
                if ( freesize == verif ) goto endtry    ;//     Can't delete!
        }
        while( freesize < size );       // Keep hope... :-)

//----------------------------- Ok, maintenant on a forcément la place...

        ret = CopyFileCD_HD( filecd, filehd )   ;//  ;-)

endtry:
        ResumeMusic( TRUE ) ;

        return ret ;
}
/*-------------------------------------------------------------------------*/
void    CloseFdNar()
{
        if ( FdNar )//  Fichier ouvert CD ou HD, on doit le fermer
        {
                Close(FdNar)            ;
                FdNar = 0L              ;
        }
}
/*-------------------------------------------------------------------------*/
void    InitFileNar( char *file, int32_t from )
{
        uint32_t     offset          ;

        CloseFdNar()            ;

        FlagVoiceCD = 0         ;//Je touche pas au CD pour le moment

        if ( from == FROM_CD )  PauseMusic(FALSE)       ;

        FdNar = OpenRead( file )                ;// CD or HD, it's working
                                                 // with FdNar, so...  ;-)
        if ( !FdNar )   goto error              ;

        offset = 0                              ;

        while(!offset)                           // Sans Filet
        {
                Read( FdNar, &offset, 4L )      ;
        }

        MaxVoice = (offset/4)-1                 ;// Normalement en phase
                                                 // avec MaxText mais bon,
                                                 // en chantier... {:) --D      (un ouvrier, je sais, il est nul celui la, désolé...)
        Seek( FdNar, 0L, SEEK_FROM_START )           ;

        if ( Read( FdNar, BufMemoSeek, offset ) != offset )
        {
                CloseFdNar()    ;
                goto error      ;
        }

        FlagVoiceCD = from      ;//     0 si HD, 1 si CD (cf InitSpeak )

error:
        if ( from == FROM_CD )  ResumeMusic(FALSE)      ;
}
/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/
void    InitSpeak( int32_t file )
{
        int32_t     size            ;
        char    filehd[ADELINE_MAX_PATH];
        char    filecd[ADELINE_MAX_PATH];
        char    fileName[ADELINE_MAX_PATH];

//      if ( CDDrive < 0 )      return          ;// a virer, d'ailleur c'est fait... ;-)

        if ( file < START_FILE_ISLAND-1 ) return;// SYS CRE not spoken


#ifndef LBA_EDITOR
        // Grosse Rustine crade LBA2 (fin de projet oblige...) pour la
        // scene finale dans le desert (on avait un transfert de voix
        // alors qu'il n'y a pas de dialogue !)

        if( PLAY_THE_END
        AND Island==2 )// desert
        {
                return ;
        }
#endif

        snprintf(fileName, ADELINE_MAX_PATH, "%s%s%s", ListLanguage[LanguageCD], ListFileText[file], EXT_VOX);
        GetVoicePath(filehd, ADELINE_MAX_PATH, fileName);

        size = FileSize( filehd )               ;

        if ( size )             //      Already on HD
        {
                AddFileNameOnHD( filehd, size, time(NULL) );// Maj Timer

#ifdef  ONE_GAME_DIRECTORY      //      Uniquement en version HD
                Touch( filehd )                 ;
#endif

                InitFileNar( filehd, FROM_HD )  ;
                return                          ;
        }

        GetVoicePath(filecd, ADELINE_MAX_PATH, fileName, true);

	CloseFdNar()	;	// To close last file so that it can be deleted

        if ( !TryCopyFileCD_HD( filecd, filehd ) )
        {
                InitFileNar( filecd, FROM_CD )  ;// CD
        }
        else
        {
	        size = FileSize( filehd )	;
                AddFileNameOnHD( filehd, size, time(NULL) );// FileCD_Size TryCopy...
                InitFileNar( filehd, FROM_HD )  ;// HD
        }
}
/*-------------------------------------------------------------------------*/
void    PlaySpeakVoc(int32_t fd)
{
        int32_t    size    ;
        int32_t    sizelzss;
        int16_t    method  ;
        uint32_t     pan = 64 ;
        int32_t     volume ;

//      modif du 4/10/94 au cas ou SayMessage avant ( crac HP )
        if ( IsSamplePlaying(SPEAK_SAMPLE))  StopOneSample(SPEAK_SAMPLE)        ;

        Read( fd, &size, 4L )        ;
        Read( fd, &sizelzss, 4L )    ;
        Read( fd, &method, 2L )      ;

        if ( method == 0 )
        {
                Read( fd, BufSpeak, size )     ;
        }
        else
        {
        // ATTENTION: bouzille ScreenAux
                Read( fd, ScreenAux, sizelzss ) ;/* 256Ko max ds ScreenAux */
                ExpandLZ( BufSpeak, ScreenAux, size, 2 );
        }

        FlagNextVoc = *BufSpeak ;
        *BufSpeak = 'W'         ;// Must be correct for the sound driver

        NumObjSpeak = NumObjDial ;
        volume = VoiceVolume ;

        // Paning de la voix (ne le faire que pour les SAY_MESSAGES ?)
        if( NumObjSpeak != -1
        AND FlagDial&DIAL_SAY )
        {
                int32_t     distance ;

                PtrProjectPoint( ListObjet[NumObjSpeak].Obj.X,
                                 ListObjet[NumObjSpeak].Obj.Y,
                                 ListObjet[NumObjSpeak].Obj.Z ) ;

                if( CubeMode==CUBE_INTERIEUR )
                        distance = Distance2D( 320, 240, Xp, Yp ) ;
                else
                {
                        distance = Distance3D(  ListObjet[NumObjSpeak].Obj.X,
                                                ListObjet[NumObjSpeak].Obj.Y,
                                                ListObjet[NumObjSpeak].Obj.Z,
                                                CameraX, CameraY, CameraZ ) ;
                }

                GiveBalance( Xp, Yp, distance, &pan, &volume ) ;
                volume = RegleTrois( 0, VoiceVolume, 127, volume ) ;
        }

        PlaySample( BufSpeak, SPEAK_SAMPLE, 4096, 1, volume, pan ) ;

        NumObjSpeak = -1 ;

}
/*-------------------------------------------------------------------------*/
int32_t     TestSpk( int32_t fd )
{
#ifdef  LBA_EDITOR
        if ( !(OptionsDebug&OPT_SPEAK_MESSAGES) )       return(0)       ;//     Le Codeur ne veut pas
#endif
        if ( !FlagSpeak )       return(0)       ;//     Le joueur ne veut pas
        if ( !fd )              return(0)       ;//     Le programme ne peut pas

        if ( IsSamplePlaying( SPEAK_SAMPLE ))   return(1);// ça joue...

        if ( FlagNextVoc )                      // Ya une suite...
        {
                PlaySpeakVoc( fd )              ;//     Scratch ScreenAux
                return(1)                       ;// Ca continue de jouer...
        }

        return(0)       ;                       // A plus, snif... :-(
}
/*-------------------------------------------------------------------------*/
int32_t     TestSpeak()
{
        return(TestSpk( FdNar ));
}
/*-------------------------------------------------------------------------*/
//#ifdef        A_VOIR_SI_UTIL_STOP_MUSIC_BEFORE_PLAYING
/*
int32_t    TestSpeakFromCD()
{
        int32_t     ret     ;

        if ( !CDDrive  )        return(0)       ;

        ret = TestSpk( FdCd )   ;

        if (( !ret ) AND ( FdCd ))
        {
                Close(FdCd)     ;
                FdCd = 0L       ;
        }

        return( ret )   ;
}
*/
/*-------------------------------------------------------------------------*/
/*
void    SpeakFromCD( int32_t file, int32_t text )
{
        uint16_t     *pt             ;
        int32_t    num, offset     ;
        int32_t     max             ;
        char    tmpname[ADELINE_MAX_PATH]    ;
        char    tmpFilename[ADELINE_MAX_PATH];

        if ( !CDDrive ) return  ;

        snprintf(tmpFilename, ADELINE_MAX_PATH, "%s%s.ord, ListLanguage[LanguageCD], ListFileText[file]);
        GetResPath(tmpname, ADELINE_MAX_PATH, tmpFilename);


//--------------------------------------
        max = FileSize( tmpname )/2     ;
        Load( tmpname, BufSpeak )       ;// Ne pas bousiller BufOrder!

        pt = (uint16_t*)BufSpeak             ;

        for ( num = 0 ; num < max ; num++ )
        {
                if ( *pt++ == text )
                        break           ;
        }

        if ( num == max )       return  ;
//--------------------------------------

        tmpname[0] = CDDrive ;
        tmpname[1] = ':'                                ;
        tmpname[2] = 0                                  ;
        strcat( tmpname, PathVoxCD )                    ;
        strcat( tmpname, ListLanguage[LanguageCD] )     ;
        strcat( tmpname, ListFileText[file])            ;
        AddExt( tmpname, EXT_VOX)                       ;

        FdCd = OpenRead( tmpname )      ;
        if ( !FdCd )    return          ;

        Seek( FdCd, num*4L, SEEK_FROM_START );

        Read( FdCd, &offset, 4L )       ;

        if ( !offset )
        {
                Close(FdCd)     ;
                return          ;
        }

        Seek( FdCd, offset, SEEK_FROM_START );
        PlaySpeakVoc(FdCd)              ;
}
*/
/*-------------------------------------------------------------------------*/
/*
int32_t     IsVoiceFileOnHD( int32_t island )
{
        char    filehd[_MAX_PATH]       ;

        strcpy( filehd, PATH_VOX_HD )                   ;
        strcat( filehd, ListLanguage[LanguageCD] )      ;
        strcat( filehd, ListFileText[island])           ;
        AddExt( filehd, EXT_VOX)                        ;

        if ( FileSize( filehd ))        return( 1L )    ;

        return(0L)      ;
}
*/
/*-------------------------------------------------------------------------*/
int32_t    Speak( int32_t text )
{
        int32_t     num     ;
        uint32_t     offset  ;

        if ( !FdNar )return(0L) ;

        num = FindText( text )  ;

        if (( num == -1 )
        OR  ( num >= MaxVoice )) return(0L)     ;//     Ne doit pas arrivé,
                                                 //     sauf en cours de dvp...
        offset = BufMemoSeek[num]       ;

        if ( !offset )  return(0L)      ;

        if( !FlagRestoreCD )
        {
                if( FlagVoiceCD == FROM_CD )
                {
                        PauseMusic(TRUE)        ;
                        FlagRestoreCD = 4       ; // 4 = ResumeMusic() ;
                }
                else
                {
                        if( !(FlagDial&DIAL_SAY) )              // Say Message
                        {
                                // baisse volume music
                                SetVolumeCD( CDVolume/2 )       ;
                                SetVolumeJingle( JingleVolume/2 )       ;
                                FlagRestoreCD = 3               ;// 3 = FadeInVolumeMusic() ;
                        }
                }
        }

        Seek( FdNar, offset, SEEK_FROM_START );
        PlaySpeakVoc( FdNar )           ;

        return(1L)                      ;
}
/*-------------------------------------------------------------------------*/
void    StopSpeak()
{
        FlagNextVoc = FALSE             ;// Important, dans tout les cas !
#ifdef  LBA_EDITOR
        if ( !(OptionsDebug&OPT_SPEAK_MESSAGES) )       return ;//     Le Codeur ne veut pas
#endif
        if ( !FlagSpeak )       return  ;
        if ( !FdNar )           return  ;
        if ( IsSamplePlaying(SPEAK_SAMPLE))  StopOneSample(SPEAK_SAMPLE)               ;

/*      if( !FlagRestoreCD )
        {
                if( FlagVoiceCD == FROM_CD )
                {
                        FlagRestoreCD = 4       ;// 4 = ResumeMusic(TRUE) ;
                }
                else
                {
                        FlagRestoreCD = 3       ;// 3 = FadeInVolumeMusic() ;
                }
        }
*/
}
/*-------------------------------------------------------------------------*/
#else

//-------------------------------------------------------------------------
//           █▀▀▀▀ █▀▀▀▄ █▀▀▀█ █▀▀▀█ █▄ ▄█       █▀▀▀▀ ██▄ █ █▀▀▀▄
//           ██    ██  █ ██▀█▀ ██  █ ██▀ █       ██▀▀  ██▀██ ██  █
//           ▀▀▀▀▀ ▀▀▀▀  ▀▀  ▀ ▀▀▀▀▀ ▀▀  ▀       ▀▀▀▀▀ ▀▀  ▀ ▀▀▀▀
//-------------------------------------------------------------------------

//----------------------------------------------------------------------------
int32_t     Speak(int32_t text)
{
        text=text       ;//     Avoid Compilator Warning
        return(0)       ;
}
//----------------------------------------------------------------------------
int32_t     TestSpeak()
{
        return(0)       ;
}
//----------------------------------------------------------------------------
//void  StopSpeak() { }
//----------------------------------------------------------------------------
#endif
/*-------------------------------------------------------------------------*/
void    InitDial( int32_t file )
{
        NormalWinDial() ;//     By Security

        if ( LastFileInit == file )     return  ;
        LastFileInit = file                     ;

        GetResPath(FileText, ADELINE_MAX_PATH, TEXT_HQR_NAME);
        MaxText = (uint16_t)(Load_HQR( FileText, BufOrder,
                          ( Language*MAX_TEXT_LANG*2)+(file*2)+0)/2) ;

        Load_HQR( FileText, BufText,
                          ( Language*MAX_TEXT_LANG*2)+(file*2)+1) ;

#ifdef  CDROM
        if ( FlagSpeak )        InitSpeak(file) ;
#endif
}
/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/
void    ClearDial()
{
}
/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/
//      NEW
int32_t     FlagGui = 0     ;

void    GetNextWord(char *ptchaine, char *mot)
{
        char *dst;
        const char *pt;

        dst = mot       ;
        LenWord = 0     ;

        if (( *ptchaine == '\"' ) AND ( *(ptchaine+1) == ' ' ))
        {
                *dst++ = *ptchaine++    ;
                *dst++ = CODE_HARD_SPACE;//     Code SPACE
                ptchaine++              ;
                LenWord += 2            ;
                FlagGui = 1             ;// Open "
        }

        while(( *ptchaine != 0 )
        AND ( *ptchaine != 1 )
        AND ( *ptchaine != ' ' ))
        {
                *dst++ = *ptchaine++    ;
                LenWord++               ;

                while ( *ptchaine == ' ' )
                {

                        if ( FlagGui )  pt = strchr( "!?);:\"", *(ptchaine+1))  ;
                        else            pt = strchr( "!?);:", *(ptchaine+1))    ;

                        if ( pt )
                        {
                                if ( *pt == '\"' )      FlagGui = 0     ;
                                ptchaine++              ;
                                *dst++ = CODE_HARD_SPACE;//     Code SPACE
                                *dst++ = *ptchaine++    ;//     Ponctuation
                                LenWord += 2            ;
                        }
                        else    break   ;
                }

        }

        *dst = 0                        ;
        SizeWord = SizeFont(mot)        ;
}
/*-------------------------------------------------------------------------*/
static inline int32_t  PushCar( int32_t x, int32_t y, char c )
{
        if(NbCar>=MAX_STACK)
        {
                return  FALSE   ;
        }

        StackCar[NbCar].c = c   ;
        StackCar[NbCar].x = x   ;
        StackCar[NbCar].y = y   ;
        NbCar++                 ;

        return  TRUE            ;
}

/*-------------------------------------------------------------------------*/
static inline void FlushCar()
{
        if ( NbCar < MAX_SHADE )
        {
                return  ;
        }

        memmove(&StackCar[0], &StackCar[NbCar-(MAX_SHADE-1)], (MAX_SHADE-1)*sizeof(StackCar[0]));

        NbCar = MAX_SHADE-1     ;
}
/*-------------------------------------------------------------------------*/
void    AffOneCar( int32_t x, int32_t y, char c, int32_t coul )
{
        int32_t     x0, y0, x1, y1  ;

        if (( c != 32 ) AND ( c != CODE_HARD_SPACE ))
        {
#ifdef  LBA_EDITOR
                if ( !(OptionsDebug&OPT_QUICK_MESSAGES) )
#endif
#ifdef  LORAN
                if ( !QuickMessage )
#endif
                {
                        ColorFont( BLACK )      ;
                        CarFont( x+2, y+4, c )  ;
                }

                ColorFont( coul )               ;
                CarFont( x, y, c )              ;

                x0 = x          ;
                y0 = y          ;
                x1 = x+32       ;
                y1 = y+38       ;
                if ( x0 < Dial_X0+1 )   x0 = Dial_X0+1  ;
                if ( y0 < Dial_Y0+1 )   y0 = Dial_Y0+1  ;
                if ( x1 > Dial_X1-1 )   x1 = Dial_X1-1  ;
                if ( y1 > Dial_Y1-1 )   y1 = Dial_Y1-1  ;

                BoxStaticAdd( x0, y0, x1, y1 )          ;
        }
}
/*-------------------------------------------------------------------------*/
void    AffAllCar()
{
        T_STACKCAR *pt  ;
        int32_t i, c        ;

        pt = &StackCar[NbCar-1] ;

        c = MinDegrade          ;

        for ( i = NbCar-1 ; i >= 0 ; i--, pt-- )
        {
                AffOneCar( pt->x, pt->y, pt->c, c )     ;

                if ( c < MaxDegrade )   c++             ;
        }

        FlushCar()      ;
}
/*-------------------------------------------------------------------------*/
void    TestCoulDial( int32_t coul )
{
        MinDegrade = coul*16    ;
        MaxDegrade = coul*16+12 ;
}
/*-------------------------------------------------------------------------*/
void    NormalWinDial()
{
        Dial_X0 = 8                     ;
        Dial_Y0 = ClipWindowYMax-137    ;       // 334 lorsque ClipWindowYMax==479
        Dial_X1 = 639-8                 ;
        Dial_Y1 = ClipWindowYMax-8      ;

        MaxLineDial = 3                         ;
        DialMaxSize = ((Dial_X1-8)-(Dial_X0+8)) ;
}
/*-------------------------------------------------------------------------*/
void    DemoWinDial()
{
        Dial_X0 = -6                    ;
        Dial_Y0 = 340                   ;       // 334 lorsque ClipWindowYMax==479
        Dial_X1 = 639+6                 ;
        Dial_Y1 = 8                     ;

        MaxLineDial = 3                         ;
        DialMaxSize = ((Dial_X1-8)-(Dial_X0+8)) ;
}
/*-------------------------------------------------------------------------*/
void    BigWinDial()
{
        Dial_X0 = 8                     ;
        Dial_Y0 = ClipWindowYMin+8      ;
        Dial_X1 = 639-8                 ;
        Dial_Y1 = ClipWindowYMax-8      ;

        MaxLineDial = (Dial_Y1-Dial_Y0)/42      ;
        DialMaxSize = ((Dial_X1-8)-(Dial_X0+8)) ;

}
/*-------------------------------------------------------------------------*/
void    HoloWinDial()
{
        Dial_X0 = 8     ;
        Dial_Y0 = 425   ;
        Dial_X1 = 631   ;
        Dial_Y1 = 477   ;


        MaxLineDial = 1 ;
        DialMaxSize = ((Dial_X1-8)-(Dial_X0+8)) ;
}
/*-------------------------------------------------------------------------*/
/*
void    DefWinDial( int32_t x0, int32_t y0, int32_t x1, int32_t y1 )
{
        int16_t    yh, yb   ;
        int16_t    xl, xr   ;

        Dial_X0 = x0    ;
        Dial_Y0 = y0    ;
        Dial_X1 = x1    ;
        Dial_Y1 = y1    ;

        xl = Dial_X0+8  ;
        xr = Dial_X1-8  ;
        yh = Dial_Y0+8  ;
        yb = Dial_Y1-40 ;

        DialMaxSize = ((Dial_X1-8)-(Dial_X0+8)) ;
        MaxLineDial = (yb-yh)/36        ;
}
*/
/*-------------------------------------------------------------------------*/
void    ExplainWinDial()
{

        Dial_X0 = INV_START_X+INV_INTER_X                               ;
        Dial_Y0 = INV_START_Y+(3*INV_INTER_Y)+INV_SIZEO_Y               ;
        Dial_X1 = INV_END_X-INV_INTER_X                                 ;
        Dial_Y1 = INV_END_Y-INV_INTER_Y                                 ;

        MaxLineDial = (Dial_Y1-Dial_Y0)/42      ;
        DialMaxSize = ((Dial_X1-8)-(Dial_X0+8)) ;

}
/*-------------------------------------------------------------------------*/
int32_t     GereFlagDial( int32_t text )
{
        int32_t     ret = FALSE     ;

        FlagMessageShade = TRUE ;

        // Gere code d'attribut
        if( FlagDial&DIAL_DEF )         // Normal Message
        {
                NormalWinDial() ;
        }

        if( FlagDial&DIAL_BIG )         // Big Message
        {
                BigWinDial()    ;
        }

        if( FlagDial&DIAL_EXP )         // Explaination Inventory
        {
                ExplainWinDial()        ;
                FlagMessageShade = FALSE;
        }

#ifdef  DEMO
        if( FlagDial&DIAL_DEM )         // SlideShow Demo Jouable
        {
                DemoWinDial()           ;
                FlagMessageShade = FALSE;
        }
#endif

        if( FlagDial&DIAL_FUL )         // FullScreen Message
        {
                BigWinDial()            ;
                FlagMessageShade = FALSE;
        }

        if( FlagDial&DIAL_SAY )         // Say Message
        {
                InitIncrustDisp( INCRUST_TEXT,
                                 (int16_t)text,
                                 0, 0,
                                 (int16_t)(NumObjDial | (ListObjet[NumObjDial].CoulObj<<8)), 1, 2 )                 ;

                // Optimisation : mise a jour des globales servant a
                // GetMultiText pour ne pas charger le texte 2 fois
                memmove( BufferMultiText, PtText, SizeText )    ;
                BufferMultiText[SizeText-1] = 0                 ;
                NumMultiText = text                             ;
                FileMultiText = LastFileInit                    ;

                if ( FlagSpeak
#ifdef  LBA_EDITOR
                AND  (OptionsDebug&OPT_SPEAK_MESSAGES)
#endif
                )       ret = Speak(text)       ;

                ret = TRUE ;
        }
        return ret      ;
}

/*-------------------------------------------------------------------------*/
int32_t    GetText( int32_t text )
{
        uint16_t   offset0 ;
        uint16_t   offset1 ;
        int32_t    num      ;

        num = FindText( text )          ;//     Must have good number
        if ( num == -1 )        return(0L);//   RETURN

        offset0 = *(uint16_t*)(BufText+((num+0)*2L));
        offset1 = *(uint16_t*)(BufText+((num+1)*2L));

        PtText = BufText+offset0        ;

        FlagDial = *PtText++            ; //  attribut pour GereFlagDial()

        SizeText = offset1-offset0-1    ; // -1 pour virer octet d'attribut

        return(1L)                      ;
}
/*-------------------------------------------------------------------------*/

#define AffFleche()     DrawAngles( Dial_X0, Dial_Y0, Dial_X1, Dial_Y1, ARROW_ID/*|A_FLIP*/ ) ;

/*-------------------------------------------------------------------------*/
//----- : incrust vignette Radio
void    TestAndDrawRadio( void )
{
        if( FlagDial&DIAL_RAD )         // Message Radio
        {
                int32_t     sprite ;
                int32_t     mindx, mindy ;

                // ATTENTION: rustine car seuls ZOE et BALDINO peuvent parler
                //            avec la radio, donc on teste qui c'est avec la
                //            couleur !

                if( ListObjet[NumObjDial].CoulObj==COUL_ZOE )
                {
                        // c'est zoé qui cause
                        sprite = SYS_SPRITE_ZOE ;
                }
                else
                {
                        // c'est baldino qui cause
                        sprite = SYS_SPRITE_BALD ;
                }

                mindx = PtrZvExtra[ sprite*8 + 0 ] ;
                mindy = PtrZvExtra[ sprite*8 + 1 ] ;

                if( FlagDisplayText )
                {
                        // affiché en haut à droite de la fenetre de dialogue
                        mindx += Dial_X1 ;
                        mindy += Dial_Y0 ;
                }
                else
                {
                        // affiché en haut à droite de l'ecran
                        mindx += ModeDesiredX-1 ;
                        mindy += ClipWindowYMin ;
                }

                AffGraph( 0, mindx, mindy, HQR_Get(HQRPtrSprite,sprite) ) ;

                if( FlagDisplayText OR !FlagAnimWhoSpeak )
                {
                        BoxStaticAdd( ScreenXMin, ScreenYMin, ScreenXMax, ScreenYMax ) ;
                }
                else
                {
                        BoxMovingAdd( ScreenXMin, ScreenYMin, ScreenXMax, ScreenYMax ) ;
                }
        }
}

/*-------------------------------------------------------------------------*/
//      Prepare le Screen avec boite message shade et cadre et bulle
void    NewInitDialWindow()
{

//----- Cadre et Shade
        if( FlagMessageShade )
        {
                BackupAngles( Dial_X0, Dial_Y0, Dial_X1, Dial_Y1 ) ;
                ShadeBoxBlk( Dial_X0+1, Dial_Y0+1, Dial_X1-1, Dial_Y1-1, 8 )               ;
        }

//----- Pour Big Message surtout et bulle a cheval sur texte
        if( Bulle )     DrawBulle( NumObjDial ) ;

//----- incrust vignette Radio
        TestAndDrawRadio() ;

        if( FlagMessageShade )
        {
                DrawCadre( Dial_X0, Dial_Y0, Dial_X1, Dial_Y1, ALL_ANGLES ) ;
                RestoreAngles( Dial_X0, Dial_Y0, Dial_X1, Dial_Y1 ) ;
        }

//----- Debug for Editor
//----- Save Result in Screen ( J'en prends plus car apres, le BoxStaticAdd
//                              va recopier cette zone modulo 8... )
        CopyBlock( 0, Dial_Y0, ModeDesiredX-1, ModeDesiredY-1, Log,
                   0, Dial_Y0, Screen ) ;

//----- Display empty window
        BoxStaticAdd( Dial_X0, Dial_Y0, Dial_X1, Dial_Y1 )     ;

//----- Cas d'un message suivant l'affichage d'une PCX (on se trouve
//           sur une frame noire) !

        if( FlagFade )
        {
                FadeToPalAndSamples( PtrPal ) ;
                FlagFade = FALSE ;
        }

//----- Reset Char Display
        NbCar = 0       ;
}
/*-------------------------------------------------------------------------*/
void    NextDialWindow()
{
//----- Restore Window saved in Screen ( and scratch old text )
        CopyBlock(      Dial_X0, Dial_Y0, Dial_X1, Dial_Y1, Screen,
                        Dial_X0, Dial_Y0, Log )                 ;

//----- Display empty window
        BoxStaticAdd( Dial_X0, Dial_Y0, Dial_X1, Dial_Y1 )     ;

//----- Reset Char Display
        NbCar = 0       ;
}
/*-------------------------------------------------------------------------*/
//      Utilise pour HoloGlobe et HoloPlan ( sans AffScene ni clip box )
void    HoloInitDialWindow()
{
        HoloWinDial()   ;

        BackupAngles( Dial_X0, Dial_Y0, Dial_X1, Dial_Y1 ) ;
        ShadeBoxBlk( Dial_X0+1, Dial_Y0+1, Dial_X1-1, Dial_Y1-1, 8 )               ;
        DrawCadre( Dial_X0, Dial_Y0, Dial_X1, Dial_Y1, ALL_ANGLES ) ;
        RestoreAngles( Dial_X0, Dial_Y0, Dial_X1, Dial_Y1 ) ;

        CopyBlock(      Dial_X0, Dial_Y0, Dial_X1, Dial_Y1, Log,
                        Dial_X0, Dial_Y0, Screen )              ;
}
/*-------------------------------------------------------------------------*/

void    CommonOpenDial( int32_t text )
{
        CloseDial()             ;

        CurrentDial = text      ;

        X_Dial = Dial_X0+8      ;
        Y_Dial = Dial_Y0+8      ;
        NbLineDial = 0          ;
        PtDial = (char *)PtText ;
        *Word = 0               ;
        PtWord = Word           ;
        *BufLine = 0            ;
        PtLine = BufLine        ;
        NbCar = 0               ;
        FlagEndDial = FALSE     ;
        FlagEndPage = FALSE    ;
        FlagRunningDial = TRUE  ;

        SetFont( LbaFont, INTER_LEAVE, INTER_SPACE )    ;
}

/*-------------------------------------------------------------------------*/

void    OpenDial(int32_t text)
{
        CommonOpenDial( text )  ;

        NewInitDialWindow()     ;

#ifdef  LBA_EDITOR
        if( OptionsDebug&OPT_QUICK_MESSAGES )
        {
                CoulText( YELLOW, -1 )                                  ;
                GraphPrintf( FALSE, Dial_X0+2, Dial_Y0+2, "Mess:%d   ", text )  ;
        }
#endif
}
/*-------------------------------------------------------------------------*/
void    GetNextLine()
{
        int32_t    dx, dd  ;
        int32_t    flag    ;

        SizeLine = 0    ;
        NbSpace = 0     ;
        *BufLine = 0    ;
        SizeSpace = INTER_SPACE ;
        flag = 1        ;//     Justifie

//----- Retrait du texte si vignette Baldino ou Zoe en Radio...
//      if (( FlagDial & DIAL_BIG ) AND ( FlagDial & DIAL_RAD ))
        if (( FlagDial & DIAL_RAD ))
        {
                int32_t     clipxmax = 8 ;

                if ( NbLineDial < 3 )
                {
                        if( ListObjet[NumObjDial].CoulObj==COUL_ZOE )
                        {
//                              clipxmax = 118 ;
                                clipxmax = 148 ;
                        }
                        else
                        {
                                clipxmax = 148 ;
                        }
                }

                DialMaxSize = ((Dial_X1-clipxmax)-(Dial_X0+8))  ;
        }
//-----
        while(TRUE)
        {
                while( *PtDial == ' ' ) PtDial++;
                if ( *PtDial == 0 )     break   ;
                GetNextWord( PtDial, Word )     ;
                if ( SizeLine+SizeSpace+SizeWord > DialMaxSize ) break  ;
//------------- Caractere Spéciaux, saut de ligne, de page, etc.
                if ( *PtDial == 1 )
                {
                        PtDial++        ;
                        flag = 0        ;
                        break           ;
                }
                if ( *Word == '@' )
                {
                        flag = 0                ;
                        PtDial++                ;
                        if ( SizeLine == 0 )// Line Vide
                        {
                                strcpy( BufLine, " " )  ;
                                SizeLine = INTER_SPACE  ;
                        }
                        if ( *(Word+1) == 'P' )
                        {
                                NbLineDial = MaxLineDial;
                                PtDial++                ;
                        }
                        break   ;
                }
//-------------
                PtDial += LenWord               ;
                strcat( BufLine, Word )         ;
                strcat( BufLine, " " )          ;
                SizeLine += (SizeWord+SizeSpace);
                NbSpace++                       ;
                if ( *PtDial == 0 )     break   ;
                PtDial++                        ;
        }

        if ( NbSpace )  NbSpace--       ;// Ne doit jamais arrive :-]

        if (( *PtDial != 0 )             // Derniere Ligne ou Ligne seule
        AND ( flag == 1 ))               // Pas tout le temps, c'est a c...
        {
                dx = DialMaxSize-SizeLine       ;
                dd = dx/NbSpace                 ;
                SizeSpace += dd                 ;
                dd = NbSpace*dd                 ;
                NbBigSpace = dx-dd              ;
        }

        LenLine = strlen(BufLine)       ;
        PtLine = BufLine                ;
        DialNbLine++ ;  //  pour la version demo le 02/08/96
}
/*-------------------------------------------------------------------------*/
void    InitEndPage()
{
        int32_t    i       ;

        *BufLine = 0                    ;
        for ( i = 0 ; i < NB_DEGRADE ; i++ )    strcat( BufLine, " ")   ;
        PtLine = BufLine                ;
        LenLine = NB_DEGRADE            ;
        SizeLine = 16                   ;// Bidon
        NbLineDial = 0                  ;
}
/*-------------------------------------------------------------------------*/
int32_t     NextDialCar()
{
        static  int32_t     savetimer       ;
        static  int32_t     flagnewpage =TRUE;
        static  int32_t     flagfirstline   ;
                int32_t     iter            ;
                int32_t     res=1           ;
                int32_t     dx, dy          ;


        if ( FlagRunningDial == FALSE )
        {
                flagnewpage =TRUE       ;
                return  0               ;
        }

        if( flagnewpage )
        {
                savetimer   = TimerRefHR;
                flagnewpage = FALSE     ;
                flagfirstline = TRUE    ;
        }

        iter = TimerRefHR - savetimer   ;

#ifdef  LBA_EDITOR
        if ( OptionsDebug&OPT_QUICK_MESSAGES )
        {
                iter = 1000000  ;       // Huge value so display whole line
        }
#endif

#ifdef  DEMO
        if ( FlagDial & DIAL_DEM )      iter = 1000000  ;
#endif

        if ( FlagSpeedMessage )         iter = 1000000  ;

        if(iter >= 0)
        {
                iter = 1 + iter / TIME_DELTA_CAR        ;

                savetimer += iter * TIME_DELTA_CAR      ;

                for(; iter>0; iter--)
                {
                        if ( *PtLine == 0 )
                        {
//----------------------------- End Texte Management
                                if ( FlagEndDial == TRUE )       // The END
                                {
                                        if( FlecheForcee ) AffFleche()  ;
                                        CloseDial()             ;
                                        FlagRunningDial = FALSE ;
                                        flagnewpage     = TRUE  ;
                                        res = 0                 ;// RETURN 0
                                        break                   ;
                                }

                                if ( *PtDial == 0 )             // Pre END
                                {
                                        InitEndPage()           ;
                                        FlagEndDial = TRUE      ;
                                        res = 1                 ;
                                        break                   ;// RETURN 1
                                }
//----------------------------- Page Management
                                if (  FlagEndPage == 2 )
                                {
                                        FlagEndPage = 0         ;
                                        NextDialWindow()        ;
                                        X_Dial = Dial_X0+8      ;
                                        Y_Dial = Dial_Y0+8      ;
                                        flagnewpage     = TRUE  ;
                                        res = 1                 ;// RETURN 1
                                        break                   ;
                                }
                                else if( FlagEndPage == 1 )      // PAGE
                                {
                                        FlagEndPage = 2         ;
                                        AffFleche()             ;
                                        flagnewpage     = TRUE  ;
                                        res = 2                 ;// RETURN 2
                                        break                   ;
                                }
//-----------------------------

                                if ( flagfirstline == FALSE )
                                {
                                        X_Dial = Dial_X0+8      ;
                                        Y_Dial += INTER_LINE    ;
                                        if ( ++NbLineDial >= MaxLineDial )
                                        {
                                                FlagEndPage = 1 ;// Pre PAGE
                                                InitEndPage()   ;
                                                res = 1         ;
                                                break           ;
                                        }
                                }
                                else    flagfirstline = FALSE   ;

                                GetNextLine()           ;
                        }

                        if ( *PtLine != 0 )
                        {
                                if(!PushCar( X_Dial, Y_Dial, *PtLine ))
                                {
                                        break   ;
                                }
                                // FIXME: There is a bug here, *PtLine may be
                                //  negative (character with accent, past 127
                                //  value on a signed char).
                                //  Can reproduce by interacting with
                                //  Twinsen and Zoe statue on the main square at
                                //  the first external scenario of the game or
                                //  fisher in yellow cap on the docs.
                                GetDxDyMask( *PtLine, &dx, &dy, LbaFont );

                                if ( *PtLine != ' ' )
                                {
                                        X_Dial += dx+INTER_LEAVE;
                                }
                                else
                                {
                                        if ( NbBigSpace )
                                        {
                                                NbBigSpace--    ;
                                                X_Dial++        ;
                                        }
                                        X_Dial += SizeSpace     ;
                                }

                                PtLine++        ;
                        }
                }
        }

        AffAllCar()     ;

        return res      ;
}
/*-------------------------------------------------------------------------*/
void    CloseDial()
{
        FlagRunningDial = FALSE ;
        NextDialCar()           ;       // to force it to reset
}
/*-------------------------------------------------------------------------*/
int32_t     FlagAnimWhoSpeak=0      ;
int32_t     WhoSpeak=0              ;
int32_t     XSpeak, YSpeak, ZSpeak  ;
int32_t     OrgAnimSpeak            ;
int32_t     AlphaSpeak, BetaSpeak, GammaSpeak;
T_OBJET *PtrWhoSpeak            ;
/*-------------------------------------------------------------------------*/
void    InitWhoSpeak( int32_t numobj )
{
        int32_t     numanim, flag=0, YProj  ;

        FlagAnimWhoSpeak = FALSE        ;

        WhoSpeak = numobj               ;

        PtrWhoSpeak = &ListObjet[WhoSpeak];

        if ( PtrWhoSpeak->Flags & SPRITE_3D )   return  ;

        XSpeak = X0 = PtrWhoSpeak->Obj.X;
        YSpeak = Y0 = PtrWhoSpeak->Obj.Y;
        ZSpeak = Z0 = PtrWhoSpeak->Obj.Z;

        PtrProjectPoint( X0, Y0, Z0 )   ;
        YProj = Yp                      ;

        if ((( ( YProj >= Dial_Y0 ) OR ( FlagDial&(DIAL_BIG|DIAL_FUL))) AND ( FlagDisplayText ))
        OR  ( FlagDial&(DIAL_EXP|DIAL_DEM)) )
        {
                CopyScreen( Log, Screen )       ;
                BoxReset()                      ;
                return                          ;//     Can't do it...
        }

        FlagAnimWhoSpeak = TRUE         ;

        AlphaSpeak = PtrWhoSpeak->Obj.Alpha     ;
        BetaSpeak = PtrWhoSpeak->Obj.Beta       ;
        GammaSpeak = PtrWhoSpeak->Obj.Gamma     ;

        OrgAnimSpeak = PtrWhoSpeak->Obj.Anim.Num;

        numanim = SearchAnim( ListObjet[numobj].AnimDial, numobj );

        if( numanim == -1 )
        {
                numanim = SearchAnim( GEN_ANIM_RIEN, numobj ) ;
#ifdef  LBA_EDITOR
                if( numanim==-1 )
                {
                        Message( "InitWhoSpeak(): OBJET sans ANIM", TRUE ) ;
                        FlagAnimWhoSpeak = FALSE        ;
                        return                          ;
                }
#endif
        }

        ObjectInitAnim( &PtrWhoSpeak->Obj, (void*)numanim )     ;
}
/*-------------------------------------------------------------------------*/
void    ClearWhoSpeak()
{
        if ( !FlagAnimWhoSpeak )        return  ;

        PtrWhoSpeak->Obj.X = XSpeak     ;
        PtrWhoSpeak->Obj.Y = YSpeak     ;
        PtrWhoSpeak->Obj.Z = ZSpeak     ;

        PtrWhoSpeak->Obj.Alpha = AlphaSpeak     ;
        PtrWhoSpeak->Obj.Beta = BetaSpeak       ;
        PtrWhoSpeak->Obj.Gamma = GammaSpeak     ;

        ObjectInitAnim( &PtrWhoSpeak->Obj, (void*)OrgAnimSpeak )                        ;
}
/*-------------------------------------------------------------------------*/

void    SpeakAnimation()
{
        int32_t     saveyclip ;

        if ( FlagZoomed )       DrawOneInventory(InvSelect)     ;

        if ( FlagAnimWhoSpeak )
        {
                saveyclip = ClipWindowYMax      ;

                SetClipWindow( ClipWindowXMin, ClipWindowYMin, ClipWindowXMax, Dial_Y0-1 ) ;
                UnsetClip() ;

                AffScene( AFF_OBJETS_NO_FLIP )          ;

                if( Bulle )     DrawBulle( NumObjDial ) ;

                SetClipWindow( ClipWindowXMin, ClipWindowYMin, ClipWindowXMax, saveyclip ) ;

                UnsetClip()             ;

                if( !FlagDisplayText )  TestAndDrawRadio() ;

                ObjectSetInterDep( &PtrWhoSpeak->Obj );

                PtrWhoSpeak->Obj.X = XSpeak     ;
                PtrWhoSpeak->Obj.Y = YSpeak     ;
                PtrWhoSpeak->Obj.Z = ZSpeak     ;
        }

        BoxUpdate()     ;// For Char & perhaps Speaking guy...

        ManageTime()    ;
        MyGetInput()    ;
}
//────────────────────────────────────────────────────────────────────────────
//                                 D I A L
//────────────────────────────────────────────────────────────────────────────
void    Dial( int32_t text, int32_t drawscene )
{
        int32_t     ret = 0         ;
        int32_t     flagabort=0     ;

#ifndef LBA_EDITOR
        ClearIncrusts( INCRUST_SYS_TEXT ) ;
        ClearIncrusts( INCRUST_TEXT ) ;
#endif

/*      if ( FirstTime == AFF_ALL_FLIP )// Si CAM_FOLLOW juste avant MESSAGE
        {
                AffScene( AFF_ALL_FLIP )        ;
        }
*/
        FlagGui = 0     ;//     NEW

        NormalWinDial( )        ;//     By default
        FlagMessageShade = TRUE ;

        if( !GetText( text ) )  return ;        // Test rajouté  pour
                                                // éviter plantage.
        if( GereFlagDial( text ) )      return ;

//----- Si CAM_FOLLOW juste avant MESSAGE ( cas dans grot01 )
// Déplacé le 30/05/97
        if ( FirstTime == AFF_ALL_FLIP )// Si CAM_FOLLOW juste avant MESSAGE
        {
                AffScene( AFF_ALL_FLIP )        ;
        }
        else    if( !(FlagDial&(DIAL_BIG|DIAL_FUL|DIAL_EXP|DIAL_DEM)) )
        {
                AffScene( AFF_OBJETS_NO_FLIP ) ;
                BoxBlit() ;
//              BoxUpdate() ;
        }
//-----

        DialNbLine = 0 ;        //  pour la démo le 02/08/96

        SaveTimer( ) ;

        TestCoulDial( ListObjet[NumObjDial].CoulObj ) ;

        MemoClip()      ;
        UnsetClip()     ;

        BackupScreen( FALSE )           ;

//      InitWhoSpeak( NumObjDial )      ;

        if ( FlagSpeak
#ifdef  LBA_EDITOR
        AND  OptionsDebug&OPT_SPEAK_MESSAGES
#endif
        )
                ret = Speak(text)       ;
//-----
        if (( !FlagDisplayText )        // Pas de texte et Voix OK
        AND ( ret ))
        {
                Dial_Y0 = 480 ; // Pour ne pas avoir d'overlap
                Dial_Y1 = 480 ;

                InitWhoSpeak( NumObjDial )      ;

                while( (TestSpeak()) AND (MyKey!=K_ESC) AND !(Input&I_MENUS) )
                {
                        SpeakAnimation();
                }
                StopSpeak()     ;
                ClearWhoSpeak() ;
                FlagAnimWhoSpeak = FALSE ; // Cela pose-t-il un probleme ??
                RestoreClip()   ;
                InitWaitNoKey() ;
                InitWaitNoInput( I_FIRE|I_ACTION|I_MENUS ) ;
                RestoreTimer( ) ;
                return          ;
        }
//-----

        InitWhoSpeak( NumObjDial )      ;

        OpenDial( text )                ;

        while(TRUE)
        {
                ret = NextDialCar()     ;

                TestSpeak()             ;
                SpeakAnimation()        ;


                if ( ret == 2 ) /*      Attente de Touche       */
                {
                        while( MyKey OR Input )
                        {
                                TestSpeak()     ;// Tu relaches ?
                                SpeakAnimation();
                        }

                        if( DemoSlide )
                        {
                                int32_t     endtimer = TimerRefHR + DialNbLine*1000 ;

                                while( TimerRefHR<endtimer
                                AND !MyKey AND !Input )
                                {
                                        SpeakAnimation();
                                }
                        }
                        else    while( !MyKey AND !Input )
                        {
                                TestSpeak()     ;// Tu appuies ?
                                SpeakAnimation();
                        }

                        DialNbLine = 0  ;
                }

                if ( MyKey==K_ESC OR Input&I_MENUS )    flagabort = 1   ;

                if ((( ret == 0 ) AND ( !TestSpeak()))// Tout fini
                OR ( flagabort ))       break   ;// Ou Abort by player
        }

        StopSpeak()     ;
        CloseDial()     ;

        if(( ret == 0 ) AND ( !flagabort )
#ifdef  DEMO
        AND ( !FlagSlideShow )
#endif
        )
        {
                ManageTime() ;

                while( MyKey OR Input )
                {
                        SpeakAnimation();
                }

                if( DemoSlide )
                {
                        int32_t     endtimer = TimerRefHR + DialNbLine*1000 ;

                        while( TimerRefHR<endtimer
                        AND !MyKey AND !Input )
                        {
                                SpeakAnimation() ;
                        }
                }
                else    while( !MyKey AND !Input )
                {
                        SpeakAnimation() ;
                }
        }

        RestoreClip()   ;

        ClearWhoSpeak() ;

        FlagAnimWhoSpeak = FALSE ; // Cela pose-t-il un probleme ??

//----- remplace le RestoreScreen pour le CinemaMode (c crade !)
        if( drawscene )
        {
                CopyScreen( ScreenAux, Screen ) ;
                CopyScreen( ScreenAux, Log )    ;
                BoxStaticAdd( 0, 0, ModeDesiredX, ModeDesiredY ) ;
                RestoreTimer()                  ;
                SaveTimer()                     ;
                AffScene( AFF_OBJETS_NO_FLIP )  ;
                FixeCinemaMode( FALSE )         ;
                BoxBlit()                       ;
        }
//-----

        InitWaitNoKey() ;
        InitWaitNoInput( I_FIRE|I_ACTION|I_MENUS ) ;

        RestoreTimer( ) ;
}
/*──────────────────────────────────────────────────────────────────────────*/
int32_t     MyDial( int32_t nummess )   // attends une touche si autre page sinon continue
{
//      int32_t     memoflagdisplaytext ;
        int32_t     dialstat = 1    ;
        int32_t     esc = FALSE ;

#ifndef LBA_EDITOR
        ClearIncrusts( INCRUST_SYS_TEXT ) ;
        ClearIncrusts( INCRUST_TEXT ) ;
#endif

        BoxClean() ;// Clean Log from last AffScene

//----- Si CAM_FOLLOW juste avant MESSAGE ( cas dans grot01 )
        if ( FirstTime == AFF_ALL_FLIP )// Si CAM_FOLLOW juste avant MESSAGE
        {
                AffScene( AFF_ALL_NO_FLIP )     ;
        }
        else    AffScene( AFF_OBJETS_NO_FLIP ) ;
//-----

        CopyScreen( Log, Screen ) ;
        BoxUpdate() ;

        FlagGui = 0     ;//     NEW

        if ( FlagSpeak
#ifdef  LBA_EDITOR
        AND OptionsDebug&OPT_SPEAK_MESSAGES
#endif
        )       Speak(nummess)  ;

        InitWaitNoKey() ;
        InitWaitNoInput( I_FIRE|I_ACTION|I_MENUS ) ;

        if( FlagDisplayText )
        {
                NormalWinDial( )        ;
                FlagMessageShade = TRUE ;

                if( !GetText( nummess ) )       return FALSE ;  // Test rajouté pour
                                                                // éviter plantage.

/*              // Magouille pour etre sùr d'incruster la bulle en BoxStaticAdd
                // quand FlagDisplayText=FALSE (cf DrawBulle())
                memoflagdisplaytext = FlagDisplayText ;
                FlagDisplayText = TRUE ;
*/
                OpenDial( nummess )     ;

//              FlagDisplayText = memoflagdisplaytext ;
        }

//      while( dialstat AND !esc )
        while( !esc )
        {
                ManageTime()            ;

                dialstat = NextDialCar();

                if( !FlagDisplayText AND Bulle )        DrawBulle( NumObjDial ) ;
                BoxUpdate() ;

                TestSpeak()             ;
                if( dialstat == 2 )             // encore 1 page
                {
                        while( MyKey OR Input )
                        {
                                TestSpeak() ;
                                MyGetInput() ;
                        }

                        while( !MyKey AND !Input )
                        {
                                TestSpeak() ;
                                MyGetInput() ;
                        }
                }
                else
                {
                        MyGetInput() ;
                        if( (MyKey==K_ESC OR Input&I_MENUS)
                        OR  ((dialstat==0) AND (!TestSpeak())) ) // Tout fini
                        {
                                // affiche fin du message a vitesse grand v
                                FlagSpeedMessage = TRUE ;
                                while( NextDialCar()!=0 ) ;
                                FlagSpeedMessage = FALSE ;
                                esc = 1 ;
                                StopSpeak() ;
                        }
                }
        }

        /*if( !esc )*/  while(TestSpeak())      ManageSystem()  ;// Wait until silence

        StopSpeak() ;// Security
        CloseDial() ;

        InitWaitNoKey() ;
        InitWaitNoInput( I_FIRE|I_ACTION|I_MENUS ) ;

        return esc ;
}
/*──────────────────────────────────────────────────────────────────────────*/
// attention size max ou tronquée à 255 car + 0
char    *GetMultiText( int32_t text, char *dst )
{
        char    *pts    ;
        char    *ptd    ;
        int32_t     smax ;

        if( (text == NumMultiText ) AND ( LastFileInit == FileMultiText) )
        {
                strcpy( dst, BufferMultiText ) ;
                return dst ;
        }

        if ( !GetText( text ))
        {
                *dst = 0        ;
                return 0L       ;
        }

        pts = (char *)PtText    ;
        ptd = dst               ;

        smax = SizeText-1       ;

        if( smax > 255 )        smax = 255 ;

        memmove( dst, PtText, smax ) ;
        dst[smax] = 0 ;

        memmove( BufferMultiText, dst, smax+1 ) ;
        NumMultiText = text ;
        FileMultiText = LastFileInit ;

        return(dst)     ;
}
/*-------------------------------------------------------------------------*/
#ifdef  LBA_EDITOR
void    CleanMessage( char *string, int32_t flag )
{
        CopyScreen( Log, Screen )       ;
        Message( string, flag )         ;
        CopyScreen( Screen, Log )       ;
        BoxStaticFullflip();
}
#endif

#ifndef COMPILATOR
#ifdef  LBA_EDITOR
/*-------------------------------------------------------------------------*/
/*--- PARTIE RESERVEE A L'EDITION DES MESSAGES (le 03/05/95) ----------*/

#define GetTxtNextLine(ptr)     (strchr(ptr,0x0A)+1)

void    LoadListMessages( int32_t file )

// Cette fonction doit imperativement etre appellee apres un InitDial
// car elle considere que la variables MaxText est deja
// positionnee !!!!
{
        char    nametxt[256]   ;        // nom du fichier .txt
        char    *buftxt = 0L ;
        char    *ptr ;                  // pointe sur buftxt
        int32_t     sizetxt ;
        int32_t     mess = 0 ;              // message en cours
        int32_t     n ;
        int32_t     flag ;

        // si un fichier .txt d'une autre ile a deja ete lu, on libere
        // la structure
        FreeListMessages( ) ;

        strcpy( nametxt, PATH_TXT )            ;
        strcat( nametxt, ListLanguage[Language] )   ;
        strcat( nametxt, ListFileText[file])   ;
        AddExt( nametxt, ".txt")               ;

        sizetxt = FileSize( nametxt ) ;
        buftxt  = (char *)LoadMalloc( nametxt ) ;

        if( !buftxt )   TheEndCheckFile( nametxt ) ;

        // compte le nombre de messages dans le fichier
        ptr = buftxt ;
        NbMess = 0 ;
        while( ptr<buftxt+sizetxt )
        {
                if( *ptr=='*' AND *(ptr+1)!='*' )
                {
                        NbMess++ ;
                }

                ptr++ ;
        }

        // alloue memoire pour la liste de messages
        MessList = (struct ListMessages *) Malloc( NbMess*sizeof(struct ListMessages) ) ;

        if( !MessList )
        {
                Message( "Memoire insuffisante pour la liste des messages.", TRUE ) ;
                Free( buftxt ) ;
                return ;
        }

        for( n=0; n<NbMess; n++ )
        {
                MessList[n].Perso = -1 ;
                MessList[n].Message = -1 ;
        }

        ptr = buftxt ;

        while( ptr AND (ptr<buftxt+sizetxt) AND (mess<NbMess) )
        {
                while( ptr AND (ptr<buftxt+sizetxt) AND *ptr!='*' )
                {
                        ptr = GetTxtNextLine(ptr) ;
                }

                if( ptr AND (ptr<buftxt+sizetxt) )
                {
                        // si le caractere suivant un '*' est un '*' alors c'est
                        // la fin du fichier
                        if( ptr AND *(ptr+1)!='*' )
                        {
                                ptr++ ; // pointe apres le '*'

                                while( *ptr<'0' OR *ptr>'9' )   ptr++ ;

                                MessList[mess].Message = atol( ptr ) ;

                                flag = FALSE ;

                                while( ptr AND (ptr<buftxt+sizetxt) AND !flag )
                                {
                                        ptr = (char *)strchr( ptr, '#' ) ;

                                        if( ptr AND (*(ptr+1)=='p' OR *(ptr+1)=='P') )
                                        {
                                                ptr+=2 ;        // pointe apres le 'p'

                                                if( *ptr>='0' AND *ptr<='9' )
                                                {
                                                        MessList[mess++].Perso = atol(ptr) ;
                                                }

                                                flag = TRUE ;
                                        }
                                        else    ptr++ ; // pointe apres le '#'
                                }
                        }
                        else    ptr = 0L ;
                }
        }

        Free( buftxt ) ;
}

/*-------------------------------------------------------------------------*/
void    FreeListMessages( )

{
        if( MessList )
        {
                Free( MessList ) ;
                MessList = NULL  ;
        }
}

/*-------------------------------------------------------------------------*/
int32_t     NextMessagePerso( int32_t numperso, int32_t message )

{
        int32_t     n, i = 0 ;

        if( !MessList OR numperso==-1 ) return( -1 ) ;

        // cherche index message
        if( message!=-1 )
        {
                while( i<NbMess
                AND (MessList[i].Perso!=numperso
                OR MessList[i].Message!=message) )
                {
                        i++ ;
                }

                if( i>=NbMess ) i = 0 ;
                else                    i++ ;
        }

        for( n=i; n<NbMess; n++ )
        {
                if( MessList[n].Perso==numperso )
                {
                        return( MessList[n].Message ) ;
                }
        }

        // on a trouve aucun message, on tente dans la premiere partie
        // du tableau.
        for( n=0; n<i; n++ )
        {
                if( MessList[n].Perso==numperso )
                {
                        return( MessList[n].Message ) ;
                }
        }

        // pas d'autre message pour ce perso, on retourne l'ancien
        return( message ) ;
}

/*-------------------------------------------------------------------------*/
int32_t     PreviousMessagePerso( int32_t numperso, int32_t message )

{
        int32_t     n, i = 0 ;

        if( !MessList OR numperso==-1 ) return( -1 ) ;

        // cherche index message
        if( message!=-1 )
        {
                while( i<NbMess
                AND (MessList[i].Perso!=numperso
                OR MessList[i].Message!=message) )
                {
                        i++ ;
                }

                if( i>=NbMess ) i = 0 ;
                else                    i-- ;
        }

        for( n=i; n>=0; n-- )
        {
                if( MessList[n].Perso==numperso )
                {
                        return( MessList[n].Message ) ;
                }
        }

        // on a trouve aucun message, on tente dans la deuxieme partie
        // du tableau.
        for( n=NbMess-1; n>i; n-- )
        {
                if( MessList[n].Perso==numperso )
                {
                        return( MessList[n].Message ) ;
                }
        }

        // pas d'autre message pour ce perso, on retourne l'ancien
        return( message ) ;
}

/*-------------------------------------------------------------------------*/
int32_t     VerifyMessagePerso( int32_t numperso, int32_t message )

{
        int32_t     n ;
        int32_t     firstmessage = -1 ;

        if( !MessList OR numperso==-1 ) return( -1 ) ;

        for( n=0; n<NbMess; n++ )
        {
                if( MessList[n].Perso==numperso )
                {
                        if( MessList[n].Message==message )
                        {
                                return( message ) ;
                        }

                        if( firstmessage==-1 )
                        {
                                firstmessage = MessList[n].Message ;
                        }
                }
        }

        // le message n'existe pas pour ce perso, on retourne le premier
        // valide
        return( firstmessage ) ;
}
#endif
#endif
/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/
