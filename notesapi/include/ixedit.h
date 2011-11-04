
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/* ***************************************************************** */
/*                                                                   */
/* Licensed Materials - Property of IBM                              */
/*                                                                   */
/* L-GHUS-76ALVG, L-GHUS-76ALWH                                      */
/*                                                                   */
/* Copyright IBM Corp. 1989, 2006  All Rights Reserved.              */
/*                                                                   */
/* US Government Users Restricted Rights - Use, duplication or       */
/* disclosure restricted by GSA ADP Schedule Contract with           */
/* IBM Corp.                                                         */
/*                                                                   */
/* ***************************************************************** */

#ifdef __cplusplus
extern "C" {
#endif


/* This file contains typedefs for data structures passed from the editor */
/* to import/export procedures. */

#ifndef IXEDIT_DEFS
#define IXEDIT_DEFS

#ifndef FONTID_DEFS
#include "fontid.h"		/* for FONTID */
#endif

#ifndef EDIT_ODS_DEFS
#include "editods.h"	/* for HEAD_DESC_BUFFER */
#endif

#ifndef NAME_DEFS
#include "names.h"		/* for MAXPATH */
#endif


/* Block passed to all editor imports */

typedef struct
	{
	char OutputFileName[OLDMAXPATH];/* File to be filled by import with CD records */
	FONTID FontID;					/* font used at the current caret position */
	} EDITIMPORTDATA;


/* Block passed to all editor exports */

typedef struct
	{
	char InputFileName[OLDMAXPATH];	/* File to be read by export containing CD records */
	DHANDLE hCompBuffer;			 	/* Handle to composite buffer (V1 Exports) */
	DWORD CompLength;				/* Length of composite buffer (V1 Exports) */
	HEAD_DESC_BUFFER HeaderBuffer; 
	HEAD_DESC_BUFFER FooterBuffer;		
	PRINT_SETTINGS   PrintSettings;
	} EDITEXPORTDATA;


#endif

#ifdef __cplusplus
}
#endif


#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif

