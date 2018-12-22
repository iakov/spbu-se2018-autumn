#!/bin/bash
case "_$TRAVIS_OS_NAME" in
  _osx)
    export PATH="/usr/local/opt/gnu-sed/libexec/gnubin:/usr/local/opt/coreutils/libexec/gnubin:$PATH"
esac

. $(dirname $(readlink -f $0))/../common/testRunner

forAllUsers $ROOT_SOURCES_DIR

returnCode=$(setStatus $totalErrors)
return $returnCode 2>/dev/null || exit $returnCode

