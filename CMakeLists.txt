cmake_minimum_required(VERSION 3.7)

project(BIBLIOENSIAS)

find_package(PkgConfig)

pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_INCLUDE_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

set(SRC_DIR .)
set(HEADERS_FOLDER headers)


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lm -O0 -Wall -Werror -fdump-rtl-expand")

include_directories(${SRC_DIR}/pages/book_page)
include_directories(${SRC_DIR}/pages/main_page)

set(SRCS
    ${SRC_DIR}/main.c
    ${SRC_DIR}/pages/book_page/book.c
    ${SRC_DIR}/pages/main_page/acceuil.c
)

add_executable(BIBLIOENSIAS ${SRCS})
target_link_libraries(BIBLIOENSIAS ${GTK3_LIBRARIES} m)
