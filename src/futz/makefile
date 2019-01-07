SOURCES_SHARED = Futz.cpp \
      GameBase.cpp \
      TimeKeeper.cpp \
      3rdParty/stb_image.cpp \
      platforms/SystemLayerBase.cpp \
      renderers/dummy/DummyRenderer.cpp \
      renderers/gl1/GL1Renderer.cpp \
      camera/Camera.cpp \
      input/Input.cpp \
      input/InputEventQueue.cpp \
      core/Node.cpp \
      core/Transform.cpp \
      core/Profiler.cpp \
      core/components/AxisAlignedBoundingBox.cpp \
      core/components/BoundingBox.cpp \
      core/components/BoundingSphere.cpp \
      core/components/BoxCollider.cpp \
      core/components/DrawModel.cpp \
      core/components/DrawAxis.cpp \
      scenegraph/SceneGraph.cpp \
      models/Model.cpp \
      models/Material.cpp \
      models/Triangle.cpp \
      models/dummy/DummyModel.cpp \
      models/wavefront/WavefrontModel.cpp \
      math/Matrix4.cpp math/Vector3.cpp math/Quaternion.cpp \

SOURCES_SDL =  $(SOURCES_SHARED) platforms/FutzSDL.cpp
SOURCES_SDL2 =  $(SOURCES_SHARED) platforms/FutzSDL2.cpp
SOURCES_GLUT =  $(SOURCES_SHARED) platforms/FutzGlut.cpp

OBJECTS_SDL=$(SOURCES_SDL:.cpp=.o)
OBJECTS_SDL2=$(SOURCES_SDL2:.cpp=.o)
OBJECTS_GLUT=$(SOURCES_GLUT:.cpp=.o)

OUT_SDL = bin/libfutz_sdl.a
OUT_SDL2 = bin/libfutz_sdl2.a
OUT_GLUT = bin/libfutz_glut.a


UNAME := $(shell uname)

OS = LINUX
ifeq ($(UNAME),Darwin)
  OS = OSX
endif

all:
	$(MAKE) sdl
	$(MAKE) sdl2
	$(MAKE) glut

sdl:
	rm -f Futz.o
	$(MAKE) sdlR DEFINES="-D FUTZ_PLATFORM_SDL -D FUTZ_RENDERER_GL1 -D $(OS)" 
sdl2:
	rm -f Futz.o
	$(MAKE) sdl2R DEFINES="-D FUTZ_PLATFORM_SDL2 -D FUTZ_RENDERER_GL1 -D $(OS)" 
glut:
	rm -f Futz.o
	$(MAKE) glutR DEFINES="-D FUTZ_PLATFORM_GLUT -D FUTZ_RENDERER_GL1 -D $(OS)" 

sdlR: $(OUT_SDL)
sdl2R: $(OUT_SDL2)
glutR: $(OUT_GLUT)


.cpp.o:
	$(LAYER)
	$(CC) $(DEFINES) $(INCLUDES) $(CCFLAGS) -c $< -o $@

# C++ compiler flags (-g -O2 -Wall)
CCFLAGS = -g

# compiler
CC = g++

.SUFFIXES: .cpp

$(OUT_SDL): $(OBJECTS_SDL)
	ar rcs $(OUT_SDL) $(OBJECTS_SDL)

$(OUT_SDL2): $(OBJECTS_SDL2)
	ar rcs $(OUT_SDL2) $(OBJECTS_SDL2)

$(OUT_GLUT): $(OBJECTS_GLUT)
	ar rcs $(OUT_GLUT) $(OBJECTS_GLUT)

clean:
	rm -f $(OBJECTS_GLUT) $(OBJECTS_SDL) $(OUT_SDL) $(OUT_SDL2) $(OUT_GLUT)
