
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
**	urltypes.h
**
**	All Rights Reserved
*/

#if !defined(URLTYPES_H)
#define URLTYPES_H


#define	MAX_DOMINO_URL_LENGTH	2048

#define MAX_DOMINO_USERAGENT_LENGTH 128

/* URL Addressable Type
*
* This enumerates the kinds of Notes objects addressable via Domino URLs,
* or specified along the path portion of the url.
*/
typedef enum _UAT
{
	UAT_None					= 0,
	UAT_Server 					= 1,
	UAT_Database				= 2,
	UAT_View					= 3,
	UAT_Form					= 4,
	UAT_Navigator				= 5,
	UAT_Agent					= 6,
	UAT_Document				= 7,
	UAT_Filename				= 8, 	/* internal filename of attachment */
	UAT_ActualFilename			= 9,	/* external filename of attachment if different */
	UAT_Field					= 10,
	UAT_FieldOffset				= 11,
	UAT_FieldSuboffset			= 12,
	UAT_Page					= 13,
	UAT_FrameSet				= 14,
	UAT_ImageResource			= 15,
	UAT_CssResource				= 16,
	UAT_JavascriptLib			= 17,
	UAT_FileResource			= 18,
	UAT_About					= 19,
	UAT_Help					= 20,
	UAT_Icon					= 21,
	UAT_SearchForm				= 22,
	UAT_SearchSiteForm			= 23,
	UAT_Outline					= 24,
	UAT_NumberOfTypes			/* must be the last one */
} UAT;


/* URL Reference Type
*
* This enumerates ways a Notes Object can be references in a URL path.
*/
typedef enum _URT   	/* Reference types */
{
	URT_None				= 0,
	URT_Name				= 1,
	URT_Unid				= 2,
	URT_NoteId				= 3,
	URT_Special				= 4,	/* special name */
	URT_RepId				= 5,
	URT_NumberOfTypes			/* must be the last one */
} URT;

/*
 * URL Specal Values
 * values that stand for the "special name" URL components.
 */
typedef enum _USV
{
	USV_About				= 0,
	USV_Help				= 1,
	USV_Icon				= 2,
	USV_DefaultView			= 3,
	USV_DefaultForm			= 4,
	USV_DefaultNav			= 5,
	USV_SearchForm			= 6,
	USV_DefaultOutline		= 7,
	USV_First				= 8,
	USV_FileField			= 9,
	USV_NumberOfValues			/* must be the last one */
} USV;


/* Domino Command Argument Ids
*
*	This enumerates the command arguments supported in Domino urls.
*	(e.g., &Start=..., &Count=...).
*
*	CAI = Command Argument ID
*/
typedef enum
{
	CAI_Start					= 0,
	CAI_StartKey				= 1,
	CAI_Count					= 2,
	CAI_Expand					= 3,
	CAI_FullyExpand			= 4,
	CAI_ExpandView				= 5,
	CAI_Collapse				= 6,
	CAI_CollapseView			= 7,
	CAI_3PaneUI					= 8,
	CAI_TargetFrame			= 9,
	CAI_FieldElemType			= 10,
	CAI_FieldElemFormat		= 11,
	CAI_SearchQuery			= 12,
	CAI_OldSearchQuery		= 13,
	CAI_SearchMax				= 14,
	CAI_SearchWV				= 15,
	CAI_SearchOrder			= 16,
	CAI_SearchThesarus		= 17,
	CAI_ResortAscending		= 18,
	CAI_ResortDescending		= 19,
	CAI_ParentUNID				= 20,
	CAI_Click					= 21,
	CAI_UserName				= 22,
	CAI_Password				= 23,
	CAI_To						= 24,
	CAI_ISMAPx					= 25,
	CAI_ISMAPy					= 26,
	CAI_Grid					   = 27,
	CAI_Date					   = 28,
	CAI_TemplateType			= 29,
	CAI_TargetUNID				= 30,
	CAI_ExpandSection			= 31,
	CAI_Login					= 32,
	CAI_PickupCert				= 33,
	CAI_PickupCACert			= 34,
	CAI_SubmitCert				= 35,
	CAI_ServerRequest			= 36,
	CAI_ServerPickup			= 37,
	CAI_PickupID				= 38,
	CAI_TranslateForm			= 39,
	CAI_SpecialAction			= 40,
	CAI_AllowGetMethod		= 41,
	CAI_Seq						= 42,
	CAI_BaseTarget				= 43,
	CAI_ExpandOutline			= 44,
	CAI_StartOutline			= 45,
	CAI_Days					   = 46,
	CAI_TableTab				= 47,
	CAI_MIME					   = 48,
	CAI_RestrictToCategory	= 49,
	CAI_Highlight				= 50,
	CAI_Frame					= 51,
	CAI_FrameSrc				= 52,
	CAI_Navigate				= 53,
	CAI_SkipNavigate			= 54,
	CAI_SkipCount				= 55,
	CAI_EndView					= 56,
	CAI_TableRow				= 57,
	CAI_RedirectTo				= 58,
	CAI_SessionId				= 59,
	CAI_SourceFolder			= 60,
	CAI_SearchFuzzy			= 61,
	CAI_HardDelete				= 62,
	CAI_SimpleView				= 63,
	CAI_SearchEntry			= 64,
	CAI_Name					   = 65,
	CAI_Id						= 66,
	CAI_RootAlias				= 67,
	CAI_Scope					= 68,
	CAI_DblClkTarget			= 69,
	CAI_Charset					= 70,
	CAI_EmptyTrash				= 71,
	CAI_EndKey					= 72,
	CAI_PreFormat				= 73,
	CAI_ImgIndex				= 74,
	CAI_AutoFramed				= 75,
	CAI_OutputFormat			= 76,
	CAI_InheritParent			= 77,
	CAI_Last			/* must be the last entry */
} CmdArgID;


