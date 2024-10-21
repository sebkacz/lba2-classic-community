#include <SYSTEM/INPUT.H>

#include <SYSTEM/ADELINE_TYPES.H>
#include <SYSTEM/KEYBOARD.H>

//***************************************************************************
	uint32_t	Input		;

//***************************************************************************
static	uint32_t	NoRepeatInput	;

//***************************************************************************
static	int32_t	NbKeys		;
static	uint32_t	*InputKeys	;
static	uint32_t	*InputMasks	;

//***************************************************************************
void	DefineInputKeys(int32_t nbkeys, uint32_t *keys, uint32_t *inputmasks)
{
	NbKeys		= nbkeys	;
	InputKeys	= keys		;
	InputMasks	= inputmasks	;
}

//***************************************************************************
void    GetInput(uint32_t norepeat)
{
	int32_t     i	;

	// update TabKeys
	ManageKeyboard()		;

	// update NoRepeatInput
	NoRepeatInput	|= norepeat	;

	// reset Input
	Input = 0 			;

        // Rebuild Input
        for(i=0; i<NbKeys; i++)
        {
                if(CheckKey(InputKeys[i]))	Input |= InputMasks[i]	;
        }

	// compute new NoRepeatInput
	norepeat	=  NoRepeatInput & Input ;

	// mask Input
	Input		&= ~NoRepeatInput;

	// update NoRepeatInput
	NoRepeatInput	=  norepeat	;
}

//***************************************************************************
// Added le 06/06/97 (function becose NoRepeatInput is static)
void    ClearNoRepeatInput( void )
{
	NoRepeatInput	=  0	;
}

//***************************************************************************
