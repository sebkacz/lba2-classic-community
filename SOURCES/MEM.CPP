/*

			Gestion de la mémoire LBA2


*/


#include	"C_EXTERN.H"	// include LBA2

#include <SVGA/SCREEN.H>
#include "DIRECTORIES.H"

extern	uint8_t  	*BufferSmack ;// tempo ?

int32_t	PtrSceneMem	;
int32_t	BufferFile3DMem ;
int32_t	TabPartFlowMem  ;
int32_t	BufferPofMem    ;
int32_t	BufferImpactMem ;

struct	SizeInfo {
	int32_t	MaxSizeListDecors ;
	int32_t	MaxSizeBodyDecors ;
	int32_t	MaxSizeTexDef ;
	int32_t	MaxTotalBodyDecors ;
	} ;

// penser à réaligner les pointeurs (par une macro ?)

T_MEM	ListMem[] = {
	{(void**)&PtrZBuffer, SIZE_Z_BUFFER},	// Calculé dynamiquement (GRILLE.CPP) -> InitBufferCube())
	{(void**)&ScreenAux, 640*480+RECOVER_AREA},
	{(void**)&BufSpeak, 640*480+RECOVER_AREA},
	{(void**)&Screen, 640*480+RECOVER_AREA},
	{(void**)&BufferMaskBrick,0},	// Calculé dynamiquement (GRILLE.CPP -> InitBufferCube())
	{(void**)&BufMap,0},	// Calculé dynamiquement (GRILLE.CPP -> InitBufferCube())
	{(void**)&TabBlock,0},	// Calculé dynamiquement (GRILLE.CPP -> InitBufferCube())
	{(void**)&ListFlowDots, sizeof(S_ONE_DOT)*MAX_FLOW_DOTS*MAX_FLOWS},
	{(void**)&PtrXplPalette, SIZE_XPL},
	{(void**)&BufferSmack, 100000L},// tempo ?
	} ;

