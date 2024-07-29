set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_C_COMPILER clang)
cmake_minimum_required(VERSION 3.10)

# Назва проекту
project(Game)

# Версія стандарту C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS True)
# Джерельні файли
set(SOURCE_FILES
    main.cpp
    canvasitem.cpp
    entities/enemy.cpp
    entities/bullet.cpp
    entities/player.cpp
    canvasitems/sprite.cpp
    audioserver.cpp
)

# Вихідний файл
add_executable(Game ${SOURCE_FILES})

# Підключення бібліотек
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(OpenAL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${OPENAL_INCLUDE_DIRS})

# Пошук бібліотеки SOIL вручну
find_library(SOIL_LIBRARY SOIL)
if (NOT SOIL_LIBRARY)
    message(FATAL_ERROR "Could not find SOIL library")
endif()

# Пошук бібліотеки SndFile вручну
find_path(SNDFILE_INCLUDE_DIR sndfile.h)
find_library(SNDFILE_LIBRARY sndfile)
if (NOT SNDFILE_INCLUDE_DIR OR NOT SNDFILE_LIBRARY)
    message(FATAL_ERROR "Could not find SndFile library")
endif()
include_directories(${SNDFILE_INCLUDE_DIR})

# Підключення бібліотек до проекту
target_link_libraries(Game ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${SNDFILE_LIBRARY} ${OPENAL_LIBRARIES} ${SOIL_LIBRARY} openal)

