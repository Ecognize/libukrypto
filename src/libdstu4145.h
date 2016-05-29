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
#ifndef _LIBDSTU4145_H_
#define _LIBDSTU4145_H_

#include <stdint.h>
#include <stdbool.h>

/**
 * \file libdstu4145.h
 * \brief ДСТУ4145 implemenation in C
 * \author Oleksiy Protas
 *
 * Software implemenation of Ukrainian digital signature ДСТУ4145 standard.
 * The constants defined in the standard are named according to the document.
 * Where applicable, bit values are converted to bytes for ease.
 * Unless otherwise is directly specified all length are considered to be bytes
 * by default.
 *
 */

/**
 * \def dstu4145_maxLiH
 * \brief Maximum size of the hash function identifier
 */
#define dstu4145_maxLiH   8

/**
 * \def dstu4145_defaultiH
 * \brief Default hash function identifier. Function is defined in ГОСТ 34.311
 */
#define dstu4145_defaultiH (&((const uint8_t)1))

/**
 * \def dstu4145_defaultLiH
 * \brief Default hash function identifier length
 */
#define dstu4145_defaultLiH 1

/**
 * \fn size_t dstu4145_hashlen (const uint8_t *iH, size_t LiH)
 * \brief Return the hash function output length for the function specified
 *
 * \param iH Hash function identifier
 * \param LiH Hash function identifier length
 * \return Hash function output length
 */
size_t dstu4145_hashlen(const uint8_t *iH, size_t LiH);

/* \fn  bool dstu4145_hashmessage (const uint8_t *T, size_t LT, const uint8_t *iH, size_t LiH, uint8_t *HT, size_t LH)
 * \brief Compute a hash of the message with the function specified
 *
 * \param T Message to hash
 * \param LT Message length
 * \param iH Hash function identifier
 * \param LiH Hash function identifier length
 * \param HT Output buffer for the hash
 * \param LH Allocated length of the buffer
 * \return false if the hash function requested is not implemented or the storage is insufficient, true otherwise
 *
 * Buffer length can be queried with dstu4145_hashlen function
 */
bool dstu4145_hashmessage(const uint8_t *T, size_t LT,
                          const uint8_t *iH, size_t LiH,
                          uint8_t *HT, size_t LH); /* TODO: maybe return a more sensible thing */

#endif /* _LIBDSTU4145_H_ */
