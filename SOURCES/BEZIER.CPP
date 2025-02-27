/*══════════════════════════════════════════════════════════════════════════*

		██████┐ █┐   █┐ █████┐  ██████┐ ██████┐ ██████┐
		██┌─██│ ██┐ ██│ ██┌██│  ██┌─██│ ██┌───┘ ██┌───┘
		██│ ██│ ██████│ ██████┐ ██████│ █████┐  ██████┐
		██│ ██│ ██┌─██│ ██┌─██│ ██┌██┌┘ ██┌──┘  └───██│
		██████│ ██│ ██│ ██████│ ██│└██┐ ██████┐ ██████│
		└─────┘ └─┘ └─┘ └─────┘ └─┘ └─┘ └─────┘ └─────┘

			   (merci Time Commando !!!)

 *══════════════════════════════════════════════════════════════════════════*/

#include	"C_EXTERN.H"

/*──────────────────────────────────────────────────────────────────────────*/
//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
int32_t		TabCoorPoint[480][4];
int32_t		TabNbPoint[480];
int32_t		MinYTabPoint,MaxYTabPoint;

int32_t		XS0,YS0,XS1,YS1,XS2,YS2,XS3,YS3 ;

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
void CalculeLigneOmbre( int32_t x1, int32_t y1, int32_t x2, int32_t y2 )
{
	int32_t temp;
	int32_t ix;
	int32_t x,y;
	int32_t hauteur;

	if( y1 > y2 )
	{
		temp=x1;
		x1=x2;
		x2=temp;

		temp=y1;
		y1=y2;
		y2=temp;
	}

	if( (y2>=ClipYMin) AND (y1<=ClipYMax) )
	{
		hauteur=y2-y1+1;

		ix=WTOF(x2-x1)/hauteur;

		x=WTOF(x1);

		if (y1<ClipYMin)
		{
			x+=ix*(ClipYMin-y1-1);
			y1=ClipYMin-1;
		}

		if (y2>ClipYMax) y2=ClipYMax;

		if (y1<MinYTabPoint) MinYTabPoint=y1;

		if (y2>MaxYTabPoint) MaxYTabPoint=y2;


		x+=ix;
		y1++;

		for( y=y1; y<=y2; y++ )
		{
			TabCoorPoint[y][TabNbPoint[y]++]=FTOW(x);
			//Plot(FTOW(x),y,15);
			x+=ix;
		}

	}
}

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
void	DrawOmbre(int32_t x0,int32_t y0,int32_t x1,int32_t y1,int32_t x2,int32_t y2,int32_t x3,int32_t y3)
{
	int32_t	start_x,start_y;

	int32_t	qx[5];
	int32_t	qy[5];

	int32_t	x[4];
	int32_t	y[4];

	int32_t	ax;
	int32_t	ay;

	int32_t	b1x,b2x;
	int32_t	b1y,b2y;

	int32_t	c1x,c2x,c3x,c4x;
	int32_t	c1y,c2y,c3y,c4y;

	int32_t	firstx,inter1x,midx,inter2x,lastx;
	int32_t	firsty,inter1y,midy,inter2y,lasty;


	int32_t	n,i;

	x[0] = WTOF(x0);
	y[0] = WTOF(y0);
	x[1] = WTOF(x1);
	y[1] = WTOF(y1);
	x[2] = WTOF(x2);
	y[2] = WTOF(y2);
	x[3] = WTOF(x3);
	y[3] = WTOF(y3);


	start_x = (x0+x1) >> 1;
	start_y = (y0+y1) >> 1;

	firstx = ( x[0] + x[1]) >> 1;			  // 0
	firsty = ( y[0] + y[1]) >> 1;

	for( n=0; n<4; n++)
	{

		//
		//
		// Génère les valeurs initiales (Niveau 0)
		//
		//

		ax =   x[(n+1)&3];
		lastx = ( ax + x[(n+2)&3]) >> 1;

		ay =   y[(n+1)&3];
		lasty = ( ay + y[(n+2)&3]) >> 1;




		//
		//
		// Calcule les valeurs intermédiaires (Niveau 1)
		//
		//

		b1x   = ( firstx + ax) >> 1;
		b2x   = ( lastx  + ax) >> 1;
		midx  = ( b1x	 + b2x) >> 1;

		b1y   = ( firsty + ay) >> 1;
		b2y   = ( lasty  + ay) >> 1;
		midy  = ( b1y	 + b2y) >> 1;




		//
		//
		// Calcule les valeurs intermédiaires (Niveau 2)
		//
		//

		c1x	= ( b1x  + firstx ) >> 1;
		c2x	= ( b1x  + midx   ) >> 1;
		inter1x = ( c1x  + c2x) >> 1;
		c3x	= ( b2x  + midx   ) >> 1;
		c4x	= ( b2x  + lastx  ) >> 1;
		inter2x = ( c3x  + c4x) >> 1;

		c1y	= ( b1y  + firsty ) >> 1;
		c2y	= ( b1y  + midy   ) >> 1;
		inter1y = ( c1y  + c2y) >> 1;
		c3y	= ( b2y  + midy   ) >> 1;
		c4y	= ( b2y  + lasty  ) >> 1;
		inter2y = ( c3y  + c4y) >> 1;



		//
		// Stocke toutes les valeurs dans le tableau final
		// Puis lance le traçage virtuel
		//

		qx[0] = firstx;
		qx[1] = inter1x;
		qx[2] = midx;
		qx[3] = inter2x;
		qx[4] = lastx;

		qy[0] = firsty;
		qy[1] = inter1y;
		qy[2] = midy;
		qy[3] = inter2y;
		qy[4] = lasty;


		for( i=0; i<4; i++ )
		{
			CalculeLigneOmbre(start_x,start_y,FTOW(qx[i+1]),FTOW(qy[i+1]));

			start_x=FTOW(qx[i+1]);
			start_y=FTOW(qy[i+1]);
		}
		firstx = lastx;
		firsty = lasty;
	}
}

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
void	DrawLineShade(	int32_t x0, int32_t z0, int32_t x1, int32_t z1, int32_t x2, int32_t z2, int32_t x3, int32_t z3 )
{
	int32_t	y,j,k;
	int32_t	temp;

	MinYTabPoint=ClipYMax;
	MaxYTabPoint=ClipYMin;

	DrawOmbre(x0,z0,x1,z1,x2,z2,x3,z3);

	for ( y = MinYTabPoint; y <= MaxYTabPoint; y++ )
	{
		switch( TabNbPoint[y] )
		{
		case 2: //----------------------------------------------------

			if( TabCoorPoint[y][0] < TabCoorPoint[y][1] )
				ShadeBoxBlk( TabCoorPoint[y][0], y, TabCoorPoint[y][1], y, ShadowLevel );
			else	ShadeBoxBlk( TabCoorPoint[y][1], y, TabCoorPoint[y][0], y, ShadowLevel );
			break;

		case 4: //----------------------------------------------------
			for( j=0; j<=2; j++ )
			{
				for( k=1; k<=3; k++ )
				{
					if( TabCoorPoint[y][k] < TabCoorPoint[y][j] )
					{
						temp=TabCoorPoint[y][j];
						TabCoorPoint[y][j]=TabCoorPoint[y][k];
						TabCoorPoint[y][k]=temp;
					}
				}
			}

			if( TabCoorPoint[y][0] < TabCoorPoint[y][1] )
				ShadeBoxBlk( TabCoorPoint[y][0], y, TabCoorPoint[y][1], y, ShadowLevel );
			else	ShadeBoxBlk( TabCoorPoint[y][1], y, TabCoorPoint[y][0], y, ShadowLevel );

			if( TabCoorPoint[y][2] < TabCoorPoint[y][3] )
				ShadeBoxBlk( TabCoorPoint[y][2], y, TabCoorPoint[y][3], y, ShadowLevel );
			else	ShadeBoxBlk( TabCoorPoint[y][3], y, TabCoorPoint[y][2], y, ShadowLevel );
			break;
		}

		TabNbPoint[y] = 0 ;	// reinit for next Shadow
	}
}

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
// Version ZVs absolues précalculées
int32_t	TestZVDecorsXZFull( int32_t xw, int32_t zw, int32_t y0, int32_t y1, T_DECORS *objet )
{
	if( objet->Body & DEC_INVISIBLE )	return FALSE ;

	if( objet->XMin > xw )	return	FALSE ;
	if( objet->XMax < xw )	return	FALSE ;

	if( objet->ZMin > zw )	return	FALSE ;
	if( objet->ZMax < zw )	return	FALSE ;

	if( objet->YMin > y1 )	return	FALSE ;
	if( objet->YMax < y0 )	return	FALSE ;

	return TRUE ;
}

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
int32_t	TestZVObjectsXZFull( int32_t xw, int32_t zw, int32_t y0, int32_t y1, T_OBJET *objet )
{
	int32_t	ymin,ymax ;

	ymin = objet->Obj.Y + objet->YMin ;
	ymax = objet->Obj.Y + objet->YMax ;

	if( ymin<y0 OR ymin>/*=*/y1 OR ymax>y1  )	return	FALSE ;
	if( ymax < y0 )	return	FALSE ;

	if( objet->Obj.Body.Num == -1
	OR  objet->Flags&INVISIBLE )	return FALSE ;

	if( (objet->Obj.X+objet->XMin) > xw )	return	FALSE ;
	if( (objet->Obj.X+objet->XMax) < xw )	return	FALSE ;

	if( (objet->Obj.Z+objet->ZMin) > zw )	return	FALSE ;
	if( (objet->Obj.Z+objet->ZMax) < zw )	return	FALSE ;

	return TRUE ;
}

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
int32_t	ShadowTestDecors = 0 ;

int32_t	AdjustShadowDecors( int32_t xw, int32_t zw, int32_t y0, int32_t y1 )
{
	int32_t	i ;
	T_DECORS       	*ptrd ;
	T_LIST_TRI	*ptrtri = ListTriExt ;

	// decors
	for( i=0; i<NbObjScreen; i++, ptrtri++ )
	{
		ptrd = ptrtri->PtrDec ;

		if( ptrd->Body&DEC_DRAWN OR FirstLoop )
		{
			if( TestZVDecorsXZFull( xw, zw, y0, y1, ptrd ) )
			{
				y0 = ptrd->YMax ;
			}
		}
	}

	return y0 ;
}

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
int32_t	ShadowTestObject = 0 ;

int32_t	AdjustShadowObjects( int32_t xw, int32_t zw, int32_t y0, int32_t y1 )
{
	int32_t	i ;
	T_OBJET	*ptrobj = ListObjet ;

	ShadowTestObject = -1 ;

	// decors
	for ( i=0; i<NbObjets; i++, ptrobj++ )
	{
		if( ptrobj->WorkFlags&WAS_DRAWN OR FirstLoop )
		{
		if( TestZVObjectsXZFull( xw, zw, y0, y1, ptrobj ) )
		{
			y0 = ptrobj->Obj.Y + ptrobj->YMax ;
			ShadowTestObject = i ;
		}
		}
	}

	return y0 ;
}

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
int32_t	ProjectShadowExt( T_SORT *ptrs, int32_t beta )
{
	int32_t	xmin, zmin, xmax, zmax, xw, yw, zw ;
	int32_t	cy		;
	int32_t	altitude_ref	;
	int32_t	dx2, dz2 	;

	ClearScreenMinMax();

	xw = ptrs->Xw ;
	yw = ptrs->Yw ;
	zw = ptrs->Zw ;

	xmin = ptrs->XMin - xw ;
	zmin = ptrs->ZMin - zw ;
	xmax = ptrs->XMax - xw ;
	zmax = ptrs->ZMax - zw ;

	dx2 = (xmin+xmax)/2 ;
	dz2 = (zmin+zmax)/2 ;

	// inclure ici la gestion des objets du decors
	altitude_ref = yw ;
//	altitude_ref = CalculAltitudeObjet( xw, zw );
	altitude_ref = AdjustShadowDecors( xw, zw, altitude_ref, ptrs->YMax/*yw*/ ) ;
	altitude_ref = AdjustShadowObjects( xw, zw, altitude_ref, ptrs->YMax/*yw*/ ) ;

	ptrs->Yw = altitude_ref ;	// Pour les recouvrements
	ptrs->YMax = altitude_ref + (ptrs->YMax-yw) ;

	Rotate( dx2, zmin, beta );

	X0 += xw ;
	Z0 += zw ;

	cy = CalculAltitudeObjet( X0, Z0, -1 ) ;
	cy = AdjustShadowDecors( X0, Z0, cy, altitude_ref ) ;
	cy = AdjustShadowObjects( X0, Z0, cy, altitude_ref ) ;

	if( cy < altitude_ref-ALTITUDE_MAX )	  cy = altitude_ref-ALTITUDE_MAX;
	else if( cy > altitude_ref+ALTITUDE_MAX ) cy = altitude_ref+ALTITUDE_MAX;

	LongWorldRotatePoint( X0, cy, Z0 ) ;
	if( !LongProjectPoint( X0,Y0,Z0 ) )	return FALSE ;
	XS0 = Xp ;
	YS0 = Yp ;
	AdjustScreenMinMax();

	Rotate( xmin, dz2, beta );

	X0 += xw ;
	Z0 += zw ;

	cy = CalculAltitudeObjet( X0, Z0, -1 ) ;
	cy = AdjustShadowDecors( X0, Z0, cy, altitude_ref ) ;
	cy = AdjustShadowObjects( X0, Z0, cy, altitude_ref ) ;

	if( cy < altitude_ref-ALTITUDE_MAX )	  cy = altitude_ref-ALTITUDE_MAX;
	else if( cy > altitude_ref+ALTITUDE_MAX ) cy = altitude_ref+ALTITUDE_MAX;

	LongWorldRotatePoint( X0, cy, Z0 ) ;
	if( !LongProjectPoint( X0,Y0,Z0 ) )	return FALSE ;
	XS1 = Xp ;
	YS1 = Yp ;
	AdjustScreenMinMax();

	Rotate( dx2, zmax, beta );

	X0 += xw ;
	Z0 += zw ;

	cy = CalculAltitudeObjet( X0, Z0, -1 ) ;
	cy = AdjustShadowDecors( X0, Z0, cy, altitude_ref ) ;
	cy = AdjustShadowObjects( X0, Z0, cy, altitude_ref ) ;

	if( cy < altitude_ref-ALTITUDE_MAX )	  cy = altitude_ref-ALTITUDE_MAX;
	else if( cy > altitude_ref+ALTITUDE_MAX ) cy = altitude_ref+ALTITUDE_MAX;

	LongWorldRotatePoint( X0, cy, Z0 ) ;
	if( !LongProjectPoint( X0,Y0,Z0 ) )	return FALSE ;
	XS2 = Xp ;
	YS2 = Yp ;
	AdjustScreenMinMax();

	Rotate( xmax, dz2, beta );

	X0 += xw ;
	Z0 += zw ;

	cy = CalculAltitudeObjet( X0, Z0, -1 ) ;
	cy = AdjustShadowDecors( X0, Z0, cy, altitude_ref ) ;
	cy = AdjustShadowObjects( X0, Z0, cy, altitude_ref ) ;

	if( cy < altitude_ref-ALTITUDE_MAX )	  cy = altitude_ref-ALTITUDE_MAX;
	else if( cy > altitude_ref+ALTITUDE_MAX ) cy = altitude_ref+ALTITUDE_MAX;

	LongWorldRotatePoint( X0, cy, Z0 ) ;
	if( !LongProjectPoint( X0,Y0,Z0 ) )	return FALSE ;
	XS3 = Xp ;
	YS3 = Yp ;
	AdjustScreenMinMax();

//	UnsetClip() ;
	SetClip( ScreenXMin, ScreenYMin, ScreenXMax, ScreenYMax ) ;

	return TRUE ;
}

//▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
void	DrawShadow()
{
	DrawLineShade( XS0, YS0, XS1, YS1, XS2, YS2, XS3, YS3 ) ;

//	BoxMovingAdd( ClipXMin, ClipYMin, ClipXMax, ClipYMax ) ;

#ifdef	LBA_EDITOR
	if( FlagInfos&INFO_DRAW_ZV )
	{
		Line( XS0, YS0, XS1, YS1, BLUE ) ;
		Line( XS1, YS1, XS2, YS2, BLUE ) ;
		Line( XS2, YS2, XS3, YS3, BLUE ) ;
		Line( XS3, YS3, XS0, YS0, BLUE ) ;
	}
#endif
}
