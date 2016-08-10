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
#include "kalyna.h"
#include <string.h> 

int ukrypto_kalyna_init(UKRYPTO_KALYNA_CTX *ctx, unsigned short bs, unsigned short ks, uint8_t *key, bool encrypt)
{
    if (!ctx || !(bs == 128 || bs == 256 || bs == 512) || !( bs == ks || ks == 2*bs ))
        return 0; // TODO: proper error
    
    /* Record the params, converting to bytes */
    ctx->bs = bs / 8;
    ctx->ks = ks / 8;
    ctx->encrypt = encrypt;
    
    /* Allocate state matrix */
    ctx->state = malloc(ctx->bs);
    
    /* Init rounds amount */
    ctx->rs = 0;
    
    /* Copying the key over */
    ctx->key = malloc(ctx->ks);
    memcpy(ctx->key, key, ctx->ks);
}

int ukrypto_kalyna_cleanup(UKRYPTO_KALYNA_CTX *ctx)
{
    if (!ctx)
        return 0; // TODO proper error
        
    free(ctx->state);
    ctx->state = 0;
    
    free(ctx->key);
    ctx->key = 0;
}
