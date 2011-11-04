
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

/*	ID Table Routines
*
*	This package is used to create and manipulate tables that contain
*	compressed double-word values that typically represent IDs.  The
*	primitives allow the caller to create an ID table, add or delete IDs,
*	and query for the presence of an ID.
*
*	Compression of the table is achieved by virtue of the fact that it
*	is assumed that the ID space is relatively "regular", that is, that
*	ID values differ from each other by some regular value, say 4.
*
*	ID tables are always stored in Canonical format.
*
*	(This .H file is global so that the ODS routines can access it; all
*	 access to the following structures should be via the programmatic
*	 interfaces provided.)
*/

#ifndef IDTABLE_DEFS
#define IDTABLE_DEFS


#define IDTABLE_MODIFIED 	0x0001	/* modified - set by Insert/Delete */
									/* and can be cleared by caller if desired */
#define IDTABLE_INVERTED	0x0002	/* sense of list inverted */
									/* (reserved for use by caller only) */

/*	Function Declarations */

STATUS LNPUBLIC IDCreateTable (DWORD Alignment, DHANDLE far *rethTable);
STATUS LNPUBLIC IDDestroyTable(DHANDLE hTable);
STATUS 	LNPUBLIC IDInsert (DHANDLE hTable, DWORD id, BOOL far *retfInserted);
STATUS 	LNPUBLIC IDDelete (DHANDLE hTable, DWORD id, BOOL far *retfDeleted);
STATUS 	LNPUBLIC IDDeleteAll (DHANDLE hTable);
BOOL	LNPUBLIC IDScan (DHANDLE hTable, BOOL fFirst, DWORD far *retID);
typedef STATUS (LNCALLBACKPTR IDENUMERATEPROC)
					(void far *Parameter, DWORD id);
STATUS	LNPUBLIC IDEnumerate (DHANDLE hTable,
								IDENUMERATEPROC Routine,
								void far *Parameter);
DWORD	LNPUBLIC IDEntries (DHANDLE hTable);
BOOL	LNPUBLIC IDIsPresent (DHANDLE hTable, DWORD id);
DWORD	LNPUBLIC IDTableSize (DHANDLE hTable);
STATUS	LNPUBLIC IDTableCopy (DHANDLE hTable, DHANDLE far *rethTable);
DWORD	LNPUBLIC IDTableSizeP (void far *pIDTable);
WORD	LNPUBLIC IDTableFlags (void far *pIDTable);
TIMEDATE LNPUBLIC IDTableTime (void far *pIDTable);
void	LNPUBLIC IDTableSetFlags (void far *pIDTable, WORD Flags);
void	LNPUBLIC IDTableSetTime (void far *pIDTable, TIMEDATE Time);
STATUS  LNPUBLIC IDTableIntersect	(DHANDLE hSrc1Table,DHANDLE hSrc2Table,DHANDLE *rethDstTable);
BOOL	LNPUBLIC IDAreTablesEqual	(DHANDLE hSrc1Table, DHANDLE hSrc2Table);
STATUS	LNPUBLIC IDDeleteTable  (DHANDLE hTable, DHANDLE hIDsToDelete);
STATUS	LNPUBLIC IDInsertTable  (DHANDLE hTable, DHANDLE hIDsToAdd);


#endif


/*	End of ID Table Routines */

#ifdef __cplusplus
}
#endif


#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif

