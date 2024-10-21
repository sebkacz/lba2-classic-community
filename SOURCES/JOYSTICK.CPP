#include        "C_EXTERN.H"

//***************************************************************************

static  uint32_t             JoyThere        = 0     ;
static  uint32_t             JoyUsed         = -1    ;
static  uint32_t             JoyHasPov       = 0     ;
static  int32_t             JoyRange[16][6][2]      ;
//static  JOYINFOEX       JoyInfoEx               ;
// FIXME: Implement using SDL

//***************************************************************************
void    DetectJoys()
{
  // FIXME: Implement using SDL
//        uint32_t             i, j, n, k      ;
//        JOYCAPS         caps            ;
//
//        n = ade_min(joyGetNumDevs(), 16) 	;
//
//        JoyInfoEx.dwSize = sizeof(JoyInfoEx)    ;
//        JoyInfoEx.dwFlags = JOY_RETURNALL       ;
//
//        for(i=0, j=1; i<n; i++, j<<=1)
//        {
//                if(JoyThere&j)
//                {
//                        continue        ;
//                }
//
//                for(k=1000; k>0; k--)
//                {
//                        if(joyGetPosEx(JOYSTICKID1+i, &JoyInfoEx) != JOYERR_NOERROR)
//                        {
//                                k = 0   ;
//                                break   ;
//                        }
//                        if(!JoyInfoEx.dwButtons)
//                        {
//                                break   ;
//                        }
//                }
//                if(!k)
//                {
//                        continue        ;
//                }
//
//                if(joyGetDevCaps(JOYSTICKID1+i, &caps, sizeof(JOYCAPS)) != JOYERR_NOERROR)
//                {
//                        continue        ;
//                }
//
//                JoyThere |= j ;
//
//                if(caps.wCaps&JOYCAPS_HASPOV)
//                {
//                        JoyHasPov |= j  ;
//                }
//
//                JoyRange[i][0][0] = (caps.wXmax + caps.wXmin)/2 ;
//                JoyRange[i][0][1] = (caps.wXmax - caps.wXmin)/3 ;
//
//                JoyRange[i][1][0] = (caps.wYmax + caps.wYmin)/2 ;
//                JoyRange[i][1][1] = (caps.wYmax - caps.wYmin)/3 ;
//
//                JoyRange[i][2][0] = (caps.wZmax + caps.wZmin)/2 ;
//                JoyRange[i][2][1] = (caps.wZmax - caps.wZmin)/3 ;
//
//                JoyRange[i][3][0] = (caps.wRmax + caps.wRmin)/2 ;
//                JoyRange[i][3][1] = (caps.wRmax - caps.wRmin)/3 ;
//
//                JoyRange[i][4][0] = (caps.wUmax + caps.wUmin)/2 ;
//                JoyRange[i][4][1] = (caps.wUmax - caps.wUmin)/3 ;
//
//                JoyRange[i][5][0] = (caps.wVmax + caps.wVmin)/2 ;
//                JoyRange[i][5][1] = (caps.wVmax - caps.wVmin)/3 ;
//        }
}

//***************************************************************************
static inline uint32_t JoyMakeBitfield(uint32_t n, uint32_t *val, int32_t pov)
{
        int32_t     res, i, j       ;
        int32_t     temp            ;

        res     = 0 ;

        // FIXME: Implement using SDL
//        for(i=0, j=1; i<6; i++, j<<=2)
//        {
//                temp    = val[i] - JoyRange[n][i][0];
//
//                if(temp > JoyRange[n][i][1])
//                {
//                        res |= j;
//                }
//                else if(-temp > JoyRange[n][i][1])
//                {
//                        res |= j*2;
//                }
//        }
//
//        switch(pov)
//        {
//        case JOY_POVRIGHT:
//                res |= 1<<12 ;
//                break ;
//        case JOY_POVLEFT:
//                res |= 1<<13 ;
//                break ;
//        case JOY_POVBACKWARD:
//                res |= 1<<14 ;
//                break ;
//        case JOY_POVFORWARD:
//                res |= 1<<15 ;
//                break ;
//        }

        return res ;
}

//***************************************************************************
void    GetJoys(uint32_t *bitfield)
{
        // FIXME: Implement using SDL
//        int32_t     i, j;
//
//        if(!JoyUsed)    return  ;
//
//        for(i=0, j=1; i < 16; i++, j<<=1)
//        {
//                if(!(JoyUsed&JoyThere&j))	continue ;
//
//                // read buttons
//                JoyInfoEx.dwSize = sizeof(JoyInfoEx) ;
//                JoyInfoEx.dwFlags = JOY_RETURNALL ;
//                if(joyGetPosEx(JOYSTICKID1+i, &JoyInfoEx) == JOYERR_NOERROR)
//                {
//                        if(!(JoyHasPov&j))
//                        {
//                                JoyInfoEx.dwPOV = -1    ;
//                        }
//                        bitfield[i*2]  = JoyInfoEx.dwButtons ;
//                        bitfield[i*2+1]= JoyMakeBitfield(i, &JoyInfoEx.dwXpos, JoyInfoEx.dwPOV);
//                }
//                else
//                {
//                        bitfield[i*2]  = 0 ;
//                        bitfield[i*2+1]= 0 ;
//                }
//        }
}

//***************************************************************************
