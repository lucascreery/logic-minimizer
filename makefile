CC = g++

MAIN = qmc

CFLAGS = -g

INCLUDES = -I./include

LFLAGS = -L./lib

LIBS = 

SRCS = main.cpp src/logicfunctions.cpp src/input.cpp src/petricks.cpp

all: $(MAIN)

$(MAIN):
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(SRCS) $(LFLAGS) $(LIBS)

clean:
	$(RM) *.o *~ $(TARGET)

depend: $(SRCS)
	makedepend $(INCLUDES) $^