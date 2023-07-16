cmake_minimum_required(VERSION 3.16...3.26)

include("${CMAKE_CURRENT_SOURCE_DIR}/cmake/common/bootstrap.cmake" NO_POLICY_SCOPE)

project(Codejam VERSION 1.0.0)

option(ENABLE_FRONTEND_API "Use obs-frontend-api for UI functionality" ON)
option(ENABLE_QT "Use Qt functionality" ON)

include(compilerconfig)
include(defaults)
include(helpers)

add_library(${CMAKE_PROJECT_NAME} MODULE)

add_library(browser SHARED)
target_sources(browser PRIVATE src/browser.cpp src/browser.hpp)

find_package(libobs REQUIRED)

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE OBS::libobs)

# LibOBS
# target_link_libraries(browser PRIVATE OBS::libobs)

# OBS frontend
if(ENABLE_FRONTEND_API)
  find_package(obs-frontend-api REQUIRED)
  target_link_libraries(browser PRIVATE OBS::obs-frontend-api)
  target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE OBS::obs-frontend-api)
endif()

if(ENABLE_QT)
  find_qt(COMPONENTS Core Gui Widgets)
  target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE Qt::Core Qt::Gui Qt::Widgets)
  target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${Qt6Widgets_INCLUDE_DIRS})
  target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE ${Qt6Widgets_DEFINITIONS})

  target_compile_options(
    ${CMAKE_PROJECT_NAME} PRIVATE $<$<C_COMPILER_ID:Clang,AppleClang>:-Wno-quoted-include-in-framework-header
                                  -Wno-comma>)
  set_target_properties(
    ${CMAKE_PROJECT_NAME}
    PROPERTIES AUTOMOC ON
               AUTOUIC ON
               AUTORCC ON)
endif()

find_package(cpr REQUIRED)
add_library(TwitchClient SHARED)
target_sources(TwitchClient PRIVATE src/TwitchClient.cpp src/TwitchClient.hpp)
target_link_libraries(TwitchClient PRIVATE cpr::cpr)

# Executable for testing TwitchClient. Should replace with unit tests at some point
# add_executable(TwitchClientTest)
# target_sources(TwitchClientTest PRIVATE src/TwitchClientTest.cpp)
# target_link_libraries(TwitchClientTest PRIVATE TwitchClient)

find_package(nlohmann_json 3.2.0 REQUIRED)
add_library(TwitchClipFetcher SHARED)
target_sources(TwitchClipFetcher PRIVATE src/TwitchClipFetcher.cpp src/TwitchClipFetcher.hpp)
target_link_libraries(TwitchClipFetcher PRIVATE nlohmann_json::nlohmann_json)

# Executable for testing TwitchClipFetcher. Should replace with unit tests at some point
# add_executable(TwitchClipFetcherTest)
# target_sources(TwitchClipFetcherTest PRIVATE src/TwitchClipFetcherTest.cpp)
# target_link_libraries(TwitchClipFetcherTest PRIVATE TwitchClipFetcher TwitchClient)

# target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE TwitchClipFetcher TwitchClient)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE nlohmann_json::nlohmann_json cpr::cpr)
target_sources(${CMAKE_PROJECT_NAME} PRIVATE src/plugin-main.cpp src/test.cpp src/TwitchClipFetcher.cpp src/TwitchClient.cpp src/browser.cpp)

set_target_properties_plugin(${CMAKE_PROJECT_NAME} PROPERTIES OUTPUT_NAME ${_name})
