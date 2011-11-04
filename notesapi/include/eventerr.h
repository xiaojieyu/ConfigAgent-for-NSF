
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/* ***************************************************************** */
/*                                                                   */
/* Licensed Materials - Property of IBM                              */
/*                                                                   */
/* L-GHUS-76ALVG, L-GHUS-76ALWH                                      */
/*                                                                   */
/* Copyright IBM Corp. 1992, 2007  All Rights Reserved.              */
/*                                                                   */
/* US Government Users Restricted Rights - Use, duplication or       */
/* disclosure restricted by GSA ADP Schedule Contract with           */
/* IBM Corp.                                                         */
/*                                                                   */
/* ***************************************************************** */

#ifndef EVENT_ERR_DEFS
#define EVENT_ERR_DEFS

/*	Message codes for the Event Package PKG_EVENT from 0-47 */

#define ERR_EVENT_EXCEED_MEM	PKG_EVENT+1
	errortext(ERR_EVENT_EXCEED_MEM, 	"Warning: Cannot record event - cannot keep up with event occurrence rate!\nDecrease logging levels or increase the event pool size by setting EVENT_POOL_SIZE in NOTES.INI. Default size is %,d bytes. Maximum size is %,d bytes.\r\n")
#define ERR_EVENT_DUPL_QUEUE	PKG_EVENT+2
	errortext(ERR_EVENT_DUPL_QUEUE, 	"A queue with that name already exists.")
#define ERR_EVENT_NOT_Q			PKG_EVENT+3
	errortext(ERR_EVENT_NOT_Q, 	"Not a known event queue.")
#define ERR_EVENT_EXCEED_QUOTA	PKG_EVENT+4
	errortext(ERR_EVENT_EXCEED_QUOTA, 	"Cannot enqueue event - quota exceeded!")
#define ERR_EVTQUEUE_EMPTY		PKG_EVENT+5
	errortext(ERR_EVTQUEUE_EMPTY, 	"No entries in this queue")
#define ERR_EVENT_NO_SUCH_QUEUE	PKG_EVENT+6
	errortext(ERR_EVENT_NO_SUCH_QUEUE, 	"No such queue")
#define ERR_EVENT_NOT_YOUR_Q 	PKG_EVENT+7
	errortext(ERR_EVENT_NOT_YOUR_Q, 	"Can only access your queue.")
#define ERR_EVENT_WRONG_VERSION	PKG_EVENT+8
	errortext(ERR_EVENT_WRONG_VERSION,"Wrong version of event package.")
#define ERR_EVENT_BAD_SEVERITY	PKG_EVENT+9
	errortext(ERR_EVENT_BAD_SEVERITY,"Invalid severity encountered.")
#define ERR_EVENT_NOT_INITIALIZED	PKG_EVENT+10
	errortext(ERR_EVENT_NOT_INITIALIZED,"Event support not initialized.")
#define ERR_EVENT_POOLFULL		PKG_EVENT+11
	errortext(ERR_EVENT_POOLFULL,"Insufficient memory - event pool is full. You can increase it's size via the NOTES.INI setting EVENT_POOL_SIZE.")
#define ERR_EVENT_SHUTDOWN		PKG_EVENT+12
	internaltext(ERR_EVENT_SHUTDOWN,"Shutdown requested")
#define ERR_EVENT_BAD_MONITOR_METHOD	PKG_EVENT+13
	errortext(ERR_EVENT_BAD_MONITOR_METHOD,"Invalid monitor method encountered.")
#define ERR_EVENT_BAD_TYPE	PKG_EVENT+14
	errortext(ERR_EVENT_BAD_TYPE,"Invalid type encountered.")

#define TASK_NAME_STRINGS			PKG_EVENT+15
	donottranslatetext(TASK_NAME_STRINGS, 	"Chronos|Database Compactor|Admin Process|Agent Manager|Billing|Calendar Connector|Cluster Directory|Cluster Replicator|Collector|Database Server")

