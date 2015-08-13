# Find Gracenote SDK Path

FIND_PATH(GRACENOTESDK_INCLUDE_DIR NAMES gnsdk.h
  PATHS
    /usr/local/include
    /usr/X11/include
    /usr/include
  HINTS
    $ENV{GRACENOTESDK_ROOT}
)

if (APPLE)
  set (LIB_HINT $ENV{GRACENOTESDK_ROOT}/lib/mac_x86-64)
elseif (UNIX)
  if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
    set (LIB_HINT $ENV{GRACENOTESDK_ROOT}/lib/linux_x86-64)
  else()
    set (LIB_HINT $ENV{GRACENOTESDK_ROOT}/lib/linux_x86-32)
  endif()
elseif (WIN32)
  if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
    set (LIB_HINT $ENV{GRACENOTESDK_ROOT}/lib/win_x86-64)
  else()
    set (LIB_HINT $ENV{GRACENOTESDK_ROOT}/lib/win_x86-32)
  endif()
else()
  message (FATAL_ERROR "platform is not supported")
endif()  

FIND_LIBRARY(GRACENOTESDK_LIBRARY NAMES fontconfig ${FONTCONFIG_PKG_LIBRARY}
  PATHS
    /usr/local
    /usr/X11
    /usr
  HINTS
    LIB_HINT
    
  PATH_SUFFIXES
    lib64
    lib64
)

include(FindPackageHandleStandardArgs)
set(GRACENOTE_FAILURE_MSG "WARNING: Gracenote SDK not found. Build cannot continue")
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GracenoteSDK ${GRACENOTE_FAILURE_MSG} GRACENOTESDK_LIBRARY GRACENOTESDK_INCLUDE_DIR )