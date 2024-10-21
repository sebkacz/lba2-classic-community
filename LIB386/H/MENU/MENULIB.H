//──────────────────────────────────────────────────────────────────────────
#ifndef	LIB_MENU_MENULIB
#define	LIB_MENU_MENULIB

//──────────────────────────────────────────────────────────────────────────
#ifdef __cplusplus
extern "C" {
#endif

//──────────────────────────────────────────────────────────────────────────
// PalMenu colors

#define BLACK		0
#define B_GREY		1	// 2, 3
#define B_RED	 	4	// 5, 6
#define YELLOW		7

// Unused: 8, 9

// Reserved: 10 to 245

#define BLUE		246
#define GREEN		247
#define CYAN		248
#define RED		249
#define MAGENTA		250

// Unused: 251, 252, 253, 254

#define WHITE		255

//──────────────────────────────────────────────────────────────────────────
#define SELECT_NO_FLAG		0
#define SELECT_SHOW_EXT 	1
#define SELECT_TEST_EXIST	2
#define SELECT_TEST_OVERWRITE	4
#define SELECT_KEEP_POS 	8

#define NO_FLAG 		0
#define FLAG_PUSHED		0x00000001
#define FLAG_RED		0x00000002
#define FLAG_NO_PUSH		0x00000004
#define FLAG_CENTRE		0x00000100
#define FLAG_CONTOUR		0x00000200
#define FLAG_FILENAME		0x00000400
#define FLAG_REPEAT		0x00000800

#define TYPE_TEXT		0x00000001
#define TYPE_BUTTON		0x00000002
#define TYPE_WINDOW		0x00000004
#define TYPE_SWITCH		0x00000008
#define TYPE_CHANGE_VALUE	0x00000010
#define TYPE_DEC_VALUE		0x00000020
#define TYPE_INC_VALUE		0x00000040

//──────────────────────────────────────────────────────────────────────────
typedef struct	{	int32_t	X1 ;		// size/pos pixel box
			int32_t	Y1 ;
			int32_t	X2 ;
			int32_t	Y2 ;

			int32_t	Type ;
			int32_t	Flags ; 	// texte centré...

			int32_t	Handle ;	// info retournée si != -1
			const char	*PtrString ;

			int32_t	*PtrVar ;	// info switch
			int32_t	Mask ;

		}	T_CLICK_BOX ;


typedef struct	{	int32_t		NbBox 		;
			int32_t		LastClicked 	;
			T_CLICK_BOX	*PtrMallocList 	;

			int32_t	Largeur ;	// en caractere
			int32_t	Hauteur ;

			int32_t	X1 ;
			int32_t	Y1 ;
			int32_t	X2 ;
			int32_t	Y2 ;
			int32_t	Dx ;
			int32_t	Dy ;

			int32_t	Flags ;

			int32_t	Repeat ;

		}	T_MENU ;

typedef struct	{	int32_t	WindowX1 ;
			int32_t	WindowY1 ;
			int32_t	WindowX2 ;
			int32_t	WindowY2 ;
			int32_t	WindowLig ;
			int32_t	WindowCol ;
			int32_t	WindowTab ;
			int32_t	WindowNbIndex ;
			char	**WindowArray ;

		}	T_WINLIST ;

//──────────────────────────────────────────────────────────────────────────
extern	int32_t		Pointed 		;
extern	int32_t		FlagAutoPal		;

//──────────────────────────────────────────────────────────────────────────
#define			SetMenuAutoPal(	flag )	\
			FlagAutoPal = (flag)

//──────────────────────────────────────────────────────────────────────────
extern void 		DrawWindow(	int32_t x1,	int32_t y1,	int32_t x2,	int32_t y2,
					int32_t flags			);

extern void 		DrawBox(	T_MENU *ptrmenu, int32_t numlcb,
					int32_t pushed			);

extern T_CLICK_BOX 	*AddHeaderButton(T_MENU *ptrmenu,
					int32_t x1, int32_t y1,	int32_t width, int32_t height );

extern int32_t 		ScanListClick(	T_MENU *ptrmenu			);

//──────────────────────────────────────────────────────────────────────────
extern void 		InitPalMenu(	void		);

extern void 		CopyPalMenu(	uint8_t *ptrpal	);

//──────────────────────────────────────────────────────────────────────────
extern void 		OpenWindow(	T_WINLIST *wlist,
					int32_t x1, int32_t y1, int32_t largeur, int32_t hauteur);

extern void 		WinSepar(	T_WINLIST *wlist	);

extern void 		WinText(	T_WINLIST *wlist,
					char *string, int32_t value );

extern void 		WinList(	T_WINLIST *wlist,
					char **index, int32_t nb, int32_t size);

extern void 		WinSelect(	T_WINLIST *wlist,
					int32_t selected, int32_t coul	);

extern void 		FlipWindow(	T_WINLIST *wlist	);

extern int32_t 		GetIndexWinList(T_WINLIST *wlist	);

//──────────────────────────────────────────────────────────────────────────
extern int32_t 		OpenMenu(	T_MENU *ptrmenu, int32_t width, int32_t height);

extern void 		AddButton(	T_MENU *ptrmenu, int32_t handle,
					int32_t x1, int32_t y1, int32_t width, int32_t height,
					int32_t flags, const char *ptrstring	);

extern void 		AddChangeValue(	T_MENU *ptrmenu, int32_t handle,
					int32_t x1, int32_t y1, int32_t width, int32_t height,
					int32_t flags, char *ptrstring, int32_t *ptrvar,
					int32_t step, int32_t minvar, int32_t maxvar);

extern void 		AddSwitch(	T_MENU *ptrmenu, int32_t handle,
					int32_t x1, int32_t y1, int32_t width, int32_t height,
					int32_t flags, const char *ptrstring, int32_t *ptrvar,
					int32_t mask			);

extern void 		AddText(	T_MENU *ptrmenu,
					int32_t x1, int32_t y1, int32_t width, int32_t height,
					int32_t flags, const char *ptrstring);

extern void 		AddWindow(	T_MENU *ptrmenu, int32_t handle,
					int32_t x1, int32_t y1 ,int32_t width, int32_t height,
					int32_t flags			);

extern int32_t 		DrawMenu(	T_MENU *ptrmenu,
					int32_t x1, int32_t y1			);

extern int32_t 		GereMenu(	T_MENU *ptrmenu			);

extern void 		CloseMenu(	T_MENU *ptrmenu			);
extern void 		ClearMenu(	T_MENU *ptrmenu			);

//──────────────────────────────────────────────────────────────────────────
extern void 		GetWindowButton(T_MENU *ptrmenu, int32_t handle,
					T_WINLIST *wlist		);

extern void 		GetCoorButton(	T_MENU *ptrmenu, int32_t handle,
					int32_t *x0, int32_t *y0, int32_t *x1, int32_t *y1);

extern int32_t 		GetOptimalSize(	int32_t deltax		);

extern void 		GetCoorMenu(	T_MENU *ptrmenu,
					int32_t *x0, int32_t *y0, int32_t *x1, int32_t *y1);

extern void 		GetSizeMenu(	T_MENU *ptrmenu,
					uint32_t *pdx, uint32_t *pdy 	);

extern int32_t 		MenuBestFitX(	int32_t deltax 		);
extern int32_t 		MenuBestFitY(	int32_t deltay 		);

//──────────────────────────────────────────────────────────────────────────
#ifdef __cplusplus
}
#endif

//──────────────────────────────────────────────────────────────────────────
#endif//LIB_MENU_MENULIB

//──────────────────────────────────────────────────────────────────────────
