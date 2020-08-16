#!/bin/bash

BASE=`(pwd)`
LIB_ROCKET_DEPS="$PWD/dependencies"

if [ ! -f "$LIB_ROCKET_DEPS/lib/librocket-deps.a" ]; then
  ./install-dependencies.sh
fi

if [ ! -d "$BASE/target" ]; then
  mkdir $BASE/target
fi

cd $BASE/target

cmake -D CMAKE_BUILD_TYPE=DEBUG -D CMAKE_INSTALL_PREFIX=$BASE/distribution ../src
make -j4
make install

