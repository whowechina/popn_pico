add_executable(pico_popn main.c buttons.c usb_descriptors.c)
add_compile_options(-Wfatal-errors -O3)
include_directories(${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(pico_popn PRIVATE
        pico_multicore
        pico_stdlib
        tinyusb_device
        tinyusb_board)

pico_add_extra_outputs(pico_popn)