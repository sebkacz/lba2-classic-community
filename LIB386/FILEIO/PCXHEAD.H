//──────────────────────────────────────────────────────────────────────────
#define	SIZE_BUF	2048L

//──────────────────────────────────────────────────────────────────────────
typedef	struct
	{
		char 	password;
		char 	version;
		char 	encoding;
		char 	bits_per_pixel;
		int16_t 	xmin, ymin, xmax, ymax;
		int16_t 	xres, yres;
		uint8_t 	palette[48];
		char 	reserved;
		char 	no_of_planes;
		int16_t 	bytes_per_line;
		int16_t 	palette_type;
		char 	filler[58];
	} 	PCX_HEADER	;

//──────────────────────────────────────────────────────────────────────────
extern	PCX_HEADER	PcxHeader;

//──────────────────────────────────────────────────────────────────────────
extern	int32_t		Index	;

//──────────────────────────────────────────────────────────────────────────

