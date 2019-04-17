cmake_minimum_required(VERSION 3.12)
project (torch-js)

# Use C++11
set(CMAKE_CXX_STANDARD 11)
if (NOT MSVC)
  set(CMAKE_C_STANDARD 11)
endif()

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  # Without this set, the package is only found by absolute path, so you can't move it on disk
  set(INSTALL_RPATH "@loader_path")
  set(CMAKE_BUILD_WITH_INSTALL_RPATH 1)
endif()

find_package(Torch REQUIRED)

include_directories(${CMAKE_JS_INC})
file(GLOB SOURCE_FILES "src/*.cc" "src/*.h")
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
set_property(TARGET ${PROJECT_NAME} PROPERTY INSTALL_RPATH  "@loader_path")
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_JS_INC})
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/node_modules/node-addon-api")
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})
target_link_libraries(${PROJECT_NAME} "${TORCH_LIBRARIES}")

add_definitions( -Wall -O2 -fexceptions )
