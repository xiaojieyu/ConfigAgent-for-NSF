
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/*********************************************************************/
/*                                                                   */
/* Licensed Materials - Property of IBM                              */
/*                                                                   */
/* L-GHUS-76ALVG, L-GHUS-76ALWH                                      */
/*                                                                   */
/* Copyright IBM Corp. 2002, 2007  All Rights Reserved.              */
/*                                                                   */
/* US Government Users Restricted Rights - Use, duplication or       */
/* disclosure restricted by GSA ADP Schedule Contract with           */
/* IBM Corp.                                                         */
/*                                                                   */
/*********************************************************************/

//______________________________________________________________________
//
//		File:		nlookup.h
//
//______________________________________________________________________


#if !defined(NLOOKUP_H)
#define NLOOKUP_H


#ifdef __cplusplus
extern "C" {
#endif

/* nlookup.cpp */

typedef struct {
	char		*pUserName;
	char		*pAltUserName;
	char		*pAltUserNameLang;
	char		*pOldWebName;
	char		*pInternetAddress;
	char		*pSSOTokenUserName;
	void		*pReserved;
} NABLOOKUP_RECORD;

//---
//		Routines exposing NAB lookup class via C for the SDK
//

STATUS LNPUBLIC NABLookupOpen( void **retpNABLookup, DWORD dwReserved, void *vpReserved );
STATUS LNPUBLIC NABLookupAuthenticatedUser( void *pNABLookup,
								  char	*orgName,
								  char	*user,
								  DWORD	flags,
								  NABLOOKUP_RECORD	*pRetNabLookupRecord,
								  DWORD dwNablookupRecordSize,
								  DWORD dwReserved,
								  void *vpReserved );
void LNPUBLIC NABLookupClose( void **pNABLookup,
							 void *pNabLookupRecord,
							 DWORD dwNablookupRecordSize,
							 DWORD dwReserved,
							 void *vpReserved );
#ifdef __cplusplus
}
#endif


#endif // NLOOKUP_H

#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif

