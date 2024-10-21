//--------------------------------------------------------------------------
#ifndef	LIB_AIL_AIL
#define	LIB_AIL_AIL

//--------------------------------------------------------------------------
#ifdef __cplusplus
extern "C" {
#endif

//--------------------------------------------------------------------------
extern	int32_t		Sample_Driver_Enabled	;
extern	int32_t		Midi_Driver_Enabled	;
extern	int32_t		SamplingRate		;

//--------------------------------------------------------------------------
extern	char		MidiDriverName[]	;
extern	char		SampleDriverName[]	;

//--------------------------------------------------------------------------
extern	VOID_FUNC	*PauseMidiPtr		;
extern	VOID_FUNC	*ResumeMidiPtr		;

extern	VOID_FUNC	*PauseSamplesPtr	;
extern	VOID_FUNC	*ResumeSamplesPtr	;

//--------------------------------------------------------------------------
extern	VOID_FUNC	PauseBothMiles		;

//--------------------------------------------------------------------------
extern	VOID_FUNC	ResumeBothMiles		;

//--------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif

//--------------------------------------------------------------------------
#endif//LIB_AIL_AIL

//--------------------------------------------------------------------------
