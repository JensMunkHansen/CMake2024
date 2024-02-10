#!/bin/bash

find . -name _CPack_Packages -type d | xargs -i -t rm -Rf {}
find . -name build -type d | xargs -i -t rm -Rf {}
find . -name release -type d | xargs -i -t rm -Rf {}
find . -name debug -type d | xargs -i -t rm -Rf {}
find . -name install -type d | xargs -i -t rm -Rf {}
