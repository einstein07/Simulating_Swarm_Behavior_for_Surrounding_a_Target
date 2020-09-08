# Minimal C/C++ makefile
# Kevin Nickels
# Just type "make exec" and if exec.cc or .c exists, it'll do the right thing

CXXFLAGS = `pkg-config --cflags playerc++` -g
CFLAGS = `pkg-config --cflags playerc` -g
LDLIBS = `pkg-config --libs playerc++`
CC = g++

all: simple
