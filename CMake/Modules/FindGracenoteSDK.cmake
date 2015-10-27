# Find Gracenote SDK Path

string(REPLACE "\"" "" GRACENOTESDK_ROOT $ENV{GRACENOTESDK_ROOT})

find_path(GRACENOTESDK_INCLUDE_DIR NAMES gnsdk.h
  PATHS
    /usr/local/include
    /usr/X11/include
    /usr/include
  HINTS
    ${GRACENOTESDK_ROOT}/include
)

message (${GRACENOTESDK_INCLUDE_DIR})

if (APPLE)
  set (LIB_SUFFIX ".dylib")
  set (LIB_PREFIX "lib")
  set (GRACENOTESDK_LIB_DIR ${GRACENOTESDK_ROOT}/lib/mac_x86-64)
  set (GRACENOTESDK_PLATFORM_INCLUDE_DIR ${GRACENOTESDK_ROOT}/include/mac_x86-64)
elseif (UNIX)
  set (LIB_SUFFIX ".so")
  set (LIB_PREFIX "lib")
  if ("${MYARCH}" STREQUAL "")
    if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
      set (GRACENOTESDK_LIB_DIR ${GRACENOTESDK_ROOT}/lib/linux_x86-64)
      set (GRACENOTESDK_PLATFORM_INCLUDE_DIR ${GRACENOTESDK_ROOT}/include/linux_x86-64)
    else()
      set (GRACENOTESDK_LIB_DIR ${GRACENOTESDK_ROOT}/lib/linux_x86-32)
      set (GRACENOTESDK_PLATFORM_INCLUDE_DIR ${GRACENOTESDK_ROOT}/include/linux_x86-32)
    endif()
  else()
    set (GRACENOTESDK_LIB_DIR ${GRACENOTESDK_ROOT}/lib/${MYARCH})
    set (GRACENOTESDK_PLATFORM_INCLUDE_DIR ${GRACENOTESDK_ROOT}/include/${MYARCH})
  endif()
else()
  message (FATAL_ERROR "platform is not supported")
endif()

file (STRINGS ${GRACENOTESDK_ROOT}/version GRACENOTESDK_VER)
#string(REGEX MATCH ".\[0-9]+\\.[0-9]+.[0-9]+" GRACENOTESDK_VER ${GRACENOTESDK_VER})

find_library(
    GRACENOTESDK_LIBRARY
    NAMES 
      gnsdk_manager
  PATHS
    /usr/local
    /usr/X11
    /usr
    ${GRACENOTESDK_LIB_DIR}
  HINTS
    ${GRACENOTESDK_LIB_DIR}
  PATH_SUFFIXES
    lib
    lib64
)

set (GRACENOTESDK_LIBRARIES 
      gnsdk_manager
      gnsdk_link
      gnsdk_lookup_local
      gnsdk_lookup_localstream
      gnsdk_dsp
      gnsdk_manager
      gnsdk_moodgrid
      gnsdk_musicid
      gnsdk_musicid_file
      gnsdk_musicid_stream
      gnsdk_playlist
      gnsdk_storage_sqlite
      gnsdk_video
)

include(FindPackageHandleStandardArgs)
set(GRACENOTE_FAILURE_MSG "Gracenote SDK not found. Build cannot continue")
FIND_PACKAGE_HANDLE_STANDARD_ARGS(
  GracenoteSDK 
  FAIL_MESSAGE GRACENOTE_FAILURE_MSG
  REQUIRED_VARS GRACENOTESDK_LIBRARY GRACENOTESDK_INCLUDE_DIR
  VERSION_VAR GRACENOTESDK_VER
)

mark_as_advanced(GRACENOTESDK_INCLUDE_DIR GRACENOTESDK_LIBRARY )