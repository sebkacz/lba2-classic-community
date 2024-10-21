#ifndef	DECORS_H
#define	DECORS_H

/*--------------------------------------------------------------------------*/
extern void FixeObjetsDecorsInvisibles( void ) ;
/*--------------------------------------------------------------------------*/
extern int sub_qsort_decors(const void *a,const void *b);
/*--------------------------------------------------------------------------*/
extern int sub_qsort_decors_zbuf(const void *a,const void *b);
/*--------------------------------------------------------------------------*/
extern void AffichageObjetDecorsZV(void) ;
/*--------------------------------------------------------------------------*/
extern void AffichageObjetDecorsZBuf(void);
/*--------------------------------------------------------------------------*/
extern int32_t TestZVDecors(int32_t xw,int32_t yw,int32_t zw,T_DECORS *objet);

#endif	// DECORS_H
