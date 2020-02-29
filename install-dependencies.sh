#!/bin/bash

PWD=`(pwd)`
LIB_ROCKET_DEPS="$PWD/dependencies"

if [ ! -d "$LIB_ROCKET_DEPS" ]; then
  echo -e "\x1b[32mChecking out dependencies\x1b[0m"
  git submodule update --recursive --init
fi

if [ ! -f "$LIB_ROCKET_DEPS/librocket-deps.a" ]; then
  cd $LIB_ROCKET_DEPS && ./build.sh && cp "$LIB_ROCKET_DEPS/target/install/lib/librocket-deps.a" "$LIB_ROCKET_DEPS/librocket-deps.a"
fi

echo -e "\x1b[32;5m///-- Ready to launch --///\x1b[0m"
