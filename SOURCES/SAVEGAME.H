#ifndef	SAVEGAME_H
#define	SAVEGAME_H

extern	uint8_t	*PtrSave ;

#ifdef	DEMO
#define	NB_DEMOSAVE	3
extern	int32_t	CurrentDemoSave ;
extern	int32_t	NewDemoSave ;
extern	char	*ListDemoSave[NB_DEMOSAVE] ;

/*--------------------------------------------------------------------------*/
extern	int32_t	SetDemoSaveGame( int32_t num ) ;
/*--------------------------------------------------------------------------*/
#endif

/*--------------------------------------------------------------------------*/
extern void AutoSaveGame(void);
/*--------------------------------------------------------------------------*/
extern void CurrentSaveGame(void);
/*--------------------------------------------------------------------------*/
extern void SaveGame(int32_t flagmess);
/*--------------------------------------------------------------------------*/
extern void LoadGameNumCube(void);
/*--------------------------------------------------------------------------*/
extern void LoadGamePlayerName(void);
/*--------------------------------------------------------------------------*/
extern uint8_t   *LoadGameScreen(void);
/*--------------------------------------------------------------------------*/
extern int32_t  LoadGame(void);
/*--------------------------------------------------------------------------*/
extern int32_t  LoadGameOldVersion(void) ;
/*--------------------------------------------------------------------------*/
extern void SaveContexte( int32_t savetimerrefhr ) ;
/*--------------------------------------------------------------------------*/
extern int32_t  LoadContexte( int32_t *savetimerrefhr ) ;
/*--------------------------------------------------------------------------*/

#endif	// SAVEGAME_H
