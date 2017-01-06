# - Try to find LIBUSB
# Once done this will define
#  LIBUSB_FOUND - System has LIBUSB
#  LIBUSB_INCLUDE_DIRS - The LIBUSB include directories
#  LIBUSB_LIBRARIES - The libraries needed to use LIBUSB
#  LIBUSB_DEFINITIONS - Compiler switches required for using LIBUSB

find_package(PkgConfig)
pkg_check_modules(PC_LIBUSB QUIET libusb)
set(LIBUSB_DEFINITIONS ${PC_LIBUSB_CFLAGS_OTHER})

find_path(LIBUSB_INCLUDE_DIR usb.h
        HINTS ${PC_LIBUSB_INCLUDEDIR} ${PC_LIBUSB_INCLUDE_DIRS}
        PATH_SUFFIXES LIBUSB )

find_library(LIBUSB_LIBRARY NAMES usb LIBUSB
        HINTS ${PC_LIBUSB_LIBDIR} ${PC_LIBUSB_LIBRARY_DIRS} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set LIBUSB_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(LIBUSB  DEFAULT_MSG
        LIBUSB_LIBRARY LIBUSB_INCLUDE_DIR)

mark_as_advanced(LIBUSB_INCLUDE_DIR LIBUSB_LIBRARY )

set(LIBUSB_LIBRARIES ${LIBUSB_LIBRARY} )
set(LIBUSB_INCLUDE_DIRS ${LIBUSB_INCLUDE_DIR} )