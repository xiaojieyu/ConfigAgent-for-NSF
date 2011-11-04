
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/* ***************************************************************** */
/*                                                                   */
/* Licensed Materials - Property of IBM                              */
/*                                                                   */
/* L-GHUS-76ALVG, L-GHUS-76ALWH                                      */
/*                                                                   */
/* Copyright IBM Corp. 1991, 2007  All Rights Reserved.              */
/*                                                                   */
/* US Government Users Restricted Rights - Use, duplication or       */
/* disclosure restricted by GSA ADP Schedule Contract with           */
/* IBM Corp.                                                         */
/*                                                                   */
/* ***************************************************************** */

#ifndef ENV_DEFS
#define ENV_DEFS

#ifdef __cplusplus
extern "C" {
#endif

/*	Size of the buffer used to hold the environment variable values (i.e., it
	excludes the variable name) but including the trailing null terminator.

	NOTE:	The largest known example of an environment variable value is a
			max'ed out COMx=...  (the modem init strings can be large, and
			there's plenty of them).
*/

/* This needs to be way bigger than 256 to accomodate the current WinXP max.

   From http://www.microsoft.com/resources/documentation/windows/xp/all/proddocs/en-us/ntcmds_shelloverview.mspx?mfr=true:
		The maximum individual environment variable size is 8,192 bytes.
		The maximum total environment variable size for all variables, which includes variable names and the
		equal sign, is 65,536 KB.

   With the Win32 API, each environment variable can be as big as 32,767 bytes:
   http://msdn.microsoft.com/library/default.asp?url=/library/en-us/dllproc/base/getenvironmentvariable.asp

   Bumping up MAXENVVALUE to 8192 caused blown stacks with testnsf due to its smaller stack size, so for now, we'll go
   with a separate variable, MAX_ENVAPI_BUF_SIZE, to be used in conjunction with direct calls to GetEnvironmentVariable
   and SetEnvironmentVariable. -kbh, 10/09/2006
*/
#define MAX_ENVAPI_BUF_SIZE	32767

#define	MAXENVVALUE 256

/* Used to preface ini variables that are different between OSs which may */
/* share the same INI file. */

#if defined(PM)
#define OS_PREFIX			"PM"
#elif defined(W)
#define OS_PREFIX				"WIN"
#else
#define OS_PREFIX				""		/* Only necessary to distinguish */
									/* between entries used in a multi */
									/* OS environment with a single NOTES.INI */
#endif
/*	Environment variable package */
#define NATIVE "Native"
/*  System temp directory constants */
#define TEMP_DIR_PREFIX				"notes"
#define TEMP_DIR_SUFFIX_LEN			6	  /* If changing, must change TEMP_DIR_SUFFIX_FORMATSPEC to match */
#define TEMP_DIR_SUFFIX_FORMATSPEC	"%06x"
#define TEMP_DIR_DEFAULT_SUFFIX		"G00000"
#define TEMP_DIR_SUFFIX_MAX_VALUE	0x00FFFFFF

BOOL LNPUBLIC		OSGetEnvironmentString (const char far *VariableName, char far *retValueBuffer, WORD BufferLength);
long LNPUBLIC		OSGetEnvironmentLong (const char far *VariableName);

/* On a 64bit platform this will potential lose data as a long may be 64bit but an int is 32bit */

#define OSGetEnvironmentInt(s) ((int) OSGetEnvironmentLong(s))

void LNPUBLIC		OSSetEnvironmentVariable (const char far *VariableName, const char far *Value);
void LNPUBLIC		OSSetEnvironmentInt (const char far *VariableName, int Value);

#ifdef __cplusplus
}
#endif


#endif



#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif

