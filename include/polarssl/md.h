/**
 * \file md.h
 * 
 * \brief Generic message digest wrapper
 *
 * \author Adriaan de Jong <dejong@fox-it.com>
 *
 *  Copyright (C) 2006-2010, Brainspark B.V.
 *
 *  This file is part of PolarSSL (http://www.polarssl.org)
 *  Lead Maintainer: Paul Bakker <polarssl_maintainer at polarssl.org>
 *
 *  All rights reserved.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef POLARSSL_MD_H
#define POLARSSL_MD_H

typedef enum {
    POLARSSL_MD_MD2=0,
    POLARSSL_MD_MD4,
    POLARSSL_MD_MD5,
    POLARSSL_MD_SHA1,
    POLARSSL_MD_SHA224,
    POLARSSL_MD_SHA256,
    POLARSSL_MD_SHA384,
    POLARSSL_MD_SHA512,
} md_type_t;

/**
 * Message digest information. Allows message digest functions to be called
 * in a generic way.
 */
typedef struct {
    /** Digest identifier */
    md_type_t type;

    /** Name of the message digest */
    const char * name;

    /** Output length of the digest function */
    int size;

    /** Digest initialisation function */
    void (*starts_func)( void *ctx );

    /** Digest update function */
    void (*update_func)( void *ctx, const unsigned char *input, int ilen );

    /** Digest finalisation function */
    void (*finish_func)( void *ctx, unsigned char *output );

    /** Generic digest function */
    void (*digest_func)( const unsigned char *input, int ilen,
                            unsigned char *output );

    /** Generic file digest function */
    int (*file_func)( const char *path, unsigned char *output );

    /** HMAC Initialisation function */
    void (*hmac_starts_func)( void *ctx, const unsigned char *key, int keylen );

    /** HMAC update function */
    void (*hmac_update_func)( void *ctx, const unsigned char *input, int ilen );

    /** HMAC finalisation function */
    void (*hmac_finish_func)( void *ctx, unsigned char *output);

    /** HMAC context reset function */
    void (*hmac_reset_func)( void *ctx );

    /** Generic HMAC function */
    void (*hmac_func)( const unsigned char *key, int keylen,
                    const unsigned char *input, int ilen,
                    unsigned char *output );

    /** Allocate a new context */
    void * (*ctx_alloc_func)( void );

    /** Free the given context */
    void (*ctx_free_func)( void *ctx );

} md_info_t;

/**
 * Generic message digest context.
 */
typedef struct {
    /** Information about the associated message digest */
    const md_info_t *md_info;

    /** Digest-specific context */
    void *md_ctx;
} md_context_t;

#define MD_CONTEXT_T_INIT { \
    NULL, /* md_info */ \
    NULL, /* md_ctx */ \
}

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief           Returns the message digest information associated with the
 *                  given digest name.
 *
 * \param md_name	Name of the digest to search for.
 *
 * \return          The message digest information associated with md_name or
 *                  NULL if not found.
 */
const md_info_t *md_info_from_string( const char *md_name );

/**
 * \brief           Returns the message digest information associated with the
 *                  given digest type.
 *
 * \param md_type   type of digest to search for.
 *
 * \return          The message digest information associated with md_type or
 *                  NULL if not found.
 */
const md_info_t *md_info_from_type( md_type_t md_type );

/**
 * \brief           Returns the size of the message digest output.
 *
 * \param md_info   message digest info
 *
 * \return          size of the message digest output.
 */
static inline unsigned char md_get_size ( const md_info_t *md_info)
{
    return md_info->size;
}

/**
 * \brief           Returns the type of the message digest output.
 *
 * \param md_info   message digest info
 *
 * \return          type of the message digest output.
 */
static inline md_type_t md_get_type ( const md_info_t *md_info )
{
    return md_info->type;
}

/**
 * \brief           Returns the name of the message digest output.
 *
 * \param md_info   message digest info
 *
 * \return          name of the message digest output.
 */
static inline const char *md_get_name ( const md_info_t *md_info )
{
    return md_info->name;
}

