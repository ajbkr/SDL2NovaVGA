#!/usr/bin/env bash
g++ -o examples/ColorPalette/ColorPalette -x c++ examples/ColorPalette/ColorPalette.ino SDL2NovaVGA.cpp -I. -D_GNU_SOURCE=1 -D_REENTRANT -lSDL2 -Wall
g++ -o examples/Stripes/Stripes -x c++ examples/Stripes/Stripes.ino SDL2NovaVGA.cpp -I. -D_GNU_SOURCE=1 -D_REENTRANT -lSDL2 -Wall
