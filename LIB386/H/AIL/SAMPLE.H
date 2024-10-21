//--------------------------------------------------------------------------
#ifndef	LIB_AIL_SAMPLE
#define	LIB_AIL_SAMPLE

//--------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------------------------------------------------
extern	char		SampleDriverName[]	;

extern	int32_t		Sample_Driver_Enabled	;

extern	int32_t		SamplingRate		;

extern	int32_t		SampleOverflow		;

//--------------------------------------------------------------------------
typedef	struct {
		int32_t	Usernum	;
		int32_t	Pitch  	;
		uint8_t	Repeat	;
		uint8_t	Volume	;
		uint8_t	Pan	;
		uint8_t	Dummy	;
	}	SAMPLE_PLAYING	;

//--------------------------------------------------------------------------
extern	VOID_FUNC	ClearSampleDriver	;
extern	VOID_FUNC	PauseSamples		;
extern	VOID_FUNC	ResumeSamples		;

//--------------------------------------------------------------------------
extern	int32_t		UseWaveMixer		;

//--------------------------------------------------------------------------
int32_t	InitSampleDriver(	char *driver_name	)	;

//--------------------------------------------------------------------------
//	SetMasterVolumeSample :		Set master volume for all samples
//
//			  volume : 	master volume (0-127)
//
//	Returns	: 			Nothing
//--------------------------------------------------------------------------
void	SetMasterVolumeSample(	int32_t volume 		)	;

//--------------------------------------------------------------------------
//	GetMasterVolumeSample :		Get master volume for all samples
//
//	Returns	: 			Master Volume
//--------------------------------------------------------------------------
int32_t	GetMasterVolumeSample(	void			)	;

//--------------------------------------------------------------------------
//	FadeOutSamples :		Fade out all samples (except stream)
//
//			  delay : 	delay for fade (in ms)
//
//	Returns	: 			scaling factor (from delay to 0)
//--------------------------------------------------------------------------
int32_t	FadeOutSamples(		int32_t delay 		)	;

//--------------------------------------------------------------------------
//	FadeInSamples :			Fade in all samples (except stream)
//
//			  delay : 	delay for fade (in ms)
//
//	Returns	: 			scaling factor (from 0 to delay)
//--------------------------------------------------------------------------
int32_t	FadeInSamples(		int32_t delay 		)	;

//--------------------------------------------------------------------------
//	InverseStereoSample :		Reverse left and right channels
//
//			  inverse : 	TRUE for inverse, FALSE to reset
//
//	Returns	: 			Nothing
//--------------------------------------------------------------------------
void	InverseStereoSample(	int32_t inverse 		)	;

//--------------------------------------------------------------------------
//	PlaySample : 			Play a Sample
//
//			  buffer    :	Pointer to the sample in mem
//			  userhandle: 	user handle (0 - 0xFFFF)
//			  pitchbend : 	4096 is no bend
//			  repeat    : 	number of times to play the sample
//			  volume    : 	Volume (127 max, clipped if > 127)
//			  pan	    : 	Paning (0-127, 64 dead center)
//
//	Returns	: 			lib sample handle
//--------------------------------------------------------------------------
uint32_t	PlaySample( 		void *buffer,
				uint32_t userhandle,
				int32_t pitchbend,
				int32_t repeat,
				int32_t volume,
				int32_t pan		)	;

//--------------------------------------------------------------------------
//	TimerPlaySample :		Play a Sample and repeat with period
//
//			  buffer    :	Pointer to the sample in mem
//			  userhandle: 	user handle (0 - 0xFFFF)
//			  pitchbend : 	4096 is no bend
//			  repeat    : 	number of times to play the sample
//			  volume    : 	Volume (127 max)
//			  pan	    : 	Paning (0-127, 64 dead center)
//			  period    :   in ms
//
//	Returns	: 			TRUE / FALSE
//--------------------------------------------------------------------------
uint32_t	TimerPlaySample(	void *ptrsample,
				uint32_t usernum,
				int32_t pitchbend,
				int32_t nbrepeat,
				int32_t volume,
				int32_t pan,
				int32_t period	);

//--------------------------------------------------------------------------
//	TimerStopSample :		stop TimerPlaySample
//
//	Returns	:			nothing
//--------------------------------------------------------------------------
void	TimerStopSample(	void		)	;

