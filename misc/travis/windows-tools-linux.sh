#!/bin/bash
#
# This build script is licensed under CC0 1.0 Universal:
# https://creativecommons.org/publicdomain/zero/1.0/

cd
mkdir mxe
cd mxe

wget http://pkg.mxe.cc/repos/tar/mxe-x86-64-w64-mingw32.static/mxe-x86-64-w64-mingw32.static-binutils_2.25.1.tar.xz
tar -xf mxe-x86-64-w64-mingw32.static-binutils_2.25.1.tar.xz

wget http://pkg.mxe.cc/repos/tar/mxe-x86-64-w64-mingw32.static/mxe-x86-64-w64-mingw32.static-gcc_5.4.0.tar.xz
tar -xf mxe-x86-64-w64-mingw32.static-gcc_5.4.0.tar.xz

# cd
# git clone https://github.com/mxe/mxe.git && cd mxe

# make update-package-gcc
# make gcc pkgconf MXE_TARGETS='x86_64-w64-mingw32.static.posix i686-w64-mingw32.static.posix'

# # Let Scons know about it

# MXE='${pwd}/usr/bin'
# export PATH=$PATH:$MXE
# export MINGW32_PREFIX=$MXE/i686-w64-mingw32.static.posix-
# export MINGW64_PREFIX=$MXE/x86_64-w64-mingw32.static.posix-
