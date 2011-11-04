
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/*********************************************************************/
/*                                                                   */
/* Licensed Materials - Property of IBM                              */
/*                                                                   */
/* L-GHUS-76ALVG, L-GHUS-76ALWH                                      */
/*                                                                   */
/* Copyright IBM Corp. 1996, 2007  All Rights Reserved.              */
/*                                                                   */
/* US Government Users Restricted Rights - Use, duplication or       */
/* disclosure restricted by GSA ADP Schedule Contract with           */
/* IBM Corp.                                                         */
/*                                                                   */
/*********************************************************************/

/*

	mailmisc.h

	Public C routines from mailmisc facility.

	Written by Brian Lambert, 5/21/96
*/

#ifndef MAILMISC_DEFS
#define MAILMISC_DEFS

#ifdef __cplusplus
extern "C" {
#endif


#include "mime.h"	


STATUS LNPUBLIC MMCreateConvControls(CCHANDLE *phCC);
STATUS LNPUBLIC MMDestroyConvControls(CCHANDLE hCC);
void   LNPUBLIC MMConvDefaults(CCHANDLE hCC);


/* 'set' access routines */

/*	Import / Export */

void LNPUBLIC MMSetReadReceipt(CCHANDLE hCC, WORD wReadReceipt);		/*	0 - Do not pass read receipt requests when importing or exporting (default)
																				1 - Support read receipt requests (as Return-Receipt-To when exporting)
																				2 - Support read receipt requests (as Disposition-Notification-To when exporting) */


void LNPUBLIC MMSetResent(CCHANDLE hCC, BOOL bSupportResent);				/*	if TRUE support Resent-XXX headers when importing (default is FALSE) */

void LNPUBLIC MMSetStripGroups(CCHANDLE hCC, BOOL bStripGroups);			/*	if TRUE strip groups from all addresses when importing (default is FALSE) */

void LNPUBLIC MMSetMaxHops(CCHANDLE hCC, WORD wMaxHops);					/*	Used to generate $Hops when importing (default is 25) */

void LNPUBLIC MMSetDropItems(CCHANDLE hCC, char *pszDropItems);			/*	Comma delimited list of item names to remove from msgs as they are exported (default is "") */

void LNPUBLIC MMSetAddItems(CCHANDLE hCC, char *pszAddItems);				/*	Comma delimited list of items names to preserve in msgs as they're exported (default is "") */

void LNPUBLIC MMSetInternetDomain(CCHANDLE hCC, char *pszInternetDomain);	/*	Local Internet Domain name used to construct Message-ID and 821 addresses (default is "") */

void LNPUBLIC MMSetNotesDomain(CCHANDLE hCC, char *pszNotesDomain);		/*	Local notes domain, used to construct 821 addresses (default is "") */

void LNPUBLIC MMSetAddPhrase(CCHANDLE hCC, WORD wAddPhrase);				/*	0/1 - no phrase added or removed,
																				2   - add abbreviated DN,
																				3   - add alt name if it exists else DN,
																				4   - Remove all phrases and comments (default 0) */

void LNPUBLIC MMSetImplicitBCC(CCHANDLE hCC, BOOL bImplicitBCC);			/*	if TRUE, add a BCC for every recipient not listed in a To, CC, or Bcc header when importing (default FALSE) */

void LNPUBLIC MMSetSkipX(CCHANDLE hCC, BOOL bSkipX);						/*	if TRUE, don't export any headers named x-notes- (default FALSE) */


/*	Conversion */

void LNPUBLIC MMSetAttachEncoding(CCHANDLE hCC, WORD wAttachEncoding);	/* 0 - base64 (default) */
																			/* 1 - quoted-printable */
																			/* 2 - uuencode */
																			/* 3 - binhex 4.0 */

void LNPUBLIC MMSetTypeFace(CCHANDLE hCC, WORD wTypeFace);				/* 0 - Times Roman */
																			/* 1 - Helvetica */
																			/* 2 - Courier (default) */

void LNPUBLIC MMSetPointSize(CCHANDLE hCC, WORD wPointSize);				/* one of: 6, 8, 9, 10 (default), 12, 14, 18, 24 */

void LNPUBLIC MMSetCharSetDetect(CCHANDLE hCC, BOOL bCharSetDetect);		/* if TRUE auto-detect if necessary when */
																			/*  converting MIME to CD (default is FALSE) */

void LNPUBLIC MMSetKeepTabs(CCHANDLE hCC, BOOL bKeepTabs);				/* if TRUE, when converting CD to MIME */
																			/*  Stream, don't convert tabs to spaces */
																			/*  (default is FALSE) */

void LNPUBLIC MMSetInbLineLen(CCHANDLE hCC, WORD wInbLineLen);			/* if set, when converting MIME rich text */
																			/*  parts to CD, justify using this right */
																			/*  margin.  (text/plain parts are never */
																			/*  justified) (default is 75) */

void LNPUBLIC MMSetOutbLineLen(CCHANDLE hCC, WORD wOutbLineLen);			/* if set, when convert CD to MIME, */
																			/*  justify using this right margin */
																			/*  (default is 75) */

void LNPUBLIC MMSetMacAttachEncoding(CCHANDLE hCC, WORD wMacAttachEncoding);	/* CD to MIME conversion */
																				/* 0 - MultiPart/AppleDouble (default) */
																				/* 1 - Application/Mac-BinHex40 */

void LNPUBLIC MMSetMessageContentEncoding(CCHANDLE hCC, WORD wMessageContentEncoding);	/* CD to MIME conversion */
																						/* 0 - text/plain (w/o images & attachments) */
																						/* 1 - text/plain (w/images & attachments) */
																						/* 2 - text/html (w/images & attachments) */
																						/* 3 - multipart/alternative: text/plain & text/html (w/images & attachments) */


/* 'get' access routines */

WORD   LNPUBLIC MMGetReadReceipt(CCHANDLE hCC);

BOOL   LNPUBLIC MMGetResent(CCHANDLE hCC);

BOOL   LNPUBLIC MMGetStripGroups(CCHANDLE hCC);

WORD   LNPUBLIC MMGetMaxHops(CCHANDLE hCC);

char * LNPUBLIC MMGetDropItems(CCHANDLE hCC);

char * LNPUBLIC MMGetAddItems(CCHANDLE hCC);

char * LNPUBLIC MMGetInternetDomain(CCHANDLE hCC);

char * LNPUBLIC MMGetNotesDomain(CCHANDLE hCC);

WORD   LNPUBLIC MMGetAddPhrase(CCHANDLE hCC);

BOOL   LNPUBLIC MMGetImplicitBCC(CCHANDLE hCC);

BOOL   LNPUBLIC MMGetSkipX(CCHANDLE hCC);


/*	Conversion */

WORD   LNPUBLIC MMGetAttachEncoding(CCHANDLE hCC);

WORD   LNPUBLIC MMGetTypeFace(CCHANDLE hCC);

WORD   LNPUBLIC MMGetPointSize(CCHANDLE hCC);

BOOL   LNPUBLIC MMGetCharSetDetect(CCHANDLE hCC);

BOOL   LNPUBLIC MMGetKeepTabs(CCHANDLE hCC);

WORD   LNPUBLIC MMGetInbLineLen(CCHANDLE hCC);

WORD   LNPUBLIC MMGetOutbLineLen(CCHANDLE hCC);

WORD   LNPUBLIC MMGetMacAttachEncoding(CCHANDLE hCC);

WORD   LNPUBLIC MMGetMessageContentEncoding(CCHANDLE hCC);



#ifdef __cplusplus
}
#endif

#endif

#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif

