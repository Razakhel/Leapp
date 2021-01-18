###############################
# Finding the Leap Motion SDK #
###############################

if (WIN32 OR CYGWIN)
    # If a directory is manually specified, use it to search for the needed files; otherwise, an attempt to find it is made
    if (LEAPSDK_ROOT)
        set(LEAPSDK_SEARCH_PATHS ${LEAPSDK_ROOT})
    else ()
        if (WIN32)
            file(
                GLOB
                LEAPSDK_SEARCH_PATHS

                "C:/Leap*"
                "D:/Leap*"
                "E:/Leap*"
                "C:/Lib*/Leap*"
                "D:/Lib*/Leap*"
                "E:/Lib*/Leap*"
            )
        elseif (CYGWIN)
            file(
                GLOB
                LEAPSDK_SEARCH_PATHS

                "/cygdrive/c/Leap*"
                "/cygdrive/d/Leap*"
                "/cygdrive/e/Leap*"
                "/cygdrive/c/Lib*/Leap*"
                "/cygdrive/d/Lib*/Leap*"
                "/cygdrive/e/Lib*/Leap*"
            )
        endif ()
    endif ()

    find_library(
        LEAPSDK_LIBS

        NAMES
            LeapC
        HINTS
            ENV LEAPSDKDIR
            ENV LEAPSDK_PATH
        PATH_SUFFIXES
            lib lib/x64
        PATHS
            ${LEAPSDK_SEARCH_PATHS}
        REQUIRED
        NO_DEFAULT_PATH
    )

    if (WIN32)
        # Under Windows, finding the DLL may be useful in some cases
        find_file(
            LEAPSDK_DLL

            NAMES
                LeapC.dll
            HINTS
                ENV LEAPSDKDIR
                ENV LEAPSDK_PATH
            PATH_SUFFIXES
                lib lib/x64
            PATHS
                ${LEAPSDK_SEARCH_PATHS}
        )
    endif ()
elseif (APPLE)
    set(LEAPSDK_LIBS "-framework LeapSDK")

    file(
        GLOB
        LEAPSDK_SEARCH_PATHS

        "/System/Library/Frameworks/leap*"
        "~/Library/Frameworks/leap*"
        "/Library/Frameworks/leap*"
        "/opt/leap*"
        "/usr/local/opt/leap*"
    )
else () # Linux
    set(LEAPSDK_LIBS openal)

    file(
        GLOB
        LEAPSDK_SEARCH_PATHS

        "/usr/include"
        "/usr/local/include"
        "~/Leap*"
    )
endif ()

find_path(
    LEAPSDK_INCLUDE_DIRS

    NAMES
        LeapC.h
    HINTS
        ENV LEAPSDKDIR
        ENV LEAPSDK_SDK_PATH
    PATH_SUFFIXES
        include
    PATHS
        ${LEAPSDK_SEARCH_PATHS}
    REQUIRED
)

if (LEAPSDK_INCLUDE_DIRS AND LEAPSDK_LIBS)
    set(LeapSDK_FOUND ON)
    message("[LeapSDK] Found:")
else ()
    message("[LeapSDK] NOT found:")
endif ()

message("  - Include directory: ${LEAPSDK_INCLUDE_DIRS}")
message("  - Library: ${LEAPSDK_LIBS}")
if (WIN32)
    message("  - DLL: ${LEAPSDK_DLL}")
endif ()
