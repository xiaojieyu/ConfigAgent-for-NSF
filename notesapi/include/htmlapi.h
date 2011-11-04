
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/*********************************************************************/
/*                                                                   */
/* Licensed Materials - Property of IBM                              */
/*                                                                   */
/* L-GHUS-76ALVG, L-GHUS-76ALWH                                      */
/*                                                                   */
/* Copyright IBM Corp. 2002, 2006  All Rights Reserved.              */
/*                                                                   */
/* US Government Users Restricted Rights - Use, duplication or       */
/* disclosure restricted by GSA ADP Schedule Contract with           */
/* IBM Corp.                                                         */
/*                                                                   */
/*********************************************************************/

/*______________________________________________________________________
 *
 *		htmlapi.h
 *
 *		This is the public C API to the Domino Web Server HTML translation
 *______________________________________________________________________
 */


#if ! defined(HTMLAPI_H)
#define HTMLAPI_H


#if ! defined(GLOBAL_DEFS)
#include "global.h"
#endif

#if ! defined(URLTYPES_H)
#include "urltypes.h"
#endif

#if ! defined(NIF_DEFS)
#include "nif.h"
#endif

#if ! defined (NSF_DATA_DEFS)
#include "nsfdata.h"			/* for NOTEID and UNID */
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*
 * General Information
 * ======= ===========
 *
 * Descriptoin
 *
 * The HTML API provides program access to the Domino Web Server's CD to HTML conversion capability
 * for views, documents, and items.
 *
 *
 * Threading Issues.
 *
 * This API is  thread safe, in that it does not use any unprotected global state.
 * The HTML Converter Object itself is NOT concurrent -- you cannot use the
 * same object in multiple threads without somehow coordinating access yourself.
 * It does not really make sense to use one converter object in multiple threads anyway.
 */

/*
 * Per-Process Initialization / Termination
 * =========== ============== = ===========
 *
 * 	These deal with process-wide resources initialized and used for the
 * HTML API.
 *
 */

STATUS LNPUBLIC HTMLProcessInitialize();
/*
 * Initializes the HTML API process-wide resources.
 * Normally called once, when user process is initializing.
 * Calling this is Optional -- if not called, the first call to HTMLCreateConverter
 * 	will do initialization.
 * Multiple calls are OK -- they do not "nest" (i.e. multiple calls do not pair
 * 	with HTMLProcessTerminate().)
 * Calling this after a call to HTMLProcessTerminate() results in undefined behavior.
 * Threading: can be called from multiple threads concurrently  with HTMLCreateConverter()
 *
 * Results:
 *		ERR_HTMLAPI_INIT
 * 	-- other STATUS codes from internal calls.
 */

void LNPUBLIC HTMLProcessTerminate();
/*
 * Releases process wide resources.
 * Normally called once, when user process is terminating.
 *		Can be called earlier, if no other HTML API operations are to be performed.
 * Undefined behavior if
 *		- called before HTMLProcessInitialize()
 *		- called multiple times.
 * If not called, process will terminate with HTML API resources still allocated.
 * (Usually this is not a problem)
 * Threading: must be called from one thread, no other concurrent HTML API calls.
 */

/*
 *	CONVERTER OBJECT
 *	========= ======
 *
 *  A covverter object is used to access most of the API's features.
 *  The handle is passed as an argument to the API functions.
 *
 */
typedef MEMHANDLE HTMLHANDLE;

STATUS LNPUBLIC HTMLCreateConverter	(HTMLHANDLE *phHTML);
/*
 * Output Argument:
 *			HTMLHANDLE - the handle to the newly created converter
 */

STATUS LNPUBLIC HTMLDestroyConverter (HTMLHANDLE hHTML);
/*
 * Input Argument:
 *		HTMLHANDLE - handle of the converter to destroy.
 */


/*
 *	PROPERTIES
 *	==========
 *
 *	Information about the converter object is handled with an enumeration
 *	and a pair of get/set methods.  The data type passed through the API
 *	is void*.  Depending on the enumeration value, the thing pointed to
 *	by the void* is cast to the actual type of that property.
 *
 *	Note: r = read (only), w = write (only), rw = read/write.
 */

