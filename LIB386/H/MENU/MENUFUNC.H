//──────────────────────────────────────────────────────────────────────────
#ifndef	LIB_MENU_MENUFUNC
#define	LIB_MENU_MENUFUNC

//──────────────────────────────────────────────────────────────────────────
#ifdef __cplusplus
extern "C" {
#endif

//──────────────────────────────────────────────────────────────────────────
extern void 		Message(const char *message, int32_t flag		);
extern int32_t 		Confirm(const char *message, const char *yes, const char *no	);

//──────────────────────────────────────────────────────────────────────────
extern void 		InputString(		T_MENU *ptrmenu, int32_t handle,
						int32_t maxchar		);

//──────────────────────────────────────────────────────────────────────────
extern void 		SwitchButton(		T_MENU *ptrmenu, int32_t handle);

extern void 		ChangeButtonFlags(	T_MENU *ptrmenu, int32_t handle,
						int32_t flags,	 int32_t flagaff);

extern void 		ChangeButtonString(	T_MENU *ptrmenu, int32_t handle,
						char *string,	 int32_t flagaff);

extern void 		ChangeButtonValueLimit( T_MENU *ptrmenu, int32_t handle,
						int32_t valmin, 	 int32_t valmax );

//──────────────────────────────────────────────────────────────────────────
extern	int32_t		GetButtonFlags(		T_MENU *ptrmenu, int32_t handle );

extern	const char*		GetButtonString(	T_MENU *ptrmenu, int32_t handle );

//──────────────────────────────────────────────────────────────────────────
extern T_CLICK_BOX 	*GetPtrLcb(		T_MENU *ptrmenu,int32_t handle  );

//──────────────────────────────────────────────────────────────────────────
#ifdef __cplusplus
}
#endif

//──────────────────────────────────────────────────────────────────────────
#endif//LIB_MENU_MENUFUNC

//──────────────────────────────────────────────────────────────────────────
