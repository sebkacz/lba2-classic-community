#ifndef	OBJECT_H
#define	OBJECT_H

#define	GivePtrObjFix(index)	HQR_Get( HQR_ObjFix, index )
#define	GivePtrSample(index)	HQR_Get( HQR_Samples, index )

extern Func_TransNumPtr GivePtrAnim ;
extern Func_TransNumPtr GivePtrBody ;

/*--------------------------------------------------------------------------*/
extern void InitSysText( void ) ;
/*--------------------------------------------------------------------------*/
extern void InitObject(uint8_t numobj);
/*--------------------------------------------------------------------------*/
extern void StartInitObj(uint8_t numobj);
/*--------------------------------------------------------------------------*/
extern void StartInitAllObjs(void);
/*--------------------------------------------------------------------------*/
extern void RestartMecaPingouin(void);
/*--------------------------------------------------------------------------*/
extern void LoadFicPerso(void);
/*--------------------------------------------------------------------------*/
extern void InitPerso(void);
/*--------------------------------------------------------------------------*/
extern void UseOneClover( void ) ;
/*--------------------------------------------------------------------------*/
extern void SetComportement(uint8_t comportement);
/*--------------------------------------------------------------------------*/
extern void RestartPerso(void);
/*--------------------------------------------------------------------------*/
extern void ClearVarsCube(void);
/*--------------------------------------------------------------------------*/
extern void ClearFoudre( void ) ;
/*--------------------------------------------------------------------------*/
extern void ClearScene(void);
/*--------------------------------------------------------------------------*/
extern void InitLoadedGame(void);
/*--------------------------------------------------------------------------*/
extern void LoadFile3dObjects(void);
/*--------------------------------------------------------------------------*/
extern void ChangeCube(void);
/*--------------------------------------------------------------------------*/
extern void HitObj(uint8_t numhitter,uint8_t num,int32_t hitforce,int32_t beta);
/*--------------------------------------------------------------------------*/
extern void FoudroieObj( uint8_t numhitter, uint8_t num, int32_t armure ) ;
/*--------------------------------------------------------------------------*/
extern int32_t  CheckZvOnZv(uint8_t numobj,uint8_t numobjt);
/*--------------------------------------------------------------------------*/
extern int32_t  CheckObjCol(uint8_t numobj);
/*--------------------------------------------------------------------------*/
extern uint8_t   IsObjCol( uint8_t numobj ) ;
/*--------------------------------------------------------------------------*/
extern void CheckCarrier(uint8_t numobj);
/*--------------------------------------------------------------------------*/
extern int32_t  CheckValidObjPos(uint8_t numobj,uint8_t owner);
/*--------------------------------------------------------------------------*/
extern void PosObjetAroundAnother( uint8_t numsrc, uint8_t numtopos ) ;
/*--------------------------------------------------------------------------*/
extern	uint8_t  ChoiceHeroBody( uint8_t genbody ) ;
/*--------------------------------------------------------------------------*/
extern void InitBody(uint8_t gennewbody,uint8_t numobj);
/*--------------------------------------------------------------------------*/
extern void InitSprite(int32_t newsprite,T_OBJET *numobj);
/*--------------------------------------------------------------------------*/
extern void SetAnim(uint8_t numobj,uint16_t anim);
/*--------------------------------------------------------------------------*/
extern int32_t  InitAnim(uint16_t gennewanim,uint8_t flag,uint8_t numobj);
/*--------------------------------------------------------------------------*/
extern Func_ReajustPos ReajustPos ;
/*--------------------------------------------------------------------------*/
extern void ReceptionObj(void);
/*--------------------------------------------------------------------------*/
extern void DoCornerReajust(int32_t nx,int32_t ny,int32_t nz);
/*--------------------------------------------------------------------------*/
extern int32_t  DoCornerReajustTwinsen(int32_t nx,int32_t ny,int32_t nz);
/*--------------------------------------------------------------------------*/
extern int32_t  CheckCarryBy(uint8_t numobj);
/*--------------------------------------------------------------------------*/
extern int32_t GereCodesJeu( uint8_t numobj ) ;
/*--------------------------------------------------------------------------*/
extern void GereObjAnim(uint8_t numobj);
/*--------------------------------------------------------------------------*/
extern Func_DoAnim DoAnim ;
/*--------------------------------------------------------------------------*/
extern void ManualRealAngle(T_OBJET *ptrobj);
/*--------------------------------------------------------------------------*/
extern void ClearRealAngle(T_OBJET *ptrobj);
/*--------------------------------------------------------------------------*/
extern void ThrowMecaPingouin( void ) ;
/*--------------------------------------------------------------------------*/
extern void ExplodeMecaPingouin( void );
/*--------------------------------------------------------------------------*/
extern void DoDir(uint8_t numobj);
/*--------------------------------------------------------------------------*/
extern void ResetCinemaMode( void ) ;
/*--------------------------------------------------------------------------*/
extern void FixeCinemaMode( int32_t flagflip ) ;
/*--------------------------------------------------------------------------*/
extern void RestoreCinemaMode( void ) ;
/*--------------------------------------------------------------------------*/
extern void InsertChainBeforeEntry(int32_t list0,T_SORT *pt0,int32_t list1,T_SORT *pt1);
/*--------------------------------------------------------------------------*/
extern void InsertChainAfterEntry(int32_t list0,T_SORT *pt1);
/*--------------------------------------------------------------------------*/
extern Func_TreeInsert TreeInsert2 ;
/*--------------------------------------------------------------------------*/
extern int32_t AffOneObject(T_SORT *pt);
/*--------------------------------------------------------------------------*/
extern void AffScene(int32_t flagflip);
/*--------------------------------------------------------------------------*/
extern void SetZoneCamera(T_ZONE *ptrz);
/*--------------------------------------------------------------------------*/
extern void CheckZoneSce(T_OBJET *ptrobj,uint8_t numobj);
/*--------------------------------------------------------------------------*/
extern void CheckBuggyZoneGiver( T_OBJET *ptrobj ) ;
/*--------------------------------------------------------------------------*/

#endif	// OBJECT_H
