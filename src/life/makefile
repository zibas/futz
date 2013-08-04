# To build with SDL:
# make LAYER=SDL
EXECUTABLE_GLUT=3dlife
EXECUTABLE_SDL=3dlife_sdl
FUTZ_PATH=../futz

UNAME := $(shell uname)

DEFINES=-D NONE
FRAMEWORK=

CC=g++
CFLAGS=-c -Wall
SOURCES=main.cpp Life3d.cpp liblife.c
OBJECTS=$(SOURCES:.cpp=.o)
INCLUDES = -I. -I../include/ -I$(FUTZ_PATH)

ifeq ($(LAYER),SDL)
	LIBS = -L../ -L/usr/local/lib -lm  -L$(FUTZ_PATH)/bin -lfutz_sdl -lGL -lGLU -lSDL
	EXECUTABLE=$(EXECUTABLE_SDL)
	 #SDL 1.2 is kind of insane on OSX: http://www.digitalmars.com/d/archives/digitalmars/D/12078.html
	ifeq ($(UNAME),Darwin)
	  DEFINES=-D OSX
	  LIBS = -L../ -L/usr/local/lib -lm  -L$(FUTZ_PATH)/bin -lfutz_sdl -lGL -lGLU
	  LIBS += -L"/System/Library/Frameworks/OpenGL.framework/Libraries"
	  LIBS += `sdl-config --libs`
	  INCLUDES += `sdl-config --cflags`
	  FRAMEWORK = -framework SDL
	  FRAMEWORK += -framework OpenGL 
	endif
else
	LIBS = -L../ -L/usr/local/lib -lm -L. -L$(FUTZ_PATH)/bin -lfutz_glut -lGL -lGLU -lglut 
	EXECUTABLE=$(EXECUTABLE_GLUT)
	ifeq ($(UNAME),Darwin)
	  DEFINES=-D OSX
	  LIBS = -L../ -L/usr/local/lib -lm  -L$(FUTZ_PATH)/bin -lfutz_glut -lGL -lGLU
	  LIBS += -L"/System/Library/Frameworks/OpenGL.framework/Libraries"
	  FRAMEWORK = -framework GLUT
	  FRAMEWORK += -framework OpenGL 
	endif

endif


all: 
	$(CC) $(DEFINES) $(SOURCES) $(INCLUDES) $(LIBS) $(FRAMEWORK) -o $(EXECUTABLE)

clean:
	rm -rf *o $(EXECUTABLE_GLUT) $(EXECUTABLE_SDL)
