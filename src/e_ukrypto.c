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

#include "ukrypto.h"

#if !FINA_VENKO
    #include "legacy.h"
#endif

static const char *ukrypto_id = "ukrypto";
static const char *ukrypto_name = "Ukrainian cryptography standards implementation";

/* FIXME: should we support "default" versions of algorithms? */
#define MAX_ALGOS   50

/* Message digests (hash functions) */
static int digests[MAX_ALGOS + 1];
static size_t n_digests = 0;

static void prepare_digests()
{
    /* GOST hash */
    // algo_add(digests, NID_id_Gost34311);
    // algo_add(digests, NID_id_GostR3411_94_with_GostR3410_94);
    // algo_add(digests, NID_id_HmacGost34311);
    // algo_add(digests, NID_id_HMACGostR3411_94);

    /* Kupyna */
    // algo_add(digests, NID_id_Dstu7564_256);
    // algo_add(digests, NID_id_Dstu7564_384);
    // algo_add(digests, NID_id_Dstu7564_512);
    // algo_add(digests, NID_id_Dstu7564mac_256);
    // algo_add(digests, NID_id_Dstu7564mac_384);
    // algo_add(digests, NID_id_Dstu7564mac_512);

    algo_add(digests, 0);
}

static int ukrypto_digests(ENGINE *e, const EVP_MD **digest, const int **nids, int nid)
{
    /* NULL parameter means we were asked about supported NIDs */
    if (!digest)
    {
        *nids = digests;
        return n_digests - 1;
    }
}

/* Ciphers */
static int ciphers[MAX_ALGOS + 1];
static size_t n_ciphers = 0;

static void prepare_ciphers()
{
    /* GOST cipher */
    /* TODO: verify foreign IDs */
    algo_add(ciphers, NID_id_Gost28147ecb);
    // algo_add(ciphers, NID_id_Gost28147_89);
    // algo_add(ciphers, NID_id_Gost28147ctr);
    // algo_add(ciphers, NID_id_Gost28147cfb);
    // algo_add(ciphers, NID_id_Gost28147cmac);

    /* Kalyna */
    // algo_add(ciphers, NID_id_Dstu7624ecb_128);
    // algo_add(ciphers, NID_id_Dstu7624ecb_256);
    // algo_add(ciphers, NID_id_Dstu7624ecb_512);
    // algo_add(ciphers, NID_id_Dstu7624ctr_128);
    // algo_add(ciphers, NID_id_Dstu7624ctr_256);
    // algo_add(ciphers, NID_id_Dstu7624ctr_512);
    // algo_add(ciphers, NID_id_Dstu7624cfb_128);
    // algo_add(ciphers, NID_id_Dstu7624cfb_256);
    // algo_add(ciphers, NID_id_Dstu7624cfb_512);
    // algo_add(ciphers, NID_id_Dstu7624cmac_128);
    // algo_add(ciphers, NID_id_Dstu7624cmac_256);
    // algo_add(ciphers, NID_id_Dstu7624cmac_512);
    // algo_add(ciphers, NID_id_Dstu7624cbc_128);
    // algo_add(ciphers, NID_id_Dstu7624cbc_256);
    // algo_add(ciphers, NID_id_Dstu7624cbc_512);
    // algo_add(ciphers, NID_id_Dstu7624ofb_128);
    // algo_add(ciphers, NID_id_Dstu7624ofb_256);
    // algo_add(ciphers, NID_id_Dstu7624ofb_512);
    // algo_add(ciphers, NID_id_Dstu7624gmac_128);
    // algo_add(ciphers, NID_id_Dstu7624gmac_256);
    // algo_add(ciphers, NID_id_Dstu7624gmac_512);
    // algo_add(ciphers, NID_id_Dstu7624ccm_128);
    // algo_add(ciphers, NID_id_Dstu7624ccm_256);
    // algo_add(ciphers, NID_id_Dstu7624ccm_512);
    // algo_add(ciphers, NID_id_Dstu7624xts_128);
    // algo_add(ciphers, NID_id_Dstu7624xts_256);
    // algo_add(ciphers, NID_id_Dstu7624xts_512);
    // algo_add(ciphers, NID_id_Dstu7624kw_128);
    // algo_add(ciphers, NID_id_Dstu7624kw_256);
    // algo_add(ciphers, NID_id_Dstu7624kw_512);

    algo_add(ciphers, 0);
}

static int ukrypto_ciphers(ENGINE *e, const EVP_CIPHER **cipher, const int **nids, int nid)
{
    /* NULL parameter means we were asked about supported NIDs */
    if (!cipher)
    {
        *nids = ciphers;
        return n_ciphers - 1;
    }
}

/* Digital Signature */
static int pkeymeths[MAX_ALGOS + 1];
static size_t n_pkeymeths = 0;

static void prepare_pkeymeths()
{
    /* DSTU 4145 */
    // algo_add(pkeymeths, NID_id_Dstu4145WithGost34311);
    // algo_add(pkeymeths, NID_id_Dstu4145WithDstu7564_256);
    // algo_add(pkeymeths, NID_id_Dstu4145WithDstu7564_384);
    // algo_add(pkeymeths, NID_id_Dstu4145WithDstu7564_512);

    /* GOST 34.310 signature */
    // algo_add(pkeymeths, NID_id_Gost34310WithGost34311); /* TODO: add foreign ID */

    //algo_add(pkeymeths, 0);
}

// FIXME: doesn't work in OSX (OpenSSL v 0.9.8)
// static int ukrypto_pkeymeths(ENGINE *e, EVP_PKEY_METHOD **pmeth, const int **nids, int nid)
// {
//     /* NULL parameter means we were asked about supported NIDs */
//     if (!pmeth)
//     {
//         *nids = pkeymeths;
//         return n_pkeymeths - 1;
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
    // prepare_digests();
    prepare_ciphers();
    // prepare_pkeymeths();

    /* Registering stuff */
//    if (!ENGINE_set_digests(e, ukrypto_digests))
//        return ukrypto_error("Can not setup digests\n");
    if (!ENGINE_set_ciphers(e, ukrypto_ciphers))
        return ukrypto_error("Can not setup ciphers\n");
//    if (!ENGINE_set_pkey_meths(e, ukrypto_pkeymeths))
//        return ukrypto_error("Can not setup public key methods\n");

    return 1;
}

IMPLEMENT_DYNAMIC_BIND_FN(ukrypto_bind)
IMPLEMENT_DYNAMIC_CHECK_FN()
