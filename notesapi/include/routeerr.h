
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

/* PUBLIC error messages returned by Router library routines,
	which may be returned to programs other than the Router itself. */

#ifndef ROUTER_ERR_DEFS
#define ROUTER_ERR_DEFS

#define	ERR_ROUTER_UNKNOWN			(PKG_ROUTER+1)
	errortext(ERR_ROUTER_UNKNOWN,	"*** UNKNOWN ROUTER ERROR ***")
#define ERR_ROUTER_MSGTRACK_REQUEST_UPDATE	(PKG_ROUTER+2)
	errortext(ERR_ROUTER_MSGTRACK_REQUEST_UPDATE, "Error updating message tracking request")
#define ERR_ROUTER_MSGTRACK_REQUEST_QUEUE	(PKG_ROUTER+3)
	errortext(ERR_ROUTER_MSGTRACK_REQUEST_QUEUE, "Error queuing message tracking request")
#define ERR_ROUTER_NOTUNIQUE		(PKG_ROUTER+4)
	errortext(ERR_ROUTER_NOTUNIQUE,	"Recipient user name %a not unique.  Several matches found in Domino Directory.")
#define ERR_ROUTER_NOSUCHUSER		(PKG_ROUTER+5)
	errortext(ERR_ROUTER_NOSUCHUSER,"User %a not listed in Domino Directory")
#define ERR_ROUTER_NOMAILFILE		(PKG_ROUTER+6)
	errortext(ERR_ROUTER_NOMAILFILE, "Recipient's Domino Directory entry does not specify a valid Notes mail file")
#define ERR_ROUTER_NEWMAIL			(PKG_ROUTER+7)
	errortext(ERR_ROUTER_NEWMAIL, "New mail has been delivered to you!")
#define ERR_ROUTER_NOROUTETOSERVERFROM (PKG_ROUTER+8)
	errortext(ERR_ROUTER_NOROUTETOSERVERFROM, "No route found to server %a from server %a.  Check Server and Connection documents in the Domino Directory.")
#define ERR_ROUTER_NOROUTETODOMAINFROM (PKG_ROUTER+9)
	errortext(ERR_ROUTER_NOROUTETODOMAINFROM, "No route found to domain %s from server %a.  Check Server, Connection and Domain documents in the Domino Directory.")
#define ERR_ROUTER_NOROUTETODOMAINVIA (PKG_ROUTER+10)
	errortext(ERR_ROUTER_NOROUTETODOMAINVIA, "No route found to domain %s from server %a via server %a.  Check Server, Connection and Domain documents in the Domino Directory.")
#define ERR_ROUTER_DELIVERY_FILE	(PKG_ROUTER+11)
	errortext(ERR_ROUTER_DELIVERY_FILE, "Error delivering to %a %p; %e")
#define ERR_ROUTER_TRANSFER_FILE	(PKG_ROUTER+12)
	errortext(ERR_ROUTER_TRANSFER_FILE, "Error transferring to %p; %e %s")
#define ERR_ROUTER_NOGROUP			(PKG_ROUTER+13)
	errortext(ERR_ROUTER_NOGROUP, 	"Unsupported use of group name; Cannot send to a Group @ Domain nor auto-forward to a Group")
#define ERR_ROUTER_ROUTING_LOOP		(PKG_ROUTER+14)
	errortext(ERR_ROUTER_ROUTING_LOOP, 	"Maximum hop count exceeded.  Message probably in a routing loop.")
#define ERR_ROUTER_ACCESS_DENIED 	(PKG_ROUTER+15)
	errortext(ERR_ROUTER_ACCESS_DENIED, "Your Domain does not have access to route messages to the specified domain.")
#define ERR_ROUTER_MESSAGE_QUEUE 	(PKG_ROUTER+16)
	errortext(ERR_ROUTER_MESSAGE_QUEUE, "Unable to allocate mail message queue entry.")
#define ERR_ROUTER_MSGQ_POOLFULL 	(PKG_ROUTER+17)
	errortext(ERR_ROUTER_MSGQ_POOLFULL, "Insufficient memory - Router message queue is full.")
