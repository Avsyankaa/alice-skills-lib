cmake_minimum_required(VERSION 3.9)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include("tools/gate/cmake/HunterGate.cmake")

HunterGate(
  URL "https://github.com/ruslo/hunter/archive/v0.23.31.tar.gz"
  SHA1 "3d94b8522541c4c8eaac606f4c47d09322a8019c"
)

project(alice)
string(APPEND CMAKE_CXX_FLAGS "-Wall -Wextra -Wno-unused-command-line-argument -Wnon-virtual-dtor -pedantic -pthread")

hunter_add_package(GTest)
find_package(GTest CONFIG REQUIRED)

hunter_add_package(nlohmann_json)
find_package(nlohmann_json CONFIG REQUIRED)

hunter_add_package(Boost)
find_package(Boost CONFIG REQUIRED)

hunter_add_package(Beast)
find_package(Beast CONFIG REQUIRED)

add_executable(alice_tests
  source/Request.cpp
  source/Meta.cpp
  source/Session.cpp
  source/Response.cpp
  source/Button.cpp
  source/Card.cpp
  source/ButtonPicture.cpp
  tests/request_unittests.cpp
  tests/response_unittests.cpp
)

add_executable(alice_main
  source/Request.cpp
  source/Meta.cpp
  source/Session.cpp
  source/Response.cpp
  source/Button.cpp
  source/Card.cpp
  source/ButtonPicture.cpp
  source/main.cpp
)

target_include_directories(alice_tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)
target_include_directories(alice_main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/includes)

target_link_libraries(alice_tests GTest::main nlohmann_json::nlohmann_json Boost::boost Boost::system)
target_link_libraries(alice_main nlohmann_json::nlohmann_json Boost::boost Boost::system)

enable_testing()
add_test(NAME tests COMMAND alice_tests)

if(MSVC)
  add_definitions(-D_WIN32_WINNT=0x0601)
  add_definitions(-D_SCL_SECURE_NO_WARNINGS=1)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS=1)
  add_definitions(-D_SILENCE_CXX17_ALLOCATOR_VOID_DEPRECATION_WARNING)
  add_compile_options(/MP)
  string(REPLACE "/W3" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER build)

file(GLOB APP_FILES
  source/Request.cpp
  source/Meta.cpp
  source/Session.cpp
  source/Response.cpp
  source/Button.cpp
  source/Card.cpp
  source/ButtonPicture.cpp
  source/main.cpp
)

source_group("" FILES ${APP_FILES})

add_executable(websocket-chat-server ${APP_FILES})

if(NOT WIN32)
  find_package(Threads)
  target_link_libraries(websocket-chat-server PRIVATE Threads::Threads nlohmann_json::nlohmann_json Boost::boost Boost::system))
endif()

set_target_properties(websocket-chat-server PROPERTIES
  VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY
  VS_STARTUP_PROJECT websocket-chat-server)
