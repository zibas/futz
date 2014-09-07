# To build with SDL:
# make LAYER=SDL
EXECUTABLE_GLUT=demo_glut
EXECUTABLE_SDL=demo_sdl
EXECUTABLE_SDL2=demo_sdl2

UNAME := $(shell uname)

DEFINES=-D NONE
FRAMEWORK=

CC=g++
CFLAGS=-c -Wall
SOURCES=main.cpp Demo.cpp Asteroids.cpp Ships.cpp
OBJECTS=$(SOURCES:.cpp=.o)
INCLUDES = -I. -I../include/ -I../futz/

ifeq ($(LAYER),SDL)
	LIBS = -L../ -L/usr/local/lib -lm  -L../futz/bin/ -lfutz_sdl -lGL -lGLU -lSDL
	EXECUTABLE=$(EXECUTABLE_SDL)
else ifeq ($(LAYER),SDL2)
	LIBS = -L../ -L/usr/local/lib -lm  -L../futz/bin/ -lfutz_sdl2 -lGL -lGLU -lSDL2
	EXECUTABLE=$(EXECUTABLE_SDL2)
	ifeq ($(UNAME),Darwin)
	  DEFINES=-D OSX
	  LIBS = -L../ -L/usr/local/lib -lm  -L../futz/bin/ -lfutz_sdl2 -lGL -lGLU
	  LIBS += -L"/System/Library/Frameworks/OpenGL.framework/Libraries"
	  FRAMEWORK = -framework SDL2
	  FRAMEWORK += -framework OpenGL 
	endif
else
	LIBS = -L../ -L/usr/local/lib -lm  -L../futz/bin/ -lfutz_glut -lGL -lGLU -lglut
	EXECUTABLE=$(EXECUTABLE_GLUT)
	ifeq ($(UNAME),Darwin)
	  DEFINES=-D OSX
	  LIBS = -L../ -L/usr/local/lib -lm  -L../futz/bin/ -lfutz_glut -lGL -lGLU
	  LIBS += -L"/System/Library/Frameworks/OpenGL.framework/Libraries"
	  FRAMEWORK = -framework GLUT
	  FRAMEWORK += -framework OpenGL 
	endif

endif


all: 
	$(CC) $(DEFINES) $(SOURCES) $(INCLUDES) $(LIBS) $(FRAMEWORK) -o $(EXECUTABLE)

clean:
	rm -rf *o $(EXECUTABLE_GLUT) $(EXECUTABLE_SDL) $(EXECUTABLE_SDL2)
