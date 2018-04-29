set(MATRIX_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/lib/matrix/include/)

include_directories(${MATRIX_INCLUDE_DIR})

set(LED_MATRIX
        ${PROJECT_SOURCE_DIR}/lib/matrix/lib/led-matrix.cc
        ${PROJECT_SOURCE_DIR}/lib/matrix/lib/options-initialize.cc
        ${PROJECT_SOURCE_DIR}/lib/matrix/lib/multiplex-mappers.cc
        ${PROJECT_SOURCE_DIR}/lib/matrix/lib/pixel-mapper.cc)
set(THREAD
        ${PROJECT_SOURCE_DIR}/lib/matrix/lib/thread.cc)
set(FRAMEBUFFER
        ${PROJECT_SOURCE_DIR}/lib/matrix/lib/framebuffer.cc
        ${PROJECT_SOURCE_DIR}/lib/matrix/lib/hardware-mapping.c)
set(GRAPHICS
        ${PROJECT_SOURCE_DIR}/lib/matrix/lib/graphics.cc)

set(OTHER ${PROJECT_SOURCE_DIR}/lib/matrix/lib/gpio.cc )

#add_definitions(-DRGB_CLASSIC_PINOUT)
#add_definitions(-DDRGB_SLOWDOWN_GPIO=2)

find_package (Threads)
find_library(REAL_TIME rt)
message(Real-time: ${REAL_TIME})
set(THREADING ${REAL_TIME} ${CMAKE_THREAD_LIBS_INIT})

add_library(matrix ${LED_MATRIX} ${THREAD} ${FRAMEBUFFER} ${GRAPHICS} ${OTHER})
target_link_libraries(matrix ${THREADING})