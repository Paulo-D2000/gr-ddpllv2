find_package(PkgConfig)

PKG_CHECK_MODULES(PC_GR_DD_PLLV2 gnuradio-dd_pllv2)

FIND_PATH(
    GR_DD_PLLV2_INCLUDE_DIRS
    NAMES gnuradio/dd_pllv2/api.h
    HINTS $ENV{DD_PLLV2_DIR}/include
        ${PC_DD_PLLV2_INCLUDEDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/include
          /usr/local/include
          /usr/include
)

FIND_LIBRARY(
    GR_DD_PLLV2_LIBRARIES
    NAMES gnuradio-dd_pllv2
    HINTS $ENV{DD_PLLV2_DIR}/lib
        ${PC_DD_PLLV2_LIBDIR}
    PATHS ${CMAKE_INSTALL_PREFIX}/lib
          ${CMAKE_INSTALL_PREFIX}/lib64
          /usr/local/lib
          /usr/local/lib64
          /usr/lib
          /usr/lib64
          )

include("${CMAKE_CURRENT_LIST_DIR}/gnuradio-dd_pllv2Target.cmake")

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(GR_DD_PLLV2 DEFAULT_MSG GR_DD_PLLV2_LIBRARIES GR_DD_PLLV2_INCLUDE_DIRS)
MARK_AS_ADVANCED(GR_DD_PLLV2_LIBRARIES GR_DD_PLLV2_INCLUDE_DIRS)