#define TASK_NAME_STRINGS_2			PKG_EVENT+16
	donottranslatetext(TASK_NAME_STRINGS_2, "Event|FTP Server|HTTP Web Server|IMAP Server|Indexer|LDAP Server|MTBFManager|NNTP Server|POP3 Server|Router|Replicator|Schedule Manager|Stats|WEB Retriever|Reporter|SMTPMTA|Health Monitoring")

#define ERR_EVENT_REPORT_DB_NOT_OPEN	PKG_EVENT+17
	errortext(ERR_EVENT_REPORT_DB_NOT_OPEN,"The report database could not be opened.")
#define ERR_EVENT_NO_SRV_ACCESS_VIEW	PKG_EVENT+18
	errortext(ERR_EVENT_NO_SRV_ACCESS_VIEW,"The server access view does not exist. Update the Statistics Report template.")

#define ERR_REMOTE_COLLECTOR_QUEUE		PKG_EVENT+19
	errortext(ERR_REMOTE_COLLECTOR_QUEUE,"The Statistics Collector is not running on the proxy server.")

#define ERR_CONFIG_DB_TIMEOUT		PKG_EVENT+20
	errortext(ERR_CONFIG_DB_TIMEOUT,"Task timed out waiting for Monitoring Configuration database to be created. Please restart task.")

#define ERR_ADDIN_CREATE_CONFIG		PKG_EVENT+21
	errortext(ERR_ADDIN_CREATE_CONFIG,"Upgrading or creating the Monitoring Configuration database...")

#define ERR_ADDIN_NO_CONFIG			PKG_EVENT+22
	errortext(ERR_ADDIN_NO_CONFIG,"Cannot create the Monitoring Configuration database.")

#define ERR_EVENT_NOT_LOADED				(PKG_EVENT+23)
	errortext(ERR_EVENT_NOT_LOADED,			"Domino Domain Monitoring functions cannot be executed when the Event task is not loaded.")

#define ERR_DDM_REPORT_DOC_PROBLEM				(PKG_EVENT+24)
	errortext(ERR_DDM_REPORT_DOC_PROBLEM,		"A DDM report document could not be opened.")
#define ERR_DDM_REPORT_DOC_PROBLEM_EXT			(PKG_EVENT+25)
	errortext(ERR_DDM_REPORT_DOC_PROBLEM_EXT,	"A DDM report document (NoteID 0x%X) could not be opened.")

#define ERR_ADDIN_DELETE_GROUP				PKG_EVENT+26
	stringtext(ERR_ADDIN_DELETE_GROUP,		"Do you want to delete the selected groups?")

#define ERR_REMOTE_COLLECTOR_R4				PKG_EVENT+27
	stringtext(ERR_REMOTE_COLLECTOR_R4,		"The remote collection server must be R5 or greater.")

#define ERR_ADDIN_CREATE_REDZONE			PKG_EVENT+28
	errortext(ERR_ADDIN_CREATE_REDZONE,		"Creating the Server Health Monitoring database...")

#define ERR_ADDIN_NO_REDZONE				PKG_EVENT+29
	errortext(ERR_ADDIN_NO_REDZONE,			"Cannot create the Server Health Monitoring database.")

#define ERR_ADDIN_UPDATE_REDZONE			PKG_EVENT+30
	errortext(ERR_ADDIN_UPDATE_REDZONE,		"Updating the Server Health Monitoring database design and configuration documents.")

#define ERR_OPEN_DDM		  				PKG_EVENT+31
	errortext(ERR_OPEN_DDM,					"Event: Error opening domain monitoring database %p")

#define ERR_DDM_LOADING_CFG_VIEW_EVENT		PKG_EVENT+32
	errortext(ERR_DDM_LOADING_CFG_VIEW_EVENT,	"Event: Error loading domain monitoring configuration view '%s'")

