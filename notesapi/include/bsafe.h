
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

/* BSAFE (Security Package) interface definitions */

#ifndef	BSAFE_DEFS
#define	BSAFE_DEFS

#define SEC_ai_RC2_CBC_BSAFE1           3
#define SEC_ai_RSAPrivate_BSAFE1        4
#define SEC_ai_RSAPublic_BSAFE1         5
#define SEC_ai_RSAPrivate_PKCS1        16
#define SEC_ai_RC2_CBC_PAD			   19
#define SEC_ai_RSAPublic_PKCS1		   20
#define SEC_ai_AES_PKCS5               27
#define SEC_ki_RSAPrivate_BSAFE1        3
#define SEC_ki_RSAPublic_BSAFE1         4
#define SEC_ki_RSAPublic_BER            5
#define SEC_ki_RSAPrivate_BER           6
#define SEC_ki_RC2_FromRawKey           7
#define SEC_ki_AES                     27
#ifdef __cplusplus
extern "C" {
#endif

STATUS LNPUBLIC SECAttachToID (void);		/* Don't let parent process 	*/
											/* control our ID file.			*/
STATUS LNPUBLIC SECReattachToRootID (void);	/* Resync ID file with our		*/
											/* root process but remain		*/
											/* attached to the new	file.	*/

#define	fSECToken_EnableRenewal		0x0001


typedef struct
	{
	MEMHANDLE	mhName;
	MEMHANDLE	mhDomainList;
	WORD		wNumDomains;
	BOOL		bSecureOnly;
	MEMHANDLE	mhData;
	}
	SSO_TOKEN;

/* SSO Formats */
typedef enum {
	SECTOKENFORMAT_UNKNOWN = 0,
	SECTOKENFORMAT_LTPATOKEN,
	SECTOKENFORMAT_LTPATOKEN2
} SECTOKENFORMAT;


typedef struct									/* Structure to store returned Ltpa tokens in a list.		*/
	{						
	MEMHANDLE					mhSelf;			/* Memory allocated for this struct 						*/
	SECTOKENFORMAT				TokenType;
	MEMHANDLE					mhToken;
	SSO_TOKEN					*pToken;		/* locked pointer to token allocated in mhToken				*/
	void						*pNext;			/* struct SSO_LTPA_TOKEN_LIST * to next struct in list	*/
	}
	SSO_LTPA_TOKEN_LIST;

typedef struct					/* Structure to store info found	*/
	{							/* in the LtpaToken2 data area.	    */
	MEMHANDLE					mhSelf;
	MEMHANDLE					mhKey;
	char						*pKey;
	DWORD						dwKeyLength;
	MEMHANDLE					mhValue;
	char						*pValue;
	DWORD						dwValueLength;
	void						*pNext; /* struct SSO_LTPA2_ATTR  * pointer */
	}
	SSO_LTPA2_ATTR;

#define	SECTOKEN_RETURN_USERNAME				0x00000001
#define	SECTOKEN_RETURN_ATTRIBUTE_LIST			0x00000002
#define	SECTOKEN_RETURN_RENEWAL_TIME			0x00000004
#define	SECTOKEN_RETURN_RAWTOKENUSERNAME		0x00000008

typedef struct					/* Structure to store info found	*/
	{							/* in the SSO token.			    */
	MEMHANDLE		mhItem;
	char			*ptr;
    DWORD			dwLength;
	}
	SSO_TOKEN_ITEM;

typedef struct					/* Structure to describe info found	*/
	{							/* in the SSO token.			    */
	DWORD					dwStructVersion; /* currently must be set to 0 */
	DWORD					dwTokenVersion; /* currently not used */
	SECTOKENFORMAT			TokenType;
	SSO_TOKEN_ITEM			Username;
	SSO_TOKEN_ITEM			RawTokenUsername;
	TIMEDATE				Creation;
	TIMEDATE				Expiration;
	SSO_LTPA2_ATTR 			*AttributesList;
	void					*vpReservedTiming;
	void					*vpReserved;
	}
	SSO_TOKEN_INFO_DESC;


typedef SSO_LTPA_TOKEN_LIST *PSSO_LTPA_TOKEN_LIST;

typedef SSO_LTPA2_ATTR *PSSO_LTPA2_ATTR;


/* For creating one or more SSO tokens according to configuration.
 * The caller can request information about the preferred token (first) in the list.  The
 * output is to be returned in retpInfo struct.
 * Optional output is requested by setting the dwRequestedInfoFlags.  Currently supported flags:
 *  SECTOKEN_RETURN_RAWTOKENUSERNAME - return the user name exactly as it appears in the token.
 *  SECTOKEN_RETURN_RENEWAL_TIME - return renewal information that may apply in Domino-only configurations 
 *                                  supporting idle session timeout.  A pointer to the renewal timedate
 *                                  is returned in retpInfo->vpReservedTiming.
 * If dwRequestedInfoFlags is non-zero, the caller must free the resources associated with the output 
 * retpInfo by calling SECTokenFreeInfo().
 */
STATUS LNPUBLIC SECTokenListGenerate(	
	char				*ServerName,		/* Reserved as NULL (ignored) */
	char				*OrgName,
	char				*ConfigName,	
	char				*UserName,
	TIMEDATE			*Creation,
	TIMEDATE			*Expiration,
	void				*pAttributes, 		/* currently ignored, for future use as input */
	DWORD				dwRequestedInfoFlags,
	SSO_TOKEN_INFO_DESC	*retpInfo,
	SSO_LTPA_TOKEN_LIST	**retpTokenList,	/* return pointer to the token list */
	DWORD				dwReserved,
	void				*vpReserved
	);

/* For freeing one or more SSO tokens in the list created by SECTokenListGenerate() */
void LNPUBLIC SECTokenListFree(
	SSO_LTPA_TOKEN_LIST **pTokenList,
	DWORD				dwReserved,
	void				*vpReserved
	);

/* For freeing token information returned by SECTokenListGenerate(), SECTokenListValidate(), SECTokenValidate2() */
void LNPUBLIC SECTokenFreeInfo(
	SSO_TOKEN_INFO_DESC *pInfo,
	BOOL bFreeAll,  /* If TRUE, then free all allocated items in the pInfo struct */
	DWORD dwRequestedInfoFlags ); /* If bFreeAll is FALSE, then free items associated with flags passed in. */

/* For creating an SSO token (LtpaToken)  */
STATUS LNPUBLIC SECTokenGenerate(	
	char		*ServerName,	/* Reserved as NULL (ignored) */
	char		*OrgName,
	char		*ConfigName,	
	char		*UserName,
	TIMEDATE	*Creation,
	TIMEDATE	*Expiration,
	MEMHANDLE	*retmhToken,
	DWORD		dwReserved,
	void		*vpReserved
	);

/* For freeing the SSO token that was created by SECTokenGenerate() */
void LNPUBLIC SECTokenFree(
	MEMHANDLE	*mhToken
	);

/* For validating an SSO token that has been received */
STATUS LNPUBLIC SECTokenValidate(
	char		*ServerName,	/* Reserved as NULL (ignored) */
	char		*OrgName,
	char		*ConfigName,	
	char		*TokenData,
	char		*retUsername,
	TIMEDATE	*retCreation,
	TIMEDATE	*retExpiration,
	DWORD		dwReserved,
	void		*vpReserved
	);

/* For validating an SSO token that has been received.  If the token has been received in a cookie,
 * the AssumedType of token would be evident to the caller by the name of the cookie (LtpaToken vs LtpaToken2).
 * AssumedType can be set to SECTOKENFORMAT_UNKNOWN, however this may negatively impact performance.
 *
 * The caller can request information about the validated token to be returned in retpInfo struct.
 * If retpInfo is non-null, then the retpInfo will always contain this output:
 *    TokenType -- currently either SECTOKENFORMAT_LTPATOKEN or SECTOKENFORMAT_LTPATOKEN2
 *    Expiration
 *    Creation (if Domino format token)
 * Optional output is requested by setting the dwRequestedInfoFlags.  Currently supported flags:
 *  SECTOKEN_RETURN_USERNAME - return the name of the user whom this token represents.
 *  SECTOKEN_RETURN_RAWTOKENUSERNAME - return the user name exactly as it appears in the token.
 *  SECTOKEN_RETURN_ATTRIBUTE_LIST - return the attribute list contained in an LtpaToken2 token.
 *  SECTOKEN_RETURN_RENEWAL_TIME - return renewal information that may apply in Domino-only configurations 
 *                                  supporting idle session timeout.  A pointer to the renewal timedate
 *                                  is returned in retpInfo->vpReservedTiming.
 * If dwRequestedInfoFlags is non-zero, the caller must free the resources associated with the output 
 * retpInfo by calling SECTokenFreeInfo().
 */
STATUS LNPUBLIC SECTokenValidate2(
	char			*ServerName,		/* Reserved as NULL (ignored) */
	char			*OrgName,
	char			*ConfigName,	
	char			*TokenData,
	SECTOKENFORMAT	AssumedType,
	DWORD			dwRequestedInfoFlags,
	SSO_TOKEN_INFO_DESC	*retpInfo,
	DWORD			dwReserved,
	void			*vpReserved
	);

/* Allocate a new entry that can be inserted into a Single Sign-On  token list.  The entry will  
 * usually just be storing a token that may need to be validated, therefore it is optional to provide 
 * domain info settings associated with the browser cookie.
 */
STATUS LNPUBLIC SECCreateTokenListEntry( SECTOKENFORMAT TokenType, 
								 char *pToken, 	/* a locked pointer to the token */
 								 char *pTokenName, /* e.g. LtpaToken */
								 char *pDomainList, /* locked pointer (currently always one domain only), or NULL*/
                                 WORD wNumDomains, /* if non-zero, should currently always be 1 */
								 BOOL bSecureOnly, /* currently always set to FALSE */
								 SSO_LTPA_TOKEN_LIST **retpEntry,
                                 DWORD dwReserved,
                                 void *vpReserved);

/* Validate the input Single Sign-On token list. The list can contain one or more tokens.
 * The info returned will be the info based on the token pointed to by the returned
 * retpValidatedToken, which is, according to the configuration, the preferred token in the list.  If 
 * the caller wants to validate each token individually, the caller should use SECTokenValidate2 
 * instead for each token (because this routine only returns results for the preferred token in the list).
 * The caller can request a compatibility token in retpCompatibilityToken, which would be returned only
 * if the configuration is in compatibility mode and if the pTokenList does not already contain both
 * LtpaToken and LtpaToken2. If a compatibility token is returned, it must be freed by the caller.
 *
 * The caller can request information about the validated token to be returned in retpInfo struct.
 * If retpInfo is non-null, then the retpInfo will always contain this output:
 *    TokenType -- currently either SECTOKENFORMAT_LTPATOKEN or SECTOKENFORMAT_LTPATOKEN2
 *    Expiration
 *    Creation (if Domino format token)
 * Optional output is requested by setting the dwRequestedInfoFlags.  Currently supported flags:
 *  SECTOKEN_RETURN_USERNAME - return the name of the user whom this token represents.
 *  SECTOKEN_RETURN_RAWTOKENUSERNAME - return the user name exactly as it appears in the token.
 *  SECTOKEN_RETURN_ATTRIBUTE_LIST - return the attribute list contained in an LtpaToken2 token.
 *  SECTOKEN_RETURN_RENEWAL_TIME - return renewal information that may apply in Domino-only configurations 
 *                                  supporting idle session timeout.  A pointer to the renewal timedate
 *                                  is returned in retpInfo->vpReservedTiming.
 * If dwRequestedInfoFlags is non-zero, the caller must free the resources associated with the output 
 * retpInfo by calling SECTokenFreeInfo().
 */
STATUS LNPUBLIC SECTokenListValidate(
										char				*ServerName,
										char				*OrgName,
										char				*ConfigName,	
										SSO_LTPA_TOKEN_LIST	*pTokenList,
										SSO_LTPA_TOKEN_LIST	**retpValidatedToken,
										DWORD				dwRequestedInfoFlags,
 										SSO_TOKEN_INFO_DESC	*retpInfo,
										SSO_LTPA_TOKEN_LIST	**retpCompatibilityToken,
										DWORD				dwReserved,
										void				*vpReserved
										);

/* For freeing the attribute list returned by SECTokenValidate2() or SECTokenListValidate() */
void LNPUBLIC SECTokenFreeAttrList (SSO_LTPA2_ATTR **pAttrList,
									DWORD dwReserved,
									void *vpReserved
									);

STATUS LNPUBLIC SECGetSSONameMappingConfig	(
	char		*ServerName, 	/* Reserved as NULL (ignored) */
	char		*OrgName,
	char		*ConfigName,
	BOOL		*retbNameMapping,
	DWORD		dwReserved,
	void		*vpReserved
	);


#ifdef __cplusplus
}
#endif

#endif /* BSAFE_DEFS */

#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif

