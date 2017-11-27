
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

# configuration
set(PLUGIN       "rcmc")       # plugin name
set(NAMESPACE    "")        # namespace
set(SOURCES      "rcmc.cpp")    # sources of the plugin

# script
project(${PLUGIN})

# look for OTAWA
if(NOT OTAWA_CONFIG)
    find_program(OTAWA_CONFIG otawa-config DOC "path to otawa-config")
    if(NOT OTAWA_CONFIG)
        message(FATAL_ERROR "ERROR: otawa-config is required !")
    endif()
endif()
message(STATUS "otawa-config found at ${OTAWA_CONFIG}")
execute_process(COMMAND "${OTAWA_CONFIG}" --cflags                  OUTPUT_VARIABLE OTAWA_CFLAGS  OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND "${OTAWA_CONFIG}" --libs -p ${PLUGIN} -r    OUTPUT_VARIABLE OTAWA_LDFLAGS OUTPUT_STRIP_TRAILING_WHITESPACE)
execute_process(COMMAND "${OTAWA_CONFIG}" --prefix                  OUTPUT_VARIABLE OTAWA_PREFIX  OUTPUT_STRIP_TRAILING_WHITESPACE)
set(CMAKE_CXX_STANDARD 11)

# C++ flags
add_compile_options("-Wall")
if(CMAKE_VERSION LESS "3.1")
    add_compile_options(--std=c++11)
    message(STATUS "C++11 set using cflags")
else()
    set(CMAKE_CXX_STANDARD 11)
    message(STATUS "C++ set using CMAKE_CXX_STANDARD")
endif()

# plugin definition
include_directories("${CMAKE_SOURCE_DIR}" ".")
add_library("${PLUGIN}" SHARED ${SOURCES})
set_property(TARGET "${PLUGIN}" PROPERTY PREFIX "")
set_property(TARGET "${PLUGIN}" PROPERTY COMPILE_FLAGS "${OTAWA_CFLAGS}")
target_link_libraries(${PLUGIN} "${OTAWA_LDFLAGS}")

# installation
set(PLUGIN_PATH "${OTAWA_PREFIX}/lib/otawa/${NAMESPACE}")
install(TARGETS ${PLUGIN} LIBRARY DESTINATION ${PLUGIN_PATH})
install(FILES ${PLUGIN}.eld DESTINATION ${PLUGIN_PATH})
install(FILES rcmc.osx DESTINATION ${OTAWA_PREFIX}/share/Otawa/scripts)
