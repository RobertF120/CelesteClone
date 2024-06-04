#!/bin/bash

libs=-luser32
warnings="-Who-writable-strings -Who-format-security"

clang++ -g src/main.cpp  -oCelesteClone.exe $libs $warnings