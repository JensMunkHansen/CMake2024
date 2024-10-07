#!/bin/bash

# approx 52.000 lines of code

find . \( -name \*.bat -or -name \*.py -or -name \*.in -or -name \*.cxx -or -name \*.h -or -name \*.cmake -or -name \*.cpp \) ! -path "./build/*" ! -path "./build_Debug/*" ! -path "./build_debug/*" | xargs -i -t less {} 2>/dev/null | wc -l | numfmt --to=iec-i

