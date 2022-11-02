cmake_minimum_required(VERSION 3.18.4)
project(flagpole_io_hardware_controller C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/)

add_executable(flagpole_io_hardware_controller main.c include/request.c include/request.h include/data-store.c include/data-store.h include/string-util.c include/string-util.h include/gpio.c include/gpio.h)

find_package(hiredis REQUIRED)
include_directories(${HIREDIS_INCLUDE_DIRS})
target_link_libraries(flagpole_io_hardware_controller ${HIREDIS_LIBRARIES})

include_directories(~/Downloads/jsmn)

find_package(pigpio REQUIRED)
include_directories(${pigpio_INCLUDE_DIRS})
target_link_libraries(flagpole_io_hardware_controller ${pigpio_LIBRARY} ${pigpiod_if_LIBRARY} ${pigpiod_if2_LIBRARY})