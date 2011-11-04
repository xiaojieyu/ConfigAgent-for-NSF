
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/*********************************************************************/
/*                                                                   */
/* Licensed Materials - Property of IBM                              */
/*                                                                   */
/* L-GHUS-76ALVG, L-GHUS-76ALWH                                      */
/*                                                                   */
/* Copyright IBM Corp. 1999, 2007  All Rights Reserved.              */
/*                                                                   */
/* US Government Users Restricted Rights - Use, duplication or       */
/* disclosure restricted by GSA ADP Schedule Contract with           */
/* IBM Corp.                                                         */
/*                                                                   */
/*********************************************************************/

/*
**	mime.h
**
**	Header file for MIME utility routines.
**
**	All Rights Reserved
**	Original by Tom Galvin, 02/17/98
*/

#ifndef MIME_H_DEFS
#define MIME_H_DEFS

#ifdef __cplusplus
extern "C" {
#endif


/*
**	Type of RFC822 Message
*/
#define MIME_HEADER_MAP_EMAIL		0
#define MIME_HEADER_MAP_HTTP		1
#define MIME_HEADER_MAP_NEWS		2
#define MIME_HEADER_MAP_UNKNOWN		MIME_HEADER_MAP_EMAIL

/*
**	Define the type of header field.
*/
#define MIME_HEADER_FORMAT_ADDRESS		0
#define MIME_HEADER_FORMAT_DATE			1
#define MIME_HEADER_FORMAT_NOTES_ITEM	2
#define MIME_HEADER_FORMAT_TEXT			3
#define MIME_HEADER_FORMAT_TEXT_LIST	4


typedef void * CCHANDLE;


STATUS LNPUBLIC MIMEHeaderNameToItemName (
	WORD wMessageType,							/* Type of Message           */
	char *pszHeaderName,						/* RFC822 Header Name        */
	char *pszHeaderBody,						/* Optional RFC822 Header Body (for X-Notes-Item headers) */
	char *retszItemName,						/* Return Item Name Buffer   */
	WORD wItemNameSize,							/* Size of Item Name Buffer  */
	WORD *retwHeaderType,						/* Return the Type of Header */
	WORD *retwItemFlags,						/* Optional Return Item Flags*/
	WORD *retwDataType );						/* Optional Return Data Type */


STATUS LNPUBLIC MIMEItemNameToHeaderName (
	WORD wMessageType,							/* Type of RFC822 Message    */
	char *pszItemName,							/* Notes Item Name           */
	char *retszHeaderName,						/* Return Header Name Buffer */
	WORD wHeaderNameSize,						/* Size Header Name Buffer   */
	WORD *retwHeaderType );						/* Optional Return Type      */


STATUS LNPUBLIC MIMEConvertMIMEParts (
	NOTEHANDLE hNote,						/* IN   : Note Handle            */
	BOOL bCanonical );						/* IN   : Note Opened Canonical  */

STATUS LNPUBLIC MIMEConvertMIMEPart (
	NOTEHANDLE hNote,						/* IN   : Note Handle            */
	char *pItemName,						/* IN   : Item Name              */
	WORD wItemNameLen );					/* IN   : Length of Item Name    */

STATUS LNPUBLIC MIMEConvertRFC822TextItem (
	NOTEHANDLE hNote,						/* IN   : Note Handle            */
	char *pItemName,						/* IN   : Item Name              */
	WORD wItemNameLen );					/* IN   : Length of Item Name    */

STATUS LNPUBLIC MIMEConvertRFC822TextItems (
	NOTEHANDLE hNote,						/* IN   : Note Handle            */
	BOOL bCanonical );						/* IN   : Note Opened Canonical  */

STATUS LNPUBLIC MIMEConvertRFC822TextItemByBLOCKID (
	NOTEHANDLE hNote,						/* IN   : Note Handle            */
	BLOCKID bhItem,							/* IN   : Block Handle to Item   */
	BLOCKID bhValue );						/* IN   : Block Handle to Value  */


STATUS LNPUBLIC MIMEConvertMIMEPartsCC (
	NOTEHANDLE hNote,						/* IN   : Note Handle            */
	BOOL bCanonical,						/* IN   : Note Opened Canonical  */
	CCHANDLE hCC );							/* IN	: ptr to CONVERSION_CONTROLS structure */

STATUS LNPUBLIC MIMEConvertMIMEPartCC (
	NOTEHANDLE hNote,						/* IN   : Note Handle            */
	char *pItemName,						/* IN   : Item Name              */
	WORD wItemNameLen,						/* IN   : Length of Item Name    */
	CCHANDLE hCC );							/* IN	: ptr to CONVERSION_CONTROLS structure */

STATUS LNPUBLIC MIMEConvertCDParts (
	NOTEHANDLE hNote,						/* IN   : Note Handle             */
	BOOL bCanonical,						/* IN   : Note Opened Canonical   */
	BOOL bIsNativeMIME,						/* IN   : Note has NativeMIME item*/
	CCHANDLE hCC );							/* IN   : Conversion Controls     */


typedef void * MIMEHANDLE;


#define NULLMIMEHANDLE NULLPTR

#define MIME_STREAM_OPEN_READ				0x00000001	/* Open the Stream for Read  */
#define MIME_STREAM_OPEN_WRITE				0x00000002	/* Open the Stream for Write */


#define MIME_STREAM_MIME_INCLUDE_HEADERS	0x00000010	/* Include MIME Headers      */
#define MIME_STREAM_RFC2822_INCLUDE_HEADERS	0x00000020	/* Include RFC822 Headers */

/* Include RFC822, MIME Headers      */

#define MIME_STREAM_INCLUDE_HEADERS			(MIME_STREAM_MIME_INCLUDE_HEADERS|MIME_STREAM_RFC2822_INCLUDE_HEADERS)

#define MIME_STREAM_SUCCESS			0
#define MIME_STREAM_EOS				1
#define MIME_STREAM_IO				2


STATUS LNPUBLIC MIMEStreamOpen (
	NOTEHANDLE hNote,							/* Note Handle               */
	char *pchItemName,							/* Item Name                 */
	WORD wItemNameLen,							/* Length of Item Name       */
	DWORD dwOpenFlags,							/* MIME Stream Open Flags    */
	MIMEHANDLE *rethMIMEStream );				/* Return MIME Stream Handle */

void LNPUBLIC MIMEStreamClose (
	MIMEHANDLE hMIMEStream );					/* MIME Stream Handle        */

int LNPUBLIC MIMEStreamGetLine (
	char *szLine,								/* Get Line Buffer           */
	unsigned int uiMaxLineSize,					/* Maximum Size of Line      */
	MIMEHANDLE hMIMEStream );					/* MIME Stream Handle        */

int LNPUBLIC MIMEStreamPutLine (
	char *szLine,								/* Get Line Buffer           */
	MIMEHANDLE hMIMEStream );					/* MIME Stream Handle        */

int LNPUBLIC MIMEStreamRead (
	unsigned char *chData,						/* Read Buffer               */
	unsigned int *retuiDataLen,					/* Return Number Bytes Read  */
	unsigned int uiMaxDataLen,					/* Maximum Size of Buffer    */
	MIMEHANDLE hMIMEStream );					/* MIME Stream Handle        */

int LNPUBLIC MIMEStreamWrite (
	unsigned char *chData,						/* Buffer to Write           */
	unsigned int uiDataLen,						/* Length of Buffer to Write */
	MIMEHANDLE hMIMEStream );					/* MIME Stream Handle        */

int LNPUBLIC MIMEStreamRewind (
	MIMEHANDLE hMIMEStream );					/* MIME Stream Handle        */


/*	Define the MIME stream itemize options. */
#define MIME_STREAM_NO_DELETE_ATTACHMENTS	0x00000001
#define MIME_STREAM_ITEMIZE_HEADERS			0x00000002
#define MIME_STREAM_ITEMIZE_BODY			0x00000004

#define MIME_STREAM_ITEMIZE_FULL			(MIME_STREAM_ITEMIZE_HEADERS|MIME_STREAM_ITEMIZE_BODY)


STATUS LNPUBLIC MIMEStreamItemize (
	NOTEHANDLE hNote,						/* IN   : Note Handle            */
	char *pchItemName,						/* IN   : (Opt.) Item Name       */
	WORD wItemNameLen,						/* IN   : (Opt.) Item Name Length*/
	DWORD dwFlags,							/* IN   : Stream Itemize Flags   */
	MIMEHANDLE hMIMEStream );				/* IN   : MIME Stream Handle     */


#ifdef __cplusplus
}
#endif

#endif /* MIME_H_DEFS */

#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif

