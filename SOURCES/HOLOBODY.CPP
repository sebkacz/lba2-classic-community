
#include	"C_EXTERN.H"


//****************************************************************************
//****************************************************************************
//────────────────────────────────────────────────────────────────────────────
//────────────────────────────────────────────────────────────────────────────
//	echelle 256 = 1
void	ScaleRotBody3D( uint8_t *ptbody, int32_t scale, int32_t flagrot )
{
	int16_t	*pt	;
	uint32_t	i	;
	uint32_t	nb, off	;
	int32_t x0, y0, z0	;
	int32_t x1, y1, z1	;
	T_BODY_HEADER	*pth ;

//----- La ZV
	pth = (T_BODY_HEADER *)ptbody	;

	x0 = (pth->XMin * scale)/256;
	x1 = (pth->XMax * scale)/256;
	y0 = (pth->YMin * scale)/256;
	y1 = (pth->YMax * scale)/256;
	z0 = (pth->ZMin * scale)/256;
	z1 = (pth->ZMax * scale)/256;

	if ( flagrot )
	{
		Rotate( z0, y0, 1024 )	;
		y0 = Z0			;
		z0 = X0			;
		Rotate( z1, y1, 1024 )	;
		y1 = Z0			;
		z1 = X0			;
	}

	pth->XMin = (int16_t)x0	;
	pth->XMax = (int16_t)y0	;
	pth->YMin = (int16_t)z0	;
	pth->YMax = (int16_t)x1	;
	pth->ZMin = (int16_t)y1	;
	pth->ZMax = (int16_t)z1	;

//----- Les Points 3D
	nb  = pth->NbPoints	;//	NbObjPoint
	off = pth->OffPoints	;//	Offset points
	pt = (int16_t*)(ptbody+off);//	Jump to points

	for ( i = 0 ; i < nb ; i++, pt += 4 )
	{
		x0 = (pt[0] * scale)/256	;//	X
		y0 = (pt[1] * scale)/256	;//	Y
		z0 = (pt[2] * scale)/256	;//	Z
		if ( flagrot )
		{
			Rotate( z0, y0, 1024 )	;
			y0 = Z0			;
			z0 = X0			;
		}
		pt[0] = (int16_t)x0	;
		pt[1] = (int16_t)y0	;
		pt[2] = (int16_t)z0	;
	}

	if ( flagrot )
	{

//----- Les Normals aux points et aux faces
		nb  = pth->NbNormales	;//	Nb Normals aux points
		off = pth->OffNormales	;//	Offset Normals
		nb += pth->NbNormFaces	;//	Add Normals aux faces
		pt = (int16_t*)(ptbody+off)	;

		for ( i = 0 ; i < nb ; i++, pt += 4 )
		{
			Rotate( pt[2], pt[1], 1024 )	;
			pt[1] = (int16_t)Z0		;
			pt[2] = (int16_t)X0		;
		}
	}

//----- Les Rayons des Spheres
	nb  = pth->NbSpheres	;//	NbSpheres
	off = pth->OffSpheres	;//	Offset Spheres
	pt = (int16_t*)(ptbody+off)	;

	pt += 3		;//	Jump type & coul & p1
	for ( i = 0 ; i < nb ; i++ , pt += 4 )
	{
		*pt = (int16_t)((*pt * scale)/256)	;//	Rayon
	}
}

//────────────────────────────────────────────────────────────────────────────
uint32_t	GetSizeBody3D( uint8_t *ptbody )
{
	T_BODY_HEADER *pth ;
	uint32_t	nb, off	;

	pth = (T_BODY_HEADER *)ptbody	;

	nb  = pth->NbTextures	;//	Nb Texture
	off = pth->OffTextures	;//	Offset Texture

	off += nb*4	;//	Add (orgMap+RepMask)*NbTexture

	return(off)	;

}
//────────────────────────────────────────────────────────────────────────────
//	echelle 256 = 1
void	ScaleRotAnim3D( uint8_t *ptanim, int32_t scale, int32_t flagrot )
{
	int16_t	*pt	;
	uint16_t	nbframe	;
	uint16_t	nbgroup	;
	uint16_t	grp, frm;
	int32_t	x, y, z	;

	pt = (int16_t*)ptanim	;
	nbframe = *(uint16_t*)pt++	;
	nbgroup = *(uint16_t*)pt	;
	pt += 3			;

	for ( frm = 0 ; frm < nbframe ; frm++ )
	{
		pt++			;//	Jump Time
		x = (pt[0] * scale)/256	;//	StepX
		y = (pt[1] * scale)/256	;//	StepY
		z = (pt[2] * scale)/256	;//	StepZ
		if ( flagrot )
		{
			Rotate( z, y, 1024 )	;
			y = Z0		;
			z = X0		;
		}
		pt[0] = (int16_t)x		;
		pt[1] = (int16_t)y		;
		pt[2] = (int16_t)z		;

		pt += 7			;//	Jump MasterRot, al, be & ga

		for ( grp = 1 ; grp < nbgroup ; grp++, pt += 4 )
		{
			if ( *pt == 0 )	continue;// Only Transition
			x = (pt[1] * scale)/256	;//	StepX
			y = (pt[2] * scale)/256	;//	StepY
			z = (pt[3] * scale)/256	;//	StepZ
			if ( flagrot )
			{
				Rotate( z, y, 1024 )	;
				y = Z0		;
				z = X0		;
			}
			pt[1] = (int16_t)x		;
			pt[2] = (int16_t)y		;
			pt[3] = (int16_t)z		;
		}
	}
}
//────────────────────────────────────────────────────────────────────────────
//	echelle 256 = 1
uint32_t	GetSizeAnim3D( uint8_t *ptanim )
{
	int16_t	*pt	;
	uint16_t	nbframe	;
	uint16_t	nbgroup	;

	pt = (int16_t*)ptanim	;

	nbframe = *(uint16_t*)pt++	;
	nbgroup = *(uint16_t*)pt	;

	pt += (3+(nbframe*(nbgroup+1)*4))	;

	return((uint32_t)pt-(uint32_t)ptanim)	;
}
//────────────────────────────────────────────────────────────────────────────
