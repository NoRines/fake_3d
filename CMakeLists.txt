cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

project(fake_3d)

find_package(SDL2 REQUIRED)

file(GLOB code "code/*.cpp")
file(GLOB frameBuffers "code/Graphics/FrameBuffers/*.cpp")

add_executable(
	fake_3d
	${code}
	${frameBuffers}
)

target_link_libraries(fake_3d ${SDL2_LIBRARIES})