#define ERR_ROUTER_TRANSFER_Q_POOLFULL 	(PKG_ROUTER+18)
	errortext(ERR_ROUTER_TRANSFER_Q_POOLFULL, "Insufficient memory - Router transfer queue is full.")
#define ERR_ROUTER_TOO_MANY_RECIPS 	(PKG_ROUTER+19)
	errortext(ERR_ROUTER_TOO_MANY_RECIPS, "Message contains too many recipients (over 4 megabytes).")
#define ERR_ROUTER_LIST_LOOP		(PKG_ROUTER+20)
	errortext(ERR_ROUTER_LIST_LOOP,	"Groups cannot be nested more than 20 levels deep.")
#define ERR_ROUTER_BILLING_NOMEM	(PKG_ROUTER+21)
	errortext(ERR_ROUTER_BILLING_NOMEM, "Billing record not written. Insufficient memory.")  
#define STR_ROUTER_MSGSIZE_FORMULA 		(PKG_ROUTER+22)
	stringtext(STR_ROUTER_MSGSIZE_FORMULA,	"default MAIL_MSGSIZE:=@doclength;@all")
#define ERR_ROUTER_DELIVER_LOOP		(PKG_ROUTER+23)
	errortext(ERR_ROUTER_DELIVER_LOOP, 	"Maximum forwarding loop count exceeded.  Message probably in a forwarding loop. Examine Forwarding Address of intended recipient in Domino Directory.")
#define ERR_ROUTER_NOROUTETODOMAIN		(PKG_ROUTER+24)
	errortext(ERR_ROUTER_NOROUTETODOMAIN,"No route found to domain %s.  Check Server, Connection and Domain documents in Domino Directory.")
#define ERR_ROUTER_NOROUTETOSERVER		(PKG_ROUTER+25)
	errortext(ERR_ROUTER_NOROUTETOSERVER,"No route found to server %a.  Check Server and Connection documents in Domino Directory.")
#define ERR_ROUTER_NOLOCALSERVER		(PKG_ROUTER+26)
	errortext(ERR_ROUTER_NOLOCALSERVER,	"No Server entry in Domino Directory for local server.")
#define ERR_REPORTS_TOOMANYRESPONSES	(PKG_ROUTER+27)
	errortext(ERR_REPORTS_TOOMANYRESPONSES,	"To many responses found when creating message report.")
#define ERR_ROUTER_UPGRADE_FAILED	 	(PKG_ROUTER+28)
	errortext(ERR_ROUTER_UPGRADE_FAILED, "Upgrade of mailbox file %p failed; %e")
#define ERR_ROUTER_TOOMANYCONN			(PKG_ROUTER+29)
	errortext(ERR_ROUTER_TOOMANYCONN,	"Too many Connections")
#define ERR_ROUTER_TOOMANYSERVERS		(PKG_ROUTER+30)
	errortext(ERR_ROUTER_TOOMANYSERVERS,"Too many Servers")
#define ERR_ROUTER_TOOMANYDOMAINS		(PKG_ROUTER+31)
	errortext(ERR_ROUTER_TOOMANYDOMAINS,"Too many Domains")
#define ERR_ROUTER_SYMBOL_TASKS_FULL	(PKG_ROUTER+32)
	errortext(ERR_ROUTER_SYMBOL_TASKS_FULL,"Insufficient memory - Router unable to allocate a new symbol for mailbox task.")
#define ERR_ROUTER_TABLE_MEM_ERROR	 	(PKG_ROUTER+33)
	errortext(ERR_ROUTER_TABLE_MEM_ERROR, "Insufficient memory - Router unable to allocate routing tables.")
#define ERR_ROUTER_DOMAIN_NAMESPACE	 	(PKG_ROUTER+34)
	errortext(ERR_ROUTER_DOMAIN_NAMESPACE, "Unable to add namespace $Domains to Indexer's queue.")
#define ERR_ROUTER_CONNECTION_NAMESPACE	 	(PKG_ROUTER+35)
	errortext(ERR_ROUTER_CONNECTION_NAMESPACE, "Unable to add namespace $Connections to Indexer's queue.")
#define ERR_ROUTER_SERVER_NAMESPACE	 	(PKG_ROUTER+36)
	errortext(ERR_ROUTER_SERVER_NAMESPACE, "Unable to add namespace $Servers to Indexer's queue.")
#define ERR_ROUTER_TOOMANYADJDOMAINS		(PKG_ROUTER+37)
	errortext(ERR_ROUTER_TOOMANYADJDOMAINS,	"Router: Too many Adjacent Domains")
#define ERR_ROUTER_FIND_VIEW_ERR			(PKG_ROUTER+38)
	errortext(ERR_ROUTER_FIND_VIEW_ERR,	"Router: Unable to find view in Domino Directory")
#define ERR_ROUTER_OPEN_VIEW_ERR			(PKG_ROUTER+39)
	errortext(ERR_ROUTER_OPEN_VIEW_ERR,	"Router: Unable to open view in Domino Directory")

#define ERR_ROUTER_MBOX_UPGRADE				(PKG_ROUTER+40)
	errortext(ERR_ROUTER_MBOX_UPGRADE, 		"Upgrading mailbox file %p")

#define ERR_ROUTER_DOMAIN_BUFFER_EXCEEDED	(PKG_ROUTER+41)
	errortext(ERR_ROUTER_DOMAIN_BUFFER_EXCEEDED, "Insufficient memory - Forwarding address + domain name exceeds buffer size for recipient %s.")

#define ERR_ROUTER_SYMBOL_TABLE						(PKG_ROUTER+42)
	errortext(ERR_ROUTER_SYMBOL_TABLE,				"Unable to add name to routing symbol table")
#define ERR_ROUTER_SERVERNOTLOCALDOMAIN				(PKG_ROUTER+43)
	errortext(ERR_ROUTER_SERVERNOTLOCALDOMAIN,		"Router: Server %a not in local domain; Server ignored.")
#define ERR_ROUTER_DUPSERVER						(PKG_ROUTER+44)
	errortext(ERR_ROUTER_DUPSERVER,					"Router: Duplicate server entry in Domino Directory for %a")
#define ERR_ROUTER_NOSERVERENTRY					(PKG_ROUTER+45)
	errortext(ERR_ROUTER_NOSERVERENTRY,				"Router: Connection from server %a not used; Server not found in Domino Directory.")
#define ERR_ROUTER_CONNNOTLOCALDOMAIN				(PKG_ROUTER+46)
	errortext(ERR_ROUTER_CONNNOTLOCALDOMAIN,		"Router: Connection from server %a not used; Server not in local domain.")
#define ERR_ROUTER_ROUTE_TO_SELF					(PKG_ROUTER+47)
	errortext(ERR_ROUTER_ROUTE_TO_SELF, 	"Attempt made to transfer message to self via SMTP. Possible DNS configuration error.")
#define ERR_ROUTER_DNS_UNAVAILABLE					(PKG_ROUTER+48)
	errortext(ERR_ROUTER_DNS_UNAVAILABLE,			"DNS is unavailable, message will be requeued.")
#define ERR_ROUTER_TOO_BIG							(PKG_ROUTER+49)
	errortext(ERR_ROUTER_TOO_BIG,					"The size of this message exceeds the administrator specified maximum message size for this server")
#define ERR_ROUTER_DUPPULLCONN						(PKG_ROUTER+50)
	errortext(ERR_ROUTER_DUPPULLCONN,				"Router: Duplicate Pull Routing connection entry in Domino Directory for %a")

#define ERR_ROUTER_DELIVERY_USER	(PKG_ROUTER+51)
	errortext(ERR_ROUTER_DELIVERY_USER, "Error delivering to %a; %e")

#define ERR_ROUTER_MSGTRACK_UNDERQUALIFIED			(PKG_ROUTER+52)
	errortext(ERR_ROUTER_MSGTRACK_UNDERQUALIFIED,	"Message tracking query returned more than one result")
#define ERR_ROUTER_MSGTRACK_INPROGRESS				(PKG_ROUTER+53)
	errortext(ERR_ROUTER_MSGTRACK_INPROGRESS,		"Tracking operation is in progress.") 
#define ERR_ROUTER_MSGTRACK_NOTFOUND				(PKG_ROUTER+54)
	errortext(ERR_ROUTER_MSGTRACK_NOTFOUND,			"Message tracking query returned no results")
#define ERR_ROUTER_MSGTRACK_DUPLICATE				(PKG_ROUTER+55)
	errortext(ERR_ROUTER_MSGTRACK_DUPLICATE,		"Found an unexpected duplicate message")
#define ERR_ROUTER_MBOX_TITLE	 					(PKG_ROUTER+56)
	errortext(ERR_ROUTER_MBOX_TITLE,				"%.*s Mailbox")
#define ERR_ROUTER_PROFILE_OPEN_ERROR				(PKG_ROUTER+57)
	errortext(ERR_ROUTER_PROFILE_OPEN_ERROR,		"Router: Unable to retrieve mail filters from database %s; %e")
#define ERR_ROUTER_MSGTRACK_AUTHENTICATION			(PKG_ROUTER+58)
	errortext(ERR_ROUTER_MSGTRACK_AUTHENTICATION,	"You are not authorized to do message tracking")
#define ERR_ROUTER_MSGTRACK_SUBJECT					(PKG_ROUTER+59)
	errortext(ERR_ROUTER_MSGTRACK_SUBJECT,			"You are not authorized to track message subjects.")
#define ERR_ROUTER_FILE_IN_USE						(PKG_ROUTER+60)
	errortext(ERR_ROUTER_FILE_IN_USE,				"Delivery to mail file in progress by another thread, try again later")
#define ERR_ROUTER_MBOX_CREATE						(PKG_ROUTER+61)
	errortext(ERR_ROUTER_MBOX_CREATE,				"Creating new mailbox file %p")
#define ERR_ROUTER_MBOX_OPEN						(PKG_ROUTER+62)
	errortext(ERR_ROUTER_MBOX_OPEN, 				"Unable to open mailbox file %p")
#define ERR_ROUTER_NOROUTETOIDOMAIN					(PKG_ROUTER+63)
	errortext(ERR_ROUTER_NOROUTETOIDOMAIN,"No route found to domain %s.  Check DNS configuration.")
#define ERR_ROUTER_FILTERS_UPDATED					(PKG_ROUTER+64)
	errortext(ERR_ROUTER_FILTERS_UPDATED,			"Successfully registered %d system filters.")
#define ERR_ROUTER_FILTERS_ERROR					(PKG_ROUTER+65)
	errortext(ERR_ROUTER_FILTERS_ERROR,				"Error registering system filters: %e.")
#define	ERR_CMD_SET_RULES							(PKG_ROUTER+66)
	stringtext(ERR_CMD_SET_RULES,					"RULES")
#define	ERR_HELP_SET_RULES							(PKG_ROUTER+67)
	stringtext(ERR_HELP_SET_RULES,					"Reload system mail rules")
#define	ERR_SENDER_NOT_AUTHORIZED_TO_MAIL_TO_USER	(PKG_ROUTER+68)
	stringtext(ERR_SENDER_NOT_AUTHORIZED_TO_MAIL_TO_USER,	"Not authorized to send mail to this user or group")

/* R6 SMTP Logical Function Hooks */
#define ERR_HOOK_SMTP_ERROR							(PKG_ROUTER+69)
	errortext(ERR_HOOK_SMTP_ERROR, 					"SMTP Protocol Returned a Permanent Error")
#define ERR_HOOK_SMTP_TRANSIENT						(PKG_ROUTER+70)
	errortext(ERR_HOOK_SMTP_TRANSIENT, 				"SMTP Protocol Returned a Transient Error")

#define ERR_ROUTER_MAX_USER_FILTERS					(PKG_ROUTER+71)
	errortext(ERR_ROUTER_MAX_USER_FILTERS,			"Router: Maximum number user mail rules exceeded for %a. Only the first %d enabled rules will be executed. %d not registered.")
#define ERR_ROUTER_MAX_SYSTEM_FILTERS				(PKG_ROUTER+72)
	errortext(ERR_ROUTER_MAX_SYSTEM_FILTERS,		"Maximum number of system mail rules exceeded. Only the first %d enabled rules will be executed. %d not registered.")
#define ERR_ROUTER_RULE_REGISTER_ERROR				(PKG_ROUTER+73)
	errortext(ERR_ROUTER_RULE_REGISTER_ERROR,		"Error registering mail rule %d for database %s")
#define ERR_ROUTER_TOO_MANY_EXPANDED			 	(PKG_ROUTER+74)
	errortext(ERR_ROUTER_TOO_MANY_EXPANDED, 		"Group expansion results exceed maximum size")
#define ERR_ROUTER_MAX_BLOCK_RULE_SIZE				(PKG_ROUTER+75)
	errortext(ERR_ROUTER_MAX_BLOCK_RULE_SIZE,		"Block sender rule exceeds maximum size set by administrator.")
#define ERR_ROUTER_EFFECTIVE_SIZE_TOO_BIG			(PKG_ROUTER+76)
	errortext(ERR_ROUTER_EFFECTIVE_SIZE_TOO_BIG,		"Router: Unable to dispatch message. Effective size, number of recipients times message size, %ld exceeds %ld KBytes")
#define ERR_ROUTER_MAX_DELIVERY_DB_SIZE				(PKG_ROUTER+77)
	errortext(ERR_ROUTER_MAX_DELIVERY_DB_SIZE,		"Router: Recipient's mail file size exceeds the maximum size allowed for mail delivery.")

/* NOTE:	PKG_ROUTER+79 is the LAST code available for this file.  See */
/* globerr.h for dependency which restricts this string ID space. */


#define ERR_ROUTER2_OVERDISKQUOTA				(PKG_ROUTER2+1)
	errortext(ERR_ROUTER2_OVERDISKQUOTA,			"Router: Database disk quota exceeded")
#define ERR_ROUTER2_TEMP_OVERDISKQUOTA				(PKG_ROUTER2+2)
	errortext(ERR_ROUTER2_TEMP_OVERDISKQUOTA,		"Router: Warning: database disk quota exceeded")
#define ERR_ROUTER2_CONNECT_FAILED				(PKG_ROUTER2+3)
	errortext(ERR_ROUTER2_CONNECT_FAILED,			"Router: Failed to connect to SMTP host %a because %s")
#define ERR_ROUTER2_SMTPRELAY					(PKG_ROUTER2+4)
	errortext(ERR_ROUTER2_SMTPRELAY,				"Your message was successfully relayed by %s at %s to the remote mail system %s that does not support confirmation of delivery.")
#define ERR_ROUTER2_MESSAGE_SIZE_TOO_BIG				(PKG_ROUTER2+5)
	errortext(ERR_ROUTER2_MESSAGE_SIZE_TOO_BIG, 		"Router: Unable to dispatch message. Size exceeds %ld KBytes")
#define ERR_ROUTER2_SENDING_RESTRICTION				(PKG_ROUTER2+6)
	errortext(ERR_ROUTER2_SENDING_RESTRICTION, 		"Router: %s is restricted from sending mail through server %a")
#define ERR_ROUTER2_NOROUTETODOMAINDNS 				(PKG_ROUTER2+7)
	errortext(ERR_ROUTER2_NOROUTETODOMAINDNS,		"No route found to domain %s from server %a.  Check DNS configuration.")
#define ERR_ROUTER2_LOW_PRIORITY_DELAY				(PKG_ROUTER2+8)
	errortext(ERR_ROUTER2_LOW_PRIORITY_DELAY,		"Router: Message transfer for %d recipients has been delayed until low priority time range %z - %z")
#define ERR_ROUTER2_ACTION_NDR_MSG				(PKG_ROUTER2+9)
	errortext(ERR_ROUTER2_ACTION_NDR_MSG,			"Message rejected for policy reasons")
#define ERR_ROUTER2_SMTPRELAY_OUTBOUND				(PKG_ROUTER2+10)
	errortext(ERR_ROUTER2_SMTPRELAY_OUTBOUND,		"Your message was successfully relayed by %s at %s to the remote mail system %s. Outbound support for confirmations is not configured.")
#define ERR_ROUTER2_ANONYMOUS_RESTRICTION			(PKG_ROUTER2+11)
	errortext(ERR_ROUTER2_ANONYMOUS_RESTRICTION,		"Router: Administrator has specified that Anonymous mail cannot be routed.")
#define ERR_ROUTER_OOOPROFILE_OPEN_ERROR			(PKG_ROUTER2+12)
	errortext(ERR_ROUTER_OOOPROFILE_OPEN_ERROR,		"Router: Unable to open out of office profile in database %p: %e")
#define ERR_ROUTER_OOO_DISABLE_ERROR				(PKG_ROUTER2+13)
	errortext(ERR_ROUTER_OOO_DISABLE_ERROR,			"Router: Error disabling out of office service in database %p: %e")
#define ERR_ROUTER_OOO_INITCACHE_ERROR				(PKG_ROUTER2+14)
	errortext(ERR_ROUTER_OOO_INITCACHE_ERROR,		"Router: Error initializing out of office service in database %p: %e")
#define ERR_ROUTER_OOO_NOTIFY_ERROR					(PKG_ROUTER2+15)	
	errortext(ERR_ROUTER_OOO_NOTIFY_ERROR,			"Router: Error generating out of office notification from %a to %a: %e")
#define ERR_ROUTER_OOO_REPORT_ERROR					(PKG_ROUTER2+16)
	errortext(ERR_ROUTER_OOO_REPORT_ERROR,			"Router: Error generating out of office report in %p: %e")
#define ERR_ROUTER_OOO_NOTIFYLIST_ERROR				(PKG_ROUTER2+17)
	errortext(ERR_ROUTER_OOO_NOTIFYLIST_ERROR,		"Router: Error processing out of office responder for %a, failed to add %a to the list of notified people: %e")
#define ERR_ROUTER_OOO_ICONNOTE_ERROR				(PKG_ROUTER2+18)
	errortext(ERR_ROUTER_OOO_ICONNOTE_ERROR,		"Router: Failed to open icon note for  %s")
#define ERR_ROUTER_OOO_PROFILEUPDATE_ERROR			(PKG_ROUTER2+19)
	errortext(ERR_ROUTER_OOO_PROFILEUPDATE_ERROR,	"Router: Error updating out of office profile document for  %a")
#define ERR_ROUTER_OOO_FAILOVERAGENT_ERROR			(PKG_ROUTER2+20)
	errortext(ERR_ROUTER_OOO_FAILOVERAGENT_ERROR,	"Router: Error executing out of office failover agent (%s) in  %a")
#define ERR_ROUTER_OOO_DAILYREPORT_ERROR			(PKG_ROUTER2+21)
	errortext(ERR_ROUTER_OOO_DAILYREPORT_ERROR,		"Router: Error during daily maintance check for out of office service in '%p': %e")
#define ERR_ROUTER2_DELIVERY_DELAY					(PKG_ROUTER2+22)
	errortext(ERR_ROUTER2_DELIVERY_DELAY,			"Your message has been delayed due to a temporary network, server, or mail file unavailability. Delivery of your message will be attempted again.")
#define ERR_ROUTER_OOO_NONHOME_SERVER					(PKG_ROUTER2+23)
	errortext(ERR_ROUTER_OOO_NONHOME_SERVER,			"Router: Out of office service for %a will be disabled on the home mail server %a.")
#define ERR_ROUTER_OOO_CACHEDLIST_ERROR				(PKG_ROUTER2+24)
	errortext(ERR_ROUTER_OOO_CACHEDLIST_ERROR,		"Router: Error processing out of office responder for %a, failed processing in memory list %a : %e")
#define ERR_ROUTER_SMTP_AUTH_NO_RELAY_SPEC			(PKG_ROUTER2+25)
	errortext(ERR_ROUTER_SMTP_AUTH_NO_RELAY_SPEC,	"Router: SMTP Authentication disabled.  No relay host specified in server config doc.")
#define ERR_ROUTER_JOURNAL_SMIME_ENC_FAILURE		(PKG_ROUTER2+26)
	errortext(ERR_ROUTER_JOURNAL_SMIME_ENC_FAILURE,	"Router: Failed to SMIME Encrypt message on delivery to journalling database on behalf of %s")
#define ERR_ROUTER_RECIP_SMIME_ENC_FAILURE			(PKG_ROUTER2+27)
	errortext(ERR_ROUTER_RECIP_SMIME_ENC_FAILURE,	"Router: Failed to SMIME Encrypt message on delivery to recipient %s")
#define ERR_ROUTER_RECIP_SMIME_KEY_NA				(PKG_ROUTER2+28)
	errortext(ERR_ROUTER_RECIP_SMIME_KEY_NA,		"Router: SMIME Encryption key not available for recipient")
