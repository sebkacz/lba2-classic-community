/*

	Gestion de la mémoire LBA2


*/

#define	NB_MEM_ELTS	NbTabIndex(ListMem)

enum {
	MEM_PTR_ZBUFFER = 0,
	MEM_SCREEN_AUX,
	MEM_BUFSPEAK,
	MEM_SCREEN,
	MEM_BUFFER_MASK_BRICK,
	MEM_BUF_MAP,
	MEM_TAB_BLOCK,
	MEM_LIST_FLOW_DOTS,
	MEM_PTR_XPL_PALETTE
	} ;

typedef struct {
	void	**AdrPtr ;
	int32_t	Size ;
	} T_MEM ;

extern	T_MEM	ListMem[] ;

extern	int32_t	SizeOfMemAllocated 	;	// calculée dynamiquement
extern	uint8_t	*MainBuffer		;

extern	void	AdjustLba2Mem( void ) ;
extern	void   	InitMainBuffer( void ) ;
extern	void	InitMemory( void ) ;
