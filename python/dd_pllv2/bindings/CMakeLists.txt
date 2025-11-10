# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Check if there is C++ code at all
########################################################################
if(NOT dd_pllv2_sources)
    message(STATUS "No C++ sources... skipping python bindings")
    return()
endif(NOT dd_pllv2_sources)

########################################################################
# Check for pygccxml
########################################################################
gr_python_check_module_raw("pygccxml" "import pygccxml" PYGCCXML_FOUND)

include(GrPybind)
include_directories(${CMAKE_SOURCE_DIR}/include/gnuradio)

########################################################################
# Python Bindings
########################################################################

list(APPEND dd_pllv2_python_files
    dd_pll_python.cc python_bindings.cc)

gr_pybind_make_oot(dd_pllv2 ../../.. gr::dd_pllv2 "${dd_pllv2_python_files}")

# copy bindings extension for use in QA test module
add_custom_command(
    TARGET dd_pllv2_python
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:dd_pllv2_python>
            ${PROJECT_BINARY_DIR}/test_modules/gnuradio/dd_pllv2/)

install(
    TARGETS dd_pllv2_python
    DESTINATION ${GR_PYTHON_DIR}/gnuradio/dd_pllv2
    COMPONENT pythonapi)
