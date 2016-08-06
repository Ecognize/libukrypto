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
#include "gost_hash.h"
#include <string.h>

/* Type and operation definitions mirror the ГОСТ 34.311 manual except for bit to byte conversions */
typedef uint8_t V256[32];

static void V256cpy(V256 dst, const V256 src)
{
  memcpy(dst, src, sizeof(V256));
}

static void V256xor(V256 dst, const V256 A, const V256 B)
{
  for (int i = 0; i < sizeof(V256); i++)
    dst[i] = A[i] ^ B[i];
}

static void V256P(V256 dst, const V256 X)
{

}

static void V256A(V256 dst, const V256 X)
{

}

static void V256Ek(V256 dst, const V256 H, const V256 K[4])
{

}

static void V256psi(V256 dst, const V256 X, unsigned degree)
{

}

static void V256chi(V256 dst, const V256 M, const V256 H, const V256 S)
{
  V256 T1, T2;

  V256psi(T1, S, 12);
  V256xor(T2, M, T1);
  V256psi(T1, T2, 1);
  V256xor(T2, H, T1);

  V256psi(dst, T2, 61);
}

size_t dstu4145_hashlen(const uint8_t *iH, size_t LiH)
{
  /* FIXME: only ГОСТ 34.311 standard function supported for now */
  if (LiH != dstu4145_defaultLiH || memcmp(iH, dstu4145_defaultiH, LiH))
    return 0;
  else
    return 32;
}

bool dstu4145_hashmessage(const uint8_t *T, size_t LT, const uint8_t *iH, size_t LiH, uint8_t *HT, size_t LH)
{
  /* FIXME: only ГОСТ 34.311 standard function supported for now */
  if (LiH != dstu4145_defaultLiH || memcmp(iH, dstu4145_defaultiH, LiH))
    return false;

  /* Check for storage requirements */
  if (LH < dstu4145_hashlen(iH, LiH))
    return false;

  /* Starting vector */
  const V256 H = { 0 };

  /* Keys, K[0] corresponds to K1 in the text */
  V256 K[4];

  /* Key generation parameters C[0] corresponds to C2 in text */
  const V256 C[3] = {   { 0 },
                        { 0xFF, 0x00, 0xFF, 0xFF,     0x00, 0x00, 0x00, 0xFF,
                          0xFF, 0x00, 0x00, 0xFF,     0x00, 0xFF, 0xFF, 0x00,
                          0x00, 0xFF, 0x00, 0xFF,     0x00, 0xFF, 0x00, 0xFF,
                          0xFF, 0x00, 0xFF, 0x00,     0xFF, 0x00, 0xFF, 0x00 },
                        { 0 }, };

  /* Key generation */
  V256 U; V256cpy(U, H);
  V256 V; //V256cpy(V, M);
  V256 W; V256xor(W, U, V);
  V256P(K[0], W);

  for (int i = 1; i < 4; i++)
  {
    V256 T;
    V256A(T, U);
    V256xor(U, T, C[i - 1]);

    V256A(T, V);
    V256A(V, T);

    V256xor(W, U, V);

    V256P(K[i], W);
  }

  /* Encrypting conversion */
  V256 S;
  V256Ek(S, H, K);

  /* Intermixing conversion */

  return true;
}
