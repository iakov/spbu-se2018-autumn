#!/bin/bash
set -euxo pipefail
case $TRAVIS_OS_NAME in
  osx)
    export HOMEBREW_NO_AUTO_UPDATE=1
#for GNU's "readlink -f" and gawk with RS
    brew install coreutils gawk gnu-sed
esac
