cmake_minimum_required(VERSION 3.1...3.25)
project(GOLD VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

## Uncomment and specify if CMake can not find Boost: 
# set(BOOST_ROOT "")
# set(BOOST_INCLUDEDIR "")

## Uncomment and specify if CMake can not find SDL: 
# set(SDL_LIBRARY "")
# set(SDL_INCLUDE_DIR "")

find_package(SDL2 REQUIRED)
if (NOT SDL2_FOUND)
  message(FATAL_ERROR "Fatal error: SDL2 not found.")
endif (NOT SDL2_FOUND)

find_package(Boost REQUIRED)
if (NOT Boost_FOUND)
  message(FATAL_ERROR "Fatal error: Boost not found.")
endif (NOT Boost_FOUND)

file(GLOB SOURCES
    ./*.h
    ./*.cpp
)

add_executable(GOLD ${SOURCES})

target_include_directories(GOLD PUBLIC
                           "${PROJECT_BINARY_DIR}"
                           )

set(GRAPHVIZ_LIBRARIES cgraph gvc cdt)
set(GRAPHVIZ_INCLUDE_DIRS "/usr/include/graphviz")

message("Including Boost: " ${Boost_INCLUDE_DIR})
target_include_directories(GOLD PUBLIC ${Boost_INCLUDE_DIR})

message("Including SDL2: " ${SDL2_INCLUDE_DIRS})
target_include_directories(GOLD PUBLIC ${SDL2_INCLUDE_DIRS})

message("Including graphviz:" ${GRAPHVIZ_INCLUDE_DIRS})
target_include_directories(GOLD PUBLIC ${GRAPHVIZ_INCLUDE_DIRS})

message("Linking graphviz libraries:" ${GRAPHVIZ_LIBRARIES})
target_link_libraries(GOLD ${GRAPHVIZ_LIBRARIES})

message("Linking SDL:" ${SDL2_LIBRARIES})
target_link_libraries(GOLD ${SDL2_LIBRARIES})

message("Linking SDL_image: -lSDL2_image" )
target_link_libraries(GOLD "-lSDL2_image")
