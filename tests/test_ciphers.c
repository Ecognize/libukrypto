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
#include <check.h>
#include <stdlib.h>
#include "magma.h"
#include "macros.h"

/* Generalised test of Magma cipher */
const char* magma_template(const uint8_t key[32], const uint8_t input[8], const uint8_t ref[8], bool encrypt)
{
  // TODO: custom S-box support
  /* Create a context with default params */
  UKRYPTO_MAGMA_CTX ctx;
  if (!ukrypto_magma_init(&ctx, key, encrypt))
    return "Can not initalise magma context.";

  /* Since blocks are 64-bit we can reinterpret them as uint64_t and compare in one op */
  uint64_t ciphertext;
  const char *result = NULL;
  if (!ukrypto_magma_do_cipher(&ctx, (uint8_t *)&ciphertext, input))
    result = "Can not compute magma cipher.";
  else if (ciphertext != frombitstream(ref, 64))
    result = encrypt ? "Computed cipher does not match the reference." : "Computed plaintext does not match the reference";

  if (!ukrypto_magma_cleanup(&ctx))
    return "Can not clean up magma context.";
  return result;
}

// TODO add more tests after S-box customization

/* Source: Crypto++ (TestData/gostval.dat) */
START_TEST(magma_test_gosthash_cryptopp_1)
{
  const uint8_t key[] = {
    0xbe, 0x5e, 0xc2, 0x00,  0x6c, 0xff, 0x9d, 0xcf,  0x52, 0x35, 0x49, 0x59,  0xf1, 0xff, 0x0c, 0xbf,
    0xe9, 0x50, 0x61, 0xb5,  0xa6, 0x48, 0xc1, 0x03,  0x87, 0x06, 0x9c, 0x25,  0x99, 0x7c, 0x06, 0x72,
  };
  const uint8_t input[] = {
    0x0D, 0xF8, 0x28, 0x02, 0xB7, 0x41, 0xA2, 0x92,
  };
  const uint8_t ref[] = {
    0x07, 0xF9, 0x02, 0x7D, 0xF7, 0xF7, 0xDF, 0x89,
  };

  const char * reason = magma_template(key, input, ref, true);
  fail_if(reason != NULL, reason);
  reason = magma_template(key, ref, input, false);
  fail_if(reason != NULL, reason);
}
END_TEST

START_TEST(magma_test_gosthash_cryptopp_2)
{
  const uint8_t key[] = {
    0xB3, 0x85, 0x27, 0x2A,  0xC8, 0xD7, 0x2A, 0x5A,  0x8B, 0x34, 0x4B, 0xC8,  0x03, 0x63, 0xAC, 0x4D,
    0x09, 0xBF, 0x58, 0xF4,  0x1F, 0x54, 0x06, 0x24,  0xCB, 0xCB, 0x8F, 0xDC,  0xF5, 0x53, 0x07, 0xD7,
  };
  const uint8_t input[] = {
    0x13, 0x54, 0xEE, 0x9C, 0x0A, 0x11, 0xCD, 0x4C,
  };
  const uint8_t ref[] = {
    0x4F, 0xB5, 0x05, 0x36, 0xF9, 0x60, 0xA7, 0xB1,
  };

  const char * reason = magma_template(key, input, ref, true);
  fail_if(reason != NULL, reason);
  reason = magma_template(key, ref, input, false);
  fail_if(reason != NULL, reason);
}
END_TEST

START_TEST(magma_test_gosthash_cryptopp_3)
{
  const uint8_t key[] = {
    0xAE, 0xE0, 0x2F, 0x60,  0x9A, 0x35, 0x66, 0x0E,  0x40, 0x97, 0xE5, 0x46,  0xFD, 0x30, 0x26, 0xB0,
    0x32, 0xCD, 0x10, 0x7C,  0x7D, 0x45, 0x99, 0x77,  0xAD, 0xF4, 0x89, 0xBE,  0xF2, 0x65, 0x22, 0x62,
  };
  const uint8_t input[] = {
    0x66, 0x93, 0xD4, 0x92, 0xC4, 0xB0, 0xCC, 0x39,
  };
  const uint8_t ref[] = {
    0x67, 0x00, 0x34, 0xAC, 0x0F, 0xA8, 0x11, 0xB5,
  };

  const char * reason = magma_template(key, input, ref, true);
  fail_if(reason != NULL, reason);
  reason = magma_template(key, ref, input, false);
  fail_if(reason != NULL, reason);
}
END_TEST

START_TEST(magma_test_gosthash_cryptopp_4)
{
  const uint8_t key[] = {
    0x32, 0x0E, 0x9D, 0x84,  0x22, 0x16, 0x5D, 0x58,  0x91, 0x1D, 0xFC, 0x7D,  0x8B, 0xBB, 0x1F, 0x81,
    0xB0, 0xEC, 0xD9, 0x24,  0x02, 0x3B, 0xF9, 0x4D,  0x9D, 0xF7, 0xDC, 0xF7,  0x80, 0x12, 0x40, 0xE0,
  };
  const uint8_t input[] = {
    0x99, 0xE2, 0xD1, 0x30, 0x80, 0x92, 0x8D, 0x79,
  };
  const uint8_t ref[] = {
    0x81, 0x18, 0xFF, 0x9D, 0x3B, 0x3C, 0xFE, 0x7D,
  };

  const char * reason = magma_template(key, input, ref, true);
  fail_if(reason != NULL, reason);
  reason = magma_template(key, ref, input, false);
  fail_if(reason != NULL, reason);
}
END_TEST

