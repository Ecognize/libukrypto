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
#ifndef UKRYPTO_LEGACY_H_
#define UKRYPTO_LEGACY_H_

#include <openssl/opensslv.h>
#include <stdbool.h>
#include "macros.h"

#if FINA_VENKO
    #error You have an up to date OpenSSL, do not include this header
#endif

/* GOST cipher */
extern int NID_id_Gost28147;
extern int NID_id_Gost28147ecb;
extern int NID_id_Gost28147ctr;
extern int NID_id_Gost28147cfb;
extern int NID_id_Gost28147cmac;

/* Kalyna */
extern int NID_id_Dstu7624;
extern int NID_id_Dstu7624ecb;
extern int NID_id_Dstu7624ecb_128;
extern int NID_id_Dstu7624ecb_256;
extern int NID_id_Dstu7624ecb_512;
extern int NID_id_Dstu7624ctr;
extern int NID_id_Dstu7624ctr_128;
extern int NID_id_Dstu7624ctr_256;
extern int NID_id_Dstu7624ctr_512;
extern int NID_id_Dstu7624cfb;
extern int NID_id_Dstu7624cfb_128;
extern int NID_id_Dstu7624cfb_256;
extern int NID_id_Dstu7624cfb_512;
extern int NID_id_Dstu7624cmac;
extern int NID_id_Dstu7624cmac_128;
extern int NID_id_Dstu7624cmac_256;
extern int NID_id_Dstu7624cmac_512;
extern int NID_id_Dstu7624cbc;
extern int NID_id_Dstu7624cbc_128;
extern int NID_id_Dstu7624cbc_256;
extern int NID_id_Dstu7624cbc_512;
extern int NID_id_Dstu7624ofb;
extern int NID_id_Dstu7624ofb_128;
extern int NID_id_Dstu7624ofb_256;
extern int NID_id_Dstu7624ofb_512;
extern int NID_id_Dstu7624gmac;
extern int NID_id_Dstu7624gmac_128;
extern int NID_id_Dstu7624gmac_256;
extern int NID_id_Dstu7624gmac_512;
extern int NID_id_Dstu7624ccm;
extern int NID_id_Dstu7624ccm_128;
extern int NID_id_Dstu7624ccm_256;
extern int NID_id_Dstu7624ccm_512;
extern int NID_id_Dstu7624xts;
extern int NID_id_Dstu7624xts_128;
extern int NID_id_Dstu7624xts_256;
extern int NID_id_Dstu7624xts_512;
extern int NID_id_Dstu7624kw;
extern int NID_id_Dstu7624kw_128;
extern int NID_id_Dstu7624kw_256;
extern int NID_id_Dstu7624kw_512;

/* GOST hash */
extern int NID_id_Gost34311;
extern int NID_id_HmacGost34311;

/* Kupyna */
extern int NID_id_Dstu7564;
extern int NID_id_Dstu7564_256;
extern int NID_id_Dstu7564_384;
extern int NID_id_Dstu7564_512;
extern int NID_id_Dstu7564mac_256;
extern int NID_id_Dstu7564mac_384;
extern int NID_id_Dstu7564mac_512;

/* DSTU 4145 */
extern int NID_id_Dstu4145WithGost34311;
extern int NID_id_Dstu4145WithDstu7564;
extern int NID_id_Dstu4145WithDstu7564_256;
extern int NID_id_Dstu4145WithDstu7564_384;
extern int NID_id_Dstu4145WithDstu7564_512;

/* GOST 34.310 signature */
extern int NID_id_Gost34310WithGost34311;

/* TODO: curve points */

/* Create the NIDs in runtime */
bool ukrypto_generate_nids(); 

#endif // UKRYPTO_LEGACY_H_