typedef enum
{
	HTMLAPI_PROP_TEXTLENGTH = 0
			/* (r DWORD)	Number of bytes in output HTML text buffer.
				This property is valid after calls to HTMLConvertXXX()
			*/

	,HTMLAPI_PROP_NUMREFS = 1
			/* (r DWORD)	Number of references in output list of HTML references.
				This property is valid after callst to HTMLConvertXXX()
			*/


	,HTMLAPI_PROP_USERAGENT_LEN = 3
			/* (r DWORD)  Length of the USERAGENT property -- 0 if the USERAGENT
				property isn't set.
			*/

	,HTMLAPI_PROP_USERAGENT = 4
			/* (rw char *)  NULL-terminated string indicating the "browser" being used.
				Some HTML is generated differently depending on browser.
				(On set, if the string is too big -- gerater than MAX_DOMINO_USERAGENT_LENGHT --
				 then ERR_HTMLAPI_INVALID_ARG is returned.
				 On get, buffer must hold at least PROP_USERAGENT_LEN+1 bytes.)

				This property must be set before calls to HTMLConvertXXX()
			*/


	,HTMLAPI_PROP_BINARYDATA = 6
			/* (r BOOL) Indicates (when TRUE) that the results of GetText are binary data.
				"HTMLConvertImage" and "HTMLConvertElement" usualy return binary text data.
		   */



	,HTMLAPI_PROP_MIMEMAXLINELENSEEN = 102
		    /* (r DWORD) Indicates the maximum number of LMBCS characters that have been
				encountered between newlines in the generated HTML.

				This proerty is only valid AFTER a calls to GetText() for a given converstion.

				If the result of the HTMLCovertXXX() command is "binary" data, then this property
				is not calculated, and the value returned is meaningless.

				Details:
				When GetText() is called it calculates "line lengths" by counting
				the number of LMBCS characters between CRLFs.  The maximum line length encountered
				is maitained in this property.

				Note that if GetText is called multiple	times with different starting offsets
				and with a return buffer smaller than the total text length, the line length calculations
				may not be accurate.

				Example:  assume return buffer contains:
					1 2 3 4 5 6 CR LF 7 8 9

					The text length == 11

					Call GetText with StartingOffset == 0 and *pTextLength == 11, then this property
					will have value of 6

					Call GetText with StartingOffset == 0 and *pTextLength == 4, then this property
					will have value of 4

					Next call GetText with StartingOffset == 4 and *pTextLength == 7, then this
					property will have value of 4.

			*/



} HTMLAPI_PROP_TYPE;


/*
 * get/set rotuines for properties....
 */
STATUS LNPUBLIC HTMLGetProperty (HTMLHANDLE hHTML,
				HTMLAPI_PROP_TYPE PropertyType, void *pProperty);

STATUS LNPUBLIC HTMLSetProperty (HTMLHANDLE hHTML,
				HTMLAPI_PROP_TYPE PropertyType, const void *pProperty);
/*
 *	arguments are:
 *
 *	HTMLHANDLE hHTML
 *			A handle to the converter object.
 *	HTMLAPI_PROP_TYPE PropertyType,
 *			The value of the enumeration indicating which property to get/set.
 *	void *pProperty
 *			A pointer to the value.
 *
 *
 *	Example usage:
 *		// get the length of converted text.
 *		HTMLHANDLE h; // initialized somehow
 *		DWORD tlength;
 *		STATUS r;
 *		r = HTMLGetProperty(h, HTMLAPI_PROP_TEXTLENGTH, &tlength);
 *
 */

/*
 * Set HTML Options
 */
STATUS LNPUBLIC HTMLSetHTMLOptions(HTMLHANDLE hHTML,
				const char *optionList[]);
