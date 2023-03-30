cmake_minimum_required(VERSION 3.0.0)
project(Procesor_CSS VERSION 0.1.0 LANGUAGES CXX)
set (CMAKE_CXX_STANDARD 17)

file(GLOB source_files CONFIGURE_DEPENDS "src/*.h" "src/*.cpp")


add_executable(Procesor_CSS ${source_files})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
