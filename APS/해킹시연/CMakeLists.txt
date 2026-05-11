cmake_minimum_required(VERSION 3.16)
project(gomoku CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 외부 라이브러리 없음 - Win32 GDI만 사용
add_executable(gomoku WIN32 src/main.cpp)

target_link_libraries(gomoku PRIVATE gdi32 user32 kernel32)

target_link_options(gomoku PRIVATE
    -static-libgcc
    -static-libstdc++
    -Wl,-Bstatic,-lwinpthread,-Bdynamic
)

set_target_properties(gomoku PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

target_link_options(gomoku PRIVATE "-mwindows")
target_link_options(gomoku PRIVATE "-static" "-static-libgcc" "-static-libstdc++" "-Wl,-Bstatic" "-lstdc++" "-lpthread" "-Wl,-Bdynamic")