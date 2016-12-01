#!/bin/sh
# Run the build on a selected architecture
# More info at: https://hub.docker.com/r/multiarch/debian-debootstrap/
# https://github.com/travis-ci/travis-ci/issues/3376#issuecomment-168003756

# Register binfmt handlers
docker run --rm --privileged multiarch/qemu-user-static:register

# Run the build on specified arch
docker run -it -v $(pwd):/usr/src/libukrypto multiarch/debian-debootstrap:${ARCH}-jessie /bin/bash -x /usr/src/libukrypto/.travis/docker_build.sh