int32_t	SizeOfMemAllocated 	;	// calculée dynamiquement
uint8_t	*MainBuffer		;

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
// Spécifique à LBA2: redistribue la mémoire disponible aux différents buffers
void	AdjustLba2Mem( void )
{
	char tmpFilePath[ADELINE_MAX_PATH];

	InitBufferCube() ;	// Calcule taille nécessaire à l'interieur

	// Load size plus grosse Scene
	GetResPath(tmpFilePath, ADELINE_MAX_PATH, SCENE_HQR_NAME);
	Load_HQR( tmpFilePath, &PtrSceneMem, 0 ) ;

	PtrSceneMem += RECOVER_AREA ;

	GetResPath(tmpFilePath, ADELINE_MAX_PATH, RESS_HQR_NAME);
	BufferFile3DMem = HQF_ResSize( tmpFilePath, RESS_FILE3D ) + RECOVER_AREA ;
	TabPartFlowMem  = HQF_ResSize( tmpFilePath, RESS_FLOW )   + RECOVER_AREA ;
	BufferPofMem    = HQF_ResSize( tmpFilePath, RESS_POF )    + RECOVER_AREA ;
	BufferImpactMem = HQF_ResSize( tmpFilePath, RESS_IMPACT ) + RECOVER_AREA ;
}

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
void	AdjustHQRMem( void )
{
	uint32_t	memory  ;
	uint32_t	islemem ;
	struct SizeInfo	sizeinfo ;
	char tmpFilePath[ADELINE_MAX_PATH];

	memory = AvailableMem() ;

	SpriteMem  = (memory/32) 	;
	Anim3DSMem = (memory/16)	;
	SampleMem  = (memory/16)+(memory/32)	; // *4
	AnimMem    = (memory/16)	;
	BodyMem    = (memory/16) 	;
	ObjFixMem  = (memory/32) 	;
	IsleObjMem = (memory/16)+(memory/32) 	;

	// a repartir dans les hqr exterieurs
	islemem    = (memory/16)*2/*+(memory/32)*/	;

	GetResPath(tmpFilePath, ADELINE_MAX_PATH, RESS_HQR_NAME);
	Load_HQR( tmpFilePath, &sizeinfo, RESS_EXT_SIZE_INFO ) ;

	CubeInfosMem    = (islemem/5)/10 ;
	ListDecorsMem   = islemem/10 ;
	MapPGroundMem   = 2*islemem/5 ;	// lui en donner un peu plus
	ListTexDefMem   = ((islemem/5)/10)*9 ;
	MapSommetYMem   = islemem/5 ;
	MapIntensityMem = islemem/10 ;

	if( SpriteMem < MIN_SPRITES_MEM )	SpriteMem = MIN_SPRITES_MEM ;
	if( Anim3DSMem< MIN_ANIM_3DS_MEM )	Anim3DSMem= MIN_ANIM_3DS_MEM ;
	if( SampleMem < MIN_SAMPLES_MEM ) 	SampleMem = MIN_SAMPLES_MEM ;
	if( AnimMem   < MIN_ANIMS_MEM )		AnimMem   = MIN_ANIMS_MEM ;
	if( BodyMem   < MIN_BODYS_MEM )	 	BodyMem   = MIN_BODYS_MEM ;
	if( ObjFixMem < MIN_OBJFIX_MEM ) 	ObjFixMem = MIN_OBJFIX_MEM ;
	if( IsleObjMem< sizeinfo.MaxSizeBodyDecors ) 	IsleObjMem= sizeinfo.MaxSizeBodyDecors ;
	if( CubeInfosMem< MIN_CUBE_INFOS_MEM ) 	CubeInfosMem= MIN_CUBE_INFOS_MEM ;
	if( ListDecorsMem< sizeinfo.MaxSizeListDecors ) 	ListDecorsMem= sizeinfo.MaxSizeListDecors ;
	if( MapPGroundMem< MIN_MAP_PGROUND_MEM ) 	MapPGroundMem= MIN_MAP_PGROUND_MEM ;
	if( ListTexDefMem< sizeinfo.MaxSizeTexDef ) 	ListTexDefMem= sizeinfo.MaxSizeTexDef ;
	if( MapSommetYMem< MIN_MAP_SOMMETY_MEM ) 	MapSommetYMem= MIN_MAP_SOMMETY_MEM ;
	if( MapIntensityMem< MIN_MAP_INTENSITY_MEM ) 	MapIntensityMem= MIN_MAP_INTENSITY_MEM ;

	// mettre les max
	if( SpriteMem > MAX_SPRITES_MEM )	SpriteMem = MAX_SPRITES_MEM ;
	if( Anim3DSMem> MAX_ANIM_3DS_MEM )	Anim3DSMem= MAX_ANIM_3DS_MEM ;
	if( SampleMem > MAX_SAMPLES_MEM ) 	SampleMem = MAX_SAMPLES_MEM ;
	if( AnimMem   > MAX_ANIMS_MEM )		AnimMem   = MAX_ANIMS_MEM ;
	if( BodyMem   > MAX_BODYS_MEM )	 	BodyMem   = MAX_BODYS_MEM ;
	if( ObjFixMem > MAX_OBJFIX_MEM ) 	ObjFixMem = MAX_OBJFIX_MEM ;
	if( IsleObjMem> MAX_ISLE_OBJ_MEM ) 	IsleObjMem= MAX_ISLE_OBJ_MEM ;
	if( CubeInfosMem> MAX_CUBE_INFOS_MEM ) 	CubeInfosMem= MAX_CUBE_INFOS_MEM ;
	if( ListDecorsMem> MAX_LIST_DECORS_MEM ) 	ListDecorsMem= MAX_LIST_DECORS_MEM ;
	if( MapPGroundMem> MAX_MAP_PGROUND_MEM ) 	MapPGroundMem= MAX_MAP_PGROUND_MEM ;
	if( ListTexDefMem> MAX_LIST_TEXDEF_MEM ) 	ListTexDefMem= MAX_LIST_TEXDEF_MEM ;
	if( MapSommetYMem> MAX_MAP_SOMMETY_MEM ) 	MapSommetYMem= MAX_MAP_SOMMETY_MEM ;
	if( MapIntensityMem> MAX_MAP_INTENSITY_MEM ) 	MapIntensityMem= MAX_MAP_INTENSITY_MEM ;
}

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
void   InitMainBuffer( void )
{
	T_MEM	*ptrm = ListMem ;
	uint8_t	*ptr ;
	int32_t	t ;

	AdjustLba2Mem() ;

	// Calcule mémoire nécessaire pour tous les buffers

	SizeOfMemAllocated = 0 ;

	for( t=0; t<NB_MEM_ELTS; t++, ptrm++ )
	{
		ptrm->Size = (ptrm->Size+15)&(~15) ;// aligne à 16

		SizeOfMemAllocated += ptrm->Size ;
	}

	// Alloue gros buffer

	MainBuffer = (uint8_t*)Malloc( SizeOfMemAllocated ) ;
	if( !MainBuffer )	TheEnd( NOT_ENOUGH_MEM, "MainBuffer" ) ;

	// Initialise tous les pointeurs

	ptrm = ListMem ;
	ptr  = MainBuffer ;

	for( t=0; t<NB_MEM_ELTS; t++, ptrm++ )
	{
		*ptrm->AdrPtr = ptr ;
		ptr += ptrm->Size ;
	}

	// Fixe Pointeurs partageant les même buffer
	BufCube = (uint8_t*)*ListMem[MEM_PTR_ZBUFFER].AdrPtr ;
	BufferBrick = BufCube+(SIZE_CUBE_X*SIZE_CUBE_Y*SIZE_CUBE_Z*2L) ;
}

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
void	InitMemory( void )
{
	// Alloue Memoire DOS si possible
	SkySeaTexture = (uint8_t*)SmartMalloc( 256*256L+RECOVER_AREA ) ;
	if( !SkySeaTexture )	TheEnd( NOT_ENOUGH_MEM, "SkySeaTexture" ) ;

	ObjTexture = (uint8_t*)SmartMalloc( 256*256+RECOVER_AREA ) ;
	if( !ObjTexture )	TheEnd( NOT_ENOUGH_MEM, "ObjTexture" ) ;

	GroundTexture = (uint8_t*)SmartMalloc( 256*256+RECOVER_AREA ) ;
	if( !GroundTexture )	TheEnd( NOT_ENOUGH_MEM, "GroundTexture" ) ;

	PtrScene = (uint8_t*)SmartMalloc( PtrSceneMem ) ;
	if( !PtrScene )	TheEnd( NOT_ENOUGH_MEM, "PtrScene" ) ;

	TabPartFlow = (T_FLOW*)SmartMalloc( TabPartFlowMem ) ;
	if( !TabPartFlow )	TheEnd( NOT_ENOUGH_MEM, "TabPartFlow" ) ;

	BufferPof = (uint8_t*)SmartMalloc( BufferPofMem ) ;
	if( !BufferPof )	TheEnd( NOT_ENOUGH_MEM, "BufferPof" ) ;

	BufferImpact = (uint8_t*)SmartMalloc( BufferImpactMem ) ;
	if( !BufferImpact )	TheEnd( NOT_ENOUGH_MEM, "BufferImpact" ) ;

	BufferFile3D = (uint8_t*)SmartMalloc( BufferFile3DMem ) ;
	if( !BufferFile3D )	TheEnd( NOT_ENOUGH_MEM, "BufferFile3D" ) ;

	BufferValidePos = (uint8_t*)SmartMalloc( SIZE_BUFFER_VALIDE_POS ) ;
	if( !BufferValidePos )	TheEnd( NOT_ENOUGH_MEM, "BufferValidePos" ) ;

	IsleMapIndex = (uint8_t*)SmartMalloc( 256 ) ;
	if( !IsleMapIndex )	TheEnd( NOT_ENOUGH_MEM, "IsleMapIndex" ) ;

	AdjustHQRMem() ;
}
