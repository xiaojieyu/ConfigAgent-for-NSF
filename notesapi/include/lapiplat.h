/****************************************************************************

    FILE:       lapiplat.h

    PURPOSE:    platform-specific macro definitions for toolkit samples

    DESCRIPTION:
    Notes API Toolkit version definitions and macro definitions for Notes API
    Toolkit samples to allow platform-independent sample code.  The following
    macros must be defined for each platform:

        LAPI_MAIN
        LAPI_INIT(status)
        LAPI_INIT_ERROR
        LAPI_RETURN(status)
        LAPI_DUMP_ERROR(error)

****************************************************************************/

#ifndef LAPIPLAT_DEFS
#define LAPIPLAT_DEFS

#ifdef __cplusplus
extern "C" {
#endif

#define NOTESAPI_VERSION   "Notes/Domino 8.0.1"
#define NOTESAPI_MAJOR_VERSION 8
#define NOTESAPI_MINOR_VERSION 0
#define NOTESAPI_MINOR_POINT_VERSION 1

#if defined(EBCDIC_RTL)
#include "ascii_a.h"
#endif

#ifndef GLOBAL_DEFS
#include <global.h>
#endif

#ifndef OSMISC_DEFS
#include <osmisc.h>
#endif

#if defined (UNIX)
#define LPSTR char *
#endif

/****************************************************************************
*
*       LAPI_MAIN
*
****************************************************************************/

#define LAPI_MAIN  STATUS LNPUBLIC NotesMain(int argc, char far *argv[])

/****************************************************************************
*
*       LAPI_INIT
*
****************************************************************************/

#define LAPI_INIT(x)

/****************************************************************************
*
*       LAPI_INIT_ERROR
*
****************************************************************************/

#define LAPI_INIT_ERROR

/****************************************************************************
*
*       LAPI_RETURN
*
****************************************************************************/

#define LAPI_RETURN(x)   return(x)


/****************************************************************************
*
*       LAPI_DUMP_ERROR
*
*       Use in LAPI_RETURN or as a debugging tool for dumping the associated
*       error to stdout.
*
****************************************************************************/

#define LAPI_DUMP_ERROR(x)

#ifdef __cplusplus
}
#endif

#endif
