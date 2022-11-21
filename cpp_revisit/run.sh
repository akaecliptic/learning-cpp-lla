#!/usr/bin/bash

sqlite_out="./sqlite3.o"

if [[ !(-e $sqlite_out) ]]; then bash -c "gcc -c include/libs/sqlite/sqlite3.c"; fi
bash -c "g++ sqlite3.o app.cpp src/* -o app.exe"
./app.exe
