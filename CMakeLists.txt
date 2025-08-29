cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

## RNNoise:
add_library(rnnoise STATIC)


target_include_directories(rnnoise PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/src
    ${CMAKE_CURRENT_LIST_DIR}/include
)

# Add required RNNoise source files
set(RNNoise_SRC_FILES
    ${CMAKE_CURRENT_LIST_DIR}/src/denoise.c
    ${CMAKE_CURRENT_LIST_DIR}/src/kiss_fft.c
    ${CMAKE_CURRENT_LIST_DIR}/src/pitch.c
    ${CMAKE_CURRENT_LIST_DIR}/src/celt_lpc.c
    ${CMAKE_CURRENT_LIST_DIR}/src/rnn.c
    ${CMAKE_CURRENT_LIST_DIR}/src/rnn_data.c
)

target_sources(rnnoise PRIVATE ${RNNoise_SRC_FILES})
#add_executable(rnnoise_example ${RNNoise_SRC_FILES})

# Link Math library:
target_link_libraries(rnnoise PUBLIC 
    zephyr_interface 
    m
)

#target_compile_options(rnnoise PRIVATE -DTRAINING=0 -Wall -W -O3 -g -Wno-double-promotion)
target_compile_options(rnnoise PRIVATE -DTRAINING=0 -W -O3 -g -Wno-double-promotion)