/*
 * The argument "optionList" is a NULL pointer terminated array of pointers to NULL terminated strings.
 * (argv structure).
 * Each entry represents a name=value pair, with "name" the name of an HTMLOption.
 * The options override options with the same name that were specified in the notes.ini
 * or on the form (using the $$HTMLOptions field).
 *
 * Current Set of HTMLOptions:
 *    ForceSectionExpand - 1 = expand all sections in the generated html
 *    ForceOutlineExpand - 1 = expand all outlines in the generated html
 *    RowAtATimeTableAlt - 1 = alternate representation for row-at-a time tables
 *	                           that shows all of the rows and the tab label.
 */

/*
 *	REFERENCES
 *	==========
 *
 *	An HTML page may contain references to other resources.  These are in the form of
 *	URLs that appear in anchor tags and elsewhere.  When converting a note to HTML,
 *	a number of references are generated.  References can be converted:
 *		+ automatically as part of decorating a page to be useful when viewed in
 *		a browser (next/previous links in a view, for example)
 *		+ when converting a database "link" to a URL.
 *		+ in a view, references to the actual documents.
 *
 *	These references are generated with a syntax that can be interpreted by the Domino
 *	Web Server, but might not be useful to the client of the API.
 *	So, we provide a means to examine the references on a page programatically and
 *	to replace the text of the reference with application supplied values.
 *
 *	references have the structure:
 *		type - value indicating how the reference is used.
 *		text - the URL text.
 *		command - the Domino 'url command' associated with the reference
 *		target
 *			- list of components naming the target of the reference
 *		arguments
 *			- list of name:value pairs representing the referene's arguments
 */

/*
 * Reference Types.
 *
 * Indicate the purpose / use of the rerference.
 */
typedef enum
{
	HTMLAPI_REF_UNKNOWN = 0			/* unknown purpose */
	,HTMLAPI_REF_HREF = 1			/* A tag HREF= value */
	,HTMLAPI_REF_IMG = 2			/* IMG tag SRC= value */
	,HTMLAPI_REF_FRAME = 3			/* (I)FRAME tag SRC= value */
	,HTMLAPI_REF_APPLET = 4			/* Java applet reference */
	,HTMLAPI_REF_EMBED = 5			/* plugin SRC= reference */
	,HTMLAPI_REF_OBJECT = 6			/* active object DATA= referendce */
	,HTMLAPI_REF_BASE = 7			/* BASE tag value */
	,HTMLAPI_REF_BACKGROUND = 8		/* BODY BACKGROUND */
	,HTMLAPI_REF_CID = 9			/* IMG SRC= value from MIME message */

} HTMLAPI_REF_TYPE;


/*
 * Structure used to hold URL target component.
 */
typedef struct
{
	UAT	AddressableType; 	/* the kind of note object the component refers to */
	URT	ReferenceType;		/* the value type of the component -- determines
							the branch of the following union to use */
	union
	{
		char		*name;	/* text name of an object */
		UNID		unid;	/* unique note id */
		NOTEID		nid;	/* note id */
		USV			special;	/* a special value */
		DBID		dbid;		/* database id */
	} Value;
} HTMLAPI_URLTargetComponent;


/*
*	Structure used to hold a URL argument value.
*/
typedef struct
{
	CmdArgID			Id;		/* CmdArgID identifier */
	CmdArgValueType		Type;	/* type of target or arg value (e.g., CAVT_String, CAVT_Int, etc.) */
	union
	{
		int		n;		/* When Type == CAVT_Int,		value as int */
		NOTEID	nid;	/* When Type == CAVT_NoteId,	value as NOTEID */
		UNID	unid;	/* When Type == CAVT_UNID,		value as UNID */
		char	*s;		/* When Type == CAVT_String,	value as nul-terminated string */
		struct			/* When Type == CAVT_StringList,
								value is list of NULL terminated strings. */
		{
			DWORD count;	/* number of strings in the list - 0 indicates empty list ('first' is undefined) */
			char *first;	/* pointer to first string in list - undefined if count==0 */
		} slist;
	} Value;

} HTMLAPI_URLArg;

