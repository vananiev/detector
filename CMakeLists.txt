#
cmake_minimum_required(VERSION 2.6)

cmake_policy (SET CMP0011 NEW)
cmake_policy (SET CMP0003 OLD)

OPTION (WITH_DEBUG_MODE "Build with debug mode" ON)

if (NOT UNIX)
	message (FATAL_ERROR "Not Unix!")
endif()
message ("Starting cmake")

# я вынес настройки путей, флаги компиляции в отдельный фаил, чтобы не громоздить здесь лишнего
include (cmake.conf)

# создаём новый проект
set (PROJECT detector)

# в текущем проекте ничего не нужно дополнительно компилировать
set (LIBRARIES)
# следующий код нужен для компиляции и подключения сторонних библиотек 
    foreach (LIBRARY ${LIBRARIES})
        find_library("${LIBRARY}_FOUND" ${LIBRARY})
        message(STATUS "Check the ${LIBRARY} is installed: " ${${LIBRARY}_FOUND})
        if ( "${${LIBRARY}_FOUND}" STREQUAL "${LIBRARY}_FOUND-NOTFOUND" )
            message(STATUS "Adding library sources")
            add_subdirectory (../${LIBRARY} lib/${LIBRARY})
        endif ()
    endforeach ()

# никаких дополнительных целей нет
set (TARGETS "")

set (HEADERS "")

message ( STATUS "SOURCES: ${SOURCES}")

include_directories(include)
add_subdirectory (src)


