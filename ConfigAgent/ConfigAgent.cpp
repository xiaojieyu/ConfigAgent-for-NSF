#include "stdafx.h"

#ifdef __cplusplus
extern "C" {
#endif

/* OS and C include files */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

/* Notes API include files */

#include <global.h>
#include <nsfdb.h>
#include <nsfnote.h>
#include <nsfsearc.h>
#include <nsferr.h>
#include <ods.h>
#include <textlist.h>
#include <kfm.h>
#include <osmisc.h>
#include <osfile.h>

void  LNPUBLIC  ProcessArgs (int argc, char *argv[]);

#define  STRING_LENGTH  256

/* Function prototypes */

STATUS LNPUBLIC ReadSummaryData (     /* called for every document */
            VOID far *,
            SEARCH_MATCH far *,
            ITEM_TABLE far *);
STATUS PrintSummary (char *);
STATUS ExtractTextList (char *, char *);
void PrintAPIError (STATUS);

/* Constants */
/* Notes imposes a 32K max summary buffer total size. Therefore,
   34K will safely store the printable text rendering of any single
   item.
*/
#define  MAX_ITEM_LEN       34816

/* The maximum number of items in the summary buffer of a single note
   is limited to the number of ITEM structures that will fit in 32K.
*/
#define  MAX_ITEMS          32768/sizeof(ITEM)

#define  MAX_ITEM_NAME_LEN  DESIGN_NAME_MAX


/* Global variables */
ITEM    Items[MAX_ITEMS];           /* Stores the array of ITEMs */
char    ItemText[MAX_ITEM_LEN];     /* Text rendering of item value */
char    ItemName[MAX_ITEM_NAME_LEN];/* Zero terminated item name */

/************************************************************************

    FUNCTION:   main

*************************************************************************/
#define CONFIG_AGENT_ERROR_SUCCESS (0)
#define CONFIG_AGENT_ERROR_NOTE_INIT_FAIL (-1)
#define CONFIG_AGENT_ERROR_PATH_CONSTRUCT_FAIL (-2)
#define CONFIG_AGENT_ERROR_DB_OPEN_FAIL (-3)
#define CONFIG_AGENT_ERROR_DB_CLOSE_FAIL (-4)
#define CONFIG_AGENT_ERROR_DB_SERACH_FAIL (-5)
#define CONFIG_AGENT_ERROR_FORMULA_COMPILE_FAIL (-6)

#define CONFIG_AGENT_ERROR_IDFILE_NOT_EXIST (-7)
#define CONFIG_AGENT_ERROR_BAD_PASSWORD (-8)
#define CONFIG_AGENT_ERROR_SWITCH_ID_FAIL (-9)
#define ERR_NOEXIST (0x0103)
#define ERR_BSAFE_BADPASSWORD (0x1098)
int main(int argc, char *argv[])
{
    DBHANDLE    db_handle;    /* handle of source database */
    STATUS      error = NOERROR;   /* return #Dtatus from API calls */
    
    char        formula[STRING_LENGTH];
    char        database_name[STRING_LENGTH];
    char        username_name[STRING_LENGTH];
    char        *pUserName = username_name;    
    char        *pDbFileName = database_name;  /* pathname of source database */

    ProcessArgs(argc, argv);
    
    // ConfigAgent.exe idfile passwd server dbfile formname

    char *pIDFileName = argv[1]; //"C:\\Program Files\\lotus\\notes\\data\\admin.id";
    char *pPassword = argv[2];    //"mac8.6";
    char *pServer = argv[3];    // benz
    char *pDatabase = argv[4];    // smd\smconf.nsf
    char *pForm = argv[5];    // policy

    if (strncmp(pForm, "*", strlen(pForm)) == 0)
        strncpy(formula, "@All", 5);
    else
    {
        _snprintf(formula, sizeof(formula)-1, "Form=\"%s\"", pForm);
        formula[sizeof(formula)-1] = '\0';
    }

    if (error = NotesInitExtended (argc, argv))
    {
        printf("\n Unable to initialize Notes.\n");
        return CONFIG_AGENT_ERROR_NOTE_INIT_FAIL;
    }

    if (error = OSPathNetConstruct( NULL, pServer, pDatabase, pDbFileName))
    {
        PrintAPIError (error);
        NotesTerm();
        return CONFIG_AGENT_ERROR_PATH_CONSTRUCT_FAIL;
    }

    if (error = SECKFMSwitchToIDFile(pIDFileName, pPassword,
        pUserName, STRING_LENGTH, fKFM_switchid_DontSetEnvVar, NULL))
    {
        printf ("Error: unable to open the id file '%s'\n", pIDFileName);
        PrintAPIError (error);
        NotesTerm();
        if (error == ERR_NOEXIST)
            return CONFIG_AGENT_ERROR_IDFILE_NOT_EXIST;
        else if (error == ERR_BSAFE_BADPASSWORD)
            return CONFIG_AGENT_ERROR_BAD_PASSWORD;
        else
            return CONFIG_AGENT_ERROR_SWITCH_ID_FAIL;
    }
    /* Open the database. */

    if (error = NSFDbOpen (pDbFileName, &db_handle))
    {
        printf ("Error: unable to open database '%s'\n", pDbFileName);
        PrintAPIError (error);
        NotesTerm();
        return CONFIG_AGENT_ERROR_DB_OPEN_FAIL;
    }
    
    /* Compile the selection formula. */

    //char        formula[] = "select form=\"Events\""; /* an ASCII selection formula. */
    FORMULAHANDLE    formula_handle;    /* a compiled selection formula */
    WORD     wdc;                       /* a word we don't care about */
    if (error = NSFFormulaCompile (
                NULL,               /* name of formula (none) */
                (WORD) 0,           /* length of name */
                formula,            /* the ASCII formula */
                (WORD) strlen(formula),    /* length of ASCII formula */
                &formula_handle,    /* handle to compiled formula */
                &wdc,               /* compiled formula length (don't care) */
                &wdc,               /* return code from compile (don't care) */
                &wdc, &wdc, &wdc, &wdc)) /* compile error info (don't care) */
        
    {
        NSFDbClose (db_handle);
        PrintAPIError (error);  
        NotesTerm();
        return CONFIG_AGENT_ERROR_FORMULA_COMPILE_FAIL;
    }
    /*  Call NSFSearch to find all data notes in the database.
        Specify search flag SEARCH_SUMMARY so that the action
        routine gets passed the summary buffer as input.
    */

    if (error = NSFSearch (
        db_handle,          /* database handle */
        formula_handle,         /* selection formula */
        NULL,               /* title of view in selection formula */
        SEARCH_SUMMARY,     /* search flags: get summary data! */
        NOTE_CLASS_DATA,    /* note class to find */
        NULL,               /* starting date (unused) */
        ReadSummaryData,    /* action routine for notes found */
        NULL,               /* argument to action routine */
        NULL))              /* returned ending date (unused) */

    {
        printf ("Error: unable to search database.\n");
        NSFDbClose (db_handle);
        PrintAPIError (error);
        NotesTerm();
        return CONFIG_AGENT_ERROR_DB_SERACH_FAIL;
    }

    /* Close the database. */
    if (error = NSFDbClose (db_handle))
    {
        printf ("Error: unable to close database '%s'\n", pDbFileName);
        PrintAPIError (error);
        NotesTerm();
        return CONFIG_AGENT_ERROR_DB_CLOSE_FAIL;
    }

    /* End of main routine. */
    printf("\nProgram completed successfully.\n");
    NotesTerm();
    return CONFIG_AGENT_ERROR_SUCCESS;
}


/************************************************************************

    FUNCTION:   ReadSummaryData

    PURPOSE:    If the note matches the search criteria, this prints
                the note ID and calls PrintSummary() to print out the
                summary data for the note.

    DESCRIPTION: This is the action routine called by NSFSearch for
                 each note that matches the selection criteria.

    INPUTS:
        optional_param - the optional argument that we supplied when
                         we called NSFSearch. Not used in this example.

        search_info -   supplied by NSFSearch. This is a structure of
                        information about the note that was found.

        summary_info -  The summary buffer for this note.

*************************************************************************/

STATUS LNPUBLIC ReadSummaryData
            (VOID far *optional_param,
            SEARCH_MATCH far *search_info,
            ITEM_TABLE far *summary_info)
{
    SEARCH_MATCH  SearchMatch;
    STATUS        error;

    memcpy ((char*)(&SearchMatch), (char *)search_info, sizeof(SEARCH_MATCH));

    if (!(SearchMatch.SERetFlags & SE_FMATCH))
        return (NOERROR);

    /* Print the note ID. */

    printf ("\nNote ID is: %#010lx.\n", SearchMatch.ID.NoteID);

    /* Print the summary data. */

    if (error = PrintSummary( (char*)summary_info ))
        return (error);

    return (NOERROR);
}

/************************************************************************

    FUNCTION:   PrintSummary

    PURPOSE:    Print all the items in a summary buffer.

    INPUTS:
        pSummary - a pointer to the summary buffer for one note.

    DESCRIPTION:
        The information in a summary buffer consists of an ITEM_TABLE
        structure, followed by an array of ITEM structures, followed by
        a packed sequence of field names and item values.

        ITEM_TABLE
        ITEM 1
        ITEM 2
        ...
        ITEM N
        name of item 1
        value of item 1
        name of item 2
        value of item 2
        ...
        name of item N
        value if item N

        Item names are not zero terminated. Each item value starts with
        a data type word. The lengths of the item names and item values
        will vary. The NameLength member of the ITEM structure specifies
        the length of the corresponding name, and the ValueLength member
        of the ITEM structure specifies the length of the item value.
        The ValueLength includes the length of the data type word.

        Note that this summary buffer differs in format from the buffer
        parsed by sample program VIEWSUMM. VIEWSUMM calls NIFReadEntries
        specifying READ_MASK_SUMMARYVALUES, which yields a buffer with
        format specified by ITEM_VALUE_TABLE rather than ITEM_TABLE.

        This function can parse the summary buffer of any data note
        because it does not assume the note contains items with any
        particular names. If you know the item name in advance, use
        either NSFGetSummaryValue() or NSFLocateSummaryValue().

*************************************************************************/


STATUS PrintSummary (char *pSummary)
{
    char       *pSummaryPos;        /* current position in pSummary */
    ITEM_TABLE  ItemTable;          /* header at start of pSummary */
    USHORT      ItemCount;          /* number of items in pSummary */
    USHORT      NameLength;         /* length of item name w/out terminator*/
    USHORT      ValueLength;        /* length of item value, incl. type */
    WORD        DataType;           /* item data type word */
    char       *szDataType;         /* printable data type name */
    USHORT      TextLen;            /* length of printable item text */
    NUMBER      NumericItem;        /* an item of type TYPE_NUMBER */
    NUMBER_PAIR NumberPair;         /* part of item of TYPE_NUMBER_RANGE */
    RANGE       Range;              /* part of item of TYPE_NUMBER_RANGE */
    TIMEDATE    TimeItem;           /* a time/date item */
    TIMEDATE_PAIR   TimePairItem;   /* part of time/date list or range */
    WORD        TimeStringLen;      /* length of ASCII time/date */
    STATUS      error;              /* return code from API calls */
    USHORT      i;                  /* counter for loop over items */
    USHORT      j;                  /* " " " " multi-valued items */
    char        Text[] = "TYPE_TEXT";
    char        Text_List[] = "TYPE_TEXT_LIST";
    char        Number[] = "TYPE_NUMBER";
    char        Number_Range[] = "TYPE_NUMBER_RANGE";
    char        Time[] = "TYPE_TIME";
    char        Time_Range[] = "TYPE_TIME_RANGE";
    char        Unrecognized[] = "Unrecognized";

   /* Initialize pSummaryPos to the position of the beginning of
      the summary buffer. Keep pSummary unmodified. Modify pSummaryPos.
    */

    pSummaryPos = pSummary;

   /* Copy the ITEM_TABLE header at the beginning of the summary buffer
      to a local variable. Advance pSummaryPos to point to the next
      byte in the summary buffer after the ITEM_TABLE.
    */
    memcpy ((char*)(&ItemTable), pSummaryPos, sizeof(ITEM_TABLE));
    pSummaryPos += sizeof(ItemTable);

   /* pSummaryPos now points to the first ITEM in an array of ITEM
      structures. Copy this array of ITEM structures into the global
      Items[] array.
    */

    ItemCount = ItemTable.Items;

    for (i=0; i < ItemCount; i++)
    {
        memcpy((char*)(&Items[i]), pSummaryPos, sizeof(ITEM));
        pSummaryPos += sizeof(ITEM);
    }

   /* pSummaryPos now points to the first item name. Loop over each
      item, copying the item name into the ItemName variable and
      converting the item value to printable text in ItemText.
    */

    for (i=0; i < ItemCount; i++)
    {
       /* zero out two global arrays that we re-use for each item */
        memset (ItemText, 0, MAX_ITEM_LEN);
        memset (ItemName, 0, MAX_ITEM_NAME_LEN);

        NameLength = Items[i].NameLength;
        memcpy (ItemName, pSummaryPos, NameLength);
        ItemName[NameLength] = '\0';
        pSummaryPos += NameLength;

        /*  Handle the case of a zero length item  */

        if (Items[i].ValueLength == 0)
        {
            strcpy(ItemName, "  *  ");
            ItemText[0] = '\0';
            goto PrintItem;
        }

        /* pSummaryPos now points to the item value. First get the
           data type. Then step over the data type word to the data
           value and convert the value to printable text. Store the
           text in ItemText.
        */

        memcpy ((char*)(&DataType), pSummaryPos, sizeof(WORD));
        pSummaryPos += sizeof(WORD);

        ValueLength = Items[i].ValueLength - sizeof(WORD);

        /* The way to extract an item depends on the data type. */

        switch (DataType)
        {
            case TYPE_TEXT:
                szDataType = Text;
                memcpy (ItemText, pSummaryPos, ValueLength);
                ItemText[ValueLength] = '\0';
                pSummaryPos += ValueLength;
                break;

            case TYPE_TEXT_LIST:
                szDataType = Text_List;
                if (error = ExtractTextList (pSummaryPos, ItemText))
                {
                    printf ("Error: unable to extract text list.\n");
                    ItemText[0] = '\0';
                }
                pSummaryPos += ValueLength;
                break;

            case TYPE_NUMBER:
                szDataType = Number;
                memcpy ((char *)(&NumericItem), pSummaryPos, sizeof(NUMBER));
                  sprintf (ItemText, "%f", NumericItem);
                pSummaryPos += sizeof(NUMBER);
                break;

            case TYPE_NUMBER_RANGE:
                szDataType = Number_Range;
                TextLen = 0;
                memcpy ((char*)(&Range), pSummaryPos, sizeof(RANGE));
                pSummaryPos += sizeof(RANGE);
                for (j=0; j < Range.ListEntries; j++)
                {
                    memcpy ((char*)(&NumericItem), pSummaryPos,
                            sizeof(NUMBER));
                    sprintf (ItemText+TextLen, "%f ", NumericItem);
                    pSummaryPos += sizeof(NUMBER);
                    TextLen = strlen(ItemText);
                }
                if ((Range.ListEntries != 0) && (Range.RangeEntries != 0))
                {
                    memcpy (ItemText+TextLen, "; ", 2);
                    TextLen += 2;
                }
                for (j=0; j < Range.RangeEntries; j++)
                {
                    memcpy ((char*)(&NumberPair), pSummaryPos,
                            sizeof(NUMBER_PAIR));
                    sprintf (ItemText+TextLen, "%f - %f ", NumberPair.Lower,
                             NumberPair.Upper);
                    pSummaryPos += sizeof(NUMBER_PAIR);
                    TextLen = strlen(ItemText);
                }
                break;

#ifndef APITESTMODE

            case TYPE_TIME:
                szDataType = Time;
                memcpy ((char*)(&TimeItem), pSummaryPos, sizeof(TIMEDATE));
                pSummaryPos += sizeof(TIMEDATE);
                if (error = ConvertTIMEDATEToText (
                            NULL, NULL, &TimeItem,
                            ItemText, MAXALPHATIMEDATE,
                            &TimeStringLen))
                {
                    printf ("Error: unable to convert TIMEDATE to text.\n");
                    TimeStringLen = 0;
                }
                ItemText[TimeStringLen] = '\0';
                break;

            case TYPE_TIME_RANGE:
                szDataType = Time_Range;
                TextLen = 0;
                memcpy ((char*)(&Range), pSummaryPos, sizeof(RANGE));
                pSummaryPos += sizeof(RANGE);
                for (j=0; j < Range.ListEntries; j++)
                {
                    if (j != 0)
                    {
                        memcpy (ItemText+TextLen, ",", 1);
                        TextLen++;
                    }
                    memcpy ((char*)(&TimeItem), pSummaryPos,
                            sizeof(TIMEDATE));
                    pSummaryPos += sizeof(TIMEDATE);
                    if (error = ConvertTIMEDATEToText (
                                NULL, NULL,
                                &TimeItem,
                                ItemText+TextLen,
                                MAXALPHATIMEDATE, &TimeStringLen))
                    {
                        printf("Error: unable to convert TIMEDATE to text.\n");
                        TimeStringLen = 0;
                    }
                    TextLen += TimeStringLen;
                }

                if (Range.RangeEntries == 0)
                {
                    ItemText[TextLen] = '\0';
                    break;
                }

               /* Append a space, semicolon, space to separate time/dates
                  from time/date ranges.
                */

                memcpy (ItemText+TextLen, " ; ", 3);
                TextLen += 3;

                for (j=0; j < Range.RangeEntries; j++)

                {
                    if (j != 0)
                    {
                        memcpy (ItemText+TextLen, ",", 1);
                        TextLen++;
                    }
                    memcpy ((char*)&TimePairItem, pSummaryPos,
                            sizeof(TIMEDATE_PAIR));
                    pSummaryPos += sizeof(TIMEDATE_PAIR);
                    if (error = ConvertTIMEDATEToText (
                                NULL, NULL,
                                &TimePairItem.Lower, ItemText+TextLen,
                                MAXALPHATIMEDATE, &TimeStringLen))
                    {
                        printf("Error: unable to convert TIMEDATE to text.\n");
                        TimeStringLen = 0;
                    }
                    TextLen += TimeStringLen;
                    memcpy (ItemText+TextLen, "-", 1);
                    TextLen++;
                    if (error = ConvertTIMEDATEToText (
                                NULL, NULL,
                                &TimePairItem.Upper, ItemText+TextLen,
                                MAXALPHATIMEDATE, &TimeStringLen))
                    {
                        printf("Error: unable to convert TIMEDATE to text.\n");
                        TimeStringLen = 0;
                    }
                    TextLen += TimeStringLen;
                }
                ItemText[TextLen] = '\0'; /* zero terminate the text */
                break;

#endif
            /* Item is not one of the data types this program handles. */

            default:
                szDataType = Unrecognized;
                ItemText[0] = '\0';
                pSummaryPos += ValueLength;
                break;
        } /* end of switch on data type */

PrintItem:
        /* Print the item name, data type, and value. */
        printf ("\tItem Name = %s\n", ItemName);
        printf ("\tData Type = %s\n", szDataType);

#ifndef APITESTMODE
        printf ("\tItem Value = \"%s\"\n\n", ItemText);
#else
        if (strcmp(ItemName,"$UpdatedBy")==0)
          printf ("\tItem Value =\n\n", ItemText);
        else
          printf ("\tItem Value = \"%s\"\n\n", ItemText);
#endif

    }/* End of loop over items in the summary. */

    /* Print final line feed to end display for this note. */

    printf ("\n");

    return (NOERROR);
}

/************************************************************************

    FUNCTION:   ExtractTextList

    PURPOSE:    This function extracts an item of TYPE_TEXT_LIST from a
                pSummary buffer.

    INPUTS:     char *pBuffer

    OUTPUTS:    char *TextList

*************************************************************************/

STATUS ExtractTextList (char *pBuffer, char *TextList)
{
    LIST    List;
    char   *ListEntry;  /* pointer to list entry */
    WORD    TextLen;    /* total length of string output to TextList */
    WORD    EntryLen;   /* length of one entry */
    STATUS  error;      /* return code from API calls */
    USHORT  i;          /* a counter */

    /* Initialize the total length of the list. */

    TextLen = 0;

    /* Clear the string that we'll fill up. */

    TextList[0] = '\0';

    /* Get the list header structure with the number of entries. */

    memcpy ((char*)(&List), pBuffer, sizeof(LIST));

    /* Loop over each entry of the list. */

    for (i=0; i<List.ListEntries; i++)
    {
        /* Get one entry from the list. */

        if (error = ListGetText (
                    pBuffer,
                    FALSE, /* DataType not prepended to list */
                    i,
                    &ListEntry,
                    &EntryLen))
        {
            return (ERR(error));
        }

        /*  Copy this entry to the string we are building and move the
            pointer that keeps track of how much we have in the string.
         */

        memcpy (TextList+TextLen, ListEntry, EntryLen);
        TextLen += EntryLen;

        /* Put a comma after the entry and advance the text length. */

        memcpy (TextList+TextLen, ",", 1);
        TextLen++;

    }   /* End of loop over list entries. */

    /* Put a null in place of the last comma */

    TextLen--;
    memcpy (TextList+TextLen, "\0", 1);

    return (NOERROR);
}


/************************************************************************

    FUNCTION:   ProcessArgs

    INPUTS:     argc, argv - directly from the command line

    OUTPUTS:    

*************************************************************************/

void  LNPUBLIC  ProcessArgs (int argc, char *argv[])
{
    // ConfigAgent.exe idfile passwd servername dbfile formname
    // 
    if ( argc != 6 )
    {
        printf("Print the notes summary information. \n\n");
        printf("ConfigAgent.exe idfile passwd dbfile formname\n");
        printf("  idfile\t\tnote user id file, ex. C:\\lotus\\notes\\data\\admin.id\n");
        printf("  passwd\t\tpassword for the user id file.\n");
        printf("  server\t\tdomino server name\n");
        printf("  dbfile\t\tdatabase file name\n");
        printf("  form\t\tform name in the database type, * means all form\n\n");
        fflush(stdout);
        exit(0);
    }
    else
    {
    } /* end if */

} /* ProcessArgs */


/*************************************************************************

    FUNCTION:   PrintAPIError

    PURPOSE:    This function prints the Lotus C API for Domino and Notes
        error message associated with an error code.

**************************************************************************/

void PrintAPIError (STATUS api_error)

{
    STATUS  string_id = ERR(api_error);
    char    error_text[200];
    WORD    text_len;

    /* Get the message for this Lotus C API for Domino and Notes error code
       from the resource string table. */

    text_len = OSLoadString (NULLHANDLE,
                             string_id,
                             error_text,
                             sizeof(error_text));

    /* Print it. */
    fprintf (stderr, "\n%s\n", error_text);

}

#ifdef __cplusplus
}
#endif
