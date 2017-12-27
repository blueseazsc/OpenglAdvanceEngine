cmake_minimum_required( VERSION 2.8 )

# set(CMAKE_C_COMPILER "/usr/bin/gcc")
# set(CMAKE_CXX_COMPILER "/usr/bin/g++")

project( OpenglEngine )

message(STATUS "project source dir= ${OpenglEngine_SOURCE_DIR}")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -ggdb -std=c++11")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++11")

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${OpenglEngine_SOURCE_DIR}/cmake")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(GLM REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED GLFW3)

message(STATUS "opengl include dir 			= ${OPENGL_INCLUDE_DIR}")
message(STATUS "opengl include dirs 		= ${OPENGL_INCLUDE_DIRS}")
message(STATUS "opengl ldflag 				= ${OPENGL_LDFLAGS}")
message(STATUS "opengl ldflag other 		= ${OPENGL_LDFLAGS_OTHER}")
message(STATUS "opengl cflag 				= ${OPENGL_CFLAGS}")
message(STATUS "opengl cflag other 			= ${OPENGL_CFLAGS_OTHER}")
message(STATUS "opengl library 				= ${OPENGL_LIBRARY}")
message(STATUS "opengl libraries 			= ${OPENGL_LIBRARIES}")

message(STATUS "glut include dir 			= ${GLUT_INCLUDE_DIR}")
message(STATUS "glut include dirs 			= ${GLUT_INCLUDE_DIRS}")
message(STATUS "glut ldflag 				= ${GLUT_LDFLAGS}")
message(STATUS "glut ldflag other 			= ${GLUT_LDFLAGS_OTHER}")
message(STATUS "glut cflag 					= ${GLUT_CFLAGS}")
message(STATUS "glut cflag other 			= ${GLUT_CFLAGS_OTHER}")
message(STATUS "glut library 				= ${GLUT_LIBRARY}")
message(STATUS "glut libraries 				= ${GLUT_LIBRARIES}")

message(STATUS "glfw include dir 		= ${GLFW_INCLUDE_DIR}")
message(STATUS "glfw include dirs 		= ${GLFW_INCLUDE_DIRS}")
message(STATUS "glfw ldflag 			= ${GLFW_LDFLAGS}")
message(STATUS "glfw ldflag other 		= ${GLFW_LDFLAGS_OTHER}")
message(STATUS "glfw cflag 				= ${GLFW_CFLAGS}")
message(STATUS "glfw cflag other 		= ${GLFW_CFLAGS_OTHER}")
message(STATUS "glfw library 			= ${GLFW_LIBRARY}")
message(STATUS "glfw libraries 			= ${GLFW_LIBRARIES}")

message(STATUS "glew include dir 		= ${GLEW_INCLUDE_DIR}")
message(STATUS "glew include dirs 	= ${GLEW_INCLUDE_DIRS}")
message(STATUS "glew ldflag 			= ${GLEW_LDFLAGS}")
message(STATUS "glew ldflag other 	= ${GLEW_LDFLAGS_OTHER}")
message(STATUS "glew cflag 			= ${GLEW_CFLAGS}")
message(STATUS "glew cflag other 		= ${GLEW_CFLAGS_OTHER}")
message(STATUS "glew library 			= ${GLEW_LIBRARY}")
message(STATUS "glew libraries 		= ${GLEW_LIBRARIES}")

message(STATUS "glm include dir 		= ${GLM_INCLUDE_DIR}")
message(STATUS "glm include dirs 		= ${GLM_INCLUDE_DIRS}")
message(STATUS "glm ldflag 			= ${GLM_LDFLAGS}")
message(STATUS "glm ldflag other 		= ${GLM_LDFLAGS_OTHER}")
message(STATUS "glm cflag 			= ${GLM_CFLAGS}")
message(STATUS "glm cflag other 		= ${GLM_CFLAGS_OTHER}")
message(STATUS "glm library 			= ${GLM_LIBRARY}")
message(STATUS "glm libraries 		= ${GLM_LIBRARIES}")

set(SOIL_INCLUDE_DIRS "/usr/local/include")
set(SOIL_LIBRARIES "/usr/local/lib/libSOIL.a")

add_subdirectory(src)
