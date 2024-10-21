//──────────────────────────────────────────────────────────────────────────
#include <SYSTEM.H>
#include <SVGA/SCREEN.H>
#include <FILEIO/SAVEPCX.H>

#include "PCXHEAD.H"

//──────────────────────────────────────────────────────────────────────────
static void next_char( uint32_t fd, uint8_t *pt, int32_t val)
{
	pt[Index++] = (uint8_t)val	;

	if ( Index == SIZE_BUF )
	{
		Index = 0			;
		Write( fd, pt, SIZE_BUF )	;
	}
}

//──────────────────────────────────────────────────────────────────────────
void SavePCX(char *filename, void *screen, int32_t xres, int32_t yres, void *ptrpalette)
{
	int32_t	i, k, number, num_out	;
	int32_t	ch, old_ch 		;
	uint8_t	file_buf[SIZE_BUF]	;
	int32_t	fd 			;

	PcxHeader.password	= 0x0A	;
	PcxHeader.version	= 0x05	;
	PcxHeader.encoding	= 0x01	;
	PcxHeader.xmin 		= 0	;
	PcxHeader.ymin 		= 0	;
	PcxHeader.reserved 	= 0	;
	PcxHeader.palette_type 	= 0	;

	// resx * resy - 256 colors
	PcxHeader.bits_per_pixel= 0x08		;
	PcxHeader.xmax 		= (int16_t)(xres-1)	;
	PcxHeader.ymax 		= (int16_t)(yres-1)	;
	PcxHeader.xres 		= (int16_t)xres	;
	PcxHeader.yres 		= (int16_t)yres	;
	PcxHeader.no_of_planes	= 1 		;
	PcxHeader.bytes_per_line= (int16_t)xres	;

	fd = OpenWrite(filename) 	;

	if(!fd)
	{
		return	;
	}

	Write(fd, &PcxHeader, 128)	;

	Index = 0	;

	for ( k = 0; k < yres; k++ )
	{
		number = 1	;

                old_ch = ((uint8_t*)screen)[ModeDesiredX*k]   ;

		for ( i = 1 ; i <= xres; i++ )
		{
			if ( i == xres )
			{
				ch = old_ch-1	;
			}
			else
			{
                                ch = ((uint8_t*)screen)[ModeDesiredX*k+i]     ;
			}

			if (( ch == old_ch ) && (number < 63) )
			{
				number++ ;
			}
			else
			{
				num_out = ((uint8_t) number | 0xC0)	;
				if ((number != 1) || ((old_ch & 0xC0) == 0xC0))
				{
					next_char(fd, file_buf, num_out);
				}
				next_char(fd, file_buf, old_ch)	;
				old_ch	= ch			;
				number	= 1			;
			}
		}
	}

	next_char(fd, file_buf, 0x0C)	;

	Write(fd, file_buf, Index)	;

	Write(fd, ptrpalette, 768)	;

	Close(fd) 	;
}

//──────────────────────────────────────────────────────────────────────────
