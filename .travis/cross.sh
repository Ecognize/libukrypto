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
    # TODO: Temporary workarounds before upstream patches are accepted
    echo -1 | sudo tee /proc/sys/fs/binfmt_misc/s390x > /dev/null
    echo ':s390x:M::\x7fELF\x02\x02\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x16:\xff\xff\xff\xff\xff\xff\xff\x00\xff\xff\xff\xff\xff\xff\xff\xff\xff\xfe\xff\xff:/usr/bin/qemu-s390x-static:' | sudo tee /proc/sys/fs/binfmt_misc/register > /dev/null
    echo -1 | sudo tee /proc/sys/fs/binfmt_misc/ppc > /dev/null
    echo ':ppc:M::\x7fELF\x01\x02\x01\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x02\x00\x14:\xff\xff\xff\xff\xff\xff\xff\x00\xff\xff\xff\xff\xff\xff\xff\xff\xff\xfe\xff\xff:/usr/bin/qemu-ppc-static:' | sudo tee /proc/sys/fs/binfmt_misc/register > /dev/null
    ;;
esac

# Run the build on specified arch
docker run -it -v $(pwd):/usr/src/libukrypto multiarch/debian-debootstrap:${ARCH}-jessie /bin/bash -x /usr/src/libukrypto/.travis/docker_build.sh
