/*──────────────────────────────────────────────────────────────────────────*/
#include	<SYSTEM/ADELINE.H>
#include	<SYSTEM/TIMER.H>
#include	<SYSTEM/N_MALLOC.H>
#include	<SYSTEM/LZ.H>
#include	<SYSTEM/FILES.H>
#include	<SYSTEM/HQFILE.H>
#include	<SYSTEM/HQRRESS.H>

#include	<string.h>

//──────────────────────────────────────────────────────────────────────────
typedef struct  {       int32_t		Index	;
                        void		*Ptr	;
                        int32_t		Size	;
                        uint32_t		Time	;
		}       T_HQR_BLOC 		;

//──────────────────────────────────────────────────────────────────────────
HQR_GET_CALLBACK	*HQRGetErrorFunc= NULL	;
HQR_GET_CALLBACK	*HQRGetDelFunc	= NULL	;

//──────────────────────────────────────────────────────────────────────────
int32_t	HQR_Flag ;	// flag "load done" par HQR_Get

//──────────────────────────────────────────────────────────────────────────
// initialise la gestion bufferisée d'une ressource
// hqrname: nom du .HQR contenant les fiches compactées
// maxsize: taille buffer memoire
// MaxIndex: nombre de fiche max stocké
// (devrait être > maxsize/average file size )
T_HQR_HEADER	*HQR_Init_Ressource(	const char	*hqrname,
 					int32_t	maxsize,
					int32_t	maxrsrc	)
{
	T_HQR_HEADER	*header ;
	void		*buffer ;

	header = (T_HQR_HEADER*)Malloc(	sizeof(T_HQR_HEADER)		+
					sizeof(T_HQR_BLOC) * maxrsrc	) ;

	if(!header)
	{
		return NULL	;
	}

	buffer = Malloc(maxsize+RECOVER_AREA);
	if(!buffer)
	{
error:		Free(header)	;
		return NULL	;
	}

	header->MaxSize	= maxsize	;
	header->MaxIndex= maxrsrc	;
	header->Buffer	= buffer	;

	if(!HQR_Change_Ressource(header, hqrname))
	{
		Free(buffer)	;
		goto error	;
	}

	return header		;// header
}

//──────────────────────────────────────────────────────────────────────────
// vide le buffer d'une ressource
void	HQR_Reset_Ressource(T_HQR_HEADER *header)
{
	header->FreeSize= header->MaxSize	;
	header->NbIndex	= 0			;
}

//──────────────────────────────────────────────────────────────────────────
// change le nom du fichiers HQR qui contient les fiches (vide le buffer)
int32_t	HQR_Change_Ressource(T_HQR_HEADER *header, const char *newhqrname)
{
	if(newhqrname && newhqrname[0])
	{
		strcpy(header->Name, newhqrname);

		if(!FileSize(newhqrname))
		{
			return FALSE	;
		}

	}
	else
	{
		header->Name[0] = 0	;
	}

	HQR_Reset_Ressource(header)	;

	return TRUE 			;
}

//──────────────────────────────────────────────────────────────────────────
// libère la mémoire allouée à la gestion bufferisée d'une ressource HQR
void	HQR_Free_Ressource(T_HQR_HEADER *header)
{
	if(!header)
	{
		return		;
	}

	/*AIL_vmm_unlock((void*)header, sizeof(T_HQR_HEADER) +
				  sizeof(T_HQR_BLOC) * header->MaxIndex ) ;

	AIL_vmm_unlock(header->Buffer, header->MaxSize+RECOVER_AREA);
	*/
	Free(header->Buffer)	;
	Free(header)		;
}

//──────────────────────────────────────────────────────────────────────────
// retourne le pointeur mémoire de la fiche (index) demandée
T_HQR_BLOC *HQR_GiveBloc(int32_t index, int32_t nbindex, T_HQR_BLOC *bloc) {
        if (nbindex > 0) {
                T_HQR_BLOC *endOfBlocs = &bloc[nbindex];
                for (int32_t n = 0; &bloc[n] != endOfBlocs; ++n) {
                        T_HQR_BLOC *currBloc = &bloc[n];
                        if (currBloc->Index == index) {
                          return currBloc;
                        }
                }
        }

        return NULL;
}

//──────────────────────────────────────────────────────────────────────────
// supprime une fiche dans le buffer d'une ressource
static inline void HQR_Del_Bloc(T_HQR_HEADER *header, int32_t index)
{
	int32_t		n			;
	T_HQR_BLOC	*ptrbloc		;
	int32_t		delsize			;
	void		*ptrs, *ptrd		;

	ptrbloc = (T_HQR_BLOC*)(header+1);
	delsize = ptrbloc[index].Size 	;

	// if this is last index then skip this...
	if(index < header->NbIndex-1)
	{
		// shift buffer
		ptrd = ptrbloc[index].Ptr 		;
		ptrs = (void*)((uint8_t*)ptrd + delsize)	;
		memmove(ptrd, ptrs, (header->MaxSize-header->FreeSize)-((uint32_t)ptrs-(uint32_t)(header->Buffer)) ) ;

		// shift index table
		ptrd = (void*)&ptrbloc[index]		;
		ptrs = (void*)&ptrbloc[index+1]		;
		memmove(ptrd, ptrs, (header->NbIndex-index-1)*sizeof(T_HQR_BLOC) ) ;

		// shift index value
		for(n=index; n<(header->NbIndex-1); n++ )
		{
			*(int32_t*)&(ptrbloc[n].Ptr) -= delsize;
		}
	}

	// update buffer status
	header->NbIndex-- 			;
	header->FreeSize += delsize		;
}

//──────────────────────────────────────────────────────────────────────────
// retourne le pointeur mémoire de la fiche (index) demandée
void	*HQR_Get(T_HQR_HEADER *header, int32_t index)
{
	int32_t		n, oldest	;
	uint32_t		testtime	;
	void		*ptr		;
	T_HQR_BLOC	*ptrbloc	;
	int32_t		size		;

	if(index < 0) 	goto error	;

	ptrbloc = HQR_GiveBloc(index, header->NbIndex, (T_HQR_BLOC*)(header+1));

	if(ptrbloc)
	{
		// existing index
		ptrbloc->Time	= TimerSystemHR	;// update LRU data

		HQR_Flag	= FALSE		;// NOT NEWLY LOADED

		return	ptrbloc->Ptr 		;
	}
	else	// need load
	{
		// load hqr bloc
		size = HQF_Init(header->Name, index);
		if(!size)
		{
			goto	error		;
		}

		// memory management
		ptrbloc = (T_HQR_BLOC*)(header+1);

		// check if enough space for bloc or index
		while(	(size > header->FreeSize) 		OR
			(header->NbIndex >= header->MaxIndex) 		)
		{
			// delete oldest bloc
			oldest		= -1	;
			testtime	= -1	;

			for( n=0; n<header->NbIndex; n++ )
			{
				if(ptrbloc[n].Time < testtime)
				{
					testtime= ptrbloc[n].Time	;
					oldest	= n 			;
				}
			}
			if(oldest==-1)	// not enough ram or big trouble
			{
				HQF_Close()		;
error:				if(HQRGetErrorFunc)	HQRGetErrorFunc(header->Name, index)	;
				return NULL		;
			}

			if(HQRGetDelFunc)	HQRGetDelFunc(header->Name, index)	;

			HQR_Del_Bloc( header, oldest )	;
		}

		// compute ptr
		ptr = (void *)((uint8_t*)header->Buffer + header->MaxSize - header->FreeSize);

		// space size ok, update struct
		ptrbloc[header->NbIndex].Index	= index		;
		ptrbloc[header->NbIndex].Time	= TimerSystemHR	;
		ptrbloc[header->NbIndex].Ptr	= ptr 		;
		ptrbloc[header->NbIndex].Size	= size		;

		// load it
		if(!HQF_LoadClose(ptr))
		{
			goto error	;
		}

		header->NbIndex++ 	;
		header->FreeSize-= size	;

		HQR_Flag	= TRUE	;// NEWLY LOADED

		return ptr 		;
	}
}

