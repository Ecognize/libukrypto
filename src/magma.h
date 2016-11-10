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
#ifndef UKRYPTO_MAGMA_H_
#define UKRYPTO_MAGMA_H_

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C"
{
#endif

/*!
 * Magma cipher context structure.
 */
typedef struct
{
  bool      encrypt;    /**< Whether we are encrypting or decrypting. */
  uint64_t  s_box[8];   /**< S-box. */
  size_t    rs;         /**< Rounds passed. */
  uint32_t  state[2];   /**< Encryption state. */
  uint32_t  keys[8];    /**< Encryption key (subkeys). */
} UKRYPTO_MAGMA_CTX;

/*!
 * Cipher initialisation.
 *
 * @param ctx[in]       Preallocated context structure pointer.
 * @param key[in]       Encryption key.
 * @param encrypt[in]   true if we are encrypting, false otherwise.
 *
 * @return true on success, false otherwise.
 */
bool ukrypto_magma_init(UKRYPTO_MAGMA_CTX *ctx, const uint8_t key[32], bool encrypt);


/*!
 * Cipher initialisation using 32-bit keys in host-native byte order.
 *
 * @param ctx[in]       Preallocated context structure pointer.
 * @param key[in]       Encryption key.
 * @param encrypt[in]   true if we are encrypting, false otherwise.
 *
 * @return true on success, false otherwise.
 */
bool ukrypto_magma_init_native(UKRYPTO_MAGMA_CTX *ctx, const uint32_t key[8], bool encrypt);

/*!
 * Execute the cipher function and write the result.
 *
 * @param ctx[in]       Context pointer.
 * @param out[out]      Preallocated buffer to store output to.
 * @param in[in]        Input buffer to operate on.
 *
 * @return 1 on success, 0 otherwise.
 */
bool ukrypto_magma_do_cipher(UKRYPTO_MAGMA_CTX *ctx, uint8_t *out, const uint8_t *in);

/*!
 * Execute the cipher function assuming input and output are pairs of host-native byte order 32-bit integers and write the result.
 *
 * @param ctx[in]       Context pointer.
 * @param out[out]      Preallocated buffer to store output to.
 * @param in[in]        Input values to operate on.
 *
 * @return 1 on success, 0 otherwise.
 */
bool ukrypto_magma_do_cipher_native(UKRYPTO_MAGMA_CTX *ctx, uint32_t out[2], const uint32_t in[2]);

/*!
 * Cipher cleanup.
 *
 * @param ctx[in]       Context pointer.
 * @return 1 on sucess, 0 otherwise.
 */
bool ukrypto_magma_cleanup(UKRYPTO_MAGMA_CTX *ctx);

#ifdef __cplusplus
}
#endif

#endif /* UKRYPTO_MAGMA_H_ */
