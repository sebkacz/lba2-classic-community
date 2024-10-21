#include	"C_EXTERN.H"

//
// Uniquement en version Outil: interprétation des impacts
//
// ATTENTION: Utilise ScreenAux pour charger les impacts
//

#ifdef	COMPILATOR
#define	PATH_FLOW	"f:\\projet\\lba2\\datas\\flow\\"
extern	uint8_t	*BufferDef ;
#endif

#ifdef	LBA_EDITOR
uint32_t		NbImpacts = 0 ;
T_IMPACT	ListImpact[MAX_IMPACT] ;

// ATTENTION: Laisser imperativement les instructions FLOW et THROW avant les
// autres FLOW_xxx et THROW_xxx, sinon le principe ne marche plus à cause du
// strnicmp(). (Voir GetImpCommand()).

char	*ImpCommandList[NB_IMP_COMMAND] = {
		"END",				// 0
		";",				// 1
		"SAMPLE",			// 2
		"FLOW",				// 3
		"THROW",			// 4
		"THROW_POF",			// 5
		"THROW_OBJ",			// 6
		"SPRITE",			// 7
		"FLOW_SPRITE",			// 8
		"FLOW_OBJ",			// 9
		"FLOW_POF"   			// 10
		} ;
#else
//T_HQR_HEADER	*HQR_Impact ;
uint8_t	*BufferImpact ;
#endif

#ifdef	LBA_EDITOR
/*──────────────────────────────────────────────────────────────────────────*/
int8_t	GetImpCommand( void )
{
	char	*ptr ;
	char	c ;
	int8_t	i ;

	ptr = String ;

	do	/* saute cr/lf espace */
	{
		c = *(char *)PtrFiche++ ;
		if( c == 26 /*EOF*/ )
		{
			PtrFiche-- ;
			return -1 ;
		}
	}
	while( c <= 32 ) ;

	PtrCommand = PtrFiche-1 ;

	if( c == ';' )	return IMP_REM ;	// accelere et evite l'espace obligatoire

	do	/* lit commande */
	{
		*ptr++ = c ;
		c = *(char *)PtrFiche++ ;
	}
	while( c > 32 ) ;
	if( c==26 )	PtrFiche-- ;

	*ptr++ = 0 ;

	for( i=0; i<NB_IMP_COMMAND; i++ )
	{
		if( !strncasecmp(	ImpCommandList[i],
				String,
				strlen( String ) ) )
		{
			return i ;
		}
	}

	Beep() ;
	MessageF( TRUE, "ImpCommande inconnue: %s", String ) ;

	return (int8_t)IMP_NOP ;
}

/*──────────────────────────────────────────────────────────────────────────*/
int32_t	GetNumDef( char *pathdef, char *name )
{
	int32_t	n = 0 ;
	int32_t	len ;
	char	*ptr ;
	char	*com ;	// Pointeur sur commentaire éventuel

	strupr( name ) ;
	len = strlen( name ) ;

	InitDefFile( pathdef ) ;

	do
	{
		ptr = DefFileBufferReadString( Itoa(n) ) ;

		if( ptr )
		{
			// Vire commentaire éventuel
			com = (char *) strchr( ptr, ';' ) ;
			if( com )	*com = '\0' ;

			strupr( ptr ) ;

			if( !strncmp(ptr,name,len) )	return n ;

			n++ ;
		}
	}
	while( ptr ) ;

	MessageF( TRUE, "Erreur GetNumDef(): %s introuvable", name ) ;

	return -1 ;
}

/*──────────────────────────────────────────────────────────────────────────*/
int32_t	GetNumDefAddIfNot( char *pathdef, char *name, char *rem )
{
	char	ch[256] ;
	int32_t	n = 0 ;
	int32_t	len ;
	char	*ptr ;
	int32_t	found = FALSE ;

	strupr( name ) ;
	len = strlen( name ) ;

	InitDefFile( pathdef ) ;

	strupr( OrgPtrDef ) ;

	ptr = OrgPtrDef ;

	while( ptr AND ptr<EndPtrDef )
	{
		ptr = strstr( ptr, name ) ;

		if( ptr AND ptr[len]==' ' )	break ;
	}

	if( ptr )	found = TRUE ;
	else		ptr = EndPtrDef ;	// on cherche le dernier numero

	// cherche numero

	while( ptr>=OrgPtrDef AND *ptr!=':' )	ptr-- ;

	if( ptr<OrgPtrDef )	n = 0 ;
	else
	{
		ptr-- ;
		while( ptr>=OrgPtrDef AND (*ptr>='0' AND *ptr<='9') ) ptr-- ;
		if( ptr<OrgPtrDef )	n = 0 ;
		else
		{
			ptr++ ;
			n = atoi(ptr) ;
		}
	}

	if( found )
	{
		return n ;
	}

	n++ ;

	// rajoute en fin de liste
	strcpy( ch, name ) ;
	strcat( ch, " ; " ) ;
	strcat( ch, rem  ) ;	// ajoute une remarque éventuelle

	DefFileBufferWriteString( Itoa(n), ch ) ;

#ifndef	COMPILATOR
	SampleDefModified = TRUE ;
#endif

	return n ;
}

