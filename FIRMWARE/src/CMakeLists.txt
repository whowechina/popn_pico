add_executable(${PROJECT_NAME} main.c buttons.c usb_descriptors.c)

target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Werror -Wfatal-errors -O3)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(${PROJECT_NAME} PRIVATE
    pico_multicore pico_stdlib tinyusb_device tinyusb_board)

# Make a UF2 binary
pico_add_extra_outputs(${PROJECT_NAME})
