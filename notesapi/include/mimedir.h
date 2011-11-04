
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/*********************************************************************/
/*                                                                   */
/* Licensed Materials - Property of IBM                              */
/*                                                                   */
/* L-GHUS-76ALVG, L-GHUS-76ALWH                                      */
/*                                                                   */
/* Copyright IBM Corp. 1997, 2007  All Rights Reserved.              */
/*                                                                   */
/* US Government Users Restricted Rights - Use, duplication or       */
/* disclosure restricted by GSA ADP Schedule Contract with           */
/* IBM Corp.                                                         */
/*                                                                   */
/*********************************************************************/

#ifndef _MIMEDIR_DEFS
#define _MIMEDIR_DEFS

#ifndef _MIMEDIR_SYMBOLS_DEFS
#include "mimedirs.h"
#endif


/* for NOTEHANDLE */
#ifndef NSF_DATA_DEFS
#include "nsfdata.h"
#endif

/* for CONVERSION_CONTROLS */
#ifndef MIME_H_DEFS
#include "mime.h"
#endif


typedef void *				PMIMEENTITY;

typedef DWORD HMIMEDIRECTORY;


/*	For MIMEGetEntityData  */
#define MIME_ENTITY_DATA_BODY			0	/*	Get body only  */
#define MIME_ENTITY_DATA_HEADERS		1	/*	Get headers only  */
#define MIME_ENTITY_DATA_RFC822TEXT		2	/*	Get boundary, headers and body  */
#define MIME_ENTITY_DATA_BOUNDARY		3	/*	Get boundary only */


