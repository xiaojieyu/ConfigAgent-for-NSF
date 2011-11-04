
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/* ***************************************************************** */
/*                                                                   */
/* Licensed Materials - Property of IBM                              */
/*                                                                   */
/* L-GHUS-76ALVG, L-GHUS-76ALWH                                      */
/*                                                                   */
/* Copyright IBM Corp. 2007  All Rights Reserved.                    */
/*                                                                   */
/* US Government Users Restricted Rights - Use, duplication or       */
/* disclosure restricted by GSA ADP Schedule Contract with           */
/* IBM Corp.                                                         */
/*                                                                   */
/* ***************************************************************** */

#include "names.h"
#include "nsfdata.h"

#ifdef __cplusplus
extern "C" {
#endif

/* Definitions available to all add-in outlines */
#ifndef ADDINOUT_DEFS
#define ADDINOUT_DEFS

/* Notes Add-in Outline operations */
#define NAOM_INIT						0
#define NAOM_QUERY_OUTLINE				1
#define NAOM_INIT_OUTLINE				2
#define NAOM_QUERY_OPEN					3
#define NAOM_OPEN						4
#define NAOM_CLOSE						5 
#define NAOM_SELECT						6 
#define NAOM_POST_SELECT				7
#define NAOM_DRAGDROP_DOC				8
#define NAOM_TERM_OUTLINE				9
#define NAOM_TERM						10

/* Notes Add-in Outline return values */
#define NAO_NOERROR						0
#define NAO_OPEN_CONTINUE				1
#define NAO_OPEN_STOP					2

/* Notes Add-in Outline resource values */
#define NAO_RESOURCE_NONE				0
#define NAO_RESOURCE_FORMULA			1
#define NAO_RESOURCE_URL				2
#define NAO_RESOURCE_DB					3
#define NAO_RESOURCE_NOTE				4
#define NAO_RESOURCE_NOTELINK			5

#define NAO_LENGTH_FORMULA				2048
#define	NAO_LENGTH_URL					512

typedef WORD			NAORESULT;
typedef NAORESULT		(LNCALLBACKPTR NAOPROC)(WORD Command, void far *pParam);

typedef union
{
	char				szFormula[NAO_LENGTH_FORMULA];	/* Formula */
	char				szURL[NAO_LENGTH_URL];			/* URL */
	DBHANDLE			hDb;							/* Database */
	NOTEHANDLE			hNote;							/* Note */
	NOTELINK			nlNoteLink;						/* Link */
} NAO_ENTRY_RESOURCE;

typedef struct
{
	DWORD				dwSize;							/* Size of this structure */
	char				szName[DESIGN_NAME_MAX];		/* Outline entry name, full title or named element */
	DWORD				dwID;							/* Outline entry ID */
	DWORD				dwParentID;						/* ID of parent outline entry */
	DWORD				dwRefID;						/* Outline reference ID, only used by DLL implementation */
	DWORD				dwSecRefID;						/* Outline reference ID, only used by DLL implementation */
	DWORD				dwReserved1;					/* Reserved */
	DWORD				dwReserved2;					/* Reserved */
} NAO_ENTRY_DATA;

typedef struct
{
	DWORD				dwSize;							/* Size of this structure */
	char				szName[DESIGN_NAME_MAX];		/* Image name */
	DBID				DbID;							/* Replica ID containing szImageName, if not current database */
	DBHANDLE			hDb;							/* Handle containing szImageName, if not current database and not on workspace */
	DWORD				dwReserved1;					/* Reserved */
	DWORD				dwReserved2;					/* Reserved */
} NAO_IMAGE_DATA;

typedef struct
{
	DWORD				dwSize;							/* Size of this structure */
	NAO_ENTRY_DATA		EntryData;						/* NAO_ENTRY_DATA */
	NAO_ENTRY_RESOURCE	EntryResource;					/* NAO_ENTRY_RESOURCE */
	WORD				wEntryResourceType;				/* NAO_RESOURCE_XXX */
	NAO_IMAGE_DATA		ImageData;						/* NAO_IMAGE_DATA */
	DWORD				dwReserved1;					/* Reserved */
	DWORD				dwReserved2;					/* Reserved */
} NAO_ENTRY_INFO;

typedef struct
{
	DWORD				dwSize;							/* Size of this structure */
	NAO_ENTRY_DATA		EntryData;						/* NAO_ENTRY_DATA */
	WORD				wLevel;							/* Outline level, root = 0 */
	BOOL				bNeedsRefresh;					/* Indicates outline refresh is needed */
	DWORD				dwReserved1;					/* Reserved */
	DWORD				dwReserved2;					/* Reserved */
} NAO_SELECT_INFO;

typedef struct
{
	DWORD				dwSize;							/* Size of this structure */
	char				szName[DESIGN_FORM_MAX];		/* Outline name */
	char				szAlias[DESIGN_FORM_MAX];		/* Outline alias */
	DBHANDLE			hDb;							/* Handle to current Db */
	BOOL				bExtendOutline;					/* Indicates whether or not to extend outline */
	DWORD				dwReserved1;					/* Reserved */
	DWORD				dwReserved2;					/* Reserved */
} NAO_OUTLINE_INFO;

typedef struct
{
	DWORD				dwSize;							/* Size of this structure */
	BOOL				bMove;							/* TRUE if MOVE, FALSE if COPY */
	DWORD				dwCount;						/* Number of documents being dropped */
	DBHANDLE			hSourceDb;						/* Source database handle for these notes */
	HANDLE				hIDTable;						/* ID table of documents to drop into folder */
	DBHANDLE			hDestDb;						/* Destination database handle for these notes */
	NAO_SELECT_INFO		DestFolderInfo;					/* NAO_SELECT_INFO of destination folder */
	BOOL				bNamedFolder;					/* TRUE if destination folder has a named folder element */
	BOOL				bActionEntry;					/* TRUE if destination folder has a action element */
	DWORD				dwReserved1;					/* Reserved */
	DWORD				dwReserved2;					/* Reserved */
} NAO_DRAGDROP_DOC;

#endif /* ADDINOUT_DEFS */

#ifdef __cplusplus
}
#endif


#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif

