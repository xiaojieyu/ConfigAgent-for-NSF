
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/* ***************************************************************** */
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
/* ***************************************************************** */

/* nsfole.f */

#ifndef NSF_OLEAPI_DEFS
#define NSF_OLEAPI_DEFS

#ifdef __cplusplus
extern "C" {
#endif

#ifndef OLE_ODS_DEFS
#include "oleods.h"
#endif

#ifndef NSF_NOTE_DEFS
#include "nsfnote.h"
#endif


#define OLE_ROOTISTORAGE_SUPPORTED	1
#define OLE_ISTORAGE_SUPPORTED		2

/*	
	API Utility functions used to extract, create and delete OLE2 object storage
	blobs from Notes documents.  These functions only deal with the 
	storage-related objects that comprise OLE object storage in Notes 
	documents-and do NOT address any Rich-text references or representations of
	the OLE objects.  It is assumed that the Rich Text (CDOLEBEGIN/CDOLEEND)
	objects are dealt with externally and separately from these functions.
*/

/*	NSFNoteExtractOLE2Object

	Create a copy of an OLE2 object structured storage file, serialized to
	an On-disk file.
	
	Note:  It is assumed that the caller of this function has access to the OLE 
			structured storage type (in the $OLEOBJINFO item) for this OLE object 
			and handles setting or passing this information on as appropriate. 

	Input:

		hNote
			Note handle of open Note

		pszObjectName
			Name of the OLE $FILE object which is the "master" extendable file object
			("ext***") in the set of $FILE objects that comprise this OLE object.

		char *pszFileName
			The file name, including path, into which the Storage file will be dumped.

		pEncryptionKey
			The Note's bulk data encryption key, acquired from NSFNoteDecrypt(...)

		fOverwrite
			TRUE to overwrite the file, if it already exists

		dwFlags
			Additional flags, unused at this time, must be 0

*/

STATUS LNPUBLIC NSFNoteExtractOLE2Object(
								NOTEHANDLE hNote, 
								char * pszObjectName,
								char * pszFileName,
								ENCRYPTION_KEY * pEncryptionKey,
								BOOL fOverwrite,
								DWORD dwFlags);

/*	SDK END */
/*	Do not expose this function in the public API!  It is very similar to
	NSFNoteExtractOLE2Object which does not work correctly despite the fact
	that it has been in the public API for a long time.  If and when it is
	fixed, this function should be fixed, tested, and exposed as well. */

/*	NSFNoteCipherExtractOLE2Object
	This function is preferred to the above function in 8.0.1 and later
	releases, IF the ENCRYPTION_KEY/CIPHERHANDLE argument is non-NULL.

	The arguments are the same, except that in place of the pEncryptionKey
	argument is:

		hDecryptionCipher
			For NSFNoteCipherExtractOLE2Object, the note's bulk data cipher handle,
			acquired from NSFNoteCipherDecrypt

*/

STATUS LNPUBLIC NSFNoteCipherExtractOLE2Object(
								NOTEHANDLE hNote, 
								char * pszObjectName,
								char * pszFileName,
								CIPHERHANDLE hDecryptionCipher,
								BOOL fOverwrite,
								DWORD dwFlags);
/*	SDK BEGIN */

/*	NSFNoteDeleteOLE2Object

	Delete an OLE2 structured storage object, which in Notes is stored as
	an extendable file object.  Also, optionally delete the associated
	$OLEOBJINFO item 

	Input:

		hNote
			Note handle of open Note

		pszObjectName
			Name of the OLE $FILE object which is the "master" extendable file object
			("ext***") in the set of $FILE objects that comprise this OLE object.

		fDeleteObjInfo
			True if the associated $OLEOBJINFO with this object should also be deleted

		pEncryptionKey
			The Note's bulk data encryption key, acquired from NSFNoteDecrypt(...). 
			Necessary to decrypt the $FILE extent table.

		dwFlags
			Additional flags, unused at this time, must be 0

*/

STATUS LNPUBLIC NSFNoteDeleteOLE2Object(
								NOTEHANDLE hNote,
								char * pszObjectName,
								BOOL fDeleteObjInfo,
								ENCRYPTION_KEY * pEncryptionKey,
								DWORD dwFlags);

/*	SDK END */
/*	Do not expose this function in the public API!  It is very similar to
	NSFNoteExtractOLE2Object which does not work correctly despite the fact
	that it has been in the public API for a long time.  If and when it is
	fixed, this function should be fixed, tested, and exposed as well. */

/*	NSFNoteCipherDeleteOLE2Object
	This function is preferred to the above function in 8.0.1 and later
	releases, IF the ENCRYPTION_KEY/CIPHERHANDLE argument is non-NULL.

	The arguments are the same, except that in place of the pEncryptionKey
	argument is:

		hDecryptionCipher
			For NSFNoteCipherDeleteOLE2Object, the note's bulk data cipher handle,
			acquired from NSFNoteCipherDecrypt
			Necessary to decrypt the $FILE extent table.
*/

STATUS LNPUBLIC NSFNoteCipherDeleteOLE2Object(
								NOTEHANDLE hNote,
								char * pszObjectName,
								BOOL fDeleteObjInfo,
								CIPHERHANDLE hDecryptionCipher,
								DWORD dwFlags);
/*	SDK BEGIN */

/*
	NSFNoteAttachOLE2Object

	Attach an OLE structured storage object to the specified Note, creating the
	OLE $FILE objects using the specified storage file.  Also, create an
	$OLEOBJINFO note item using the specified parameters.
	
	OLE structured storage objects can have several forms.  The forms supported are:
		- Notes OLE structured storage object - has the form RootIStorage, IStorage,
			IStream.
		- IStorage, IStream - has the form IStorage, IStream.

	Input:

		hNote
			NSF Note Handle to open note

		pszFileName
			Input file name containing the OLE structured storage file

		pszObjectName
			The name of the NSF $FILE extendable file object to create. This MUST
			match the one created in the CDOLEBEGIN record in the body of the
			document.

		fCreateInfoItem
			Obsolete, no longer used.

		pszObjDescription
			Object user description, i.e. "My Worksheet"

        pszFieldName
			Field name in which the OLE object resides within the document.

		pOleObjClassID  (see OLEODS.H, optional)
			The OLE object's GUID

		wDisplayFormat
			Visual rendering format, like bitmap, metafile,  DDEFORMAT_* from editods.h

		fScripted
			True if object is scripted (for ActiveX).  If this is true, it's up to the 
			caller to attach the associated Lotus script source and object code to this
			note, using the following naming convention <xxxx>.lso for the Lotus Script
			compiled object code and <xxxx>.lss for the Lotus Script source, where
			"xxxx" is identical to the the pszObjectName used above.  If Object name
			is "foo" then "foo.lss" has the lotus script source, and "foo.lso" has the
			Lotus script object code.

		fOleControl
			True if this object is registered an OLE ActiveX.  Optional, set to FALSE
			if unknown.  Notes will determine setting when object is activated.

		dwFlags
			OLE storage structure of incoming OLE object
				=OLE_ROOTISTORAGE_SUPPORTED, incoming OLE object's storage structure
					is RootIStorage, IStorage, IStream (same as Notes OLE storage)
				=OLE_ISTORAGE_SUPPORTED, incoming OLE object's storage structure
					is IStorage, IStream

*/


STATUS LNPUBLIC NSFNoteAttachOLE2Object(
								NOTEHANDLE hNote,
								char * pszFileName,
								char * pszObjectName,
								BOOL   fCreateInfoItem,
								char * pszObjDescription,
	                            char * pszFieldName,
								OLE_GUID  * pOleObjClassID,
								WORD wDisplayFormat,
								BOOL fScripted,
								BOOL fOleControl,
								DWORD dwFlags);

#ifdef __cplusplus
}
#endif

#endif /* NSF_OLEAPI_DEFS */


#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif

