#!/bin/bash
set -euxo pipefail
case $TRAVIS_OS_NAME in
  osx)
    export HOMEBREW_NO_AUTO_UPDATE=1
#for GNU's "readlink -f" and gawk with RS
#new bash for associative arrays
    for p in coreutils gawk gnu-sed bash ; do
      brew install $p || brew upgrade $p
    done
 ;;
  linux)
    $CC --version || \
    sudo sh -c "add-apt-repository -y ppa:jonathonf/gcc-8.1 && sudo apt-get update && sudo apt-get install -y binutils gcc-8"
  ;;
esac