/*──────────────────────────────────────────────────────────────────────────*/
// Entrée: impact en mode texte
// Sortie: impact en mode compilé dans le même buffer
int32_t	CompileImpact( uint8_t *buffer )
{
	uint8_t	*ptr = buffer ;
	int8_t	command ;
	int32_t	nbentities = 0 ;

	// Traduction et compilation de l'impact
	PtrFiche = buffer ;

	while( (command = GetImpCommand()) != IMP_NOP )
	{
		if( nbentities>=MAX_IMPACT_ENTITIES )
		{
			Beep() ;
			MessageF( TRUE, "Erreur: MAX_IMPACT_ENTITIES(%1d) atteint !", MAX_IMPACT_ENTITIES ) ;
			break ;
		}

		*ptr++ = command ;

		switch( command )
		{
			// SAMPLE nom[.wav] frequence decalage volume
			case IMP_SAMPLE:
				*(int16_t*)ptr = (int16_t)GetValue() ;	// Num Sample
				ptr+=2 ;
				*(int16_t*)ptr = (int16_t)GetValue() ;	// Frequence
				ptr+=2 ;
				*(int16_t*)ptr = (int16_t)GetValue() ;	// Decalage
				ptr+=2 ;
				*ptr++ = (uint8_t)GetValue() ;       // Volume
				nbentities++ ;
				break ;

			// FLOW nom[.flw]
			case IMP_FLOW:
				*ptr++ = (uint8_t)GetValue() ;	// Num Flow
				nbentities++ ;
				break ;

			// THROW sprite alpha beta speed poids force
			case IMP_THROW:
				*(int16_t*)ptr = (int16_t)GetValue() ;	// Sprite
				ptr+=2 ;
				*(int16_t*)ptr = (int16_t)GetValue() ;	// alpha
				ptr+=2 ;
				*(int16_t*)ptr = (int16_t)GetValue() ;	// beta
				ptr+=2 ;
				*(int16_t*)ptr = (int16_t)GetValue() ;	// Speed
				ptr+=2 ;
				*(int16_t*)ptr = (int16_t)GetValue() ;	// Poids
				ptr+=2 ;
				*ptr++ = (uint8_t)GetValue() ;	// Force
				nbentities++ ;
				break ;

			// THROW_OBJ nom[.O4D] alpha beta speed poids force
			case IMP_THROW_OBJ:
				GetFicName() ;			// Body
#ifdef	COMPILATOR
				*(int16_t*)ptr = SearchIndexBodyFix( FicName, "THROW" ) ;
				ptr += 2 ;
#else
				strcpy( (char*)ptr, FicName ) ;
				ptr+=strlen(FicName) ;
				*ptr++ = '\0' ;
#endif
				*(int16_t*)ptr = (int16_t)GetValue() ;	// alpha
				ptr+=2 ;
				*(int16_t*)ptr = (int16_t)GetValue() ;	// beta
				ptr+=2 ;
				*(int16_t*)ptr = (int16_t)GetValue() ;	// Speed
				ptr+=2 ;
				*(int16_t*)ptr = (int16_t)GetValue() ;	// Poids
				ptr+=2 ;
				*(int16_t*)ptr = (int16_t)GetValue() ;	// Rotation
				ptr+=2 ;

				*ptr++ = (uint8_t)GetValue() ;	// Force
				nbentities++ ;
				break ;

			// THROW_POF nom[.pof] alpha beta speed poids force
			case IMP_THROW_POF:
				*(int16_t*)ptr = (int16_t)GetValue() ;	// Num Pof
				ptr+=2 ;

				*(int16_t*)ptr = (int16_t)GetValue() ;	// alpha
				ptr+=2 ;
				*(int16_t*)ptr = (int16_t)GetValue() ;	// beta
				ptr+=2 ;
				*(int16_t*)ptr = (int16_t)GetValue() ;	// Speed
				ptr+=2 ;
				*(int16_t*)ptr = (int16_t)GetValue() ;	// Poids
				ptr+=2 ;
				*(int32_t*)ptr = GetValue() ;	// Scale
				ptr+=4 ;
				nbentities++ ;
				break ;

			// SPRITE deb fin tempo scale transparent
			case IMP_SPRITE:
				*(int16_t*)ptr = (int16_t)GetValue() ;	// Deb
				ptr+=2 ;
				*(int16_t*)ptr = (int16_t)GetValue() ;	// Fin
				ptr+=2 ;
				*(int32_t*)ptr = GetValue() ;	// tempo
				ptr+=4 ;
				*(int32_t*)ptr = GetValue() ;	// scale
				ptr+=4 ;
				*ptr++ = (uint8_t)GetValue() ;	// transparent on/off
				*ptr++ = (uint8_t)GetValue() ;	// Force
				nbentities++ ;
				break ;

			// FLOW_SPRITE nom[.flow] deb fin tempo scale transparent force
			case IMP_FLOW_SPRITE:
				*ptr++ = (uint8_t)GetValue() ;	// Num Flow
				*(int16_t*)ptr = (int16_t)GetValue() ;	// Deb
				ptr+=2 ;
				*(int16_t*)ptr = (int16_t)GetValue() ;	// Fin
				ptr+=2 ;
				*(int32_t*)ptr = GetValue() ;	// tempo
				ptr+=4 ;
				*(int32_t*)ptr = GetValue() ;	// scale
				ptr+=4 ;
				*ptr++ = (uint8_t)GetValue() ;	// transparent on/off
				*ptr++ = (uint8_t)GetValue() ;	// Force
				nbentities++ ;
				break ;

// ATTENTION: different ici pour la version compil

			// FLOW_OBJ nom[.flw] nom[.O4D] Force
			case IMP_FLOW_OBJ:
				*ptr++ = (uint8_t)GetValue() ;	// Num Flow
				GetFicName() ;			// Body
#ifdef	COMPILATOR
				*(int16_t*)ptr = SearchIndexBodyFix( FicName, "THROW" ) ;
				ptr += 2 ;
#else
				strcpy( (char*)ptr, FicName ) ;
				ptr+=strlen(FicName) ;
				*ptr++ = '\0' ;
#endif
				*ptr++ = (uint8_t)GetValue() ;	// Force
				nbentities++ ;
				break ;

			// FLOW_POF nom[.flw] nom[.pof] scale_deb scale_fin tempo speedrot
			case IMP_FLOW_POF:
				*ptr++ = (uint8_t)GetValue() ;	// Num Flow
				*(int16_t*)ptr = (int16_t)GetValue() ;	// Num Pof
				ptr+=2 ;

				*(int32_t*)ptr = GetValue() ;	// scale_deb
				ptr+=4 ;
				*(int32_t*)ptr = GetValue() ;	// scale_fin
				ptr+=4 ;
				*(int32_t*)ptr = GetValue() ;	// tempo scale
				ptr+=4 ;
				*(int16_t*)ptr = (int16_t)GetValue() ;	// SpeedRot
				ptr+=2 ;
				nbentities++ ;
				break ;

			default:
				ptr-- ;
				NextLine() ;
				break ;
		}
	}

	*ptr++ = IMP_END ;

	// retourne taille compilée
	return( ptr-buffer ) ;
}

