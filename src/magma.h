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
  uint8_t   s_bl[8][8]; /**< S-block. */
  size_t    rs;         /**< Rounds passed. */
  uint32_t  state[2];   /**< Encryption state. */
  uint32_t  keys[8];    /**< Encryption key (subkeys). */
} UKRYPTO_MAGMA_CTX;


#ifdef __cplusplus
}
#endif

#endif /* UKRYPTO_MAGMA_H_ */
