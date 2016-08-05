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

static const char *engine_id = "ukrypto";
static const char *engine_name = "Ukrainian cryptography standards implementation";

/* Mainly adapted from OpenSSL tutorial for now */
static int bind(ENGINE* e, const char *id)
{
    /* TODO: prevent loading multiple times maybe? */
    /* TODO: rewrite this completely anyway */
    int ret = 0;
    
    if (!ENGINE_set_id(e, engine_id))
    {
        fprintf(stderr, "ENGINE_set_id failed\n");
        goto end;
    }
    if (!ENGINE_set_name(e, engine_name))
    {
        fprintf(stderr, "ENGINE_set_name failed\n");
        goto end;
    }
    
    ret = 1;
    
    end:
    return ret;
}

IMPLEMENT_DYNAMIC_BIND_FN(bind)
IMPLEMENT_DYNAMIC_CHECK_FN()