/*──────────────────────────────────────────────────────────────────────────*/
uint8_t	*SearchImpact( char *name )
{
	char path[ADELINE_MAX_PATH] ;
	int32_t		n, size ;
	T_IMPACT	*ptri = ListImpact ;

	for( n=0; n<NbImpacts; n++, ptri++ )
	{
		if( !strcasecmp( name, ptri->name ) )
			return ptri->buf ;
	}

	if( NbImpacts>=MAX_IMPACT )
	{
		Beep() ;
		MessageF( TRUE, "Erreur: MAX_IMPACT(%1d) atteint !", MAX_IMPACT ) ;
	}

	// New Impact
	strcpy( ptri->name, name ) ;

	strcpy( path, PATH_IMPACT ) ;
	strcat( path, name ) ;
	AddExt( path, ".IMP" ) ;

	size = FileSize( path ) 		;
	ptri->buf = (uint8_t *)Malloc(size+1)	;/* Pas De Mshrink */

	if( !ptri->buf )	return NULL ;

	if( !Load( path, ptri->buf ) )	return NULL ;

	ptri->buf[size] = 26 ;

	if( CompileImpact( ptri->buf ) )
	{
		NbImpacts++ ;
		return ptri->buf ;
	}

	return NULL ;
}
#endif	// LBA_EDITOR

