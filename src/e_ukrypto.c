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
#include "libukrypto.h"
#include <openssl/engine.h>
#include <openssl/objects.h>
#include <stdio.h>
#include <stdarg.h>

/* Static array length if # of elements */
#define lengthof(x) (sizeof(x)/sizeof(x[0]))

static const char *ukrypto_id = "ukrypto";
static const char *ukrypto_name = "Ukrainian cryptography standards implementation";

/* Supported alorithms */
enum algo
{
    GOST_34_311_95 = 0,
    DSTU_4145_2001,
    DSTU_GOST_28147,
//     DUST_ISO_IEC_2_15946_3,
    n_algos
};

static int NID[n_algos];

/* TODO: study numerical forms better */
static const char *algo_desc[][3] = 
{
    {"1.2.3.4", "GOST 34.311-95", "GOST 34.311-95 hashing function" },
    {"1.2.3.5", "DSTU 4145-2002", "DSTU 4145-2002 digital signature algorithm" },
    {"1.2.3.6", "DSTU GOST 28147", "DSTU GOST 28147 encryption algorithm" },
//     {"1.2.3.7", "DSTU ISO/IEC 15946-3", "DSTU ISO/IEC 15946-3 key exchange" },
};

/* We need these for API returns, the actual data is filled at startup */
static int digests[1 + 1];
static int ciphers[1 + 1];
static int pmeths[1 + 1];

/* Message digests (hash functions) */
static int ukrypto_digests(ENGINE *e, const EVP_MD **digest, const int **nids, int nid)
{
    /* NULL parameter means we were asked about supported NIDs */
    if (!digest)
    {
        *nids = digests;
        return lengthof(digests) - 1;
    }
}

/* Ciphers */
static int ukrypto_ciphers(ENGINE *e, const EVP_CIPHER **cipher, const int **nids, int nid)
{
    /* NULL parameter means we were asked about supported NIDs */
    if (!cipher)
    {
        *nids = ciphers;
        return lengthof(ciphers) - 1;
    }
}

/* Digital Signature */
static int ukrypto_pkeymeths(ENGINE *e, EVP_PKEY_METHOD **pmeth, const int **nids, int nid)
{
    /* NULL parameter means we were asked about supported NIDs */
    if (!pmeth)
    {
        *nids = pmeths;
        return lengthof(pmeths) - 1;
    }
}

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
    /* TODO: test what happens on loading/unloading and multiple loads */
    /* TODO: rewrite this completely anyway */
    
    /* Basic setup */
    if (!ENGINE_set_id(e, ukrypto_id))
        return ukrypto_error("Can not set engine id\n");
    if (!ENGINE_set_name(e, ukrypto_name))
        return ukrypto_error("Can not set engine name\n");
    
    /* Allocating NIDs for our algorithms */
    /* TODO: study if we need to add them to OpenSSL permanently or something */
    for (int i = 0; i < n_algos; i++)
    {
        /* Not totally sure if OBJ_create indicates errors, but let's try */
        if (! ( NID[i] = OBJ_create(algo_desc[i][0], algo_desc[i][1], algo_desc[i][2]) ) )
            return ukrypto_error("Can not create a NID for %s\n", algo_desc[i][1]);
    }
    
    /* More hard-coded that I would like to, but works */
    digests[0] = NID[GOST_34_311_95];
    digests[1] = 0;
    
    ciphers[0] = NID[DSTU_GOST_28147];
    ciphers[1] = 0;
    
    pmeths[0] = NID[DSTU_4145_2001];
    pmeths[1] = 0;
    
    /* Registering stuff */
    if (!ENGINE_set_digests(e, ukrypto_digests))
        return ukrypto_error("Can not setup digests\n");
    if (!ENGINE_set_ciphers(e, ukrypto_ciphers))
        return ukrypto_error("Can not setup ciphers\n");
    if (!ENGINE_set_pkey_meths(e, ukrypto_pkeymeths))
        return ukrypto_error("Can not setup public key methods\n");
    
    return 1;
}

IMPLEMENT_DYNAMIC_BIND_FN(ukrypto_bind)
IMPLEMENT_DYNAMIC_CHECK_FN()