#ifdef __cplusplus
extern "C" {
#endif

/****************************************************************************/


/* Get and free the whole directory */


STATUS LNPUBLIC MIMEOpenDirectory(NOTEHANDLE hNote,
                                  HMIMEDIRECTORY far *rethDir);

STATUS LNPUBLIC MIMEFreeDirectory(HMIMEDIRECTORY hDir);

/****************************************************************************/


/* Retrieving the body info */

STATUS		LNPUBLIC	MIMEGetRootEntity (
	HMIMEDIRECTORY hMIMEDir,				/* IN   : MIME Directory Handle  */
	PMIMEENTITY *retpMIMEEntity );				/* OUT  : Return MIME Entity Ptr */

STATUS LNPUBLIC MIMEIterateNext (
	HMIMEDIRECTORY hMIMEDir,				/* IN   : MIME Directory Handle		*/
	PMIMEENTITY pTopMIMEEntity,				/* IN   : Topmost MIME Entity Pointer	*/
	PMIMEENTITY pPrevMIMEEntity,				/* IN   : Previous MIME Entity Pointer  */
	PMIMEENTITY *retpMIMEEntity );				/* OUT  : Return Next MIME Entity Ptr	*/

STATUS LNPUBLIC MIMEGetNextSibling (
	HMIMEDIRECTORY hMIMEDir,				/* IN   : MIME Directory Handle		*/
	PMIMEENTITY pMIMEEntity,				/* IN   : MIME Entity Pointer		*/
	PMIMEENTITY *retpMIMEEntity );				/* OUT  : Return Next Sibling Ptr	*/

STATUS LNPUBLIC MIMEGetPrevSibling (
	HMIMEDIRECTORY hMIMEDir,				/* IN   : MIME Directory Handle		*/
	PMIMEENTITY pMIMEEntity,				/* IN   : MIME Entity Pointer		*/
	PMIMEENTITY *retpMIMEEntity );				/* OUT  : Return Previous Sibling Ptr	*/

STATUS LNPUBLIC MIMEGetFirstSubpart (
	HMIMEDIRECTORY hMIMEDir,				/* IN   : MIME Directory Handle		*/
	PMIMEENTITY pMIMEEntity,				/* IN   : MIME Entity Pointer		*/
	PMIMEENTITY *retpMIMEEntity );				/* OUT  : Return First Subpart Ptr	*/

STATUS LNPUBLIC MIMEGetParent (
	HMIMEDIRECTORY hMIMEDir,				/* IN   : MIME Directory Handle		*/
	PMIMEENTITY pMIMEEntity,				/* IN   : MIME Entity Pointer		*/
	PMIMEENTITY *retpMIMEEntity );				/* OUT  : Return Parent Ptr		*/

const char * LNPUBLIC MIMEEntityGetHeader (
	PMIMEENTITY pMIMEEntity,				/* IN   : MIME Entity Pointer    */
	MIMESYMBOL	symKey );					/* IN   : header to find         */

MIMESYMBOL	LNPUBLIC	MIMEEntityContentType (
	PMIMEENTITY pMIMEEntity );				/* IN   : MIME Entity Pointer    */

MIMESYMBOL	LNPUBLIC	MIMEEntityContentSubtype (
	PMIMEENTITY pMIMEEntity );				/* IN   : MIME Entity Pointer    */

const char * LNPUBLIC MIMEEntityContentLocation(
	PMIMEENTITY pMIMEEntity );				/* IN   : MIME Entity Pointer    */

const char * LNPUBLIC MIMEEntityContentID(
	PMIMEENTITY pMIMEEntity );				/* IN   : MIME Entity Pointer    */

STATUS LNPUBLIC MIMEEntityGetTypeParam (
	PMIMEENTITY pMIMEEntity,				/* IN   : MIME Entity Pointer			*/
	MIMESYMBOL symParam,					/* IN	: MIME Parameter Attribute		*/
	DHANDLE *phValue,						/* OUT	: Return Parameter Value Handle */
	DWORD *pdwValueLen);					/* OUT	: Return Parameter Value Length */

BOOL LNPUBLIC MIMEEntityIsMessagePart( PMIMEENTITY pMimeEntity);
BOOL LNPUBLIC MIMEEntityIsMultiPart( PMIMEENTITY pMimeEntity);
BOOL LNPUBLIC MIMEEntityIsDiscretePart( PMIMEENTITY pMimeEntity);



STATUS LNPUBLIC MIMEFreeEntityDataObject(NOTEHANDLE hNote, PMIMEENTITY pEntity);

STATUS LNPUBLIC MIMEGetEntityData(NOTEHANDLE hNote,
	   					PMIMEENTITY, WORD wDataType, DWORD dwOffset, DWORD dwChunkLen,
	   					DHANDLE *phData, DWORD *pdwDataLen);

#define MIMEGetEntityDataSize(hNote, pME, wDataType, pdwDataLen) MIMEGetEntityData((hNote), (pME), (wDataType), NULL, MAXDWORD, NULL, (pdwDataLen))

/* buf should be MAXPATH long.  buf will be empty string if no dbObject */
STATUS LNPUBLIC MIMEGetEntityDBObjectName(NOTEHANDLE hNote,
										  PMIMEENTITY, char *buf);


STATUS LNPUBLIC MIMEGetEntityPartFlags(NOTEHANDLE hNote, PMIMEENTITY pME, DWORD *pdwFlags);


void LNPUBLIC MimeGetTypeInfoFromExt(
	char *ext,
	char *typeBuf,
	WORD typeBufLen,
	char *subtypeBuf,
	WORD subtypeBufLen,
	char *descrBuf,
	WORD descrBufLen);

void LNPUBLIC MimeGetExtFromTypeInfo(
	char	*type,
	char	*subtype,
	char	*extBuf,
	WORD	 extBufLen,
	char	*descrBuf,
	WORD	 descrBufLen);


STATUS LNPUBLIC MIMEGetDecodedEntityData(NOTEHANDLE hNote,
						PMIMEENTITY, DWORD dwRawOffset, DWORD dwChunkLen,
						DHANDLE *phData, DWORD *pdwDataLen, DWORD *pdwRawDataLen);


STATUS LNPUBLIC MIMEGetText(NOTEHANDLE hNote, const char *pchItemName, WORD wItemNameLen, BOOL bNotesEOL, char *pchBuf, DWORD dwMaxBufLen, DWORD *pdwBufLen);


#ifdef __cplusplus
}
#endif

#endif /* _MIMEDIR_DEFS */

#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif

