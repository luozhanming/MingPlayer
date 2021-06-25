cmake_minimum_required(VERSION 3.4.2)

set(INCLUDES ${CMAKE_SOURCE_DIR}/src/main/jni/include)

include_directories(${INCLUDES})


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -L${CMAKE_SOURCE_DIR}/libs/${CMAKE_ANDROID_ARCH_ABI}") # ffmpeg库指定


file(GLOB_RECURSE
        srcFiles
        ${CMAKE_SOURCE_DIR}/src/main/jni/*.cpp
        ${CMAKE_SOURCE_DIR}/src/main/jni/*.c)


find_library(
        ffmpeg
        ijkffmpeg
)

add_library(
        native-lib
        SHARED
        ${srcFiles}
)


target_link_libraries(
        native-lib
        ffmpeg
        log
        android
)