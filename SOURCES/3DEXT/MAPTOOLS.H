#ifndef	MAPTOOLS_H
#define	MAPTOOLS_H

/*--------------------------------------------------------------------------*/
extern int32_t CalculAltitudeObjet(int32_t x,int32_t z,int32_t cj);

/*--------------------------------------------------------------------------*/
extern int32_t GiveTriangle(int32_t x,int32_t z);

/*--------------------------------------------------------------------------*/
extern int32_t GiveTerrainCol(int32_t x,int32_t z);

/*--------------------------------------------------------------------------*/
extern	uint8_t	GiveTerrainCodeJeu( int32_t x, int32_t y, int32_t z ) ;

/*--------------------------------------------------------------------------*/
extern int32_t	SearchCameraPos( int32_t x, int32_t y, int32_t z, int32_t objbeta, int32_t mode ) ;

/*--------------------------------------------------------------------------*/

#endif	// MAPTOOLS_H
