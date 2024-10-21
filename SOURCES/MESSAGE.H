#ifndef	MESSAGE_H
#define	MESSAGE_H

//-------------------- Used by HoloGlob.cpp
extern	char    *PtDial         ;
extern	int32_t    X_Dial, Y_Dial  	;
extern	int32_t    Dial_X0		;
extern	int32_t    Dial_Y0		;
extern	int32_t    Dial_X1		;
extern	int32_t    Dial_Y1		;

extern	int32_t	FlagAnimWhoSpeak;

extern	int32_t	Language 	; // English

#ifdef	CDROM
extern	int32_t	LanguageCD 	; // Français, a changer of course!
#endif

extern	int32_t	FlagRestoreCD	;

/*
#ifdef	LBA_EDITOR
extern void InitAnimDial(char *newanimdial);
#else
extern void InitAnimDial(uint16_t newanimdial);
#endif
*/

extern  int32_t     FlagDisplayText ;

#if defined(CDROM)||defined(LBA_EDITOR)
extern	void	AddFileNameOnHD( char *filename, uint32_t size, uint32_t timer )	;
extern  uint32_t	*BufMemoSeek    ;
extern	void	InitVoiceFile( void )	;
extern	void	ClearVoiceFile( void )	;
extern	int32_t	Speak( int32_t text )	;
extern	int32_t	TestSpeak()		;
extern	void	StopSpeak()		;
extern	void	CloseFdNar()		;
#else
#define	StopSpeak()
#endif

extern	int32_t IsVoiceFileOnHD( int32_t island );
extern void InitLanguage(void);
extern int32_t  FindText(int32_t text);
extern void InitDial(int32_t file);
extern void ClearDial(void);
extern void GetNextWord(char *ptchaine,char *mot);
extern void AffOneCar(int32_t x,int32_t y,char c,int32_t coul);
extern void AffAllCar(void);
extern void CoulDial(int32_t min,int32_t max,int32_t step);
extern void TestCoulDial(int32_t coul);
extern int32_t  GereFlagDial( int32_t text );
extern int32_t  GetText(int32_t text);
extern void AffFleche(void);
//----- incrust vignette Radio
extern void TestAndDrawRadio( void ) ;
extern void InitDialWindow(void);
extern void HoloInitDialWindow(void);
extern void AffHoloDialWindow(void);
extern void NormalWinDial(void);
extern void BigWinDial(void);
extern void HoloWinDial(void) ;
extern void CommonOpenDial(int32_t text);
extern void OpenDial(int32_t text);
extern void GetNextLine(void);
extern void InitEndPage(void);
extern void NextDialWindow();
extern int32_t  NextDialCar(void);
extern void CloseDial(void);
extern void InitWhoSpeak(int32_t numobj);
extern void ClearWhoSpeak(void);
extern void SpeakAnimation(void);
extern void Dial(int32_t text,int32_t drawscene);
extern int32_t  MyDial(int32_t nummess);
extern char *GetMultiText(int32_t text,char *dst);
extern void CleanMessage(char *string,int32_t flag);
extern void LoadListMessages(int32_t file);
extern void FreeListMessages(void);
extern int32_t  NextMessagePerso(int32_t numperso,int32_t message);
extern int32_t  PreviousMessagePerso(int32_t numperso,int32_t message);
extern int32_t  VerifyMessagePerso(int32_t numperso,int32_t message);

#endif	// MESSAGE_H
