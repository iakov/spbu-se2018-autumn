#!/bin/bash
case "_$TRAVIS_OS_NAME" in
  _osx)
    shopt -s expand_aliases
    alias readlink=greadlink
esac

. $(dirname $(readlink -f $0))/../common/testRunner

forAllUsers $ROOT_SOURCES_DIR

returnCode=$(setStatus $totalErrors)
return $returnCode 2>/dev/null || exit $returnCode

