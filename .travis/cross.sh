#!/bin/sh
# Run the build on a selected architecture
# More info at: https://hub.docker.com/r/multiarch/debian-debootstrap/
# https://github.com/travis-ci/travis-ci/issues/3376#issuecomment-168003756

# Register binfmt handlers for archs that we can run natively on x86_64
case "${ARCH}" in
  i386|x86_64)    # manual indicates arm64 should also work but it really doesn't
    ;;
  *)
    docker run --rm --privileged multiarch/qemu-user-static:register
    ;;
esac

# Run the build on specified arch
docker run --rm -v $(pwd):/usr/src/libukrypto multiarch/debian-debootstrap:${ARCH}-jessie /bin/bash -x /usr/src/libukrypto/.travis/docker_build.sh
