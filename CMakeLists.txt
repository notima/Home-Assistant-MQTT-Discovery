cmake_minimum_required(VERSION 3.14)
project(home_assistant_mqtt_discovery_lib CXX)
add_definitions(-fms-extensions)

set(CMAKE_CXX_STANDARD 11)

set(INCLUDE ./include)
set(SRC ./src)
set(TEST ./test)
include_directories(${INCLUDE})

add_executable(
    test_sensor 
    ${TEST}/test_sensor.cpp
    ${SRC}/ha_discovery.cpp
)

add_executable(
    test_tracker
    ${TEST}/test_tracker.cpp
    ${SRC}/ha_discovery.cpp
)

enable_testing()

add_test(NAME test_sensor COMMAND $<TARGET_FILE:test_sensor>)
add_test(NAME test_tracker COMMAND $<TARGET_FILE:test_tracker>)