cmake_minimum_required(VERSION 3.10)
project(tmpp)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

set(SOURCES
        src/Match.cpp
        src/Player.cpp
        src/MatchManager.cpp
)

add_executable(main1 main1.cpp ${SOURCES})

add_executable(main2 main2.cpp ${SOURCES})
