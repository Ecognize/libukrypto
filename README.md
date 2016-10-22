# UKRYPTO
Ukrainian official cryptography standards implemented as an engine module for OpenSSL.

## Standards supported
1. ДСТУ ГОСТ 28147:2009 block cipher ("Magma", ГОСТ 28147-89) (ECB-only, GOST hash S-box);
2. ДСТУ 7624:2014 block cipher ("Kalyna") [WIP];
3. ГОСТ 34.311-95 hash function (ГОСТ Р 34.11-94) [WIP];
4. ДСТУ 7564:2014 hash function ("Kupyna") [WIP];
5. ДСТУ 4145:2002 digital signature algorithm [WIP];
6. ГОСТ 34.310-95 digital signature algorithm [WIP];

## Useful commands
### Print out a certificate

`openssl x509 -in <filename>.cer -noout -text -inform der -nameopt oneline,-esc_msb,utf8`

For files issues by АЦСК ІДД ДФС. Note that while extension is `.cer`, it's actually a DER file.

## Notes
- OpenSSL linkage test and overall operations without specifiying the full path may fail on OSX due to bug in the library causing it to look up modules by wrong extension (see: #17). Temporary workaround:
```Bash
ln -s libukrypto.dylib libukrypto.1.so
```
- S-boxes for Magma are written in host native format. Meaning LSB is `0xs₁s₀`.

## TODO
- Make `check` optional.
- Code style
- Code assumes 8-bit bytes.
- Wrap malloc (OpenSSL malloc or other depending on situation)

## Fina venko
Currently, upstream `openssl` lacks the correct OID definitions for Ukrainian algorithms, so they are created at runtime via `legacy.c`.
After OIDs are merged upstream it would be possible to skip compiling the definitions, see `FINA_VENKO` macro. In future when there is no
point to support `openssl` version that does not have the correct OIDS, the whole glue code will be dropped and replaced with nice
static structure definitions à la tutorial.
