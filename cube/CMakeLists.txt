add_compile_options(-std=c++14)


# WiringPi
find_package(WiringPi REQUIRED)
include_directories(${WIRINGPI_INCLUDE_DIRS})

# libao
find_package(AO REQUIRED)
include_directories(${LIBAO_INCLUDE_DIR})

# fftw3
find_package(FFTW REQUIRED)
include_directories(${FFTW_INCLUDE_DIRS})

# rpi-rgb-led-matrix
include_directories(${PROJECT_SOURCE_DIR}/lib/matrix/include/)

# Boost system and filesystem
find_package(Boost 1.36.0 COMPONENTS system REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

# Crow
include_directories(${PROJECT_SOURCE_DIR}/lib/crow/include/)

# Json
add_definitions(-DCROW_JSON_NO_ERROR_CHECK)
include_directories(${PROJECT_SOURCE_DIR}/lib/json/include/)

# ImageMagick
add_definitions(-DMAGICKCORE_HDRI_ENABLE=0 -DMAGICKCORE_QUANTUM_DEPTH=16)
find_package(ImageMagick 6 COMPONENTS Magick++ MagickCore)
include_directories(${ImageMagick_INCLUDE_DIRS})
include_directories(${ImageMagick_Magick++_INCLUDE_DIRS})

find_library(REAL_TIME rt)

add_executable(cube
        main.cpp
        screen/screen.h screen/screen.cpp

        active_screen.h active_screen.cpp
        api_server.cpp api_server.h
        alarm.h alarm.cpp
        wakedog.cpp wakedog.h
        ringer.cpp ringer.h
        rotary_encoder.cpp rotary_encoder.h
        audio/playback.cpp audio/playback.h

        screen/gif_screen.h screen/gif_screen.cpp
        audio/playback_screen.h audio/playback_screen.cpp
        screen/clock_screen.h screen/clock_screen.cpp
        screen/boot_screen.h screen/boot_screen.cpp
        screen/empty_screen.h)
target_link_libraries(cube matrix
        ${WIRINGPI_LIBRARIES}
        ${LIBAO_LIBRARIES}
        ${Boost_LIBRARIES}
        ${ImageMagick_Magick++_LIBRARY}
        ${ImageMagick_MagickCore_LIBRARY}
        ${FFTW_LIBRARIES} ${REAL_TIME})

install(TARGETS cube RUNTIME DESTINATION bin)