/*──────────────────────────────────────────────────────────────────────────*/
#ifndef	COMPILATOR
#ifdef	LBA_EDITOR
void	DoImpact( char *name, int32_t x, int32_t y, int32_t z, uint8_t owner )
#else
void   	DoImpact( int32_t num, int32_t x, int32_t y, int32_t z, uint8_t owner )
#endif
{
	int32_t	wlong, wlong2, wlong3 ;
	int32_t	beta = 0;
	int32_t	extra ;
	uint8_t	*ptr	;
	int16_t	wword, wword2, wword3 ;
	int8_t	command ;
	uint8_t	wbyte, wbyte2	;

#ifdef	LBA_EDITOR
	SaveTimer() ;

	ptr = SearchImpact( name ) ;

	RestoreTimer() ;
#else
	ptr = BufferImpact + *(((uint32_t*)BufferImpact)+num) ;
#endif

	if( ptr )
	{
		// Exécution de l'impact

		if( owner!=255 )
		{
			beta = ListObjet[owner].Obj.Beta ;
		}

		while( (command = *ptr++) != IMP_END )
		{
			switch( command )
			{
				// SAMPLE nom[.wav] volume
				case IMP_SAMPLE:
					wword  = *(int16_t*)ptr ;	// NumSample
					ptr+=2 ;
					wword2 = *(int16_t*)ptr ;	// Frequence
					ptr+=2 ;
					wlong  = *(int16_t*)ptr ;	// Decalage
					ptr+=2 ;
					ParmSampleVolume = *ptr++ ;	// Volume

#ifdef	LBA_EDITOR
					HQ_3D_MixSample( COMMON_NUM_DEF, wword, wword2, (int16_t)wlong, 1, x, y, z ) ;
#else
					HQ_3D_MixSample( wword, wword2, (int16_t)wlong, 1, x, y, z ) ;
#endif
					break ;

				// FLOW nom[.flw]
				case IMP_FLOW:
					wbyte = *ptr++ ;	// num flow
					CreateParticleFlow( 0, owner, 0, x, y, z, beta, wbyte ) ;
					break ;

				// THROW sprite alpha beta speed poids force
				case IMP_THROW:
					wword = *(int16_t*)ptr ;	// Sprite
					ptr+=2 ;
					wlong = *(int16_t*)ptr ;	// alpha
					ptr+=2 ;
					wlong2 = *(int16_t*)ptr ;	// beta
					ptr+=2 ;
					wlong3 = *(int16_t*)ptr ;	// Speed
					ptr+=2 ;
					wword2 = *(int16_t*)ptr ;	// Poids
					ptr+=2 ;
					wbyte = *ptr++ ;	// Force

					wlong2 = (wlong2+beta)&4095 ;

					extra = ThrowExtra( owner,
						x, y, z,
						wword,
						wlong, wlong2, wlong3, (uint8_t)wword2,
						wbyte ) ;

#ifdef	LBA_EDITOR
					if( extra!=-1 AND !Shadow )
#else
					if( extra!=-1 AND Shadow<3 )
#endif
					{
						ListExtra[extra].Flags |= EXTRA_NO_SHADOW ;
					}
					break ;

				// THROW_OBJ nom[.O4D] alpha beta speed poids force
				case IMP_THROW_OBJ:
#ifdef	LBA_EDITOR
					strcpy( FicName, (char*)ptr ) ;
					ptr+=strlen(FicName) ;
					ptr++ ;			// Skip '\0'
					wword = 0 ;
#else
					wword = *(int16_t*)ptr ;	// num body
					ptr+=2 ;
#endif
					wlong = *(int16_t*)ptr ;	// alpha
					ptr+=2 ;
					wlong2 = *(int16_t*)ptr ;	// beta
					ptr+=2 ;
					wlong3 = *(int16_t*)ptr ;	// Speed
					ptr+=2 ;
					wword2 = *(int16_t*)ptr ;	// Poids
					ptr+=2 ;
					wword3 = *(int16_t*)ptr ;	// Rotation
					ptr+=2 ;

					wlong2 = (wlong2+beta)&4095 ;

					wbyte = *ptr++ ;	// Force

					extra = ThrowExtraObj( 	owner,
						x, y, z,
#ifdef	LBA_EDITOR
						FicName,
#else
						wword,
#endif
						wlong, wlong2, wlong3,
						wword3, // alpharot
						(uint8_t)wword2, wbyte ) ;

#ifdef	LBA_EDITOR
					if( extra!=-1 AND !Shadow )
#else
					if( extra!=-1 AND Shadow<2 )
#endif
					{
						ListExtra[extra].Flags |= EXTRA_NO_SHADOW ;
					}
					break ;

				// THROW_POF nom[.pof] alpha beta speed poids scale
				case IMP_THROW_POF:
					wword = *(int16_t*)ptr ;	// Num Pof
					ptr+=2 ;

					wlong  = *(int16_t*)ptr ;	// alpha
					ptr+=2 ;
					wlong2 = *(int16_t*)ptr ;	// beta
					ptr+=2 ;
					wlong3 = *(int16_t*)ptr ;	// Speed
					ptr+=2 ;
					wword2 = *(int16_t*)ptr ;	// Poids
					ptr+=2 ;

					wlong2 = (wlong2+beta)&4095 ;

					InitExtraPof( x, y, z, wword,
						      wlong, wlong2,
						      wlong3, wword2,
						      *(int32_t*)ptr, *(int32_t*)ptr, 0, // Scale
						      0, 0 ) ;

					ptr+=4 ;
					break ;

				// SPRITE deb fin tempo scale transparent
				case IMP_SPRITE:
					wword  = *(int16_t*)ptr ;	// Deb
					ptr+=2 ;
					wword2 = *(int16_t*)ptr ;	// Fin
					ptr+=2 ;
					wlong  = *(int32_t*)ptr ;	// tempo
					ptr+=4 ;
					wlong2 = *(int32_t*)ptr ;	// scale
					ptr+=4 ;
					wbyte  = *ptr++ ;	// transparent
					wbyte2  = *ptr++ ;	// force

					InitExtraAnimSprite( owner, x, y, z,
							     wword, wword2,
							     wlong, wlong2,
							     wbyte, wbyte2 ) ;
					break ;

				// FLOW_SPRITE nom[.flow] deb fin tempo scale transparent force
				case IMP_FLOW_SPRITE:
					wbyte = *ptr++ ; 	// num flow
					wword = *(int16_t*)ptr ;	// deb
					ptr+=2 ;
					wword2 = *(int16_t*)ptr ;	// fin
					ptr+=2 ;
					wlong3 = *(int32_t*)ptr ;	// tempo
					ptr+=4 ;
					wlong2 = *(int32_t*)ptr ;	// scale
					ptr+=4 ;
					wbyte2  = *ptr++ ;	// transparent
					wlong = *ptr++ ;	// force

					CreateExtraParticleFlow( FLOW_EXTRA_SPRITE,
							    owner, // owner = tous
							    wword, wword2,
							    x, y, z, 0, wbyte,
							    wlong, wlong2, wbyte2,
							    wlong3 ) ;
					break ;

				// FLOW_OBJ nom[.flw] nom[.O4D] Force
				case IMP_FLOW_OBJ:
					wbyte = *ptr++ ; 	// num flow
#ifdef	LBA_EDITOR
					strcpy( FicName, (char*)ptr ) ;
					ptr+=strlen(FicName) ;
					ptr++ ;			// Skip '\0'
					wword = 0 ;
#else
					wword = *(int16_t*)ptr ;	// num body
					ptr+=2 ;
#endif
					wlong = *ptr++ ;	// force

					CreateExtraParticleFlow( FLOW_EXTRA_OBJ,
							    owner, // owner = tous
							    wword, 0,
							    x, y, z, beta, wbyte,
							    wlong, 0, 0, 0 ) ;
					break ;

				// FLOW_POF nom[.flw] nom[.pof] scale_deb scale_fin tempo speedrot
				case IMP_FLOW_POF:
					wbyte = *ptr++ ;	// Num Flow

					wword = *(int16_t*)ptr ;	// Num Pof
					ptr+=2 ;

					wlong  = *(int32_t*)ptr ;	// scale_deb
					ptr+=4 ;
					wlong2 = *(int32_t*)ptr ;	// scale_fin
					ptr+=4 ;
					wlong3 = *(int32_t*)ptr ;	// tempo
					ptr+=4 ;
					wword2 = *(int16_t*)ptr ;	// SpeedRot
					ptr+=2 ;

					CreateExtraParticleFlow( FLOW_EXTRA_POF,
							    owner, // owner = tous
							    wword, wword2, // speedrot dans num2
							    x, y, z, beta, wbyte,
							    0, wlong, wlong2, // scale_fin dans transparent
							    wlong3 ) ;
					break ;
			}
		}
	}
}
#endif	// COMPILATOR
