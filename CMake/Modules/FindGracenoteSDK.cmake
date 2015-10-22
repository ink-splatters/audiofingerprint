# Find Gracenote SDK Path

string(REPLACE "\"" "" GRACENOTESDK_ROOT_WITHOUT_QUOTES $ENV{GRACENOTESDK_ROOT})

find_path(GRACENOTESDK_INCLUDE_DIR NAMES gnsdk.h
  PATHS
    /usr/local/include
    /usr/X11/include
    /usr/include
  HINTS
    ${GRACENOTESDK_ROOT_WITHOUT_QUOTES}/include
)

message (${GRACENOTESDK_INCLUDE_DIR})

if (APPLE)
  set (GRACENOTESDK_LIB_DIR ${GRACENOTESDK_ROOT_WITHOUT_QUOTES}/lib/mac_x86-64)
  set (GRACENOTESDK_PLATFORM_INCLUDE_DIR ${GRACENOTESDK_ROOT_WITHOUT_QUOTES}/include/mac_x86-64)
elseif (UNIX)
  if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
    set (GRACENOTESDK_LIB_DIR ${GRACENOTESDK_ROOT_WITHOUT_QUOTES}/lib/linux_x86-64)
    set (GRACENOTESDK_PLATFORM_INCLUDE_DIR ${GRACENOTESDK_ROOT_WITHOUT_QUOTES}/include/linux_x86)
  else()
    set (GRACENOTESDK_LIB_DIR ${GRACENOTESDK_ROOT_WITHOUT_QUOTES}/lib/linux_x86-32)
    set (GRACENOTESDK_PLATFORM_INCLUDE_DIR ${GRACENOTESDK_ROOT_WITHOUT_QUOTES}/include/linux_x86-32)
  endif()
elseif (WIN32)
  if("${CMAKE_SIZEOF_VOID_P}" EQUAL "8")
    set (GRACENOTESDK_LIB_DIR ${GRACENOTESDK_ROOT_WITHOUT_QUOTES}/lib/win_x86-64)
    set (GRACENOTESDK_PLATFORM_INCLUDE_DIR ${GRACENOTESDK_ROOT_WITHOUT_QUOTES}/include/win_x86-64)
  else()
    set (GRACENOTESDK_LIB_DIR ${GRACENOTESDK_ROOT_WITHOUT_QUOTES}/lib/win_x86-32)
    set (GRACENOTESDK_PLATFORM_INCLUDE_DIR ${GRACENOTESDK_ROOT_WITHOUT_QUOTES}/include/win_x86-32)
  endif()
else()
  message (FATAL_ERROR "platform is not supported")
endif()  

file (STRINGS ${GRACENOTESDK_ROOT_WITHOUT_QUOTES}/version GRACENOTESDK_VER)
string(REGEX MATCH "[0-9]+\\.[0-9]+.[0-9]+" GRACENOTESDK_VER ${GRACENOTESDK_VER})

message ("!!!lib dir ${GRACENOTESDK_LIB_DIR}")
message ("!!! suffixes: ${PATH_SUFFIXES}")
message ("!!! version: ${GRACENOTESDK_VER}")
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
      gnsdk_manager.${GRACENOTESDK_VER}
      gnsdk_link.${GRACENOTESDK_VER}
      gnsdk_lookup_local.${GRACENOTESDK_VER}
      gnsdk_lookup_localstream.${GRACENOTESDK_VER}
      gnsdk_dsp.${GRACENOTESDK_VER}
      gnsdk_manager.${GRACENOTESDK_VER}
      gnsdk_moodgrid.${GRACENOTESDK_VER}
      gnsdk_musicid.${GRACENOTESDK_VER}
      gnsdk_musicid_file.${GRACENOTESDK_VER}
      gnsdk_musicid_stream.${GRACENOTESDK_VER}
      gnsdk_playlist.${GRACENOTESDK_VER}
      gnsdk_storage_sqlite.${GRACENOTESDK_VER}
      gnsdk_video.${GRACENOTESDK_VER}
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