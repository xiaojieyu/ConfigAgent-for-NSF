
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/* ***************************************************************** */
/*                                                                   */
/* Licensed Materials - Property of IBM                              */
/*                                                                   */
/* L-GHUS-76ALVG, L-GHUS-76ALWH                                      */
/*                                                                   */
/* Copyright IBM Corp. 2000, 2006  All Rights Reserved.              */
/*                                                                   */
/* US Government Users Restricted Rights - Use, duplication or       */
/* disclosure restricted by GSA ADP Schedule Contract with           */
/* IBM Corp.                                                         */
/*                                                                   */
/* ***************************************************************** */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef DBMISC_DEFS
#define DBMISC_DEFS

#ifndef GLOBAL_DEFS
#include "global.h"
#endif

#ifndef NAME_DEFS
#include "names.h"
#endif

#ifndef NSF_DEFS
#include "nsf.h"
#endif

#ifndef ADMINP_DEFS
#include "adminp.h"
#endif

STATUS LNPUBLIC StoredFormAddItems (DBHANDLE hSrcDbHandle,
									DHANDLE hSrcNote,
									DHANDLE hDstNote,
									BOOL bDoSubforms,
									DWORD dwFlags);

STATUS LNPUBLIC StoredFormRemoveItems(	DHANDLE hNote, 
										DWORD dwFlags);

STATUS LNPUBLIC StoredFormAppendSubformToken(	char* pszSubName, 
												WORD wSubNameBufferLen);

/* end ifndef DBMISC_DEFS */
#endif

#ifdef __cplusplus
}
#endif


#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif

