
#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(P128)
#endif

/* ***************************************************************** */
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
/* ***************************************************************** */


#ifndef _LBER_H
#define _LBER_H

#ifdef __cplusplus
extern "C" {
#endif


#define LBER_BIG_TAG_MASK	0x1f
#define LBER_MORE_TAG_MASK	0x80

/*
 * Note that LBER_ERROR and LBER_DEFAULT are values that can never appear
 * as valid BER tags, and so it is safe to use them to report errors.  In
 * fact, any tag for which the following is true is invalid:
 *     (( tag & 0x00000080 ) != 0 ) && (( tag & 0xFFFFFF00 ) != 0 )
 */

/* on 64bit platforms where long is 64bit, 0xffffffff doesn't wrap and so putting it into an int and comparing it will not match
 * so, changing this to 1 less so that it can be stored in an int
 */
#if defined(NDUNIX64)
#define LBER_ERROR			0xfffffffe
#define LBER_DEFAULT		0xfffffffe
#else
#define LBER_ERROR			0xffffffff
#define LBER_DEFAULT		0xffffffff
#endif

/* general BER types we know about */

#define LBER_BOOLEAN		0x01
#define LBER_INTEGER		0x02
#define LBER_BITSTRING		0x03
#define LBER_OCTETSTRING	0x04
#define LBER_NULL			0x05
#define LBER_OBJECTID 		0x06
#define LBER_ENUMERATED		0x0a
#define LBER_IA5STRING 		0x16
#define LBER_SEQUENCE		0x30	/* constructed */
#define LBER_SET			0x31	/* constructed */

typedef struct berelement	BerElement;

#define NULLBER	((BerElement *) 0)


typedef unsigned int ber_tag_t;
typedef unsigned int ber_len_t;
typedef int ber_int_t;
typedef unsigned int ber_uint_t;
typedef int ber_slen_t;

/*  Structure for returning a sequence of octet strings + length */

typedef struct berval 
	{
	ber_len_t		bv_len;
	char			*bv_val;
	} Berval;

typedef Berval BerValue;


/*
*   Function Prototypes
*/

#define ber_skip_tag(ber, len)							ND_ber_skip_tag((ber), (len))
#define ber_peek_tag(ber, len)							ND_ber_peek_tag((ber), (len))
#define ber_first_element(ber, len, last)				ND_ber_first_element((ber), (len), (last))
#define ber_next_element(ber, len, last)				ND_ber_next_element((ber), (len), (last))
#define ber_scanf										ND_ber_scanf
#define ber_bvfree(bv)									ND_ber_bvfree((bv))
#define ber_bvecfree(bv)								ND_ber_bvecfree((bv))
#define ber_bvdup(bv)									ND_ber_bvdup((bv))
#define ber_printf										ND_ber_printf
#define ber_free(ber, freebuf)							ND_ber_free((ber), (freebuf))
#define ber_alloc_t(options)							ND_ber_alloc_t((options))
#define ber_init(bv)									ND_ber_init((bv))
#define ber_flatten(ber, bvPtr)							ND_ber_flatten((ber), (bvPtr))

/* for V3 API */
ber_tag_t LNPUBLIC ND_ber_skip_tag( BerElement *ber, ber_len_t *len );
ber_tag_t LNPUBLIC ND_ber_peek_tag( BerElement *ber, ber_len_t *len );
ber_tag_t LNPUBLIC ND_ber_first_element( BerElement *ber, ber_len_t *len, char **last);
ber_tag_t LNPUBLIC ND_ber_next_element( BerElement *ber, ber_len_t *len, char *last);
ber_tag_t LNVARARGS ND_ber_scanf( BerElement *ber, const char *fmt, ... );

void LNPUBLIC ND_ber_bvfree( struct berval *bv );
void LNPUBLIC ND_ber_bvecfree( struct berval **bv );
struct berval *	LNPUBLIC ND_ber_bvdup( const struct berval *bv );
int	LNVARARGS ND_ber_printf( BerElement *ber, const char *fmt, ... );
void LNPUBLIC ND_ber_free( BerElement *ber, int freebuf );
BerElement * LNPUBLIC ND_ber_alloc_t( int options );
BerElement * LNPUBLIC ND_ber_init( const struct berval *bv );
int LNPUBLIC ND_ber_flatten(BerElement *ber, struct berval **bvPtr);
#ifdef __cplusplus
}
#endif
#endif /* _LBER_H */

#if defined(OS400) && (__OS400_TGTVRM__ >= 510)
#pragma datamodel(pop)
#endif

