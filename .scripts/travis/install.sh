#!/bin/bash
set -euxo pipefail
case $TRAVIS_OS_NAME in
  osx)
    export HOMEBREW_NO_AUTO_UPDATE=1
    brew install coreutils #for GNU's "readlink -f"
esac
