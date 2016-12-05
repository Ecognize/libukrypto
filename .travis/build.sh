#!/bin/sh

EXTRA_OPTS=""

# Check if we need to run the build on a selected architecture via docker
# More info at: https://hub.docker.com/r/multiarch/debian-debootstrap/
# https://github.com/travis-ci/travis-ci/issues/3376#issuecomment-168003756
if [[ ! -z "$ARCH" ]]; then
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
    brew install openssl
  else
    EXTRA_OPTS="$EXTRA_OPTS -DOPENSSL_ROOT_DIR=/usr"
  fi
fi

# If we are at containerised Debian, pull the required packages manually since Travis can't
if [[ ! -z "$DEBIAN_CONTAINER" ]]; then
  # Add the repository
  echo deb http://ftp.debian.org/debian jessie-backports main >> /etc/apt/sources.list
  echo deb http://ftp.debian.org/debian jessie main >> /etc/apt/sources.list

  apt-get update
  apt-get -y -t jessie-backports install libssl-dev openssl cmake cmake-data check
fi

# Check if we need a pet copy of OpenSSL
if [[ ! -z "$OPENSSL_VERSION" && "$OPENSSL_VERSION" != "brew" ]]; then
  wget https://github.com/ErintLabs/openssl-bin/raw/master/openssl-${OPENSSL_VERSION}.tar.bz2
  tar -xf openssl-${OPENSSL_VERSION}.tar.bz2
  EXTRA_OPTS="$EXTRA_OPTS -DOPENSSL_ROOT_DIR=$(pwd)/openssl-${OPENSSL_VERSION}"
fi

mkdir build
cd build
cmake .. $EXTRA_OPTS && make && make test
