#!/bin/sh -x

[ ! -f ../`basename "$0"` ] && exit 1

REL=${1:-11.2.0}

svn co --depth empty svn://svn.freebsd.org/base/release/$REL .
svn update --depth empty lib
svn update lib/libmd
svn update --depth empty sys
svn update --depth empty sys/crypto
svn update sys/crypto/sha2
svn update sys/crypto/skein
svn update --depth empty sys/sys
svn update sys/sys/md5.h
svn update --depth empty lib/libc
svn update --depth empty lib/libc/stdlib
svn update lib/libc/stdlib/getopt.c
svn update --depth empty include
svn update include/getopt.h
svn update --depth empty sbin
svn update sbin/md5

rm -rf .svn

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
mv libmd/Makefile libmd/Makefile.bsd
mv libmd/Makefile.depend libmd/Makefile.depend.bsd
mv md5/Makefile md5/Makefile.bsd
mv md5/Makefile.depend md5/Makefile.depend.bsd
