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
    src/Leapp/*.cpp

    include/*.hpp
    include/*.inl
    include/Leapp/*.hpp
    include/Leapp/*.inl
)

# Adding every file to be compiled
file(
    GLOB
    LEAPP_FILES

    ${LEAPP_SRC}
)

###################
# Leapp - LeapSDK #
###################

find_package(LeapSDK REQUIRED)

target_include_directories(Leapp SYSTEM PUBLIC ${LEAPSDK_INCLUDE_DIRS})
target_link_libraries(Leapp PUBLIC ${LEAPSDK_LIBS})

#################
# Leapp - Build #
#################

target_include_directories(Leapp PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_sources(Leapp PRIVATE ${LEAPP_FILES})

# Build the examples
option(LEAPP_BUILD_EXAMPLES "Build examples" ON)
if (LEAPP_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()

# Allows to generate the documentation
find_package(Doxygen)
option(LEAPP_GEN_DOC "Generate documentation (requires Doxygen)" ${DOXYGEN_FOUND})
if (LEAPP_GEN_DOC)
    add_subdirectory(doc)
endif ()

########################
# Leapp - Installation #
########################

if (WIN32)
    set(CMAKE_INSTALL_PREFIX "C:/Leapp") # The default install prefix is "C:/Program Files (x86)/Leapp"
endif ()

install(TARGETS Leapp DESTINATION "lib/$<CONFIG>")

# Installing header files
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include/Leapp" DESTINATION include)
