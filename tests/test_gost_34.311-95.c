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
#include <check.h>
#include <stdlib.h>

/* TODO: check if endinanness might be an issue */
/* TODO: some verbosity on why exactly have the test failed */
/* TODO: reorganise nomenclature perhaps */

/* Base function for testing hash functions, currently only ГОСТ 34.311 is supported */
const char* hash_template(const uint8_t *T, size_t LT, const uint8_t *ref_HT, size_t ref_LH)
{
  /* Check if we compare to the hash of correct length */
  size_t LH = dstu4145_hashlen(dstu4145_defaultiH, dstu4145_defaultLiH);
  if (ref_LH != LH)
    return "Reported hash length does not match reference";

  /* Compute the hash */
  uint8_t *HT = malloc(LH);
  const char *reason = NULL;
  if (!dstu4145_hashmessage(T, LT, dstu4145_defaultiH, dstu4145_defaultLiH, HT, LH))
    reason = "Hash function failed";

  /* If computation was successful, compare it to reference */
  if (!reason)
    if (memcmp(HT, ref_HT, LH))
      reason = "Computed hash does not match the reference";

  /* Clean up and return */
  free(HT);
  return reason;
}

/* Hash function tests are taken directly from Annex A.3 of ГОСТ 34.311 */
START_TEST(gost_34_311_hash_test_a_3_1)
{
  /* "This is message, length=32 bytes" */
  const uint8_t T[] =   { 0x73, 0x65, 0x74, 0x79,   0x62, 0x20, 0x32, 0x33,
                          0x3D, 0x68, 0x74, 0x67,   0x6E, 0x65, 0x6C, 0x20,
                          0x2C, 0x65, 0x67, 0x61,   0x73, 0x73, 0x65, 0x6D,
                          0x20, 0x73, 0x69, 0x20,   0x73, 0x69, 0x68, 0x54, };

  const uint8_t HT[] =  { 0xFA, 0xFF, 0x37, 0xA6,   0x15, 0xA8, 0x16, 0x69,
                          0x1C, 0xFF, 0x3E, 0xF8,   0xB6, 0x8C, 0xA2, 0x47,
                          0xE0, 0x95, 0x25, 0xF3,   0x9F, 0x81, 0x19, 0x83,
                          0x2E, 0xB8, 0x19, 0x75,   0xD3, 0x66, 0xC4, 0xB1, };

  const char * reason = hash_template(T, sizeof(T), HT, sizeof(HT));
  fail_if(reason != NULL, reason);
}
END_TEST

START_TEST(gost_34_311_hash_test_a_3_2)
{
  /* "Suppose the original message has length = 50 bytes" */
  const uint8_t T[] =   { 0x73, 0x65,   0x74, 0x79, 0x62, 0x20,   0x30, 0x35, 0x20, 0x3D,
                                        0x20, 0x68, 0x74, 0x67,   0x6E, 0x65, 0x6C, 0x20,
                                        0x73, 0x61, 0x68, 0x20,   0x65, 0x67, 0x61, 0x73,
                                        0x73, 0x65, 0x6D, 0x20,   0x6C, 0x61, 0x6E, 0x69,
                                        0x67, 0x69, 0x72, 0x6F,   0x20, 0x65, 0x68, 0x74,
                                        0x20, 0x65, 0x73, 0x6F,   0x70, 0x70, 0x75, 0x53, };

  const uint8_t HT[] =  { 0x08, 0x52, 0xF5, 0x62,   0x3B, 0x89, 0xDD, 0x57,
                          0xAE, 0xB4, 0x78, 0x1F,   0xE5, 0x4D, 0xF1, 0x4E,
                          0xEA, 0xFB, 0xC1, 0x35,   0x06, 0x13, 0x76, 0x3A,
                          0x0D, 0x77, 0x0A, 0xA6,   0x57, 0xBA, 0x1A, 0x47, };

  const char * reason = hash_template(T, sizeof(T), HT, sizeof(HT));
  fail_if(reason != NULL, reason);
}
END_TEST

Suite *dstu4145_suite() {
  Suite *suite = suite_create("libdstu4145");
  TCase *tcase = tcase_create("Hashing");
  tcase_add_test(tcase, gost_34_311_hash_test_a_3_1);
  tcase_add_test(tcase, gost_34_311_hash_test_a_3_2);
  suite_add_tcase(suite, tcase);

  return suite;
}

int main(int argc, char** argv)
{
  int failed;
  Suite *s = dstu4145_suite();
  SRunner *sr = srunner_create(s);

  srunner_run_all(sr, CK_NORMAL);
  failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return failed;
}
