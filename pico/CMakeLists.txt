cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(sicrib_pico)

pico_sdk_init()

add_executable(sicrib_pico sicrib_pico.cpp)
add_library(arduinoFFT arduinoFFT.cpp)


pico_enable_stdio_usb(sicrib_pico 0)
pico_enable_stdio_uart(sicrib_pico 1)

pico_add_extra_outputs(sicrib_pico)

target_link_libraries(sicrib_pico
	pico_stdlib
	hardware_adc
	hardware_dma
	arduinoFFT
	)
