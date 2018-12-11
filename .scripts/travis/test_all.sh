#!/bin/bash
. $(dirname $(readlink -f $0))/../common/testRunner

forAllUsers $ROOT_SOURCES_DIR

returnCode=$(setStatus $totalErrors)
return $returnCode 2>/dev/null || exit $returnCode