#define ERR_DDM_LOADING_CFG_DOC_EVENT		PKG_EVENT+33
	errortext(ERR_DDM_LOADING_CFG_DOC_EVENT,	"Event: Error opening note with note ID 0x%04X")

#define ERR_DDM_LOADING_CFG_EVENT			PKG_EVENT+34
	errortext(ERR_DDM_LOADING_CFG_EVENT,	"Event: Error loading DDM configuration")

#define ERR_DDM_LIB_LOAD_EVENT				PKG_EVENT+35
	errortext(ERR_DDM_LIB_LOAD_EVENT,		"Event: Error loading specified library %s")

#define ERR_LOADING_DDM	   					PKG_EVENT+36
	errortext(ERR_LOADING_DDM,				"Event: Error loading domain monitoring event information from database %p")

#define ERR_DDM_OPEN_NOTE		   			PKG_EVENT+37
	errortext(ERR_DDM_OPEN_NOTE,			"Event: Error opening domain monitoring event document (Note ID 0x%04.04X) in database %p")

#define ERR_DDM_NOT_READY_FOR_BUSINESS			PKG_EVENT+38
	errortext(ERR_DDM_NOT_READY_FOR_BUSINESS,	"Domino Domain Monitoring Database is not yet opened or created. Details will be excluded from some events until the database is available.")

#define ERR_MISSING_ADDIN_NAME				PKG_EVENT+39
	errortext(ERR_MISSING_ADDIN_NAME,		"Events are being generated that should include an addin name, but do not - '%s' (0x%X) : '%s' (0x%X)")

#define ERR_RM_DISK_SPINDLE_INFO_INCOMPLETE			PKG_EVENT+40
	errortext(ERR_RM_DISK_SPINDLE_INFO_INCOMPLETE,	"The provided Disk Spindle Information is incomplete")
#define ERR_RM_DISK_SPINDLE_INFO_EXCESSIVE			PKG_EVENT+41
	errortext(ERR_RM_DISK_SPINDLE_INFO_EXCESSIVE,	"The provided Disk Spindle Information includes disks that do not exist.")
#define ERR_RM_DISK_SPINDLE_INFO_OK					PKG_EVENT+42
	errortext(ERR_RM_DISK_SPINDLE_INFO_OK,			"Disk Spindle Information has been provided in the Directory")
#define ERR_RM_DISK_SPINDLE_INFO_NOT_PROVIDED		PKG_EVENT+43
	errortext(ERR_RM_DISK_SPINDLE_INFO_NOT_PROVIDED,"Disk Spindle Information was not provided in the Directory")

#define ERR_DDM_LOADING_VIEW_EVENT			PKG_EVENT+44
	errortext(ERR_DDM_LOADING_VIEW_EVENT,	"Error loading domain monitoring view '%s'")

#define ERR_DDM_PREEXISTING_PUID			PKG_EVENT+45
	errortext(ERR_DDM_PREEXISTING_PUID,		"Preexisting PUID found %s")

#define ERR_DDM_DUPLICATE_PUID				PKG_EVENT+46
	errortext(ERR_DDM_DUPLICATE_PUID,		"%d duplicate PUIDs found")

#define ERR_NORMAL_NONNORMAL_SEV_MIX		PKG_EVENT+47
	errortext(ERR_NORMAL_NONNORMAL_SEV_MIX,	"Events are being generated with a mixed severity of normal and non-normal - '%s' (%s0x%X Sev=%d) : '%s' (%s0x%X Sev=%d)")


/* Since this name space is so underutilized, it will share its top */
/* space with the briefcase.  So unlike most error ranges, PKG_EVENT */
/* can only range from 0 to 47.  PKG_BCASE goes from 128 to 256. */

/* PKG_EVENT2 more Event codes starting from 0-31 */
			
#define ERR_RM_DISK_UTIL			(PKG_EVENT2+00)
	errortext(ERR_RM_DISK_UTIL,		"Logical disk activity (%s) exceeds configured thresholds.")
