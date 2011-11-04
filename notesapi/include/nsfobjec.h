
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/* ***************************************************************** */
/*                                                                   */
/* Licensed Materials - Property of IBM                              */
/*                                                                   */
/* L-GHUS-76ALVG, L-GHUS-76ALWH                                      */
/*                                                                   */
/* Copyright IBM Corp. 1989, 2007  All Rights Reserved.              */
/*                                                                   */
/* US Government Users Restricted Rights - Use, duplication or       */
/* disclosure restricted by GSA ADP Schedule Contract with           */
/* IBM Corp.                                                         */
/*                                                                   */
/* ***************************************************************** */

#ifndef NSF_OBJECT_DEFS
#define NSF_OBJECT_DEFS

#ifndef NSF_DEFS
#include "nsfdata.h"
#endif


#ifdef __cplusplus
extern "C" {
#endif

/* Note Storage File Object Package Definitions */

/*	Available across the network */

#if !defined(NSFDbAllocObject)
STATUS LNPUBLIC NSFDbAllocObject (DBHANDLE hDB, DWORD dwSize,
								WORD Class,
								WORD Privileges,
								DWORD far *retObjectID);
#endif


#if !defined(NSFDbReallocObject)
STATUS LNPUBLIC NSFDbReallocObject (DBHANDLE hDB, DWORD ObjectID, DWORD NewSize);
#endif

#if !defined(NSFDbFreeObject)
STATUS LNPUBLIC NSFDbFreeObject (DBHANDLE hDB, DWORD ObjectID);
#endif

#if !defined(NSFDbGetObjectSize)
STATUS LNPUBLIC NSFDbGetObjectSize (DBHANDLE hDB, DWORD ObjectID, WORD ObjectType,
								DWORD far *retSize,
								WORD far *retClass,
								WORD far *retPrivileges);
#endif

#if !defined(NSFDbReadObject)
STATUS LNPUBLIC NSFDbReadObject (DBHANDLE hDB, DWORD ObjectID,
								DWORD Offset, DWORD Length,
								DHANDLE far *rethBuffer);
#endif

#if !defined(NSFDbWriteObject)
STATUS LNPUBLIC NSFDbWriteObject (DBHANDLE hDB, DWORD ObjectID,
								DHANDLE hBuffer,
								DWORD Offset, DWORD Length);
#endif

/* End of Note Storage File Object Package */


#ifdef __cplusplus
}
#endif

#endif


#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif

