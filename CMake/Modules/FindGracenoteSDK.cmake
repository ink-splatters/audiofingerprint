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
  if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
    set (GRACENOTESDK_LIB_DIR ${GRACENOTESDK_ROOT}/lib/linux_x86-64)
    set (GRACENOTESDK_PLATFORM_INCLUDE_DIR ${GRACENOTESDK_ROOT}/include/linux_x86-64)
  else()
    set (GRACENOTESDK_LIB_DIR ${GRACENOTESDK_ROOT}/lib/linux_x86-32)
    set (GRACENOTESDK_PLATFORM_INCLUDE_DIR ${GRACENOTESDK_ROOT}/include/linux_x86-32)
  endif()
else()
  message (FATAL_ERROR "platform is not supported")
endif()  

file (STRINGS ${GRACENOTESDK_ROOT}/version GRACENOTESDK_VER)
string(REGEX MATCH ".\[0-9]+\\.[0-9]+.[0-9]+" GRACENOTESDK_VER ${GRACENOTESDK_VER})

find_library(
    GRACENOTESDK_LIBRARY
    NAMES 
      gnsdk_manager.${GRACENOTESDK_VER}
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
      -lgnsdk_manager
      -lgnsdk_link
      -lgnsdk_lookup_local
      -lgnsdk_lookup_localstream
      -lgnsdk_dsp
      -lgnsdk_manager
      -lgnsdk_moodgrid
      -lgnsdk_musicid
      -lgnsdk_musicid_file
      -lgnsdk_musicid_stream
      -lgnsdk_playlist
      -lgnsdk_storage_sqlite
      -lgnsdk_video
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