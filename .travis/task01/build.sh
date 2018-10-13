#!/bin/bash

pushd "$1"
if $CC *.c; then
  popd
else
  exit 1
fi
