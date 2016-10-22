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
#include "magma.h"

#define N_ROUNDS  32

/* Round computation function */
static void ukrypto_magma_do_round(UKRYPTO_MAGMA_CTX* ctx)
{
  /* Calculating key index */
  size_t adj_r =  ctx->encrypt? ctx->rs : N_ROUNDS - ctx->rs - 1;
  size_t ki = adj_r;
  if (adj_r >= 8)
    ki %= 8;
  if (adj_r >= 24)
    ki = 8 - 1 - ki;

  /* A + Ki mod 2^32 */
  uint32_t f = ctx->state[0] + ctx->keys[ki];

  /* XORing and switching A and B for the next round */
  uint32_t tmp = ctx->state[0];
  ctx->state[0] = ctx->state[1] ^ f;
  ctx->state[1] = tmp;
  ctx->rs ++;
}

// TODO STUB to compile
int main()
{
  UKRYPTO_MAGMA_CTX ctx;
  ctx.encrypt = true;
  //ctx.s_bl;
  ctx.rs = 0;
  //ctx.state;
  //ctx.keys;
}
