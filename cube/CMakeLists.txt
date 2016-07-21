# WiringPi
find_package(WiringPi REQUIRED)
include_directories(${WIRINGPI_INCLUDE_DIRS})

# libao
find_package(AO REQUIRED)
include_directories(${LIBAO_INCLUDE_DIR})

# rpi-rgb-led-matrix
include_directories(${PROJECT_SOURCE_DIR}/lib/matrix/include/)

# Boost system and filesystem
find_package(Boost 1.36.0 COMPONENTS system REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

# Crow
include_directories(${PROJECT_SOURCE_DIR}/lib/crow/include/)

# Json
add_definitions(-DCROW_JSON_NO_ERROR_CHECK)
include_directories(${PROJECT_SOURCE_DIR}/lib/json/src/)

# ImageMagick
add_definitions(-DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16)
find_package(ImageMagick COMPONENTS Magick++)
include_directories(${ImageMagick_INCLUDE_DIRS})
include_directories(${ImageMagick_Magick++_INCLUDE_DIR})
include_directories(${ImageMagick_Magick++_INCLUDE_DIRS})


add_executable(cube
        main.cpp
        screen/screen.h
        screen/empty_screen.h

        active_screen.cpp active_screen.h
        canvas.cpp canvas.h
        api_server.cpp api_server.h
        alarm.h alarm.cpp wakedog.cpp wakedog.h ringer.cpp ringer.h
        rotary_encoder.cpp rotary_encoder.h
        audio/playback.cpp audio/playback.h)
target_link_libraries(cube matrix ${WIRINGPI_LIBRARIES} ${LIBAO_LIBRARIES} ${Boost_LIBRARIES} ${ImageMagick_LIBRARIES})

add_executable(host_test test.cpp)
target_link_libraries(host_test ${WIRINGPI_LIBRARIES})
