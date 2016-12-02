#!/bin/sh
wget https://github.com/ErintLabs/openssl-bin/raw/master/openssl-${OPENSSL_VERSION}.tar.bz2
tar -xf openssl-${OPENSSL_VERSION}.tar.bz2
./.travis/build.sh -DOPENSSL_ROOT_DIR=$(pwd)/../openssl-${OPENSSL_VERSION}
