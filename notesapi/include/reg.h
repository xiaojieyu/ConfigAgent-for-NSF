
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/* ***************************************************************** */
/*                                                                   */
/* Licensed Materials - Property of IBM                              */
/*                                                                   */
/* L-GHUS-76ALVG, L-GHUS-76ALWH                                      */
/*                                                                   */
/* Copyright IBM Corp. 1993, 2007  All Rights Reserved.              */
/*                                                                   */
/* US Government Users Restricted Rights - Use, duplication or       */
/* disclosure restricted by GSA ADP Schedule Contract with           */
/* IBM Corp.                                                         */
/*                                                                   */
/* ***************************************************************** */

#ifdef __cplusplus
extern "C" {
#endif

#ifndef	USERREG_DEFS
#define	USERREG_DEFS

#ifndef NAME_DEFS
#include "names.h"
#endif

#ifndef KFM_DEFS
#include "kfm.h"
#endif

#ifndef OSFILE_DEFS
#include "osfile.h"
#endif

#ifndef NSF_DATA_DEFS
#include "nsfdata.h"			/* for DBHANDLE */
#endif


/* 	Definitions ---------------------------------------------------------- */
/* The following InfoType codes are defined for REGGetIDInfo */
/* Note that the Certifier Flag can only exist on a hierarchical ID */
/* and that Certifier, NotesExpress, and Desktop flags are not */
/* present in safe copies of ID files */

#define REGIDGetUSAFlag				1
/* Data structure returned is BOOL */

#define REGIDGetHierarchicalFlag	2
/* Data structure returned is BOOL */

#define REGIDGetSafeFlag			3
/* Data structure returned is BOOL */

#define REGIDGetCertifierFlag		4
/* Data structure returned is BOOL */

#define REGIDGetNotesExpressFlag	5
/* Data structure returned is BOOL */

#define REGIDGetDesktopFlag			6
/* Data structure returned is BOOL */

#define REGIDGetName				7
/* Data structure returned is char xx[MAXUSERNAME] */

#define REGIDGetPublicKey			8
/* Data structure returned is char xx[xx] */

#define REGIDGetPrivateKey			9
/* Data structure returned is char xx[xx] */

#define REGIDGetIntlPublicKey		10
/* Data structure returned is char xx[xx] */

#define REGIDGetIntlPrivateKey		11
/* Data structure returned is char xx[xx] */


typedef void (LNCALLBACKPTR REGSIGNALPROC)(char far *);
typedef WORD REGFlags;
typedef DWORD REGFlagsExt;

/* The following bits are defined in REGFlags
*
*  NOTE: fREGCreateMailFileUsingAdminp and fREGCreateMailFileNow are mutually exclusive.
*  If both flags are specified, then fREGCreateMailFileNow is the action
*  that will be performed.
*/
#define fREGCreateIDFileNow				0x0001
#define fREGUSARequested				0x0002
#define fREGCreateMailFileNow			0x0004
#define fREGCreateAddrBookEntry			0x0008
#define fREGOkayToModifyID				0x0010
#define fREGOkayToModifyAddrbook		0x0020
#define fREGSaveIDInFile				0x0040
#define fREGCreateLimitedClient			0x0080
#define fREGCreateDesktopClient			0x0100
#define fREGSaveIDInAddrBook			0x0200
#define fREGCreateMailFileUsingAdminp	0x0800	/* use admin process to create mail file */
#define fREGSetInternetPassword			0x1000	/* user only */
#define fREGSetDB2Access				0x1000	/* Server only */

#define fREGExtCreateMailFTIndex		0x00000001
#define fREGExtReturnPersonNote			0x00000002
#define fREGExtEnforceUniqueShortName	0x00000004
#define fREGExtRoamingUserNow			0x00000200
#define fREGExtRoamingFilesUsingAdminp	0x00000400
#define fREGExtCreateINetKeyPair		0x00001000
#define fREGExtMailReplicasUsingAdminp	0x00008000
#define fREGExtRoamingReplicasUsingAdminp	0x00040000
#define fREGExtRegUsingPolicy				0x00100000

/*  Use the structure below with REGNewPerson, REGNewCertifierExtended, REGNewServerExtended2 entire structure must
be initialized to zero */ 
typedef struct
	{
	DWORD	Size;				/* size of this structure - must initialize with sizeof (REG_ID_INFO) */
	WORD	Type;				/* see KFM_IDFILE_??? */
	WORD	KeyWidth;			/*	size of the key in bits:
									0 - default
									630 - Compatible with all releases
									1024 - Compatible with N/D6 and later
								*/
	WORD	PasswordKeyWidth;	/*	size of the key in bits: 
									0 - default (means an appropriate key width and type
										is selected based on the KeyWidth)
									64 - 64 bits (RC2)
									128 - 128 bits (RC2 or AES)
									256 - 256 bits (AES)
									The top nibble is a bitmask of flags as defined below
								*/
	char	*FileName;
	DWORD	Reserved[4];
	void	*pReserved[4];
	} REG_ID_INFO;

/*	Flags in top nibble of PasswordKeyWidth */
#define REG_ID_PWD_KEY_SIZE_MASK	0x0FFF	/* Bitmask for key size bits */
#define REG_ID_PWD_KEY_FLAGS_MASK	0xF000	/* Bitmask for top nibble of flags */
#define REG_ID_PWD_KEY_AES			0x1000	/* Key type is AES (if clear, key type is RC2) */

/*  Use the structure below with REGNewPerson, REGNewCertifierExtended, REGNewServerExtended2 entire structure must 
be initialized to zero */
typedef struct
	{
	DWORD		Size;			/* size of this structure - must initialize with sizeof (REG_MISC_INFO) */
	char		*Location;
	char		*Comment;
	char		*LocalAdminName;
	DWORD		Reserved[4];
	void		*pReserved[4];
	} REG_MISC_INFO;

/*  Use the structure below with REGNewServerExtended2 entire structure must be initialized to zero */
typedef struct
	{
	DWORD	Size;		/* size of this structure - must initialize with sizeof (REG_SERVER_INFO) */

	/* server name information */
	char	*Name;
	char	*OrgUnit;
	char	*Title;
	char	*DomainName;
	char	*NetworkName;
	char	*AdminName;

	/* server password information */
	char			*Password;
	WORD			PasswordQuality;

	/* control flags */
	REGFlags		Flags;

	/* server internet information */
	char	*HostName;
	HCERTIFIER hInternetCertCtx;
	char	*KeyringFileName;
	char	*KeyringPassword;

	/* ID file information */
	REG_ID_INFO		*IDInfo;

	/* generic information */
	REG_MISC_INFO	*MiscInfo;

	DWORD	Reserved[4];
	void	*pReserved[4];
	} REG_SERVER_INFO;

/*  Use the structure below with REGNewCertifierExtended entire structure must be initialized to zero */
typedef struct
	{
	DWORD			Size;			/* size of this structure - must initialize with sizeof (REG_CERTIFIER_INFO) */

	/* certifier name information */
	char 			*Country;
	char 			*Org;
	char 			*OrgUnit;

	/* certifier password information */
	char			*Password;
	WORD			PasswordQuality;

	/* certifier mail information */
	char 			*MailServerName;
	char 			*MailFileName;
	char 			*ForwardAddress;

	/* control flags */
	REGFlags		Flags;

	/* ID file information */
	REG_ID_INFO		*IDInfo;

	/* generic information */
	REG_MISC_INFO	*MiscInfo;
	
	DWORD	Reserved[4];
	void	*pReserved[4];
	} REG_CERTIFIER_INFO;

/*	REG_FILE_DUP_XXX defines used with
	OnDuplicate element of REG_ROAMING_INFO struct and REG_MAIL_INFO_EXT struct*/
#define REG_FILE_DUP_STOP				0
#define REG_FILE_DUP_UNIQUE				1
#define REG_FILE_DUP_OVERWRITE			2

/* Use the structure below with REGNewPerson entire structure must be initialized to zero */
typedef struct
	{
	DWORD	Size;			/* size of this structure - must initialize with sizeof (REG_MAIL_INFO_EXT) */
	WORD 	MailSystem;
	WORD 	MailOwnerAccess;
	DWORD	DbQuotaSizeLimit;
	DWORD	DbQuotaWarningThreshold;
	char 	*pMailServerName;
	char 	*pMailFileName;
	char 	*pMailTemplateName;
	char 	*pMailForwardAddress;
	char 	*pMailACLManager;
	DHANDLE	hReplicaServers;
	WORD	OnDuplicate;		/* one of REG_FILE_DUP_XXX */

	DWORD	Reserved[4];
	void	*pReserved[4];
	} REG_MAIL_INFO_EXT;


/* Use the structure below with REGNewPerson entire structure must be initialized to zero */
typedef struct
	{
	DWORD	Size;				/* size of this structure - must initialize with sizeof (REG_ROAMING_INFO) */
	char	*ServerName;		/*	server destination for three roaming files */
	char	*SubDirectory;		/*	path (relative) to data dir on which roaming files will be created */
	WORD	CleanupSetting;		/*	REG_ROAMING_CLEANUP_NEVER is don't cleanup
								  	REG_ROAMING_CLEANUP_EVERY_NDAYS is cleanup every ndays
								  	REG_ROAMING_CLEANUP_AT_SHUTDOWN is cleanup at shutdown
									REG_ROAMING_CLEANUP_PROMPT is prompt for cleanup*/
	WORD	CleanupPeriod;		/*	for REG_ROAMING_CLEANUP_EVERY_NDAYS - days, values 1 through 365 allowed */
	DHANDLE	hReplicaServers;	/* text list of replica servers */
	WORD	OnDuplicate;		/* one of REG_FILE_DUP_XXX */

	DWORD	Reserved[4];
	void	*pReserved[4];
	BOOL	bStoreIDInPNAB;		/* whether client setup should attach ID to personal address book */
	} REG_ROAMING_INFO;


/*	REG_ROAMING_CLEANUP_XXX defines used with
	CleanupSetting element of REG_ROAMING_INFO struct */
#define REG_ROAMING_CLEANUP_NEVER		0
#define REG_ROAMING_CLEANUP_EVERY_NDAYS	1
#define REG_ROAMING_CLEANUP_AT_SHUTDOWN	2
#define REG_ROAMING_CLEANUP_PROMPT		3

/*  Use the structure below with REGNewPerson entire structure must be initialized to zero */
typedef struct reg_person_info
	{
	DWORD		Size;			/* size of this structure - must initialize with sizeof (REG_PERSON_INFO) */

	/* person name information */
	char 		*LastName;
	char 		*FirstName;
	char 		*MiddleName;
	char 		*OrgUnit;
	char 		*ShortName;
	char 		*AlternateName;
	char		*AltOrgUnit;
	char		*InternetAddress;

	/* person password information */
	char		*Password;
	WORD		PasswordQuality;

	/* person internet key information */
	WORD		INetKeyWidth;

	/* person language info */
	char		*AltLanguage;
	char		*PreferredLanguage;

	/* setup profile info */
	char		*ProfileName;

	/* person group membership */
	void 		*pGroupList;

	/* policy information */
	char		*ExplicitPolicy;
	/* PolicyOverride function used when registering via policy (fREGExtRegUsingPolicy) 
	as a hook to modify registration items after policy evaluation but before 
	registration processing
	
	NOTE: As to not munge with internal memory, you should change pointers 
	to point to your memory, you should not change callback memory:
	
	Example:  To change the policy derived roaming subdirectory
	
	Don't do change callback memory buffer:
		Cstrcpy (PersonInfo->RoamingInfo->SubDirectory, "your new sub directory");

	Make the callback pointer point to your buffer:
		Cstrcpy (szYourBuffer, "your new sub directory");
		PersonInfo->RoamingInfo->SubDirectory = szYourBuffer;
	
	*/
	STATUS (LNCALLBACKPTR PolicyOverride)(HCERTIFIER hCertCtx, 
										char far **RegServer,
										struct reg_person_info far *PersonInfo);

	/* registration flags */
	REGFlags		Flags;
	REGFlagsExt		FlagsExt;

	REG_MAIL_INFO_EXT	*MailInfo;

	REG_ID_INFO		*IDInfo;
	
	REG_MISC_INFO	*MiscInfo;

	REG_ROAMING_INFO *RoamingInfo;

	/* when specified with fREGExtReturnPersonNote - return the person note and DB handle */
	NOTEHANDLE 	*phRetPersonNote;
	DBHANDLE 	*phRetPersonNoteNAB;

	DWORD	Reserved[4];
	void	*pReserved[4];
	} REG_PERSON_INFO;


/*  Use the structure below with REGNewUser */
typedef struct
	{
	char 	*LastName;
	char 	*FirstName;
	char 	*MidInitial;
	char 	*OrgUnit;
	char 	*ShortName;
	char 	*AlternateName;
	char	*AltOrgUnit;
	char	*AltLanguage;
	DWORD	Spare[4];

	} REG_USERNAME_INFO;

typedef struct
	{
	WORD 	MailSystem;
	WORD 	MailOwnerAccess;
	DWORD	DbQuotaSizeLimit;
	DWORD	DbQuotaWarningThreshold;
	char 	*pMailServerName;
	char 	*pMailFileName;
	char 	*pMailTemplateName;
	char 	*pMailForwardAddress;
	char 	*pMailACLManager;
	DWORD	Spare[4];
	} REG_MAIL_INFO;


/*	REG_MAIL_OWNER_ACL_XXX defines used with
	MailOwnerAccess element of REG_MAIL_INFO struct */
#define REG_MAIL_OWNER_ACL_MANAGER		0
#define REG_MAIL_OWNER_ACL_DESIGNER		1
#define REG_MAIL_OWNER_ACL_EDITOR		2


/*	Routines -------------------------------------------------------------- */

STATUS LNPUBLIC	 REGNewWorkstation (HCERTIFIER	hCertCtx,
									WORD		MakeIDType,
									char 	far *RegServer,
								  	char 	far *OrgUnit,
									char 	far *LastName, 
									char 	far *FirstName, 
									char 	far *MidInitial, 
									char 	far *Password,
									char 	far *IDFileName,
									char 	far *Location,
									char 	far *Comment,
									WORD		MailSystem,
									char 	far *MailServerName,
									char 	far *MailFileName,
									char 	far *ForwardAddress,
									REGFlags	Flags,
									WORD		MinPasswordLength,
									REGSIGNALPROC signalstatus,
									char	far *ErrorPathName);

STATUS LNPUBLIC	 REGNewWorkstationExtended (HCERTIFIER	hCertCtx,
									WORD		MakeIDType,
									char 	far *RegServer,
								  	char 	far *OrgUnit,
									char 	far *LastName, 
									char 	far *FirstName, 
									char 	far *MidInitial, 
									char 	far *Password,
									char 	far *IDFileName,
									char 	far *Location,
									char 	far *Comment,
									WORD		MailSystem,
									char 	far *MailServerName,
									char 	far *MailFileName,
									char 	far *ForwardAddress,
									char	far *ProfileName,
									char	far	*LocalAdminName,
									REGFlags	Flags,
									WORD		MinPasswordLength,
									REGSIGNALPROC signalstatus,
									char	far *ErrorPathName);

STATUS LNPUBLIC REGNewUser (	HCERTIFIER	hCertCtx,
						   		WORD		MakeIDType,
								char 	far *RegServer,
								REG_USERNAME_INFO far *RegUserNameInfo,
								REG_MAIL_INFO far *RegMailInfo,
								char 	far *Password,
								void	far	*pGroupList,
								char 	far *IDFileName,
								char 	far *Location,
								char 	far *Comment,
								char 	far *InternetAddress,
								char	far *ProfileName,
								char	far	*LocalAdminName,
								REGFlags	Flags,
								REGFlagsExt	FlagsExt,
								WORD		MinPasswordLength,
								NOTEHANDLE far	*phUserNote,
								DBHANDLE far	*phUserNoteNAB,
								REGSIGNALPROC signalstatus,
								char	far *ErrorPathName,
								void	far *Reserved,
								void	far *Spare);

STATUS LNPUBLIC REGNewPerson (	HCERTIFIER			hCertCtx,
								char far			*RegServer,
								REG_PERSON_INFO	far *PersonInfo,
								REGSIGNALPROC		signalstatus,
								char far			*RetErrorPathName,
								void far			*Spare);

STATUS LNPUBLIC	 REGNewServer	   (HCERTIFIER	hCertCtx,
									WORD		MakeIDType,
									char 	far *RegServer,
								  	char 	far *OrgUnit,
									char 	far *EntryName, 
									char 	far *Password,
									char 	far *IDFileName,
									char 	far *Location,
									char 	far *Comment,
									char 	far *DomainName,
									char 	far *NetworkName,
									char 	far *AdminName,
									char 	far *ServerTitle,
									REGFlags	Flags,
									WORD		MinPasswordLength,
									REGSIGNALPROC signalstatus,
									char	far *ErrorPathName);

STATUS LNPUBLIC	 REGNewServerExtended	   (HCERTIFIER	hCertCtx,
									WORD		MakeIDType,
									char 	far *RegServer,
								  	char 	far *OrgUnit,
									char 	far *EntryName, 
									char 	far *Password,
									char 	far *IDFileName,
									char 	far *Location,
									char 	far *Comment,
									char 	far *DomainName,
									char 	far *NetworkName,
									char 	far *AdminName,
									char 	far *ServerTitle,
									char	far	*LocalAdminName,
									REGFlags	Flags,
									WORD		MinPasswordLength,
									REGSIGNALPROC signalstatus,
									char	far *ErrorPathName);

STATUS LNPUBLIC	 REGNewCertifier (HCERTIFIER	hCertCtx,
									WORD		MakeIDType,
									char	far	*RegServer,
									char 	far *Country,
								  	char 	far *Org,
								  	char 	far *OrgUnit,
									char 	far *Password,
									char 	far *IDFileName,
									char 	far *Location,
									char 	far *Comment,
									char 	far *MailServerName,
									char 	far *MailFileName,
									char 	far *ForwardAddress,
									REGFlags	Flags,
									WORD		KeyWidth,
									WORD		MinPasswordLength,
									REGSIGNALPROC signalstatus,
									char	far	*ErrorPathName);

STATUS LNPUBLIC	 REGNewCertifierExtended (HCERTIFIER		hCertCtx,
										char far			*RegServer,
										REG_CERTIFIER_INFO	far *CertInfo,
										REGSIGNALPROC		signalstatus,
										char far			*retErrorPathName,
										void far			*Spare);

STATUS LNPUBLIC	 REGNewServerExtended2	   (HCERTIFIER			hCertCtx,
											char far			*RegServer,
											REG_SERVER_INFO far	*ServerInfo,
											REGSIGNALPROC		signalstatus,
											char far 			*retErrorPathName,
											void far			*Spare);

STATUS LNPUBLIC	 REGFindAddressBookEntry(
									DBHANDLE hAddressBook, 
				 					char far *NameSpace,
									char far *Name, 
									NOTEID far *EntryNoteID);


STATUS LNPUBLIC	 REGCrossCertifyID (HCERTIFIER		hCertCtx,
									 WORD			Spare1,
									 char far		*RegServer,
									 char far		*IDFileName,
									 char far		*Location,
									 char far		*Comment,
									 char far		*ForwardAddress,
									 WORD			Spare2,
									 REGSIGNALPROC 	signalstatus,
									 char far	 	*ErrorPathName);

STATUS LNPUBLIC	 REGGetIDInfo 	   (char	far	*IDFileName,
									WORD		InfoType,
									void	far *OutBufr,
									WORD		OutBufrLen,
									WORD	far *ActualLen);

STATUS LNPUBLIC	 REGReCertifyID	(HCERTIFIER		hCertCtx,
									 WORD			Spare1,
									 char far		*RegServer,
									 char far		*OrgUnit,
									 char far		*IDFileName,
									 TIMEDATE far	*ExpirationTime,
									 WORD			Spare2,
									 VOID far		*Spare3,
									 REGSIGNALPROC 	signalstatus,
									 char far	 	*ErrorPathName);


#endif


#ifdef __cplusplus
}
#endif

#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif

