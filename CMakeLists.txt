cmake_minimum_required(VERSION 3.11)
project(Leapp)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# If the build type hasn't been specified, defaulting it to Release
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif ()

###################
# Leapp - Library #
###################

option(LEAPP_BUILD_STATIC "Build Leapp statically" ON)
if (LEAPP_BUILD_STATIC)
    add_library(Leapp STATIC)
else ()
    add_library(Leapp SHARED)
endif ()

# Using C++17
target_compile_features(Leapp PRIVATE cxx_std_17)

##########################
# Leapp - Compiler flags #
##########################

include(CompilerFlags)
add_compiler_flags(Leapp PRIVATE)

########################
# Leapp - Source files #
########################

set(
    LEAPP_SRC

    src/*.cpp

    include/*.hpp
    include/*.inl
)

# Adding every file to be compiled
file(
    GLOB
    LEAPP_FILES

    ${LEAPP_SRC}
)

#################
# Leapp - Build #
#################

target_include_directories(Leapp PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_sources(Leapp PRIVATE ${LEAPP_FILES})

########################
# Leapp - Installation #
########################

if (WIN32)
    set(CMAKE_INSTALL_PREFIX "C:/Leapp") # The default install prefix is "C:/Program Files (x86)/Leapp"
endif ()

install(TARGETS Leapp DESTINATION "lib/$<CONFIG>")

# Installing header files
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/Leapp" DESTINATION include)
