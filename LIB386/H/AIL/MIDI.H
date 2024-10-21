//--------------------------------------------------------------------------
#ifndef	LIB_AIL_MIDI
#define	LIB_AIL_MIDI

//--------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------------------------------------------------
#define	OPL2			1
#define	OPL3			2
#define	MIDI			3

//--------------------------------------------------------------------------
extern	char		MidiDriverName[]	;

extern	int32_t		Midi_Driver_Enabled	;
extern	int32_t		Midi_Driver_Type	;

//--------------------------------------------------------------------------
extern	VOID_FUNC	ClearMidiDriver		;
extern	VOID_FUNC	PauseMidi		;
extern	VOID_FUNC	ResumeMidi		;

//--------------------------------------------------------------------------
int32_t	InitMidiDriver(	char *driver_name		)	;

//--------------------------------------------------------------------------
//	ReserMidi : 			Reset all controlers in Midi Synth
//
//	Returns	: 			nothing
//--------------------------------------------------------------------------
void	ResetMidi(		void			)	;

//--------------------------------------------------------------------------
//	PrepareMidi : 			Prepare a Midi for playback
//
//			  ptrxmi :	xmi pointer
//			  seqnum :	sequence num
//			  volume : 	Volume (127 max)
//
//	Returns	: 			boolean
//--------------------------------------------------------------------------
uint32_t	PrepareMidi( 		void *ptrxmi,
				int32_t  seqnum,
				int32_t  volume 		)	;

//--------------------------------------------------------------------------
//	ClearMidi :			stop midi until next PrepareMidi
//
//	Returns	:			nothing
//--------------------------------------------------------------------------
void	ClearMidi(		void			)	;

//--------------------------------------------------------------------------
//	PlayBlockMidi :			Play a Midi block
//
//			  blocknum :	block num
//
//	Returns	: 			nothing
//--------------------------------------------------------------------------
void	PlayBlockMidi( 		int32_t blocknum		)	;

//--------------------------------------------------------------------------
//	ChainBlockMidi :		Chain a Midi block in the sequence
//
//			  blocknum :	block num
//
//	Returns	: 			nothing
//--------------------------------------------------------------------------
void	ChainBlockMidi(		int32_t blocknum		)	;

//--------------------------------------------------------------------------
//	ChangeVolumeMidi :		Change the midi volume
//
//			  volume : 	Volume (127 max)
//			  delay	 : 	time to change the volume (in ms)
//
//	Returns	:			nothing
//--------------------------------------------------------------------------
void	ChangeVolumeMidi(	int32_t volume,
				int32_t delay		)	;

//--------------------------------------------------------------------------
//	StopMidi :			stop midi
//
//	Returns	:			nothing
//--------------------------------------------------------------------------
void	StopMidi(		void			)	;

//--------------------------------------------------------------------------
//	PauseMidi :			pause midi
//
//	Returns	:			nothing
//--------------------------------------------------------------------------
void	ResumeMidi(		void			)	;

//--------------------------------------------------------------------------
//	ResumeMidi :			resume midi
//
//	Returns	:			nothing
//--------------------------------------------------------------------------
void	ResumeMidi(		void			)	;

//--------------------------------------------------------------------------
//	StopChainMidi :			Stop chaining the midi sequence.
//					Current track keep playing
//
//	Returns	:			nothing
//--------------------------------------------------------------------------
void	StopChainMidi(		void			)	;

//--------------------------------------------------------------------------
//	GetBlockPlaying :		check which Midi block is playing
//
//	Returns	:			Midi block number (-1 if none)
//--------------------------------------------------------------------------
int32_t	GetBlockPlayingMidi(	void			)	;

//--------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif

//--------------------------------------------------------------------------
#endif//LIB_AIL_MIDI

//--------------------------------------------------------------------------

