CC=g++
CFLAGS=`pkg-config --cflags playerc++`
LDLIBS = `pkg-config --libs playerc++`
SOURCES=main.cpp robot.cpp communication.cpp movement.cpp tests.cpp
DEPS=robot.h communication.h movement.h tests.h
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=swarm

all:$(EXECUTABLE)
	@echo Make has finished.

$(EXECUTABLE):
	$(CC) -pthread -o $@ $(CFLAGS) -g $(SOURCES) $(LDLIBS)
clean:
	rm -f a.out core $(EXECUTABLE) *.o
