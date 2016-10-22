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
  else if (ciphertext != *(uint64_t *)ref)
    result = encrypt ? "Computed cipher does not match the reference." : "Computed plaintext does not match the reference";

  if (!ukrypto_magma_cleanup(&ctx))
    return "Can not clean up magma context.";
  return result;
}

/* Source: - RFC 5831 (7.3.1)
 *         - ГОСТ 34.311-95 (Annex А, 3.1) */
START_TEST(magma_test_gosthash_1_1)
{
  const uint8_t key[] = {
    0x73, 0x3d, 0x2c, 0x20,  0x65, 0x68, 0x65, 0x73,  0x74, 0x74, 0x67, 0x69,  0x32, 0x6c, 0x65, 0x68,
    0x62, 0x6e, 0x73, 0x73,  0x20, 0x65, 0x73, 0x69,  0x79, 0x67, 0x61, 0x20,  0x33, 0x20, 0x6d, 0x54,
  };
  const uint8_t input[] = {
    0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,
  };
  const uint8_t ref[] = {
    0x42, 0xab, 0xbc, 0xce,  0x32, 0xbc, 0x0b, 0x1b,
  };

  const char * reason = magma_template(key, input, ref, true);
  fail_if(reason != NULL, reason);
  reason = magma_template(key, ref, input, false);
  fail_if(reason != NULL, reason);
}
END_TEST

START_TEST(magma_test_gosthash_1_2)
{
  const uint8_t key[] = {
    0x11, 0x0c, 0x73, 0x3d,  0x0d, 0x16, 0x65, 0x68,  0x13, 0x0e, 0x74, 0x74,  0x06, 0x41, 0x79, 0x67,
    0x1d, 0x00, 0x62, 0x6e,  0x16, 0x1a, 0x20, 0x65,  0x09, 0x0d, 0x32, 0x6c,  0x4d, 0x39, 0x33, 0x20,
  };
  const uint8_t input[] = {
    0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,
  };
  const uint8_t ref[] = {
    0x52, 0x03, 0xeb, 0xc8,  0x5d, 0x9b, 0xcf, 0xfd,
  };

  const char * reason = magma_template(key, input, ref, true);
  fail_if(reason != NULL, reason);
  reason = magma_template(key, ref, input, false);
  fail_if(reason != NULL, reason);
}
END_TEST

START_TEST(magma_test_gosthash_1_3)
{
  const uint8_t key[] = {
    0x80, 0xb1, 0x11, 0xf3,  0x73, 0x0d, 0xf2, 0x16,  0x85, 0x00, 0x13, 0xf1,  0xc7, 0xe1, 0xf9, 0x41,
    0x62, 0x0c, 0x1d, 0xff,  0x3a, 0xba, 0xe9, 0x1a,  0x3f, 0xa1, 0x09, 0xf2,  0xf5, 0x13, 0xb2, 0x39,
  };
  const uint8_t input[] = {
    0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,
  };
  const uint8_t ref[] = {
    0x8d, 0x34, 0x58, 0x99,  0x00, 0xff, 0x0e, 0x28,
  };

  const char * reason = magma_template(key, input, ref, true);
  fail_if(reason != NULL, reason);
  reason = magma_template(key, ref, input, false);
  fail_if(reason != NULL, reason);
}
END_TEST

START_TEST(magma_test_gosthash_1_4)
{
  const uint8_t key[] = {
    0xa0, 0xe2, 0x80, 0x4e,  0xff, 0x1b, 0x73, 0xf2,  0xec, 0xe2, 0x7a, 0x00,  0xe7, 0xb8, 0xc7, 0xe1,
    0xee, 0x1d, 0x62, 0x0c,  0xac, 0x0c, 0xc5, 0xba,  0xa8, 0x04, 0xc0, 0x5e,  0xa1, 0x8b, 0x0a, 0xec,
  };
  const uint8_t input[] = {
    0x00, 0x00, 0x00, 0x00,  0x00, 0x00, 0x00, 0x00,
  };
  const uint8_t ref[] = {
    0xe7, 0x86, 0x04, 0x19,  0x0d, 0x2a, 0x56, 0x2d,
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
  tcase_add_test(tcase_magma, magma_test_gosthash_1_1);
  // tcase_add_test(tcase_magma, magma_test_gosthash_1_2);
  // tcase_add_test(tcase_magma, magma_test_gosthash_1_3);
  // tcase_add_test(tcase_magma, magma_test_gosthash_1_4);
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
