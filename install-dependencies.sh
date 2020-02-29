#!/bin/bash

BASE=`(pwd)`
LIB_ROCKET_DEPS="$BASE/dependencies"

if [ ! -d "$LIB_ROCKET_DEPS" ]; then
  echo -e "\x1b[32mChecking out dependencies\x1b[0m"
  git submodule update --recursive --init
fi

if [ ! -f "$LIB_ROCKET_DEPS/lib/librocket-deps.a" ]; then
  cd $LIB_ROCKET_DEPS && ./build.sh && mv "$LIB_ROCKET_DEPS/target/install" "$BASE/install" && rm -rf "$LIB_ROCKET_DEPS/*" && mv "$BASE/install" "$LIB_ROCKET_DEPS"
fi

echo -e "\x1b[32;5m///-- Ready to launch --///\x1b[0m"