#define ERR_RM_MEMORY_UTIL			(PKG_EVENT2+1)
	errortext(ERR_RM_MEMORY_UTIL,	"Memory Utilization exceeds the configured thresholds.")
#define ERR_RM_NETWORK_UTIL			(PKG_EVENT2+2)
	errortext(ERR_RM_NETWORK_UTIL,	"Network adapter activity (%s) exceeds configured thresholds.")
#define ERR_RM_CPU_UTIL				(PKG_EVENT2+3)
	errortext(ERR_RM_CPU_UTIL,		"CPU utilization exceeds configured thresholds.")

#define ERR_ADDINMON_POOL_FULL		(PKG_EVENT2+4)
	errortext(ERR_ADDINMON_POOL_FULL,		"Addin Monitoring pool is full")

#define ERR_ADMIN_MONITOR_SERVER_DOWN					(PKG_EVENT2+5)
	errortext(ERR_ADMIN_MONITOR_SERVER_DOWN, 			"Server %a is no longer running")

#define ERR_ADMIN_MONITOR_SERVER_UP						(PKG_EVENT2+6)
	errortext(ERR_ADMIN_MONITOR_SERVER_UP, 				"Server %a has come back up")

#define ERR_ADMIN_MONITOR_SERVER_TASK_ERROR				(PKG_EVENT2+7)
	errortext(ERR_ADMIN_MONITOR_SERVER_TASK_ERROR, 		"Server task %s on %a reported %s error. (%e)")

#define ERR_ADMIN_MONITOR_SERVER_TASK_TIMEOUT			(PKG_EVENT2+8)
	errortext(ERR_ADMIN_MONITOR_SERVER_TASK_TIMEOUT,	"Server task %s on %a is no longer responding")

#define ERR_ADMIN_MONITOR_SERVER_TASK_RESTART			(PKG_EVENT2+9)
	errortext(ERR_ADMIN_MONITOR_SERVER_TASK_RESTART, 	"Server task %s on %a is responding")

#define ERR_ADMIN_MONITOR_SERVER_TASK_UP				(PKG_EVENT2+10)
	errortext(ERR_ADMIN_MONITOR_SERVER_TASK_UP, 		"Server task %s on %a is running")

#define ERR_ADMIN_MONITOR_SERVER_TASK_DOWN				(PKG_EVENT2+11)
	errortext(ERR_ADMIN_MONITOR_SERVER_TASK_DOWN, 		"Server task %s on %a is no longer running")

#define ERR_ADMIN_MONITOR_SERVER_TASK_NOT_CONFIGURED		(PKG_EVENT2+12)
	errortext(ERR_ADMIN_MONITOR_SERVER_TASK_NOT_CONFIGURED, "Task %s is not configured to run on server %a")

#define	ERR_UPGRADE_MAIL_ERROR			(PKG_EVENT2+13)
	errortext(ERR_UPGRADE_MAIL_ERROR,	"Upgrade mail file error")
			
#define ERR_RM_DISABLED_PLATFORM_STATS			PKG_EVENT2+14
	errortext(ERR_RM_DISABLED_PLATFORM_STATS,	"Platform statistics are disabled")
#define ERR_RM_DISABLED_DISK_COUNTERS_WIN		PKG_EVENT2+15
	errortext(ERR_RM_DISABLED_DISK_COUNTERS_WIN,"Disk counters are disabled")
#define ERR_RM_TRANS_SAME_AS_DATA				PKG_EVENT2+16
	errortext(ERR_RM_TRANS_SAME_AS_DATA,		"Domino data files and transaction logging use the same disk")
#define ERR_RM_TRANS_SAME_AS_DATA_ISERIES		PKG_EVENT2+17
	errortext(ERR_RM_TRANS_SAME_AS_DATA_ISERIES,"Domino data files and transaction logging use the same auxiliary storage pool")
