#!/usr/bin/env bash
g++ -o main main.cpp SDL2NovaVGA.cpp -D_GNU_SOURCE=1 -D_REENTRANT -lSDL2 -Wall