/**
 * \brief          Generic message digest context setup.
 *
 * \param md_info  message digest info
 * \param ctx      generic message digest context. May not be NULL. The
 *                 digest-specific context (ctx->md_ctx) must be NULL. It will
 *                 be allocated, and must be freed using md_free() later.
 *
 * \returns        0 on success, 1 if parameter verification fails.
 */
int md_starts( const md_info_t *md_info, md_context_t *ctx );

/**
 * \brief          Generic message digest process buffer
 *
 * \param ctx      Generic message digest context
 * \param input    buffer holding the  datal
 * \param ilen     length of the input data
 *
 * \returns        0 on success, 1 if parameter verification fails.
 */
int md_update( md_context_t *ctx, const unsigned char *input, int ilen );

/**
 * \brief          Generic message digest final digest
 *
 * \param ctx      Generic message digest context
 * \param output   Generic message digest checksum result
 *
 * \returns        0 on success, 1 if parameter verification fails.
 */
int md_finish( md_context_t *ctx, unsigned char *output );

/**
 * \brief          Free the message-specific context of ctx. Freeing ctx itself
 *                 remains the responsibility of the caller.
 *
 * \param ctx      Free the -specific context
 * \param output   Generic message digest checksum result
 *
 * \returns        0 on success, 1 if parameter verification fails.
 */
int md_free_ctx( md_context_t *ctx );

/**
 * \brief          Output = message_digest( input buffer )
 *
 * \param md_info  message digest info
 * \param input    buffer holding the  data
 * \param ilen     length of the input data
 * \param output   Generic message digest checksum result
 *
 * \returns        0 on success, 1 if parameter verification fails.
 */
int md( const md_info_t *md_info, const unsigned char *input, int ilen,
        unsigned char *output );

/**
 * \brief          Output = message_digest( file contents )
 *
 * \param md_info  message digest info
 * \param path     input file name
 * \param output   generic message digest checksum result
 *
 * \return         0 if successful, 1 if fopen failed,
 *                 2 if fread failed, 3 if md_info was NULL
 */
int md_file( const md_info_t *md_info, const char *path, unsigned char *output );

/**
 * \brief          Generic HMAC context setup
 *
 * \param md_info  message digest info
 * \param ctx      HMAC context to be initialized
 * \param key      HMAC secret key
 * \param keylen   length of the HMAC key
 *
 * \returns        0 on success, 1 if parameter verification fails.
 */
int md_hmac_starts( const md_info_t *md_info, md_context_t *ctx,
                    const unsigned char *key, int keylen );

/**
 * \brief          Generic HMAC process buffer
 *
 * \param ctx      HMAC context
 * \param input    buffer holding the  data
 * \param ilen     length of the input data
 *
 * \returns        0 on success, 1 if parameter verification fails.
 */
int md_hmac_update( md_context_t *ctx, const unsigned char *input, int ilen );

/**
 * \brief          Generic HMAC final digest
 *
 * \param ctx      HMAC context
 * \param output   Generic HMAC checksum result
 *
 * \returns        0 on success, 1 if parameter verification fails.
 */
int md_hmac_finish( md_context_t *ctx, unsigned char *output);

/**
 * \brief          Generic HMAC context reset
 *
 * \param ctx      HMAC context to be reset
 *
 * \returns        0 on success, 1 if ctx is NULL.
 */
int md_hmac_reset( md_context_t *ctx );

/**
 * \brief          Output = Generic_HMAC( hmac key, input buffer )
 *
 * \param md_info  message digest info
 * \param key      HMAC secret key
 * \param keylen   length of the HMAC key
 * \param input    buffer holding the  data
 * \param ilen     length of the input data
 * \param output   Generic HMAC-result
 *
 * \returns        0 on success, 1 if parameter verification fails.
 */
int md_hmac( const md_info_t *md_info, const unsigned char *key, int keylen,
                const unsigned char *input, int ilen,
                unsigned char *output );

#ifdef __cplusplus
}
#endif

#endif /* POLARSSL_MD_H */