#define ERR_RM_BIN_SAME_AS_DATA					PKG_EVENT2+18
	errortext(ERR_RM_BIN_SAME_AS_DATA,			"Domino data files and Domino executables use the same disk")
#define ERR_RM_BIN_SAME_AS_DATA_ISERIES			PKG_EVENT2+19
	errortext(ERR_RM_BIN_SAME_AS_DATA_ISERIES,	"Domino data files and Domino executables use the same auxiliary storage pool")
#define ERR_RM_DISK_UTIL_NEED_SPINDLE_COUNT		PKG_EVENT2+20
	errortext(ERR_RM_DISK_UTIL_NEED_SPINDLE_COUNT,"Logical disk activity exceeds configured thresholds.")
#define ERR_RM_DISABLED_NET_COUNTERS_WIN		PKG_EVENT2+21
	errortext(ERR_RM_DISABLED_NET_COUNTERS_WIN,	"Network counters are disabled")

#define ERR_DETAILDOC_TOO_LARGE					PKG_EVENT2+22
	errortext(ERR_DETAILDOC_TOO_LARGE,			"Too much detail data reported by DDM probe.  Probe results will be truncated.")

#define ERR_RM_DISK_CLEAR				PKG_EVENT2+23
	errortext(ERR_RM_DISK_CLEAR,		"Logical disk activity (%s) no longer exceeds configured thresholds.")
#define ERR_RM_MEMORY_CLEAR				PKG_EVENT2+24
	errortext(ERR_RM_MEMORY_CLEAR,		"Memory Utilization no longer exceeds the configured thresholds.")
#define ERR_RM_NETWORK_CLEAR			PKG_EVENT2+25
	errortext(ERR_RM_NETWORK_CLEAR,		"Network adapter activity (%s) no longer exceeds configured thresholds.")
#define ERR_RM_CPU_CLEAR				PKG_EVENT2+26
	errortext(ERR_RM_CPU_CLEAR,			"CPU utilization no longer exceeds configured thresholds.")
#define ERR_DDM_TARGET_REFRESH_ERROR		PKG_EVENT2+27
	errortext(ERR_DDM_TARGET_REFRESH_ERROR,	"Problem refreshing DDM target server information")
#define ERR_PROBE_MEM_ALLOC					PKG_EVENT2+28
	errortext(ERR_PROBE_MEM_ALLOC,			"%s received the following memory allocation error: ")

#define	ERR_TEMPLATE_NOT_FOUND				(PKG_EVENT2+29)
	errortext(ERR_TEMPLATE_NOT_FOUND, 		"Event: Unable to create database %s since template file %s cannot be found.")
#define ERR_RM_DISABLED_PLATFORM_STATS_CLEAR			PKG_EVENT2+30
	errortext(ERR_RM_DISABLED_PLATFORM_STATS_CLEAR,	"Platform statistics are enabled")
#define ERR_RM_DISABLED_DISK_COUNTERS_WIN_CLEAR		PKG_EVENT2+31
	errortext(ERR_RM_DISABLED_DISK_COUNTERS_WIN_CLEAR,"Disk counters are enabled")

/* PKG_EVENT2 from 0-31 */

/* PKG_EVENT3 from 0-95 for strings only - no error codes */

#define	STR_STATNAME_DISK_QUEUE_LEN			(PKG_EVENT3 +0)
	stringtext(STR_STATNAME_DISK_QUEUE_LEN	, 	"Avg Disk Queue Length")
#define	STR_STATNAME_DISK_PCT_UTIL			(PKG_EVENT3 +1)
	stringtext(STR_STATNAME_DISK_PCT_UTIL, 		"Percent Disk Utilization")
#define	STR_STATNAME_DISK_SERVICE_TIME		(PKG_EVENT3 +2)
	stringtext(STR_STATNAME_DISK_SERVICE_TIME, 	"Disk Service Time (ms)")
