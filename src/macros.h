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
#ifndef UKRYPTO_MACROS_H_
#define UKRYPTO_MACROS_H_

/* Separate header not to pollute the namespace.
 * No Doxygen since most of the stuff is internal use.
 * No extern "C" because you are not supposed to include this. */

/* Static array length if # of elements */
#define lengthof(x) (sizeof(x)/sizeof(x[0]))

/* Whether the current OpenSSL release has Ukrainian OIDs */
#define FINA_VENKO  (OPENSSL_VERSION_NUMBER > 0xffffffff)

/* Add an algorithm to list, will be removed after fina venko and replaced with static initialiser */
#define algo_add(x, y) (x[n_##x++] = y)

/* Check if big or little endian */
#define IS_BIG_ENDIAN (*(uint16_t*)"\x00\xff" == 0x00ff)

/* Swap endianness.
 * Note that macros don't check types!
 * Also they are macros so careful around side effects. */
#define swap_bele_16(p) ((uint16_t)((p & 0xff) << 8 | (p & 0xff00) >> 8))
#define swap_bele_32(p) ((uint32_t)((uint32_t)swap_bele_16(((uint16_t*) &p)[0]) << 16 | swap_bele_16(((uint16_t*) &p)[1])))
#define swap_bele_64(p) ((uint64_t)((uint64_t)swap_bele_32(((uint32_t*) &p)[0]) << 32 | swap_bele_32(((uint32_t*) &p)[1])))

/* Endianness conversion if necessary, works both for input and output.
 * Use as:
 *    uint16_t n_host_format = assume_be(input_known_to_be_bigendian, 16);
 *    res_host_format = ... f(n_host_format) ...
 *    uint16_t bigendian_result = assume_be(res_host_format, 16); */
#define assume_endian(p, n, x) (x? p : swap_bele_##n(p))
#define assume_be(p, n) assume_endian(p, n, IS_BIG_ENDIAN)
#define assume_le(p, n) assume_endian(p, n, IS_BIG_ENDIAN)

#endif /* UKRYPTO_MACROS_H_ */
