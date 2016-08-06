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

/* Separate header not to pollute the namespace */

/* Static array length if # of elements */
#define lengthof(x) (sizeof(x)/sizeof(x[0]))

/* Whether the current OpenSSL release has Ukrainian OIDs */
#define FINA_VENKO  (OPENSSL_VERSION_NUMBER > 0xffffffff)

/* Add an algorithm to list, will be removed after fina venko and replaced with static initialiser */
#define algo_add(x, y) (x[n_##x++] = y)

#endif // UKRYPTO_MACROS_H_
