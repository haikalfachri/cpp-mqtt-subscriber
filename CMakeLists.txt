cmake_minimum_required(VERSION 3.5.0)
project(helloworld VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 20)
# SET(CMAKE_EXE_LINKER_FLAGS  "/FORCE")

include(CTest)
enable_testing()

include_directories(
  "C:\\vcpkg\\installed\\x64-windows\\include"
)
link_directories(
  "C:\\vcpkg\\installed\\x64-windows\\lib"
)

file(GLOB_RECURSE sources src/*.cpp src/*.cc src/*.h src/*.hpp)

add_executable(main ${sources})

find_package(PahoMqttCpp CONFIG REQUIRED)
target_link_libraries(main PahoMqttCpp::paho-mqttpp3)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)