
# Only making this file to make sure to add the proper include folder

CC := g++
CLFAGS := #we can decide what CFLAGS we want I guess
CPPFLAGS := -Iinclude

OUT = cppsweeper
#take every c++ file in src
CPP_SRCS = $(wildcard src/*.cpp)
OBJ_SRCS := $(CPP_SRCS:.cpp=.o)

all: $(OUT)
#feel free to make ANY changes to the makefile
$(OUT): $(OBJ_SRCS)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $(OUT) $(OBJ_SRCS)