#define	STR_STATNAME_MEMORY_AVAIL_RAM		(PKG_EVENT3 +3)
	stringtext(STR_STATNAME_MEMORY_AVAIL_RAM, 	"Available Memory (MB)")
#define	STR_STATNAME_MEMORY_SCAN_RATE		(PKG_EVENT3 +4)
	stringtext(STR_STATNAME_MEMORY_SCAN_RATE, 	"Scan Rate")
#define	STR_STATNAME_MEMORY_SCAN_RATIO		(PKG_EVENT3 +5)
	stringtext(STR_STATNAME_MEMORY_SCAN_RATIO, 	"Scan Ratio")
/*
* Note: Scan Ratio is not yet being used for AIX.  Scan Rate is being used instead because currently the Event for AIX Memory
*	is currently referred to as Scan Rate, where it should be "Scan Ratio"
*/
#define	STR_STATNAME_MEMORY_FAULT_RATIO		(PKG_EVENT3 +6)
	stringtext(STR_STATNAME_MEMORY_FAULT_RATIO, 	"Fault Ratio")
#define	STR_STATNAME_MEMORY_AVAIL_FRAMES		(PKG_EVENT3 +7)
	stringtext(STR_STATNAME_MEMORY_AVAIL_FRAMES,	"Available Frame Count")
#define	STR_STATNAME_MEMORY_OUT_READY_QUEUE_LEN	(PKG_EVENT3 +8)
	stringtext(STR_STATNAME_MEMORY_OUT_READY_QUEUE_LEN, 	"Out Ready Queue Length")
#define	STR_STATNAME_MEMORY_PAGING_RATE		(PKG_EVENT3 +9)
	stringtext(STR_STATNAME_MEMORY_PAGING_RATE, 	"Paging Rate")

#define	STR_STATNAME_NETWORK_PCT_BANDWIDTH_UTIL			(PKG_EVENT3 +10)
	stringtext(STR_STATNAME_NETWORK_PCT_BANDWIDTH_UTIL, 		"Percent Network Bandwidth Utilization")
#define	STR_STATNAME_NETWORK_PCT_COLLISIONS			(PKG_EVENT3 +11)
	stringtext(STR_STATNAME_NETWORK_PCT_COLLISIONS, 		"Percent Network Collisions")

#define	STR_STATNAME_CPU_PCT_UTIL			(PKG_EVENT3 +12)
	stringtext(STR_STATNAME_CPU_PCT_UTIL, 		"Percent CPU Utilization")
#define	STR_STATNAME_CPU_QUEUE_LEN			(PKG_EVENT3 +13)
	stringtext(STR_STATNAME_CPU_QUEUE_LEN, 		"Avg CPU Queue Length")

#define STR_RM_MOVE_AVG_EXPLAIN				(PKG_EVENT3+14)
	stringtext(STR_RM_MOVE_AVG_EXPLAIN,"\n\nMoving averages are calculated according to Operating System specific performance metrics observed over a rolling 15 minute period of time. Those metrics are exposed as Domino statistics.")
#define STR_RM_MOVE_AVG_EXPLAIN2			(PKG_EVENT3+15)
	stringtext(STR_RM_MOVE_AVG_EXPLAIN2,"When the moving average exceeds the configured threshold, this event is triggered. The moving average is constantly changing. Those changes are not recorded here.")
#define STR_RM_MOVE_AVG_EXPLAIN3			(PKG_EVENT3+16)
	stringtext(STR_RM_MOVE_AVG_EXPLAIN3,"When the moving average no longer exceeds the threshold, the severity of this event will return to 'Normal'.")

#define STR_DDM_MESSAGE_DDOC_HEADER					(PKG_EVENT3+17)
	stringtext(STR_DDM_MESSAGE_DDOC_HEADER,			"Documents in the %s view are sorted by %s. The following strings identify the documents related to this issue.")
#define STR_DDM_MESSAGE_DDOC_HEADER_UNID			(PKG_EVENT3+18)
	stringtext(STR_DDM_MESSAGE_DDOC_HEADER_UNID,	"Documents in the %s view are sorted by %s. The following strings and UNIDs identify the missing documents.")
