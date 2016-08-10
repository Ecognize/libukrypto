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
} UKRYPTO_KALYNA_CTX;

#ifdef __cplusplus
}
#endif 

#endif /* UKRYPTO_KALYNA_H_ */