#define ERR_ROUTER_OOO_DISABLE_FAILED				(PKG_ROUTER2+29)
	errortext(ERR_ROUTER_OOO_DISABLE_FAILED,		"Router: Error disabling out of office service for %s. Failed to reset database options.")
/* non-production error for DDM */
#define ERR_ROUTER_OOO_DEBUG_OOS					(PKG_ROUTER2+30)
	errortext(ERR_ROUTER_OOO_DEBUG_OOS,				"Router: Delivered message already processed by Out of office service. Message to '%s' from '%s', subject '%s', noteid '%s' ")


/* NOTE:	PKG_ROUTER2+47 is the LAST code available for this file.  See */
/* globerr.h for dependency which restricts this string ID space. */


#define STR_ROUTER_QUOTA_WARNING_REPORT				(PKG_ROUTER_STR+1)
	stringtext(STR_ROUTER_QUOTA_WARNING_REPORT,		"Quota Warning Report")
#define STR_ROUTER_QUOTA_ERROR_REPORT				(PKG_ROUTER_STR+2)
	stringtext(STR_ROUTER_QUOTA_ERROR_REPORT,		"Over Quota Error")
#define STR_ROUTER_OOO_REPORT						(PKG_ROUTER_STR+3)
	stringtext(STR_ROUTER_OOO_REPORT,				"While you were out, the following people were notified of your absence:")
#define STR_ROUTER_OOO_REPORT_NONE					(PKG_ROUTER_STR+4)
	stringtext(STR_ROUTER_OOO_REPORT_NONE,			"While you were out, no one was notified of your absence.")
#define STR_ROUTER_OOO_REPORT_SUBJECT				(PKG_ROUTER_STR+5)
	stringtext(STR_ROUTER_OOO_REPORT_SUBJECT,		"Out-of-office Summary")
#define STR_ROUTER_OOO_NOTIFY_ONCE					(PKG_ROUTER_STR+6)
	stringtext(STR_ROUTER_OOO_NOTIFY_ONCE,			"This is the only notification you will receive while this person is away.")
#define STR_ROUTER_OOO_ENUMERATE					(PKG_ROUTER_STR+7)
	stringtext(STR_ROUTER_OOO_ENUMERATE,			"Out of office service is activated in the following databases:")
#define STR_ROUTER_OOO_REPORT_START					(PKG_ROUTER_STR+8)
	stringtext(STR_ROUTER_OOO_REPORT_START,			"Beginning Out of office service daily maintenance.")
#define STR_ROUTER_OOO_REPORT_END					(PKG_ROUTER_STR+9)
	stringtext(STR_ROUTER_OOO_REPORT_END,			"Completed Out of office service daily maintenance.")
#define STR_ROUTER_OOO_DAILY_REPORT					(PKG_ROUTER_STR+10)
	stringtext(STR_ROUTER_OOO_DAILY_REPORT,			"Router: Daily maintenance OOO for %p.")
/* message below has 2 substrings, preserve vertical bar */
#define STR_ROUTER_OOO_GENERATEDBY					(PKG_ROUTER_STR+11)
	stringtext(STR_ROUTER_OOO_GENERATEDBY,			"Note: This is an automated response to your message | sent on ")
#define STR_ROUTER_OOO_NOTIFY_MANY					(PKG_ROUTER_STR+12)
	stringtext(STR_ROUTER_OOO_NOTIFY_MANY,			"You will receive a notification for each message you send to this person while the person is away.")	
#define STR_ROUTER_OOO_ENABLEDFOR					(PKG_ROUTER_STR+13)
	stringtext(STR_ROUTER_OOO_ENABLEDFOR,			"mail file: %s")
#define STR_ROUTER_OOO_ENDENUMERATE					(PKG_ROUTER_STR+14)
	stringtext(STR_ROUTER_OOO_ENDENUMERATE,			"Completed scan for active Out of office service.")
/* PKG_ROUTER_STR goes to 127 */


/* NOTE:	PKG_ROUTER_STR+127 is the LAST code available for this file.  See */
/* globerr.h for dependency which restricts this string ID space. */


#endif

  

#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif
