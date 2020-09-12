CC=g++
CFLAGS=`pkg-config --cflags playerc++`
LDLIBS = `pkg-config --libs playerc++`
SOURCES=main.cpp robot.cpp communication.cpp movement.cpp
DEPS=robot.h communication.h movement.h
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=swarm

all:$(EXECUTABLE)
	@echo Make has finished.

$(EXECUTABLE):
	$(CC) -o $@ $(CFLAGS) -g $(SOURCES) $(LDLIBS)
clean:
	rm -f a.out core $(EXECUTABLE) *.o
