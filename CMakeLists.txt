cmake_minimum_required(VERSION 3.22)
project(ex5_shirazholzberg)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ex5_shirazholzberg
        Movie.cpp
        Movie.h
#        print_main.cpp
        RecommendationSystem.h
        RecommendationSystemLoader.h
        User.cpp
        User.h
        UsersLoader.h RecommendationSystem.cpp RecommendationSystemLoader.cpp UsersLoader.cpp presubmit.cpp)