START_TEST(magma_test_gosthash_cryptopp_5)
{
  const uint8_t key[] = {
    0xC9, 0xF7, 0x03, 0xBB,  0xBF, 0xC6, 0x36, 0x91,  0xBF, 0xA3, 0xB7, 0xB8,  0x7E, 0xA8, 0xFD, 0x5E,
    0x8E, 0x8E, 0xF3, 0x84,  0xEF, 0x73, 0x3F, 0x1A,  0x61, 0xAE, 0xF6, 0x8C,  0x8F, 0xFA, 0x26, 0x5F,
  };
  const uint8_t input[] = {
    0xD1, 0xE7, 0x87, 0x74, 0x9C, 0x72, 0x81, 0x4C,
  };
  const uint8_t ref[] = {
    0xA0, 0x83, 0x82, 0x6A, 0x79, 0x0D, 0x3E, 0x0C,
  };

  const char * reason = magma_template(key, input, ref, true);
  fail_if(reason != NULL, reason);
  reason = magma_template(key, ref, input, false);
  fail_if(reason != NULL, reason);
}
END_TEST

START_TEST(magma_test_gosthash_cryptopp_6)
{
  const uint8_t key[] = {
    0x72, 0x8F, 0xEE, 0x32,  0xF0, 0x4B, 0x4C, 0x65,  0x4A, 0xD7, 0xF6, 0x07,  0xD7, 0x1C, 0x66, 0x0C,
    0x2C, 0x26, 0x70, 0xD7,  0xC9, 0x99, 0x71, 0x32,  0x33, 0x14, 0x9A, 0x1C,  0x0C, 0x17, 0xA1, 0xF0,
  };
  const uint8_t input[] = {
    0xD4, 0xC0, 0x53, 0x23, 0xA4, 0xF7, 0xA7, 0xB5,
  };
  const uint8_t ref[] = {
    0x4D, 0x1F, 0x2E, 0x6B, 0x0D, 0x9D, 0xE2, 0xCE,
  };

  const char * reason = magma_template(key, input, ref, true);
  fail_if(reason != NULL, reason);
  reason = magma_template(key, ref, input, false);
  fail_if(reason != NULL, reason);
}
END_TEST

START_TEST(magma_test_gosthash_cryptopp_7)
{
  const uint8_t key[] = {
    0x35, 0xFC, 0x96, 0x40,  0x22, 0x09, 0x50, 0x0F,  0xCF, 0xDE, 0xF5, 0x35,  0x2D, 0x1A, 0xBB, 0x03,
    0x8F, 0xE3, 0x3F, 0xC0,  0xD9, 0xD5, 0x85, 0x12,  0xE5, 0x63, 0x70, 0xB2,  0x2B, 0xAA, 0x13, 0x3B,
  };
  const uint8_t input[] = {
    0x87, 0x42, 0xD9, 0xA0, 0x5F, 0x6A, 0x3A, 0xF6,
  };
  const uint8_t ref[] = {
    0x2F, 0x3B, 0xB8, 0x48, 0x79, 0xD1, 0x1E, 0x52,
  };

  const char * reason = magma_template(key, input, ref, true);
  fail_if(reason != NULL, reason);
  reason = magma_template(key, ref, input, false);
  fail_if(reason != NULL, reason);
}
END_TEST

START_TEST(magma_test_gosthash_cryptopp_8)
{
  const uint8_t key[] = {
    0xD4, 0x16, 0xF6, 0x30,  0xBE, 0x65, 0xB7, 0xFE,  0x15, 0x06, 0x56, 0x18,  0x33, 0x70, 0xE0, 0x70,
    0x18, 0x23, 0x4E, 0xE5,  0xDA, 0x3D, 0x89, 0xC4,  0xCE, 0x91, 0x52, 0xA0,  0x3E, 0x5B, 0xFB, 0x77,
  };
  const uint8_t input[] = {
    0xF8, 0x65, 0x06, 0xDA, 0x04, 0xE4, 0x1C, 0xB8,
  };
  const uint8_t ref[] = {
    0x96, 0xF0, 0xA5, 0xC7, 0x7A, 0x04, 0xF5, 0xCE,
  };

  const char * reason = magma_template(key, input, ref, true);
  fail_if(reason != NULL, reason);
  reason = magma_template(key, ref, input, false);
  fail_if(reason != NULL, reason);
}
END_TEST

Suite *magma_suite() {
  Suite *suite = suite_create("Ciphers");
  TCase *tcase_magma = tcase_create("Magma");
  tcase_add_test(tcase_magma, magma_test_gosthash_cryptopp_1);
  tcase_add_test(tcase_magma, magma_test_gosthash_cryptopp_2);
  tcase_add_test(tcase_magma, magma_test_gosthash_cryptopp_3);
  tcase_add_test(tcase_magma, magma_test_gosthash_cryptopp_4);
  tcase_add_test(tcase_magma, magma_test_gosthash_cryptopp_5);
  tcase_add_test(tcase_magma, magma_test_gosthash_cryptopp_6);
  tcase_add_test(tcase_magma, magma_test_gosthash_cryptopp_7);
  tcase_add_test(tcase_magma, magma_test_gosthash_cryptopp_8);
  suite_add_tcase(suite, tcase_magma);

  return suite;
}

int main(int argc, char** argv)
{
  int failed;
  Suite *s = magma_suite();
  SRunner *sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return failed;
}
