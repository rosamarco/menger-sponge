cmake_minimum_required(VERSION 3.17)
project(Merger_sponge)

set(CMAKE_CXX_STANDARD 14)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
file(COPY shaders DESTINATION ${CMAKE_BINARY_DIR})

set(LIB_PATH ${CMAKE_CURRENT_LIST_DIR}/libs)
set(GLEW_H ${LIB_PATH}/glew-2.2.0/include)
set(GLM_H ${LIB_PATH}/glm-0.9.9.8/)
set(GLAD_H ${LIB_PATH}/glad)
set(KHR_H ${LIB_PATH}/KHR)
set(STB_H ${LIB_PATH}/stb)
set(GLAD_C ${GLAD_H}/glad.c)
include_directories(${GLEW_H} ${GLM_H} ${GLAD_H} ${KHR_H} ${STB_H} ${LIB_PATH})

add_subdirectory(${LIB_PATH}/glfw-3.3.4 build)

set(GLEW_LINK ${LIB_PATH}/glew-2.2.0/lib/glew32s.lib)
link_libraries(${OPENGL} ${GLEW_LINK})
find_package(OpenGL REQUIRED)
# Execute compilation command
set(SOURCE_FILES main.cpp)
add_executable(${PROJECT_NAME} ${GLAD_C} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} glfw)