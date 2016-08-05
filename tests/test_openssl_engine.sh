#!/bin/sh
# TODO: how do we dance around this in Windows?
if [ $# -lt 1 ]; then
    echo "Please supply the path to engine library as a parameter"
    exit 1
fi 
OPENSSL_ENGINES=$1 openssl engine -t -c dstu4145 | grep 'Ukrainian DSTU4145 standard' >/dev/null
