#ifndef	AMBIANCE_H
#define	AMBIANCE_H

extern	int32_t	RestartRainSample ;

#define	MAX_PLAYING_SAMPLES	32

#if defined(DEBUG_TOOLS)||defined(TEST_TOOLS)
extern	int32_t	NbPlayingSamples ;
extern	SAMPLE_PLAYING	ListPlayingSamples[MAX_PLAYING_SAMPLES] ;
#endif

/*--------------------------------------------------------------------------*/
extern void StartRainSample( void ) ;
/*--------------------------------------------------------------------------*/
extern HQR_GET_CALLBACK	DelBlocHQRSample ;
/*--------------------------------------------------------------------------*/
extern uint32_t  HQ_MixSample(int32_t numsample,int32_t frequence,int32_t decalage,int32_t repeat,int32_t pan,int32_t volume);
/*--------------------------------------------------------------------------*/
extern uint32_t  HQ_RestartSample( int32_t numsample, int32_t frequence, int32_t repeat, int32_t pan, int32_t volume ) ;
/*--------------------------------------------------------------------------*/
extern void HQ_StopSample();
/*--------------------------------------------------------------------------*/
#define	HQ_StopOneSample(num)	StopOneSample(num)
/*--------------------------------------------------------------------------*/
extern void HQ_FadeOutSamples( int32_t dureehr ) ;
/*--------------------------------------------------------------------------*/
extern void HQ_FadeInSamples( int32_t dureehr ) ;
/*--------------------------------------------------------------------------*/
extern void HQ_PauseSamples(void) ;
/*--------------------------------------------------------------------------*/
extern void HQ_ResumeSamples(void) ;
/*--------------------------------------------------------------------------*/
extern int32_t  GiveBalance(int32_t xp,int32_t yp,int32_t distance,uint32_t *pan,int32_t *vol);
/*--------------------------------------------------------------------------*/
extern uint32_t  HQ_3D_MixSample(int32_t numsample,int32_t frequence,int32_t decalage,int32_t repeat,int32_t x,int32_t y,int32_t z);
/*--------------------------------------------------------------------------*/
extern void HQ_ChangePanSample( int32_t numsample, int32_t volume, uint32_t pan ) ;
/*--------------------------------------------------------------------------*/
extern void HQ_3D_ChangePanSample( int32_t numsample, int32_t x, int32_t y, int32_t z ) ;
/*--------------------------------------------------------------------------*/
extern void LaunchAmbiance( void ) ;
/*--------------------------------------------------------------------------*/
extern void GereAmbiance(void);
/*--------------------------------------------------------------------------*/
extern void ClearAmbiance( void ) ;
/*--------------------------------------------------------------------------*/
extern void InitPalette( void ) ;
/*--------------------------------------------------------------------------*/
extern void ChoicePalette( void ) ;
/*--------------------------------------------------------------------------*/
extern void FadePal(uint8_t r,uint8_t v,uint8_t b,uint8_t *ptrpal,int32_t percent);
/*--------------------------------------------------------------------------*/
extern void FadeToBlack(uint8_t *ptrpal);
/*--------------------------------------------------------------------------*/
extern void WhiteFade(void);
/*--------------------------------------------------------------------------*/
extern void FadeWhiteToPal(uint8_t *ptrpal);
/*--------------------------------------------------------------------------*/
extern void FadeToPal(uint8_t *ptrpal);
/*--------------------------------------------------------------------------*/
extern void FadeToBlackAndSamples( uint8_t *ptrpal ) ;
/*--------------------------------------------------------------------------*/
extern void FadeToPalAndSamples( uint8_t *ptrpal ) ;
/*--------------------------------------------------------------------------*/
extern void SetBlackPal(void);
/*--------------------------------------------------------------------------*/
extern void FadePalToPal( uint8_t *ptrpal, uint8_t *ptrpal1 ) ;
/*--------------------------------------------------------------------------*/
extern void FadeToPalIndex( uint8_t num ) ;
/*--------------------------------------------------------------------------*/
extern void PaletteIndex(uint8_t num);
/*--------------------------------------------------------------------------*/
extern void ReadVolumeSettings(void);
/*--------------------------------------------------------------------------*/
extern void WriteVolumeSettings(void);
/*--------------------------------------------------------------------------*/

#endif	// AMBIANCE_H
