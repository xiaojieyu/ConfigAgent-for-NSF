
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

#ifndef KFM_DEFS
#define KFM_DEFS

#ifndef BSAFE_DEFS
#include "bsafe.h"						/* Get BSAFE definitions */
#endif

#ifndef MISC_DEFS
#include "misc.h"
#endif

#ifndef	NAMES_DEFS
#include "names.h"						/* Get MAXUSERNAME, etc. */
#endif

#ifndef DNAME_DEFS						/* Get DN_COMPONENTS */
#include "dname.h"
#endif

#ifndef NSF_DATA_DEFS					/* NOTEID */
#include "nsfdata.h"
#endif

#ifndef OSSIGNAL_DEFS
#include "ossignal.h"
#endif

#ifndef NSF_DATA_DEFS         /* NOTEHANDLE */
#include "nsfdata.h"
#endif
#ifdef __cplusplus
extern "C" {
#endif
#ifndef	NULLKFHANDLE
typedef void far * KFHANDLE;
#define NULLKFHANDLE ((KFHANDLE)0)
#endif

/*	Structure returned by KFMCreatePassword to encode a password securely
	in memory to avoid scavenging. 

	NOTE:	This structure is to inclue information on the password hash
			ONLY.  The 'Type' field is expected to take other values as the
			product evolves, but will always have the semanitics of how
			the hash was constructed, and which bytes in the 
			'HashedPassword' field contain the actual hash bytes.  Sometimes
			more than one hash will be stored in the hash array.
*/

typedef struct
	{
	BYTE	Type;				/* Type of hash.  This value should be		*/
								/* interpreted only by the lower Notes 		*/
								/* layers and never by software above the	*/
								/* ABPI layer.								*/
								/* hook for future compatibility.			*/
	BYTE	HashedPassword [48];  /* Hashed password						*/
	}
	KFM_PASSWORD;

typedef DHANDLE HCERTIFIER;	
#define NULLHCERTIFIER ((HCERTIFIER)0)
#define MAXRAS 8
#define KFM_ui_GetUserInfo				 1

/*	Function codes for routine SECKFMGetPublicKey
*/

#define KFM_pubkey_Primary				0
#define KFM_pubkey_International		1
#define MAX_IDRecovery_CustomMessage	512

STATUS LNPUBLIC SECKFMUserInfo			(WORD Function, 
										 char far *lpName, 
										 LICENSEID far *lpLicense);
STATUS LNPUBLIC SECKFMGetUserName		(char far *retUserName);

STATUS LNPUBLIC SECKFMSwitchToIDFile	(char	*pIDFileName
										,char	*pPassword
										,char	*pUserName
										,WORD	MaxUserNameLength
										,DWORD	ReservedFlags
										,void	*pReserved
										);								

typedef BOOL (LNCALLBACKPTR SECGETSIGNERINFOPROC)
											(void  *pCallCtx
											,void  *pCert
											,DWORD CertSize
											,WORD  Reserved1
											,WORD  Reserved2
											);

typedef BOOL (LNCALLBACKPTR SECNABENUMPROC)	(void  *pCallCtx
											,void  *pCert
											,DWORD CertSize
											,WORD  Reserved1
											,WORD  Reserved2
											);


STATUS LNPUBLIC SECGetSignerInfoFromMail	(DHANDLE	hMailNote
											,SECGETSIGNERINFOPROC CallBack
											,void 	*pCallCtx
											,DWORD	ReservedFlags
											,void	*pReserved
											);


STATUS LNPUBLIC SECNABEnumerateCertificates	(NOTEHANDLE		hNote
											,SECNABENUMPROC	CallBack
											,void			*pCallCtx
											,DWORD			ReservedFlags
											,void			*pReserved
											);

STATUS LNPUBLIC SECNABAddCertificate	(NOTEHANDLE	hNote
										,void		*pCertificate
										,DWORD		CertificateSize
										,DWORD		ReservedFlags
										,void		*pReserved
										);

STATUS LNPUBLIC SECNABRemoveCertificate (NOTEHANDLE	hNote
										,void	*pCertificate
										,DWORD  CertificateSize
										,DWORD	ReservedFlags
										,void	*pReserved
										);

#define fKFM_switchid_DontSetEnvVar			0x0008

STATUS LNPUBLIC SECKFMGetCertifierCtx   (char far		  *pCertFile, 
										 KFM_PASSWORD far *pKfmPW,
										 char far		  *pLogFile, 
										 TIMEDATE far	  *pExpDate, 
										 char far		  *retCertName,
										 HCERTIFIER far   *rethKfmCertCtx,
										 BOOL far		  *retfIsHierarchical, 
										 WORD far		  *retwFileVersion);

STATUS LNPUBLIC SECKFMGetCertifierCtxExt   
										(char far		  *pCertFile, 
										 KFM_PASSWORD far *pKfmPW,
										 char far		  *pCAServer,
										 char far		  *pCAName,
										 char far		  *pLogFile, 
										 TIMEDATE far	  *pExpDate, 
										 char far		  *retCertName,
										 HCERTIFIER far   *rethKfmCertCtx,
										 BOOL far		  *retfIsHierarchical, 
										 WORD far		  *retwFileVersion);

VOID   LNPUBLIC SECKFMFreeCertifierCtx	(HCERTIFIER hKfmCertCtx);

VOID   LNPUBLIC SECKFMCreatePassword	(char far		  *pPassword
										,KFM_PASSWORD far *retHashedPassword
										);
STATUS LNPUBLIC SECKFMSetCertifierExpiration   (HCERTIFIER hKfmCertCtx,
												TIMEDATE far *pExpirationDate);
STATUS LNPUBLIC SECKFMGetPublicKey		(char far	*pName
										,WORD		Function
										,WORD		Flags
										,DHANDLE far *rethPubKey
										);
STATUS LNPUBLIC SECKFMChangePassword    (char far   *pIDFile
										,char far   *pOldPassword
										,char far   *pNewPassword
										);


/*	Constants used to indicate various types of IDs that can be created. */

#define KFM_IDFILE_TYPE_FLAT	0	/* Flat name space (V2 compatible)		*/
#define KFM_IDFILE_TYPE_STD		1	/* Standard (user/server hierarchical)	*/
#define KFM_IDFILE_TYPE_ORG		2	/* Organization certifier				*/
#define KFM_IDFILE_TYPE_ORGUNIT	3	/* Organizational unit certifier		*/
#define KFM_IDFILE_TYPE_DERIVED 4	/* Derived from certifer context.		*/
									/*  hierarchical => STD					*/
									/*  non-hierarchical => FLAT			*/ 
#define KFM_IDFILE_TYPE_INET	5	/*	Internet certifier.					*/

typedef	struct{
	WORD	Quorum;
	WORD	NumberOfRAs;
	WORD	RALength[MAXRAS];
	char	RAs[MAXRAS][MAXUSERNAME+1];
	WORD	RecoveryPasswordLength;
	char	MailAddress[MAXPATH+1];
	char	CustomMsg[MAX_IDRecovery_CustomMessage];
} RECOVERY_INFO;

STATUS LNPUBLIC SECGetRecoveryInfo (KFHANDLE	hKFC, 
									  DHANDLE	hNote,
									  DHANDLE	*rethRecoveryInfo,
									  DWORD		*retRecoveryInfoSize,
									  RECOVERY_INFO *retRecoveryInfo,
									  void	*pReserved,
									  DWORD	ReservedFlags);

STATUS LNPUBLIC SECImportRecoveryInfo (KFHANDLE	hKFC,
									DHANDLE	hRecoveryInfo,
									DWORD	RecoveryInfoSize,
									void	*pReserved,
									DWORD	ReservedFlags);

STATUS LNPUBLIC SECMailRecoveryID (char	*pIDFileName,
								KFM_PASSWORD *pIDFilePassword,
								char	*pSubjectText, 
								char	*pMailFileName,
								void	*pReserved,
								DWORD	ReservedFlags);

STATUS LNPUBLIC SECRecoverIDFile (char	*pIDFileName,
								WORD	NumPasswords,
								char	*pPassword[8],
								char	*pNewPassword,
								WORD	NewPasswordLen,
				  				void	*pReserved,
								DWORD	ReservedFlags);

STATUS LNPUBLIC SECExtractRecoveryPassword (KFHANDLE	hKFC,
											char	*pIDFileName,
											char	*retRecoveryPassword,
											WORD	MaxRecoveryPasswordLength,
											WORD	*retRecoveryPasswordLen,
											TIMEDATE *retCreationTimeDate,
											TIMEDATE *retAcceptanceTimeDate,
											void	*pReserved,
											DWORD	ReservedFlags);

STATUS LNPUBLIC SECBuildEncryptedBackupIDFile (char		*pIDFileName, 
												KFM_PASSWORD *pIDFilePassword,
												char	*pBackupIDFileName,
												char	*retRepositoryBuf,
												DWORD	MaxRepositoryBufLen,
												DWORD	*retRepositoryBufLen,
												void	*pReserved,
												DWORD	ReservedFlags);

typedef void far * SCMCTX;
#define NULLSCMCTX ((SCMCTX) 0)
#define SC_MANIP_VERSION 8

/* Opcodes defined for SECManipulateSC
*/
#define SC_manip_GetVersion		   1
#define SC_manip_InitializeContext 2
#define SC_manip_TerminateContext  3
#define SC_manip_CheckCard         4
#define SC_manip_EnterIDFile	   5
#define SC_manip_EnterPIN		   6
#define SC_manip_SCEnableID		   7
#define SC_manip_PushInetKey	   8
#define SC_manip_FindMatchedCerts  9
#define SC_manip_GetMatchedCert	  10
#define SC_manip_ImportInetCert   11
/* Opcode added in 6.0.3 */
#define SC_manip_RefreshTokenInfo 12
/* Opcodes added in 7.0 */
#define SC_manip_PushKyrKey       13
#define SC_manip_PushNotesKey	  14
#define SC_manip_EnterIDPassword  15
#define SC_manip_FindAllKeys      16
#define SC_manip_LockIDWithKeyRO  17
#define SC_manip_LockIDWithKeyRnd 18
/* Opcodes added in 7.0.2 */
#define SC_manip_PushInetKeyAndCert 19
#define SC_manip_PushKyrKeyAndCert  20


/* Structure used for SC_manip_GetMatchedCerts 
*/
typedef struct
{
	DWORD Version;     /* This typedef describes version 0 */
	DWORD dwSize; 
	DWORD dwUnused;
	DWORD retIDLen;
	DWORD retLabelLen;
	DWORD retCertLen;
	DWORD IDOffset;    /* Offset in bytes from beginning of structure */
	DWORD LabelOffset; /* Offset in bytes from beginning of structure */
	DWORD CertOffset;  /* Offset in bytes from beginning of structure */
	/* ID */
	/* Label */
	/* Cert */
}
SC_MANIP_IMPORTABLE_CERT;

STATUS LNPUBLIC SECManipulateSC (DWORD  OpCode,
								 SCMCTX *pContext,
								 DWORD  *pdwFlags,
								 DWORD  *pdwParam1,
								 void   *pvParam2);


#define SECKFM_open_All				0x00000001

#define SECKFM_close_WriteIdFile	0x00000001

STATUS LNPUBLIC SECKFMOpen (KFHANDLE *phKFC,
							char	 *pIDFileName,
							char	 *pPassword,
							DWORD	 Flags,
							DWORD	 Reserved,
							void	 *pReserved);

STATUS LNPUBLIC SECKFMClose (KFHANDLE *phKFC,
							 DWORD 	  Flags,
							 DWORD 	  Reserved,
							 void	  *pReserved);

STATUS LNPUBLIC SECAttachIdFileToDB (DBHANDLE hDB,
										char  	*pProfileNoteName,
										DWORD 	ProfileNoteNameLength,
										char  	*pUserName,
										DWORD	UserNameLength,
										char	*pIDFileName,
										char	*pPassword,
							   			DWORD 	Reserved,
							   			void	 *pReserved);


STATUS LNPUBLIC SECExtractIdFileFromDB (DBHANDLE hDB,
										char  	*pProfileNoteName,
										DWORD 	ProfileNoteNameLength,
										char  	*pUserName,
										DWORD	UserNameLength,
										char	*pPassword,
										char	*pPutIDFileHere,
							   			DWORD 	Reserved,
							   			void	 *pReserved);

#define SEC_refreshed_NotesCerts	0x00000001
#define SEC_refreshed_InternetCerts	0x00000002
#define SEC_refreshed_UserName		0x00000004
#define SEC_refreshed_PasswordPolicy 0x00000008

STATUS LNPUBLIC SECRefreshIdFile (char	*pIDFileName, 
								  char	*pPassword,
								  char	*pServer,
								  DWORD	*retFlags,
								  DWORD Reserved,
							   	  void	 *pReserved);
STATUS LNPUBLIC NSFDB2GetUsernamePW(char *ServerName, 
										char * pFilename, 
										KFM_PASSWORD *pKfmPW, 
										char *retUserName, 
										char *retPassword);
STATUS LNPUBLIC NSFDB2PutUsernamePW(char *ServerName, 
										char * pFilename, 
										char *UserName, 
										char *Password, 
										KFM_PASSWORD *pKfmPW);
STATUS LNPUBLIC NSFDB2DeleteUsernamePW(char *ServerName, 
											char * pFilename, 
											KFM_PASSWORD *pKfmPW);

#ifdef __cplusplus
/* End brace for extern "C" */
}
#endif

#endif /* KFM_DEFS */



#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif

