#ifndef	GAMEMENU_H
#define	GAMEMENU_H

#ifdef	DEMO
extern	int32_t	FlagShowEndDemo ;
#endif

/*--------------------------------------------------------------------------*/
extern Func_Init3DView Init3DView ;
/*--------------------------------------------------------------------------*/
extern void Init3DGame(void);
/*--------------------------------------------------------------------------*/
extern void SetDetailLevel( void ) ;
/*--------------------------------------------------------------------------*/
extern void MessageTransp( char *mess, int32_t coul, int32_t moving ) ;
/*--------------------------------------------------------------------------*/
extern void InitMenuIncrustText( const char *text, int32_t sprite, int32_t time ) ;
/*--------------------------------------------------------------------------*/
extern void DrawFireBar( int32_t xmin, int32_t ymin, int32_t xmax, int32_t ymax, int32_t coul ) ;
/*--------------------------------------------------------------------------*/
#define	DrawFire( y, coul )	DrawFireBar(	320-LargeurMenu/2,	\
							y,			\
							320+LargeurMenu/2,	\
							y+HAUTEUR_STANDARD,	\
							coul)
/*--------------------------------------------------------------------------*/
extern int  my_sort_function( const void *a, const void *b) ;
/*--------------------------------------------------------------------------*/
extern int32_t  PlayerGameList(char **ptrlistname,char *listname,int32_t flagnew);
/*--------------------------------------------------------------------------*/
extern int32_t  FindPlayerFile(void);
/*--------------------------------------------------------------------------*/
extern void DrawOneString(int32_t x,int32_t y,char *playername,int32_t draw);
/*--------------------------------------------------------------------------*/
extern void ClearOneString(int32_t x,int32_t y);
/*--------------------------------------------------------------------------*/
extern void DrawSingleString(int32_t x,int32_t y,char *string);
/*--------------------------------------------------------------------------*/
extern int32_t  InputPlayerName(int32_t choice,char *name);
/*--------------------------------------------------------------------------*/
extern int32_t  ChoosePlayerName(int32_t mess,int32_t flagflip,int32_t flagnew);
/*--------------------------------------------------------------------------*/
extern void DrawOneChoice(int32_t x,int32_t y,int32_t type,int32_t num,int32_t select);
/*--------------------------------------------------------------------------*/
extern void DrawGameMenu(uint16_t *ptrmenu,int32_t justone);
/*--------------------------------------------------------------------------*/
extern int32_t  DoGameMenu(uint16_t *ptrmenu);
/*--------------------------------------------------------------------------*/
extern int32_t  OptionsMenu(int32_t flagflip);
/*--------------------------------------------------------------------------*/
extern void VolumeOptions(void);
/*--------------------------------------------------------------------------*/
extern void SavedGameManagement(void);
/*--------------------------------------------------------------------------*/
extern int32_t  DeleteSavedGame( void ) ;
/*--------------------------------------------------------------------------*/
extern void ZoomSavedGame(int32_t x,int32_t y);
/*--------------------------------------------------------------------------*/
extern void DrawScreenSave(uint8_t *ptr,int32_t x,int32_t y);
/*--------------------------------------------------------------------------*/
extern void DrawCadreSave(int32_t x,int32_t y);
/*--------------------------------------------------------------------------*/
extern int32_t  IsFirstGameLaunched( void ) ;
/*--------------------------------------------------------------------------*/
extern int32_t  MainGameMenu( int32_t load );
/*--------------------------------------------------------------------------*/
extern void GameAskChoice(int32_t nummess);
/*--------------------------------------------------------------------------*/
extern void GameOver(void);
/*--------------------------------------------------------------------------*/
extern void Help( uint8_t flaggame ) ;
/*--------------------------------------------------------------------------*/
extern void Credits(int32_t mode);
/*--------------------------------------------------------------------------*/
extern int32_t  SlideShow( void ) ;
/*--------------------------------------------------------------------------*/
extern void SlideDemo( int argc, char *argv[] ) ;
/*--------------------------------------------------------------------------*/
extern int32_t  AdelineLogo(void) ;
/*--------------------------------------------------------------------------*/
extern void DistribLogo(void) ;
/*--------------------------------------------------------------------------*/
extern int32_t  BumperLogo(void) ;
/*--------------------------------------------------------------------------*/
#ifdef	DEMO
extern void DemoLogo( void ) ;
/*--------------------------------------------------------------------------*/
extern void DemoBumper( void ) ;
#endif
/*--------------------------------------------------------------------------*/
extern void EffectPcx(uint8_t num,uint8_t *screen,uint8_t effect,uint8_t flagbcl);
/*--------------------------------------------------------------------------*/
extern void EffectPcxMess( uint8_t numpcx, uint8_t *screen, uint8_t effect, int32_t mess ) ;
/*--------------------------------------------------------------------------*/
extern void Introduction( void ) ;
/*--------------------------------------------------------------------------*/

#endif	// GAMEMENU_H
