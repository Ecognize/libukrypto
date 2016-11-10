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
#include "gost_hash.h"
// #include "kupyna.h"
#include "macros.h"

/* Generalised test of Gost hash */
const char* gost_hash_template(const uint8_t *input, const uint8_t ref[32])
{
  // TODO: iv and s-box input?
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

/* Source: - RFC 5831 (7.3.1)
 *         - ГОСТ 34.311-95 (Annex А, 3.1) */
START_TEST(gost_hash_test_standard_1)
{
  const uint8_t *input = "This is message, length=32 bytes";
  const uint8_t ref[] = {
    0xb1, 0xc4, 0x66, 0xd3, 0x75, 0x19, 0xb8, 0x2e,
    0x83, 0x19, 0x81, 0x9f, 0xf3, 0x25, 0x95, 0xe0,
    0x47, 0xa2, 0x8c, 0xb6, 0xf8, 0x3e, 0xff, 0x1c,
    0x69, 0x16, 0xa8, 0x15, 0xa6, 0x37, 0xff, 0xfa,
  };

  const char * reason = gost_hash_template(input, ref);
  fail_if(reason != NULL, reason);
}
END_TEST

START_TEST(gost_hash_test_standard_2)
{
  const uint8_t *input = "Suppose the original message has length = 50 bytes";
  const uint8_t ref[] = {
    0x47, 0x1a, 0xba, 0x57, 0xa6, 0x0a, 0x77, 0x0d,
    0x3a, 0x76, 0x13, 0x06, 0x35, 0xc1, 0xfb, 0xea,
    0x4e, 0xf1, 0x4d, 0xe5, 0x1f, 0x78, 0xb4, 0xae,
    0x57, 0xdd, 0x89, 0x3b, 0x62, 0xf5, 0x52, 0x08,
  };

  const char * reason = gost_hash_template(input, ref);
  fail_if(reason != NULL, reason);
}
END_TEST

/* Source: Wikipedia */
START_TEST(gost_hash_test_wiki_1)
{
  const uint8_t *input = "The quick brown fox jumps over the lazy dog";
  const uint8_t ref[] = {
    0x77, 0xb7, 0xfa, 0x41, 0x0c, 0x9a, 0xc5, 0x8a,
    0x25, 0xf4, 0x9b, 0xca, 0x7d, 0x04, 0x68, 0xc9,
    0x29, 0x65, 0x29, 0x31, 0x5e, 0xac, 0xa7, 0x6b,
    0xd1, 0xa1, 0x0f, 0x37, 0x6d, 0x1f, 0x42, 0x94,
  };

  const char * reason = gost_hash_template(input, ref);
  fail_if(reason != NULL, reason);
}
END_TEST

START_TEST(gost_hash_test_wiki_2)
{
  const uint8_t *input = "";
  const uint8_t ref[] = {
    0xce, 0x85, 0xb9, 0x9c, 0xc4, 0x67, 0x52, 0xff,
    0xfe, 0xe3, 0x5c, 0xab, 0x9a, 0x7b, 0x02, 0x78,
    0xab, 0xb4, 0xc2, 0xd2, 0x05, 0x5c, 0xff, 0x68,
    0x5a, 0xf4, 0x91, 0x2c, 0x49, 0x49, 0x0f, 0x8d,
  };

  const char * reason = gost_hash_template(input, ref);
  fail_if(reason != NULL, reason);
}
END_TEST

START_TEST(gost_hash_test_wiki_3)
{
  const uint8_t *input = "a";
  const uint8_t ref[] = {
    0xd4, 0x2c, 0x53, 0x9e, 0x36, 0x7c, 0x66, 0xe9,
    0xc8, 0x8a, 0x80, 0x1f, 0x66, 0x49, 0x34, 0x9c,
    0x21, 0x87, 0x1b, 0x43, 0x44, 0xc6, 0xa5, 0x73,
    0xf8, 0x49, 0xfd, 0xce, 0x62, 0xf3, 0x14, 0xdd,
  };

  const char * reason = gost_hash_template(input, ref);
  fail_if(reason != NULL, reason);
}
END_TEST

START_TEST(gost_hash_test_wiki_4)
{
  const uint8_t *input = "message digest";
  const uint8_t ref[] = {
    0xad, 0x44, 0x34, 0xec, 0xb1, 0x8f, 0x2c, 0x99,
    0xb6, 0x0c, 0xbe, 0x59, 0xec, 0x3d, 0x24, 0x69,
    0x58, 0x2b, 0x65, 0x27, 0x3f, 0x48, 0xde, 0x72,
    0xdb, 0x2f, 0xde, 0x16, 0xa4, 0x88, 0x9a, 0x4d,
  };

  const char * reason = gost_hash_template(input, ref);
  fail_if(reason != NULL, reason);
}
END_TEST

START_TEST(gost_hash_test_wiki_5)
{
  const size_t N = 128;
  const uint8_t input[N];
  memset(input, 'U', N);
  const uint8_t ref[] = {
    0x53, 0xa3, 0xa3, 0xed, 0x25, 0x18, 0x0c, 0xef,
    0x0c, 0x1d, 0x85, 0xa0, 0x74, 0x27, 0x3e, 0x55,
    0x1c, 0x25, 0x66, 0x0a, 0x87, 0x06, 0x2a, 0x52,
    0xd9, 0x26, 0xa9, 0xe8, 0xfe, 0x57, 0x33, 0xa4,
  };

  const char * reason = gost_hash_template(input, ref);
  fail_if(reason != NULL, reason);
}
END_TEST

START_TEST(gost_hash_test_wiki_6)
{
  const size_t N = 1000000;
  const uint8_t input[N];
  memset(input, 'a', N);
  const uint8_t ref[] = {
    0x5c, 0x00, 0xcc, 0xc2, 0x73, 0x4c, 0xdd, 0x33,
    0x32, 0xd3, 0xd4, 0x74, 0x95, 0x76, 0xe3, 0xc1,
    0xa7, 0xdb, 0xaf, 0x0e, 0x7e, 0xa7, 0x4e, 0x9f,
    0xa6, 0x02, 0x41, 0x3c, 0x90, 0xa1, 0x29, 0xfa,
  };

  const char * reason = gost_hash_template(input, ref);
  fail_if(reason != NULL, reason);
}
END_TEST

Suite *hashing_suite() {
  Suite *suite = suite_create("Hashing");
  TCase *tcase_gost_hash = tcase_create("Gost Hash");
  tcase_add_test(tcase_gost_hash, gost_hash_test_standard_1);
  tcase_add_test(tcase_gost_hash, gost_hash_test_standard_2);
  tcase_add_test(tcase_gost_hash, gost_hash_test_wiki_1);
  tcase_add_test(tcase_gost_hash, gost_hash_test_wiki_2);
  tcase_add_test(tcase_gost_hash, gost_hash_test_wiki_3);
  tcase_add_test(tcase_gost_hash, gost_hash_test_wiki_4);
  tcase_add_test(tcase_gost_hash, gost_hash_test_wiki_5);
  tcase_add_test(tcase_gost_hash, gost_hash_test_wiki_6);
  suite_add_tcase(suite, tcase_gost_hash);

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
