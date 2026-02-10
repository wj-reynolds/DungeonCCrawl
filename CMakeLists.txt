cmake_minimum_required(VERSION 4.1)
project(Crawl C)

set(CMAKE_C_STANDARD 23)

add_subdirectory("${PROJECT_SOURCE_DIR}/lib/glfw")

add_executable(Crawl    src/main.c
                        src/logger/logger.c
        lib/glad/gl.c
        src/core/window.c
        include/core/window.h
        include/global.h
        src/global.c
        src/crawl.c
        include/crawl.h
        src/io/input.c
        include/io/input.h
        src/graphics/render.c
        include/graphics/render.h
        src/graphics/image.c
        include/graphics/image.h
        src/graphics/mesh.c
        include/graphics/mesh.h
        src/graphics/shader.c
        include/graphics/shader.h
        src/io/fileio.c
        include/io/fileio.h
)


target_compile_options(Crawl PRIVATE -Wall -Wextra -Wfloat-equal -Wformat=2)

target_include_directories(Crawl PRIVATE    "${PROJECT_SOURCE_DIR}/include/"
                                            "${PROJECT_SOURCE_DIR}/lib/stb_image/"
)

link_directories(Crawl "${CMAKE_SOURCE_DIR}/lib/stb_image/")

target_link_libraries(Crawl glfw)
