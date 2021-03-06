# - Try to find FFTW
# Once done this will define
#  FFTW_FOUND - System has FFTW
#  FFTW_INCLUDE_DIRS - The FFTW include directories
#  FFTW_LIBRARIES - The libraries needed to use FFTW
#  FFTW_DEFINITIONS - Compiler switches required for using FFTW

find_package(PkgConfig)
pkg_check_modules(PC_FFTW QUIET fftw3)
set(FFTW_DEFINITIONS ${PC_FFTW_CFLAGS_OTHER})

find_path(FFTW_INCLUDE_DIR fftw3.h
        HINTS ${PC_FFTW_INCLUDEDIR} ${PC_FFTW_INCLUDE_DIRS}
        PATH_SUFFIXES FFTW )

find_library(FFTW_LIBRARY NAMES fftw3 FFTW
        HINTS ${PC_FFTW_LIBDIR} ${PC_FFTW_LIBRARY_DIRS} )

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set FFTW_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(FFTW  DEFAULT_MSG
        FFTW_LIBRARY FFTW_INCLUDE_DIR)

mark_as_advanced(FFTW_INCLUDE_DIR FFTW_LIBRARY )

set(FFTW_LIBRARIES ${FFTW_LIBRARY} )
set(FFTW_INCLUDE_DIRS ${FFTW_INCLUDE_DIR} )