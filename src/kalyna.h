/*
* Copyright 2016 Erint Labs OÜ
*
* Licensed under the EUPL, Version 1.1 or – as soon they
* will be approved by the European Commission - subsequent
* versions of the EUPL (the "Licence");
* You may not use this work except in compliance with the
* Licence.
* You may obtain a copy of the Licence at:
*
* https://joinup.ec.europa.eu/software/page/eupl
*
* Unless required by applicable law or agreed to in
* writing, software distributed under the Licence is
* distributed on an "AS IS" basis,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
* express or implied.
* See the Licence for the specific language governing
* permissions and limitations under the Licence.
*/
#ifndef UKRYPTO_KALYNA_H_ 
#define UKRYPTO_KALYNA_H_ 

#include <stdlib.h>
#include <stdint.h> 
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * \file kalyna.h
 * \brief ДСТУ7624:2014 implemenation in C99
 * \author Oleksiy Protas
 *
 * Ukrainian ДСТУ7624:2014 ("Калина") standard block cipher implemenation. 
 * Part of Ukrainian cryptopgraphy standards support for OpenSSL, but written
 * in a library-agnostic way. OpenSSL specific glue code is in `e_ukrypto.c`
 *
 */

/*!
 * Kalyna cipher context structure.
 */
typedef struct 
{
    size_t bs;          /**< Block size, bytes. */
    size_t ks;          /**< Key size, bytes. */
    size_t rs;          /**< Rounds passed. */
    bool encrypt;       /**< Whether we are encrypting or decrypting. */
    uint8_t *state;     /**< State matrix. */
    uint8_t *key;       /**< Encryption key. */
} UKRYPTO_KALYNA_CTX;

/*!
 * Cipher initialisation.
 * 
 * @param ctx[in]       Preallocated context structure pointer. 
 * @param bs[in]        Block size in bits (125, 256 or 512).
 * @param ks[in]        Key size in bits (equal or double block size).
 * @param key[in]       Encryption key.
 * @param encrypt[in]   true if we are encrypting, false otherwise.
 * 
 * @return 1 on success, 0 otherwise.
 */
int ukrypto_kalyna_init(UKRYPTO_KALYNA_CTX *ctx, unsigned short bs, unsigned short ks, uint8_t key, bool encrypt);

/*!
 * Cipher cleanup.
 * 
 * @param ctx[in]       Context pointer.
 * @return 1 on sucess, 0 otherwise.
 */
int ukrypto_kalyna_cleanup(UKRYPTO_KALYNA_CTX *ctx);

/*!
 * Execute the cipher function and write the result.
 * 
 * @param ctx[in]       Context pointer.
 * @param out[out]      Preallocated buffer to store output to.
 * @param in[in]        Input buffer to operate on.
 * @param inl[in]       Input buffer length.
 * 
 * @return 1 on success, 0 otherwise.
 */
int ukrypto_kalyna_do_cipher(UKRYPTO_KALYNA_CTX *ctx, uint8_t *out, const uint8_t* in, size_t inl);


#ifdef __cplusplus
}
#endif 

#endif /* UKRYPTO_KALYNA_H_ */
