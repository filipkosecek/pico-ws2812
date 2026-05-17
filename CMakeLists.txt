cmake_minimum_required(VERSION 3.13)

# Include and source dirs
set(INC_DIR ${CMAKE_CURRENT_LIST_DIR}/inc)
set(SRC_DIR ${CMAKE_CURRENT_LIST_DIR}/src)

add_library(pico-ws2812 STATIC ${SRC_DIR}/ws2812.c)

# Set C standard.
set_target_properties(pico-ws2812 PROPERTIES
        C_STANDARD 17
        C_EXTENSIONS ON
)

# Compiler options
target_compile_options(pico-ws2812 PRIVATE
        -W
        -Wall
        -Wextra
        -Werror
)

# Library settings overrides
if(NOT WS2812_N_LEDS)
        set(WS2812_N_LEDS 30)
endif()

if(NOT WS2812_PIO_BANK)
        set(WS2812_PIO_BANK pio0)
endif()

if(NOT WS2812_SM_INDEX)
        set(WS2812_SM_INDEX 0)
endif()

if(NOT WS2812_PIN)
        set(WS2812_PIN 0)
endif()

if(WS2812_RGBW)
        target_compile_definitions(pico-ws2812 PUBLIC WS2812_RGBW)
endif()

target_compile_definitions(pico-ws2812 PUBLIC
        WS2812_N_LEDS=${WS2812_N_LEDS}
        WS2812_PIO_BANK=${WS2812_PIO_BANK}
        WS2812_SM_INDEX=${WS2812_SM_INDEX}
        WS2812_PIN=${WS2812_PIN}
)

# Set the include directory.
target_include_directories(pico-ws2812 PUBLIC ${INC_DIR})

# Link Pico SDK libraries.
target_link_libraries(pico-ws2812
        pico_stdlib
        hardware_pio
)

# Compile the PIO program and generate the ws2812.pio.h file.
pico_generate_pio_header(pico-ws2812 ${SRC_DIR}/ws2812.pio)
