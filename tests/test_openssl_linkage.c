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
#include <openssl/opensslv.h>
#include <openssl/engine.h>
#include <openssl/ssl.h>
#include <stdlib.h>
#include <libgen.h>
#include <string.h>

/* Trying to load up the ukrypto engine library */
START_TEST(load_ukrypto_engine)
{
    ENGINE_load_dynamic();
    ENGINE* eng = ENGINE_by_id("ukrypto");
    ck_assert(eng != NULL);
}
END_TEST

Suite *openssl_linkage_suite()
{
    Suite *suite = suite_create("OpenSSL linkage");
    TCase *tcase = tcase_create("Engine loadup");
    tcase_add_test(tcase, load_ukrypto_engine);
    suite_add_tcase(suite, tcase);
    return suite;
}

int main(int argc, char** argv)
{
    /* Making sure OpenSSL looks up for the module in the correct folder */ 
    char buf[2048];
    strncpy(buf, dirname(argv[0]), 2048);
    setenv("OPENSSL_ENGINES", buf, 1);
    
    #if OPENSSL_VERSION_NUMBER < 0x10100000L
    SSL_library_init();
    #else
    OPENSSL_init_ssl(0, NULL);
    #endif
    SSL_load_error_strings();
    int failed;
    Suite *s = openssl_linkage_suite();
    SRunner *sr = srunner_create(s);
    
    srunner_run_all(sr, CK_NORMAL);
    failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    
    return failed;
}
