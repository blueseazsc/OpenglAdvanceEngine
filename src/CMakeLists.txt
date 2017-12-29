project( Test )

add_executable( main main.cpp util.cpp vertexbuffer.cpp shader.cpp ground.cpp model.cpp )
# add_executable( main scene_triangle.cpp util.cpp vertexbuffer.cpp shader.cpp )

target_include_directories(main PUBLIC ${OPENGL_INCLUDE_DIR} ${GLFW_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} ${SOIL_INCLUDE_DIRS})

target_link_libraries(main ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLFW_LDFLAGS} ${GLEW_LIBRARIES} ${SOIL_LIBRARIES})