/*
* To simplify memory management, the target components and args are unioned in
* one structure that can serve as the allocation unit for sequences (arrays)
* of target components and args.
*/
typedef union
{
	HTMLAPI_URLTargetComponent	Target;
	HTMLAPI_URLArg				Arg;
} HTMLAPI_URLComponent;


/*
 * the complete reference
 */
typedef struct {

	HTMLAPI_REF_TYPE	RefType;	/* How ref is used in the HTML text (HTMLAPI_REF_xxx - see list above) */
	char				*pRefText;	/* Reference's NULL-terminated text string */
	CmdId				CommandId;			/* A web server command associated with the target URL */
	HTMLAPI_URLComponent *pTargets;	/* Reference's target components */
	HTMLAPI_URLComponent	*pArgs;		/* Reference's arguments (eg, &Start=xxx, &Count=xxx, etc). */
	DWORD				NumTargets;	/* Number of components in the target part of the reference (dbname, unid, etc.) */
	DWORD				NumArgs;	/* Number of components in the args part of the reference (&Start, etc.) */
	char				*pFragment; /* NULL-terminated LMBCS text string -- the fragment part of URL
										if there is no fragment, pointer points to "" (i.e. '\0') */

	/* The rest of struct is variable in length.  Use the pointers
	 * in the elements above here to access data from here on down.
	 */
	HTMLAPI_URLComponent URLParts[1];	/* C trick to align first member of an array of target and arg values */
								/* Then come the reference's target strings, arg strings, and text string */
} HTMLAPIReference;


/*
 * operatons dealing with references
 */

STATUS LNPUBLIC HTMLGetReference (HTMLHANDLE hHTML, DWORD Index, MEMHANDLE *phRef);
/*
 *	Input:
 *		HTMLHANDLE - handle to the converter.
 *		DWORD Index - zero relative index of the reference in the list of
 *						references
 *
 *	Output:
 *		MEMHANDLE - memory handle of reference.  The handle is to a COPY of the reference
 *			information.
 *
 *	Caller is responsible for freeing the memory.
 *	Call HTMLLockAndFixupReference on 'phRef' in order to access the reference data.
 */

STATUS LNPUBLIC HTMLSetReferenceText (HTMLHANDLE hHTML, DWORD Index, char *pRefText);
/*
 * Change the text associated with a reference.
 * Input:
 *		hHTML - handle to converter
 *		Index - index of the reference to get the new text
 *		pRefText - null terminated string -- the new reference text.
 *
 */

STATUS LNPUBLIC HTMLLockAndFixupReference (MEMHANDLE hRef, HTMLAPIReference **ppRef);
/*
 * Prepare a reference for use.
 * Input:
 *		'hRef'- memory handle to reference list (this was returned from HTMLGetReference)
 *					If this is NULLMEMHANDLE then nothing happens (no error status)
 *
 * Output:
 *		ppRef - is the address of a pointer.  The pointer will be set to point into the locked and
 * 			fixedup memory.  If hRef is not null then this must not be null
 *
 * Notes:
 * 	- This needs to be called before the reference information can be accessed.
 *		- does not use HTMLHANDLE.
 * 	- caller is responsible for unlocking the MEMHANDLE.
 */



/*
 *	CONVERT ROUTINES
 *	================
 *
 *	These are used to convert notes to HTML.  The results of a ConvertXXX routine are
 * 	retained in the converter object (until the next "convert") and are retrieved with GetText().
 */
STATUS LNPUBLIC HTMLConvertNote	(HTMLHANDLE hHTML,
					DBHANDLE hDB, NOTEHANDLE hNote,
					DWORD NumArgs, HTMLAPI_URLComponent *pArgs);
