project(Leapp_Examples)

# Defining an interface library to hold common settings for all examples
add_library(Leapp_Examples INTERFACE)
target_compile_features(Leapp_Examples INTERFACE cxx_std_17)
target_link_libraries(Leapp_Examples INTERFACE Leapp)

include(CompilerFlags)
add_compiler_flags(Leapp_Examples INTERFACE)

# Disabling some warnings, which are intentionally present
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(
        LEAPP_EXAMPLES_DISABLED_WARNINGS

        -Wno-unused-variable
    )
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(
        LEAPP_EXAMPLES_DISABLED_WARNINGS

        -Wno-header-hygiene
        -Wno-unused-variable
    )
elseif (MSVC)
    set(
        LEAPP_EXAMPLES_DISABLED_WARNINGS

        # Warnings triggered by MSVC's standard library
        /wd4189 # Local variable is initalized but not referenced (unused variable)
        /wd5220 # Non-static volatile member doesn't imply non-trivial move/copy ctor/operator=
    )
endif ()

target_compile_options(Leapp_Examples INTERFACE ${LEAPP_EXAMPLES_DISABLED_WARNINGS})

add_executable(Leapp_MinDemo minDemo.cpp)
target_link_libraries(Leapp_MinDemo Leapp_Examples)

if (WIN32)
    if (NOT MSVC)
        file(COPY "${LEAPSDK_DLL}" DESTINATION "${CMAKE_BINARY_DIR}/examples")
    else ()
        # MSVC uses the config mode at build time; the copy must be performed at that time

        set(LEAPSDK_DLL_DEST "${CMAKE_BINARY_DIR}/examples")

        # When using Visual Studio, the binary directory doesn't include the config mode; it must be appended
        if (CMAKE_GENERATOR MATCHES "Visual Studio*")
            set(LEAPSDK_DLL_DEST "${LEAPSDK_DLL_DEST}/$<CONFIG>")
        endif ()

        set(${DLL_COPY_COMMAND} ${CMAKE_COMMAND} -E copy "${LEAPSDK_DLL}" "${LEAPSDK_DLL_DEST}")

        add_custom_command(TARGET Leapp_MinDemo PRE_LINK COMMAND ${DLL_COPY_COMMAND})
    endif ()
endif ()
