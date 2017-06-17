#!/bin/bash
cd server-src
g++ baseserver.cpp luavm.cpp socketevent.cpp main.cpp -llua -ldl -levent -o ../main