//--------------------------------------------------------------------------
//	ChangePitchbendSample :		Change a sample pitchbend
//
//			  sample :	sample handle
//			  pitchbend : 	4096 is no bend
//
//	Returns	:			nothing
//--------------------------------------------------------------------------
void	ChangePitchbendSample(	uint32_t sample,
				int32_t pitchbend	)	;

//--------------------------------------------------------------------------
//	ChangeVolumePanSample :		Change a sample	volume and paning
//
//			  sample :	sample handle
//			  volume : 	Volume (127 max)
//			  pan    : 	Paning (0-127, 64 dead center)
//
//	Returns	:			nothing
//--------------------------------------------------------------------------
void	ChangeVolumePanSample(	uint32_t sample,
				int32_t volume,
				int32_t pan		)	;

//--------------------------------------------------------------------------
//	GetSampleMSSHandle :		return MSS handle for a sample
//
//			  sample :	sample handle
//
//	Returns	:			HSAMPLE (see MSS doc)
//--------------------------------------------------------------------------
void*	GetSampleMSSHandle( 	uint32_t sample 	)	;

//--------------------------------------------------------------------------
//	StopOneSample :			stop a sample
//
//			  sample :	sample handle
//
//	Returns	:			nothing
//--------------------------------------------------------------------------
void	StopOneSample( 		uint32_t sample 		)	;

//--------------------------------------------------------------------------
//	StopSample :			stop all samples
//
//	Returns	:			nothing
//--------------------------------------------------------------------------
void	StopSamples(		void			)	;

//--------------------------------------------------------------------------
//	PauseOneSample :		pause a sample
//
//			  sample :	sample handle
//
//	Returns	:			nothing
//--------------------------------------------------------------------------
void	PauseOneSample(		uint32_t sample 		)	;

//--------------------------------------------------------------------------
//	ResumeOneSample :		resume a sample
//
//			  sample :	sample handle
//
//	Returns	:			nothing
//--------------------------------------------------------------------------
void	ResumeOneSample(	uint32_t sample 		)	;

//--------------------------------------------------------------------------
//	PauseSample :			pause all samples
//
//	Returns	:			nothing
//--------------------------------------------------------------------------
void	PauseSamples(		void			)	;

//--------------------------------------------------------------------------
//	ResumeSample :			resume all samples
//
//	Returns	:			nothing
//--------------------------------------------------------------------------
void	ResumeSamples(		void			)	;

//--------------------------------------------------------------------------
//	GetPlayingSamples :		get list of all playing samples
//
//			  tab :		array of sample descriptor
//			  max :		max number of samples in list
//
//	Returns	:			number of samples playing
//--------------------------------------------------------------------------
int32_t	GetPlayingSamples(	SAMPLE_PLAYING tab[],
				int32_t max			)	;

//--------------------------------------------------------------------------
//	IsSamplePlaying :		check if a sample is playing
//
//			  sample :	sample handle
//
//	Returns	:			FALSE or starting TimerRefHR
//--------------------------------------------------------------------------
uint32_t	IsSamplePlaying( 	uint32_t sample 		)	;

//--------------------------------------------------------------------------
//	GetSamplePostion :		get sample number currently playing
//
//			  sample :	sample handle
//
//	Returns	:			sample position
//--------------------------------------------------------------------------
int32_t	GetSamplePosition( uint32_t sample )				;

//--------------------------------------------------------------------------
//	GetSamplePostion :		get sample polyphonie
//
//	Returns	:			number of samples playing
//--------------------------------------------------------------------------
int32_t	GetSamplePoly( void )					;

//--------------------------------------------------------------------------
//	GetSamplePostion :		get a piece of data
//
//			  sample :	sample handle
//			  index  :	data index (0-6)
//			  value  :	data value
//
//	Returns	:			nothing
//--------------------------------------------------------------------------
void	SetDataSample( uint32_t sample, int32_t index, int32_t value )	;

//--------------------------------------------------------------------------
//	GetSamplePostion :		get a piece of data
//
//			  sample :	sample handle
//			  index :	data index (0-6)
//
//	Returns	:			value
//--------------------------------------------------------------------------
int32_t	GetDataSample( uint32_t sample, int32_t index )			;

//--------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif

//--------------------------------------------------------------------------
#endif//LIB_AIL_SAMPLE

//--------------------------------------------------------------------------