/*	Domino Command Argument Value Types (CAVT)
*/
typedef enum
{
	CAVT_String		= 0,	/* arg value is a pointer to a nul-terminated string */
	CAVT_Int		= 1,	/* arg value is an int */
	CAVT_NoteId		= 2,	/* arg value is a NOTEID */
	CAVT_UNID		= 3,	/* arg value is an UNID */
	CAVT_StringList	= 4		/* arg value is a list of null-terminated strings */

} CmdArgValueType;

/* Domino Command Ids
*
* This enumerates the commands supported in Domino urls.
*
*/
typedef enum _CmdId				
{
	kUnknownCmdId				= 0,
	kOpenServerCmdId			= 1,
	kOpenDatabaseCmdId			= 2,
	kOpenViewCmdId				= 3,
	kOpenDocumentCmdId			= 4,
	kOpenElementCmdId			= 5,
	kOpenFormCmdId				= 6,
	kOpenAgentCmdId				= 7,
	kOpenNavigatorCmdId			= 8,
	kOpenIconCmdId				= 9,
	kOpenAboutCmdId				= 10,
	kOpenHelpCmdId				= 11,
	kCreateDocumentCmdId		= 12,
	kSaveDocumentCmdId			= 13,
	kEditDocumentCmdId			= 14,
	kDeleteDocumentCmdId		= 15,
	kSearchViewCmdId			= 16,
	kSearchSiteCmdId			= 17,
	kNavigateCmdId				= 18,
	kReadFormCmdId				= 19,
	kRequestCertCmdId			= 20,
	kReadDesignCmdId			= 21,
	kReadViewEntriesCmdId		= 22,
	kReadEntriesCmdId			= 23,
	kOpenPageCmdId				= 24,
	kOpenFrameSetCmdId			= 25,
	kOpenFieldCmdId				= 26,	/* OpenField command for Java applet(s) & HTML API */
	kSearchDomainCmdId			= 27,
	kDeleteDocumentsCmdId		= 28,
	kLoginUserCmdId				= 29,
	kLogoutUserCmdId			= 30,
	kOpenImageResourceCmdId		= 31,
	kOpenImageCmdId				= 32,
	kCopyToFolderCmdId			= 33,
	kMoveToFolderCmdId			= 34,
	kRemoveFromFolderCmdId		= 35,
	kUndeleteDocumentsCmdId		= 36,
	kRedirectCmdId				= 37,
	kGetOrbCookieCmdId			= 38,
	kOpenCssResourceCmdId		= 39,
	kOpenFileResourceCmdId		= 40,
	kOpenJavascriptLibCmdId		= 41,
	kUnImplemented_01			= 42,
	kChangePasswordCmdId		= 43,
	kOpenPreferencesCmdId		= 44,
	kOpenWebServiceCmdId		= 45,
	kWsdlCmdId					= 46,
	kNumberOfCmds     		/* This must remain last */
} CmdId;


#endif /* URLTYPES_H */


#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif

