# pico-ws2812
A simple WS2812 library for Raspberry Pi Pico. It is based on the
[original example](https://github.com/raspberrypi/pico-examples/tree/master/pio/ws2812)
and inspired by ArchTonIO's [PicoRGB](https://github.com/ArchTonIO/PicoRGB)
but it aims to be simple and easy to integrate into a project as a library.

## Usage
The only dependency (aside from the standard C library) is
[Pico C SDK](https://www.raspberrypi.com/documentation/microcontrollers/c_sdk.html).

To use the library in your project, clone the repository to your project root
directory. Then include the subdirectory in the main CMakeLists file:
```
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/pico-ws2812)
```

The default pico-ws2812 settings can be overridden from your project's
CMakeLists file by setting CMake variables before calling `add_subdirectory`.
All available settings are as follows:
```
set(WS2812_N_LEDS   <n_leds>)       # Number of LEDs
set(WS2812_PIO_BANK <pio bank>)     # PIO bank (pio0 or pio1)
set(WS2812_SM_INDEX <sm index>)     # SM index (0-3)
set(WS2812_PIN      <pin num>)      # Pin to be used
set(WS2812_RGBW     <*>)            # Enable RGBW color scheme
```
