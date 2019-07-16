#!/bin/sh -eu

run_bench()
{
  make "$@"
  ./bench
  make clean
}

make clean

for opt in -O0 -Os -O1 -O2 -O3
do
  echo "\n+++ GCC +++"
  run_bench CC=gcc CFLAGS=$opt
  echo "\n+++ clang +++"
  run_bench CC=clang CFLAGS=$opt
done
