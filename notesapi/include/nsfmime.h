
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/*********************************************************************/
/*                                                                   */
/* Licensed Materials - Property of IBM                              */
/*                                                                   */
/* L-GHUS-76ALVG, L-GHUS-76ALWH                                      */
/*                                                                   */
/* Copyright IBM Corp. 1999, 2006  All Rights Reserved.              */
/*                                                                   */
/* US Government Users Restricted Rights - Use, duplication or       */
/* disclosure restricted by GSA ADP Schedule Contract with           */
/* IBM Corp.                                                         */
/*                                                                   */
/*********************************************************************/

#ifndef _NSFMIME_DEFS_
#define _NSFMIME_DEFS_

#include "nsf.h"

#ifdef __cplusplus 
extern "C" {
#endif


STATUS LNPUBLIC NSFMimePartDelete(NOTEHANDLE hNote, char *pchItemName, WORD wItemNameLen);


STATUS LNPUBLIC NSFMimePartAppend(NOTEHANDLE hNote, char *pchItemName, WORD wItemNameLen,
					WORD wPartType, DWORD dwFlags, char *pchPart, WORD wPartLen);


STATUS LNPUBLIC NSFMimePartGetInfo(NOTEHANDLE hNote, char *pchItemName, WORD wItemNameLen,
					WORD *pwPartType, DWORD *pdwFlags, WORD *pwReserved, WORD *pwPartLen,
					BLOCKID *pbhItem);

STATUS LNPUBLIC NSFMimePartGetInfoNext(NOTEHANDLE hNote, 
					BLOCKID bhItem, char *pchItemName, WORD wItemNameLen,
					WORD *pwPartType, DWORD *pdwFlags, WORD *pwReserved, WORD *pwPartLen,
					BLOCKID *pbhItemNext);

STATUS LNPUBLIC NSFMimePartGetInfoByBLOCKID(BLOCKID bhItem,
					WORD *pwPartType, DWORD *pdwFlags, WORD *pwReserved, 
					WORD *pwPartOffset, WORD *pwPartLen,
					WORD *pwBoundaryOffset, WORD *pwBoundaryLen,
					WORD *pwHeadersOffset, WORD *pwHeadersLen,
					WORD *pwBodyOffset, WORD *pwBodyLen);

STATUS LNPUBLIC NSFMimePartGetPart(BLOCKID bhItem, DHANDLE *phPart);

BOOL LNPUBLIC NSFIsFileItemMimePart(NOTEHANDLE hNote, BLOCKID bhFileItem);
BOOL LNPUBLIC NSFIsMimePartInFile(NOTEHANDLE hNote, BLOCKID bhMimeItem, char *pszFileName, WORD wMaxFileNameLen);

STATUS LNPUBLIC NSFMimePartCreateStream(NOTEHANDLE hNote, char *pchItemName, 
					WORD wItemNameLen, WORD wPartType, DWORD dwFlags, DHANDLE *phCtx);

STATUS LNPUBLIC NSFMimePartAppendStream(DHANDLE hCtx, char *pchData, WORD wDataLen);
STATUS LNPUBLIC NSFMimePartAppendFileToStream(DHANDLE hCtx, char *pszFilename);
STATUS LNPUBLIC NSFMimePartAppendObjectToStream(DHANDLE hCtx, char *pszObject);
STATUS LNPUBLIC NSFMimePartCloseStream(DHANDLE hCtx, BOOL bUpdate);

#ifdef __cplusplus 
}
#endif

#endif

#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif

