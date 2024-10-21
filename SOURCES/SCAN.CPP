#include        "C_EXTERN.H"

#include <SYSTEM/KEYBOARD.H>

#ifdef _WIN32 // Portability - Intrinsics are different for MSVC and GCC
#include <intrin.h>
#endif

//──────────────────────────────────────────────────────────────────────────
static  uint8_t      KeyState[256+16*8]   ;

//──────────────────────────────────────────────────────────────────────────
uint32_t GetBit(uint32_t val) {
  if (val == 0) {
    return 0;
  }

#ifdef _WIN32 // Portability - Intrinsics are different for MSVC and GCC
  unsigned long index;
  _BitScanForward(&index, val);
  return index;
#else // _WIN32
  return __builtin_ctz(val);
#endif // _WIN32
}

//──────────────────────────────────────────────────────────────────────────
int32_t     KeyDown()
{
        int32_t     i       ;
        int32_t     found   ;
        uint32_t     *Joys, *OldJoys ;

	DetectJoys()	;
        GetJoys((uint32_t*)(TabKeys+256))    ;
        ManageKeyboard();

        found = 0       ;

        for(i=255; i>=0; i--)
        {
                uint8_t      key     ;

                key = (uint8_t)(~KeyState[i]&0x80);

                KeyState[i] = TabKeys[i];

                TabKeys[i] &= key       ;

                // FIXME: Add checks back
                if(    /* (i>VK_MBUTTON)  &&
                        (i!=VK_EXECUTE) &&
                        (i!=VK_LWIN)    &&
                        (i!=VK_RWIN)    &&*/
                        !found&&TabKeys[i]      )
                {
                        found = i       ;
                }
        }

        OldJoys = (uint32_t*)&KeyState[256]  ;
        Joys = (uint32_t*)&TabKeys[256]      ;

        for(i=0; i<2*16; i++)
        {
                uint32_t bits        ;

                bits = ~OldJoys[i]      ;
                OldJoys[i] = Joys[i]    ;
                bits &= Joys[i]         ;
                Joys[i] = bits         	;

                if(!found&&bits)
                {
                        found = 256+i*32+GetBit(bits) ;
                }
        }

        return  found   ;
}

//──────────────────────────────────────────────────────────────────────────
