//──────────────────────────────────────────────────────────────────────────
#ifndef	LIB_MENU_SELECTOR
#define	LIB_MENU_SELECTOR

//──────────────────────────────────────────────────────────────────────────
#ifdef __cplusplus
extern "C" {
#endif

//──────────────────────────────────────────────────────────────────────────
extern	char	SelectorPathname[] 	;

//──────────────────────────────────────────────────────────────────────────
typedef	int 	(COMP_FUNC)( void const *, void const * ) ;

extern	COMP_FUNC 	MySortCompFunc	;

#pragma	aux MySortCompFunc	"*"

//──────────────────────────────────────────────────────────────────────────
extern void CutFileName( char *filename )	;

//──────────────────────────────────────────────────────────────────────────
extern int32_t FileSelector(	char *titre,		char *selection,
				char *defaultname,	int32_t flags	);

//──────────────────────────────────────────────────────────────────────────
#ifdef __cplusplus
}
#endif

//──────────────────────────────────────────────────────────────────────────
#endif//LIB_MENU_SELECTOR

//──────────────────────────────────────────────────────────────────────────