#define STR_DDM_PUID_DDOC_HEADER					(PKG_EVENT3+19)
	stringtext(STR_DDM_PUID_DDOC_HEADER,			"Documents in the %s view are sorted by a unique identifier string. The following strings identify the documents related to this issue.")

#define STR_DDM_MORE_FOUND_FEW_LISTED				(PKG_EVENT3+20)
	stringtext(STR_DDM_MORE_FOUND_FEW_LISTED,		"More entries where found, but only the first few are listed above.")

#define STR_RM_DISK_UTIL_ARGS		(PKG_EVENT3+21)
	stringtext(STR_RM_DISK_UTIL_ARGS,"When the Disk Probe issued this event, the %s had a Moving Average of %s, which was beyond the threshold value of %s. The device name associated with this event is '%s'. %s %s %s")

#define STR_RM_MEMORY_UTIL_ARGS		(PKG_EVENT3+22)
	stringtext(STR_RM_MEMORY_UTIL_ARGS, "When the Memory Probe issued this event, the %s had a Moving Average of %s, which was beyond the threshold value of %s. %s %s %s")

#define STR_RM_NETWORK_UTIL_ARGS		(PKG_EVENT3+23)
	stringtext(STR_RM_NETWORK_UTIL_ARGS,"When the Network Probe issued this event, the %s had a Moving Average of %s, which was beyond the threshold value of %s. The device name associated with this event is '%s'. %s %s %s")

#define STR_RM_CPU_UTIL_ARGS		(PKG_EVENT3+24)
	stringtext(STR_RM_CPU_UTIL_ARGS, "When the CPU Probe issued this event, the %s had a Moving Average of %s, which was beyond the threshold value of %s. %s %s %s")

#define STR_COMMAND_ARGUMENTS			(PKG_EVENT3+25)
	stringtext(STR_COMMAND_ARGUMENTS,	"%s %s command arguments = %s")
#define STR_TARGET_DB					(PKG_EVENT3+26)
	stringtext(STR_TARGET_DB,			"%s target database = %s")
#define STR_TARGET_DEST_SRV				(PKG_EVENT3+27)
	stringtext(STR_TARGET_DEST_SRV,		"%s target server = %s")
#define STR_TARGET_SRC_SRV				(PKG_EVENT3+28)
	stringtext(STR_TARGET_SRC_SRV,		"%s template source server = %s")

#define ERR_ADDIN_SETUP_EVENTS				(PKG_EVENT3+29)
	stringtext(ERR_ADDIN_SETUP_EVENTS,		"If an event of any type and of severity Fatal, Failure or Warning (High) occurs, log notification to %s.")
#define ERR_ADDIN_SETUP_ACL					(PKG_EVENT3+30)
	stringtext(ERR_ADDIN_SETUP_ACL,			"Generate a Security event of Warning (High) severity if the ACL for database %s changes.  In addition, notify %a by mail.")
#define ERR_ADDIN_SETUP_REPL				(PKG_EVENT3+31)
	stringtext(ERR_ADDIN_SETUP_REPL,		"Generate a Replication event of Warning (High) severity if the database %s on any server has not replicated in 24 hours with ANY server. In addition, notify %a via mail.")

#define STR_TARGET_DIR					(PKG_EVENT3+32)
	stringtext(STR_TARGET_DIR,			"%s target directory = %s")

#define STR_DDM_JS_PLACEHOLDER			(PKG_EVENT3+33)
	stringtext(STR_DDM_JS_PLACEHOLDER,	"Partially initialized DDM job placeholder (0x%04x)")

/* PKG_EVENT3 + 95 is the last available slot NO ERRORCODES! (because 96 = 0x60 = PKG_ADMIN_STR4 - PKG_EVENT3) */

#endif /* EVENT_ERR_DEFS */

#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif

