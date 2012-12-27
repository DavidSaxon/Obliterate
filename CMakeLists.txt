CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
CMAKE_POLICY(VERSION 2.6)
PROJECT(Obliterate)

SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake/Modules)

SET(FLAGS "${FLAGS} -g")

SET(SRCS
    ./Main.cpp
    ./Event.cpp
    ./Engine.cpp
    ./Engine_Event.cpp
    ./Engine_Resources.cpp
    ./Logo.cpp
    ./Debris.cpp
    ./Button.cpp
  )

SET(PROGRAMS Obliterate)

ADD_EXECUTABLE(Obliterate ${SRCS})

TARGET_LINK_LIBRARIES(Obliterate
  -lSDL
  -lSDL_mixer
  -lGL
  -lGLU
  -lglut
  -lpng
  -lm
  )

INSTALL(TARGETS Obliterate RUNTIME DESTINATION .)

SET_TARGET_PROPERTIES(Obliterate PROPERTIES COMPILE_FLAGS "${FLAGS}")