/*
 * Convert the hNote in the database hDB to HTML.
 * Arguments can be supplied to that augment and modify the conversion.
 * NumArgs indicates the number of arguments, while pArgs is a pointer to an array containing
 * the arguments.  Only values from the HTMLAPI_URLComponent.Arg branch are valid.
 *
 * The type of the note indicated by the NOTEHANDLE determines the web engine conversion
 * to be performed, as described in the following table.  Note that the equivalent "domino
 * url command" is given for reference.  The HTML generated through this API is the same as
 * that generated for the respective url command.
 *
 *   Noteid                          Conversion
 *	   0                                Database (OpenDatabase) - usually the list of views and folders
 *                                      available in the database.
 *
 *    DEFAULT note of a given class     Depends on class (NOTE_CLASS_ICON -> OpenIcon, etc.)
 *
 *    Document note                     Convert the contents of the document (OpenDocument).  The document's
 *                                      form is used to create a HTML presentation of the document.
 *
 *    Form note                         Convert form (OpenForm - non-post HTML generated)
 *    Frameset note                     (OpenFrameset)
 *    Help note                         Convert the help document (OpenHelp)
 *    Help-about note                 	Convert the about document (OpenAbout)
 *    Icon note                         Convert the database icon (OpenIcon)
 *    Navigator note                    (OpenNavigator)
 *    Page note                         Convert the page to HTML (OpenPage)
 *    View note                         Convert View (OpenView - unexpanded top level of view, all entries)
 *    Other types of notes              Returns error
 *
 * The arguments that are supplied via pArgs are the same as the ones available for the url command
 * associated with the note type.  So for example, if a view note is provided, the Start= argument
 * could be provided using CmdArgID value CAI_Start.  In that case view contents would start
 * at the given spot.
 */


STATUS LNPUBLIC HTMLConvertItem	(HTMLHANDLE hHTML,
				DBHANDLE hDB, NOTEHANDLE hNote, char *pszItemName);
/*
 * Convert a specific item within a note.
 *
 * Inputs:
 *		hHTML - handle to the converter
 *		hDB - handle to open database
 *		hNote - handle to note containing item
 *		pszItemName - refers to an item within the note indicated by hNote.  The first item
 *			found with name pszItemName is converted.
 *
 * Only items of type RichText or MIME can be converted.  If the item is of
 * a different type, ERR_HTMLAPI_NOT_SUPPORTED is returned.
 */


STATUS LNPUBLIC HTMLConvertElement	(HTMLHANDLE hHTML,
			DBHANDLE hDB, NOTEHANDLE hNote, char *pszItemName,
			DWORD ItemIndex, DWORD Offset);
/*
 *	Converts a portion of a note item.
 *
 *	ItemIndex - the relative item index -- if there is more than one
 *		Item with the same pszItemName, then this indicates which
 *		one (zero relative)
 *
 *	Offset - byte offset in the Item where the element starts
 *
 * Notes:
 *		This can't be used to access arbitrary parts of the item, only
 *		images and storage links.
 *
 * Limitations:
 *		- can't access mime parts.
 */

STATUS LNPUBLIC HTMLConvertImage	(HTMLHANDLE hHTML, char *pszImageName);
/*
 *	Used to access named image (.gif) from the domino web server's icons directory.
 * Note that pszImageName is simple name of the image file -- no path names or file type
 * suffix.
 */

STATUS LNPUBLIC HTMLGetText	(HTMLHANDLE hHTML,
				DWORD StartingOffset, DWORD *pTextLength,
				char *pText);
/*
 * Retrieves the generated HTML or binary data, copying it into user supplied buffer.
 *
 * Inputs:
 *		HTMLHANDLE - handle to the converter.
 *		StartingOffset - offset into generated html indicating starting point of the copy.
 *
 *		pTextLength - pointer to value containing the maximum number of characters to be copied.
 *					The value must be <= to the size of the buffer.
 *		pText - pointer to buffer
 *
 * Output:
 *		*pTextLength - modified to contain the actual number of bytes copied
 *		*pText - modified to contain the HTML.
 *
 * Notes:
 *		If an error occures, *pTextLength is not updated.
 *		If an error occures, MIMEMaxLineLenSeen property is not updated
 */




/*** End of API Definition ***/


#ifdef __cplusplus
}
#endif

#endif /* !defined(HTMLAPI_H) */

/* eof */


#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif

