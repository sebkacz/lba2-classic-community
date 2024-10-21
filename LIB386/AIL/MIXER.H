//████████████████████████████████████████████████████████████████████████████
#ifndef	LIB_AIL_MIXER
#define	LIB_AIL_MIXER

//████████████████████████████████████████████████████████████████████████████

#ifdef	__cplusplus
extern	"C"	{
#endif

//████████████████████████████████████████████████████████████████████████████

typedef	struct
	{
		int32_t	DeviceID;
		int32_t	ControlID;
		int32_t	Channels;
	}	VOLUMECONTROL	;

//████████████████████████████████████████████████████████████████████████████

// MIXERLINE_COMPONENTTYPE_DST_FIRST
// MIXERLINE_COMPONENTTYPE_DST_UNDEFINED
// MIXERLINE_COMPONENTTYPE_DST_DIGITAL
// MIXERLINE_COMPONENTTYPE_DST_LINE
// MIXERLINE_COMPONENTTYPE_DST_MONITOR
// MIXERLINE_COMPONENTTYPE_DST_SPEAKERS
// MIXERLINE_COMPONENTTYPE_DST_HEADPHONES
// MIXERLINE_COMPONENTTYPE_DST_TELEPHONE
// MIXERLINE_COMPONENTTYPE_DST_WAVEIN
// MIXERLINE_COMPONENTTYPE_DST_VOICEIN
// MIXERLINE_COMPONENTTYPE_DST_LAST

// MIXERLINE_COMPONENTTYPE_SRC_FIRST
// MIXERLINE_COMPONENTTYPE_SRC_UNDEFINED
// MIXERLINE_COMPONENTTYPE_SRC_DIGITAL
// MIXERLINE_COMPONENTTYPE_SRC_LINE
// MIXERLINE_COMPONENTTYPE_SRC_MICROPHONE
// MIXERLINE_COMPONENTTYPE_SRC_SYNTHESIZER
// MIXERLINE_COMPONENTTYPE_SRC_COMPACTDISC
// MIXERLINE_COMPONENTTYPE_SRC_TELEPHONE
// MIXERLINE_COMPONENTTYPE_SRC_PCSPEAKER
// MIXERLINE_COMPONENTTYPE_SRC_WAVEOUT
// MIXERLINE_COMPONENTTYPE_SRC_AUXILIARY
// MIXERLINE_COMPONENTTYPE_SRC_ANALOG
// MIXERLINE_COMPONENTTYPE_SRC_LAST

//████████████████████████████████████████████████████████████████████████████

int32_t	GetMixerVolDevice(VOLUMECONTROL *volcontrol, int32_t type)	;

//████████████████████████████████████████████████████████████████████████████

int32_t	GetMixerVolume(VOLUMECONTROL *volcontrol)		;

//████████████████████████████████████████████████████████████████████████████

void	SetMixerVolume(VOLUMECONTROL *volcontrol, int32_t volume)	;

//████████████████████████████████████████████████████████████████████████████

#ifdef	__cplusplus
}
#endif

//████████████████████████████████████████████████████████████████████████████

#endif//LIB_AIL_MIXER

//████████████████████████████████████████████████████████████████████████████
