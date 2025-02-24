#ifndef	PERSO_H
#define	PERSO_H

#if defined(DEBUG_TOOLS) || defined(TEST_TOOLS)
/*--------------------------------------------------------------------------*/
extern void AffDebugMenu(void);
/*--------------------------------------------------------------------------*/
#endif	// DEBUG_TOOLS

/*--------------------------------------------------------------------------*/
extern void CheckSavePcx(void);
/*--------------------------------------------------------------------------*/
extern void CheckSaveLogPcx( uint8_t *pal );
/*--------------------------------------------------------------------------*/
extern void LoadListAnim3DS( void );
/*--------------------------------------------------------------------------*/
extern void InitGameLists(void);
/*--------------------------------------------------------------------------*/
extern void InitGame(int argc);
/*--------------------------------------------------------------------------*/
extern void Introduction(void);
/*--------------------------------------------------------------------------*/
extern void GamePaused(uint32_t flags);
/*--------------------------------------------------------------------------*/
extern int32_t  MainLoop(void);
/*--------------------------------------------------------------------------*/
extern void InitProgram();
/*--------------------------------------------------------------------------*/
extern void TheEndCheckFile(const char *filename);
/*--------------------------------------------------------------------------*/
extern void InitTheEnd(int32_t num,char *error);
/*--------------------------------------------------------------------------*/
extern void TheEnd(int32_t num, const char *error);
/*--------------------------------------------------------------------------*/
extern void TheEndInfo(void);
/*--------------------------------------------------------------------------*/
extern void Message(const char *mess,int32_t flag);
/*--------------------------------------------------------------------------*/

#endif	// PERSO_H
