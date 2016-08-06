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
#include <openssl/engine.h>
#include <stdio.h>
#include <stdarg.h>
#include "macros.h"

#if !FINA_VENKO
    #include "legacy.h"
#endif

static const char *ukrypto_id = "ukrypto";
static const char *ukrypto_name = "Ukrainian cryptography standards implementation";

/* Message digests (hash functions) */
static int digests[4 + 1];

void prepare_digests()
{
    /* GOST hash */
    digests[0] = NID_id_Gost34311;
    digests[1] = NID_id_GostR3411_94_with_GostR3410_94;
    digests[2] = NID_id_HmacGost34311;
    digests[3] = NID_id_HMACGostR3411_94;
    
    digests[lengthof(digests) - 1] = 0;
}

static int ukrypto_digests(ENGINE *e, const EVP_MD **digest, const int **nids, int nid)
{  
    /* NULL parameter means we were asked about supported NIDs */
    if (!digest)
    {
        *nids = digests;
        return lengthof(digests) - 1;
    }
}

// /* Ciphers */
// static int ukrypto_ciphers(ENGINE *e, const EVP_CIPHER **cipher, const int **nids, int nid)
// {
//     /* NULL parameter means we were asked about supported NIDs */
//     if (!cipher)
//     {
//         *nids = ciphers;
//         return lengthof(ciphers) - 1;
//     }
// }
// 
// /* Digital Signature */
// static int ukrypto_pkeymeths(ENGINE *e, EVP_PKEY_METHOD **pmeth, const int **nids, int nid)
// {
//     /* NULL parameter means we were asked about supported NIDs */
//     if (!pmeth)
//     {
//         *nids = pmeths;
//         return lengthof(pmeths) - 1;
//     }
// }

/* Prints an error message and returns 1 */
static int ukrypto_error(const char *fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    vfprintf(stderr, fmt, ap);
    
    return 1;
}

/* Mainly adapted from OpenSSL tutorial for now */
static int ukrypto_bind(ENGINE* e, const char *id)
{
    /* Check if we need to allocate NIDs at runtime */
#if !FINA_VENKO
    if (!ukrypto_generate_nids())
        return ukrypto_error("Can not generate NIDs\n");
#endif
    
    /* TODO: test what happens on loading/unloading and multiple loads */
    /* TODO: rewrite this completely anyway */
    
    /* Basic setup */
    if (!ENGINE_set_id(e, ukrypto_id))
        return ukrypto_error("Can not set engine id\n");
    if (!ENGINE_set_name(e, ukrypto_name))
        return ukrypto_error("Can not set engine name\n");

    /* Preparing stuff */
    /* TODO: check difference between bind and init */
    prepare_digests();
    
    /* Registering stuff */
    if (!ENGINE_set_digests(e, ukrypto_digests))
        return ukrypto_error("Can not setup digests\n");
//     if (!ENGINE_set_ciphers(e, ukrypto_ciphers))
//         return ukrypto_error("Can not setup ciphers\n");
//     if (!ENGINE_set_pkey_meths(e, ukrypto_pkeymeths))
//         return ukrypto_error("Can not setup public key methods\n");
    
    return 1;
}

IMPLEMENT_DYNAMIC_BIND_FN(ukrypto_bind)
IMPLEMENT_DYNAMIC_CHECK_FN()

