set(apptarget waters)

find_package(glfw3 CONFIG REQUIRED)
set(EXT_LIBS glfw)

file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c)
file(GLOB headers ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)

add_executable(${apptarget} ${sources} ${headers})

target_link_libraries(${apptarget} ${ENGINE_LIBRARIES} ${EXT_LIBS})
add_dependencies(${apptarget} ${ENGINE_API})