#!/usr/bin/sh

lib_dir="src/lib"
inc_dir="src/include"

gcc -c -o "${lib_dir}/header.o" "${lib_dir}/header.c" "-I${inc_dir}"
ar rcs "${lib_dir}/libheader.a" "${lib_dir}/header.o"