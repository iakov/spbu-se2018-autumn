#!/bin/bash

find . -not -path '*/\.*' -type d -iname '*task*1*' -exec ./.travis/task01/build.sh "{}" \;
