# UKRYPTO
Ukrainian official cryptography standards implemented as an engine module for OpenSSL.

## Standards supported
1. ДСТУ ГОСТ 28147:2009 block cipher ("Magma", ГОСТ 28147-89) [WIP];
2. ДСТУ 7624:2014 block cipher ("Kalyna") [WIP];
3. ГОСТ 34.311-95 hash function (ГОСТ Р 34.11-94) [WIP];
4. ДСТУ 7564:2014 hash function ("Kupyna") [WIP];
5. ДСТУ 4145:2002 digital signature algorithm [WIP];
6. ГОСТ 34.310-95 digital signature algorithm [WIP];

## TODO
Make `check` optional.

## Fina venko
Currently, upstream `openssl` lacks the correct OID definitions for Ukrainian algorithms, so they are created at runtime via `legacy.c`.
After OIDs are merged upstream it would be possible to skip compiling the definitions, see `FINA_VENKO` macro. In future when there is no
point to support `openssl` version that does not have the correct OIDS, the whole glue code will be dropped and replaced with nice
static structure definitions à la tutorial.
