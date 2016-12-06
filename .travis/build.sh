#!/bin/bash

set -ev
EXTRA_OPTS=""

# Check if we need to run the build on a selected architecture via docker
# More info at: https://hub.docker.com/r/multiarch/debian-debootstrap/
# https://github.com/travis-ci/travis-ci/issues/3376#issuecomment-168003756
if [[ ! -z "$ARCH" && -z "$DEBIAN_CONTAINER" ]]; then
  # Register binfmt handlers for archs that we can run natively on x86_64
  case "$ARCH" in
    i386) # manual indicates arm64 should also work but it really doesn't
      ;;
    *)
      docker run --rm --privileged multiarch/qemu-user-static:register
      ;;
  esac

  # Run the build on specified arch
  docker run --rm -e DEBIAN_CONTAINER=1 -v $(pwd):/usr/src/libukrypto multiarch/debian-debootstrap:${ARCH}-jessie /bin/bash -x /usr/src/libukrypto/.travis/build.sh
  exit
fi

# If we are at OSX, install check and maybe openssl
if [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
  brew update
  brew install check
  if [[ "$OPENSSL_VERSION" == "brew" ]]; then
    brew outdated openssl || brew upgrade openssl
    EXTRA_OPTS="$EXTRA_OPTS -DOPENSSL_ROOT_DIR=/usr/local/opt/openssl"
  fi
fi

# If we are at containerised Debian, pull the required packages manually since Travis can't
if [[ ! -z "$DEBIAN_CONTAINER" ]]; then
  # Add the repository and get the packages
  echo deb http://ftp.debian.org/debian jessie-backports main >> /etc/apt/sources.list
  echo deb http://ftp.debian.org/debian jessie main >> /etc/apt/sources.list

  apt-get update
  apt-get -y -t jessie-backports install libssl-dev openssl cmake cmake-data check

  # Change to the right directory
  cd /usr/src/libukrypto
fi

# Check if we need a pet copy of OpenSSL
if [[ ! -z "$OPENSSL_VERSION" && "$OPENSSL_VERSION" != "brew" && "$OPENSSL_VERSION" != "osx" ]]; then
  wget https://github.com/ErintLabs/openssl-bin/raw/master/openssl-${OPENSSL_VERSION}.tar.bz2
  tar -xf openssl-${OPENSSL_VERSION}.tar.bz2
  EXTRA_OPTS="$EXTRA_OPTS -DOPENSSL_ROOT_DIR=$(pwd)/openssl-${OPENSSL_VERSION}"
fi

mkdir build
cd build
echo OPTS: $EXTRA_OPTS
cmake .. $EXTRA_OPTS && make

# See #17
if [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
  ln -s libukrypto.dylib libukrypto.1.so
fi

make test
