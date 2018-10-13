#!/bin/bash

pushd "$1"
if gcc *.c; then
  popd
else
  exit 1
fi
