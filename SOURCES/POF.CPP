#include	"C_EXTERN.H"

//***************************************************************************
int32_t	PofDisplay3DExt( int32_t x, int32_t y, int32_t z, int32_t num_pof, int32_t scale, int32_t rotation )
{
	int32_t	coul, n;
	int32_t	x0, y0, scale3d ;
	int32_t	xpc, ypc ;
	int16_t	*ptr_point, *ptrw;
	uint8_t	p;
	uint8_t	*ptr_pof ;

//	ptr_pof = (uint8_t*)HQR_Get( HQR_Pof, num_pof ) ;

	ptr_pof = BufferPof + *(((uint32_t*)BufferPof)+num_pof) ;

	LongWorldRotatePoint( x, y, z ) ;
	x0 = Z0;

	if( !LongProjectPoint( X0, Y0+1000, Z0 ) )	return FALSE ;
	y0 = Yp;

	if( !LongProjectPoint( X0, Y0, Z0 ) )	return FALSE ;
	xpc = Xp*65536+32768;
	ypc = Yp*65536+32768;

	scale3d = ((Yp-y0)*65536+scale/2)/scale ;

	coul = *ptr_pof++; // couleur

	n = *ptr_pof++; // nb point

	ClearScreenMinMax() ;

	if( rotation != 0 )
	{
		ptrw = (int16_t*)ptr_pof;
		ptr_point = (int16_t*)Obj_ListRotatedPoints;

		for( p=0; p<n; p++ )
		{
			Rotate( ptrw[0], ptrw[1], rotation );

			Xp = (xpc+X0*scale3d)/65536 ;
			Yp = (ypc+Z0*scale3d)/65536 ;

			AdjustScreenMinMax() ;

			*ptr_point++ = (int16_t)Xp ;
			*ptr_point++ = (int16_t)Yp ;
			ptrw += 2;
		}

		ptr_pof = (uint8_t*)ptrw;
	}
	else
	{
		ptrw = (int16_t*)ptr_pof;
		ptr_point = (int16_t*)Obj_ListRotatedPoints;

		for( p=0; p<n; p++ )
		{
			Xp = (xpc+(*ptrw++)*scale3d)/65536 ;
			Yp = (ypc+(*ptrw++)*scale3d)/65536 ;

			AdjustScreenMinMax() ;

			*ptr_point++ = (int16_t)Xp ;
			*ptr_point++ = (int16_t)Yp ;
		}

		ptr_pof = (uint8_t*)ptrw;
	}

	n = *ptr_pof++; // nb line
	while( n>0 )
	{
		p = *ptr_pof++;

		ptr_point = (int16_t*)Obj_ListRotatedPoints+p*2 ;

		x0 = *ptr_point++ ;
		y0 = *ptr_point ;

		p = *ptr_pof++;

		ptr_point = (int16_t*)Obj_ListRotatedPoints+p*2 ;

		Xp = *ptr_point++ ;
		Yp = *ptr_point ;

		Line( x0, y0, Xp, Yp, coul );

		n--;
	}

	return(TRUE);
}
