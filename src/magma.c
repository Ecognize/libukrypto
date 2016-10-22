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
#include "macros.h"

#define N_ROUNDS  32

/* Default S-Box for GOST hash function
 * Source: - RFC 5831 (7.1)
 *         - ГОСТ 34.311-95 (Annex А) */
static uint64_t gost_hash_s_box[8] =
{
  0x35f7c1b6e08d29a4, /* 8 */
  0x95701832afd6c4be, /* 7 */
  0xb9067cfe243ad185, /* 6 */
  0x352bc64ef9801ad7, /* 5 */
  0x2b30e9a48df517c6, /* 4 */
  0xefc95863d1270ab4, /* 3 */
  0xc2867ea095f314bd, /* 2 */
  0xc8b6e3294a750df1, /* 1 */
/*  fedcba9876543210   */
};

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

  /* Permutation using S-box */
  for (size_t i = 0; i < 8; i++)
  {
    uint32_t mask = (uint32_t)0xf << 4*i;
    uint32_t s    = (f & mask) >> 4*i;
    uint64_t p    = ctx->s_box[i] & ((uint64_t)0xf << 4*s);
    if (s > i)
      p>>= 4*(s - i);
    else if (s < i)
      p<<= 4*(i - s);

    f = (f & ~mask) | p;
  }

  /* Cyclic shift to the left by 11 bits */
  f = f<<11 | f>>(32-11);

  /* XORing and switching A and B for the next round */
  uint32_t tmp = ctx->state[0];
  ctx->state[0] = ctx->state[1] ^ f;
  ctx->state[1] = tmp;
  ctx->rs ++;
}

bool ukrypto_magma_init(UKRYPTO_MAGMA_CTX *ctx, const uint8_t key[32], bool encrypt)
{
  // TODO custom s-boxes
  for (size_t i = 0; i < lengthof(ctx->s_box); i++)
    ctx->s_box[i] = gost_hash_s_box[i];
  for (size_t i = 0; i < lengthof(ctx->keys); i++)
    ctx->keys[i] = frombitstream(&key[4*i], 32);
  ctx->encrypt = encrypt;
  ctx->rs = 0;
  ctx->state[0] = ctx->state[1] = 0;
  return true;
}

bool ukrypto_magma_do_cipher(UKRYPTO_MAGMA_CTX *ctx, uint8_t *out, const uint8_t *in)
{
  /* Reset everything just in case and set up initial values */
  ctx->rs = 0;
  ctx->state[0] = frombitstream(&in[0], 32);
  ctx->state[1] = frombitstream(&in[4], 32);

  /* Execute round function */
  for (size_t i = 0; i < N_ROUNDS; i++)
    ukrypto_magma_do_round(ctx);

  /* Concatenate the result */
  tobitstream(&out[0], ctx->state[1], 32);
  tobitstream(&out[4], ctx->state[0], 32);

  return true;
}

bool ukrypto_magma_cleanup(UKRYPTO_MAGMA_CTX *ctx)
{
  return true;
}
