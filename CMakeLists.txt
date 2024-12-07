cmake_minimum_required(VERSION 3.11)
set(prj "compiler")
project(${prj} VERSION 0.0)
set(CMAKE_CXX_STANDARD 20)

# [my variable]
set (
    SOURCE
        Lexer/Lexer.cpp
        Lexer/spec.cpp
        main.cpp
)
set (
    LTEST_CPP
        LTest/lex_test.cpp)

# path of out
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "../")
# [end]

add_executable(${prj} ${SOURCE} ${LTEST_CPP})
# setting boost
set(BOOST_ROOT "c:/boost")
set(BOOST_INCLUDEDIR "c:/boost/include/boost-1_86")

set(Boost_USE_STATIC_RUNTIME ON)


find_package(Boost 1.86 REQUIRED COMPONENTS locale)
if (Boost_FOUND)
    target_include_directories(${prj} PUBLIC ${Boost_INCLUDE_DIR})
    target_link_libraries(${prj} ${Boost_LIBRARIES})
    message(STATUS "Fount boost ${Boost_VERSION_STRING}")
else()
    message(STATUS "NOT fount boost")
endif()
# end

target_include_directories(${prj} PRIVATE
Lexer
LTest)
