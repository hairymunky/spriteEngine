OBJS =  events/event_controller.cpp texture_manager.cpp sdldisplay.cpp application.cpp main.cpp
CC = g++
CFLAGS = -D_DEBUG -std=c++17
LIBS = -lSDL2 -lSDL2_image
PROGNAME = sandbox 

all: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LIBS) -o $(PROGNAME)

clean:
	rm $(PROGNAME)