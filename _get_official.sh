#!/bin/sh -x

[ ! -f ../`basename "$0"` ] && exit 1

REL=${1:-13.1}

for i in \
  include/getopt.h \
  lib/libc/stdlib/getopt.c \
  lib/libmd/Makefile \
  lib/libmd/Makefile.depend \
  lib/libmd/i386/rmd160.S \
  lib/libmd/i386/sha.S \
  lib/libmd/md4.copyright \
  lib/libmd/md4.h \
  lib/libmd/md4c.c \
  lib/libmd/md5.copyright \
  lib/libmd/md5.h \
  lib/libmd/md5c.c \
  lib/libmd/mdX.3 \
  lib/libmd/mdXhl.c \
  lib/libmd/mddriver.c \
  lib/libmd/ripemd.3 \
  lib/libmd/ripemd.h \
  lib/libmd/rmd160c.c \
  lib/libmd/rmd_locl.h \
  lib/libmd/rmdconst.h \
  lib/libmd/rmddriver.c \
  lib/libmd/sha.3 \
  lib/libmd/sha.h \
  lib/libmd/sha0c.c \
  lib/libmd/sha1c.c \
  lib/libmd/sha256.3 \
  lib/libmd/sha512.3 \
  lib/libmd/sha_locl.h \
  lib/libmd/shadriver.c \
  lib/libmd/skein.3 \
  lib/libmd/skeindriver.c \
  sbin/md5/Makefile \
  sbin/md5/Makefile.depend \
  sbin/md5/md5.1 \
  sbin/md5/md5.c \
  sys/crypto/sha2/sha224.h \
  sys/crypto/sha2/sha256.h \
  sys/crypto/sha2/sha256c.c \
  sys/crypto/sha2/sha256c_arm64.c \
  sys/crypto/sha2/sha256c_impl.h \
  sys/crypto/sha2/sha384.h \
  sys/crypto/sha2/sha512.h \
  sys/crypto/sha2/sha512c.c \
  sys/crypto/sha2/sha512c_arm64.c \
  sys/crypto/sha2/sha512c_impl.h \
  sys/crypto/sha2/sha512t.h \
  sys/crypto/skein/amd64/skein_block_asm.S \
  sys/crypto/skein/skein.c \
  sys/crypto/skein/skein.h \
  sys/crypto/skein/skein_block.c \
  sys/crypto/skein/skein_debug.c \
  sys/crypto/skein/skein_debug.h \
  sys/crypto/skein/skein_freebsd.h \
  sys/crypto/skein/skein_iv.h \
  sys/crypto/skein/skein_port.h \
  sys/sys/md5.h \
  ;
do
  d=`dirname $i`
  mkdir -pv $d
  wget -4 -P $d https://raw.githubusercontent.com/freebsd/freebsd-src/releng/${REL}/$i
done

mv lib/libmd .
mv sys/crypto libmd/
mv libmd/md5.h libmd/libmd_md5.h
mv sys/sys/md5.h libmd/
rmdir sys/sys
rmdir sys
mv sbin/md5 .
rmdir sbin
mv lib/libc/stdlib md5/getopt
rmdir lib/libc
rmdir lib
mv include/getopt.h md5/getopt/
rmdir include
mv libmd/Makefile libmd/_Makefile.freebsd
mv libmd/Makefile.depend libmd/_Makefile.depend.freebsd
mv md5/Makefile md5/_Makefile.freebsd
mv md5/Makefile.depend md5/_Makefile.depend.freebsd
