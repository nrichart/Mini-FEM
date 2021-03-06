#  Copyright 2014 - UVSQ, Dassault Aviation
#  Authors list: Loïc Thébault, Eric Petit
#
#  This file is part of Mini-FEM.
#
#  Mini-FEM is free software: you can redistribute it and/or modify it under the terms
#  of the GNU Lesser General Public License as published by the Free Software
#  Foundation, either version 3 of the License, or (at your option) any later version.
#
#  Mini-FEM is distributed in the hope that it will be useful, but WITHOUT ANY
#  WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
#  PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
#
#  You should have received a copy of the GNU Lesser General Public License along with
#  Mini-FEM. If not, see <http://www.gnu.org/licenses/>.

cmake_minimum_required (VERSION 2.8.10)

# Compilers
set (EXECUTABLE_OUTPUT_PATH ../bin)
set (CMAKE_Fortran_COMPILER ifort)
set (CMAKE_CXX_COMPILER icpc)
set (CMAKE_C_COMPILER icc)

# Project
project (Mini-FEM)
enable_language (Fortran)

# Flags
set (flags "-O2 -mkl:sequential -DDATA_PATH=\\\"${DATA_PATH}\\\"")
add_definitions (-D${DISTRI} -D${SHARED})
if (${BULK})
    add_definitions (-DBULK_SYNCHRONOUS)
else (${BULK})
    add_definitions (-DMULTITHREADED_COMM)
endif (${BULK})
if (${VECTO})
    add_definitions (-DDC_VEC)
else (${VECTO})
    add_definitions (-D${VERSION})
endif (${VECTO})
if (${ARCHI} STREQUAL "SSE")
    set (flags "${flags} -msse")
    add_definitions (-DVEC_SIZE=2)
elseif (${ARCHI} STREQUAL "AVX")
    set (flags "${flags} -mavx")
    add_definitions (-DVEC_SIZE=4)
elseif (${ARCHI} STREQUAL "MIC")
    set (flags "${flags} -mmic")
    add_definitions (-DVEC_SIZE=8)
endif (${ARCHI} STREQUAL "SSE")
if (${TREE})
    add_definitions (-DTREE_CREATION)
endif (${TREE})
if (${DEBUG})
    set (flags "${flags} -g -O0")
endif (${DEBUG})
if (${VERBOSE})
    set (CMAKE_VERBOSE_MAKEFILE 1)
    if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER 15.0)
        set (flags "${flags} -qopt-report-phase=vec")
    endif()
endif (${VERBOSE})
if (${OPTIMIZED})
	add_definitions (-DOPTIMIZED)
endif (${OPTIMIZED})
if (${MATT})
	set (flags "${flags} -finstrument-functions")
endif (${MATT})
if (${PAPI})
	add_definitions (-DPAPI)
	set (lflags "${lflags} -lpapi")
endif (${PAPI})
if (${VTUNE})
	add_definitions (-DVTUNE)
endif (${VTUNE})
if (${CILKVIEW})
	add_definitions (-DCILKVIEW)
endif (${CILKVIEW})
if (${DISTRI} STREQUAL "XMPI")
    find_package (MPI)
elseif (${DISTRI} STREQUAL "GASPI")
    set (lflags "${lflags} -libverbs")
endif (${DISTRI} STREQUAL "XMPI")
if (${SHARED} STREQUAL "CILK")
	set (lflags "${lflags} -lcilkrts")
elseif (${SHARED} STREQUAL "OMP")
    set (flags "${flags} -openmp")
endif (${SHARED} STREQUAL "CILK")
set (CMAKE_CXX_FLAGS "${flags} -std=c++11")
set (CMAKE_Fortran_FLAGS "${flags} -fpp -convert big_endian")
set (CMAKE_EXE_LINKER_FLAGS "${lflags} -nofor-main -lstdc++")

# Headers
include_directories (../src/headers)
include_directories (${DC_INCLUDE})
if (${DISTRI} STREQUAL "XMPI")
    include_directories (${MPI_INCLUDE_PATH})
elseif (${DISTRI} STREQUAL "GASPI")
    include_directories (${GASPI_INCLUDE})
endif (${DISTRI} STREQUAL "XMPI")
if (${VTUNE})
    include_directories (${VTUNE_INCLUDE})
endif (${VTUNE})
if (${CILKVIEW})
    include_directories (${CILKVIEW_INCLUDE})
endif (${CILKVIEW})

# Sources
file (GLOB_RECURSE source_list ../src/*)

# Executable
set (exec miniFEM_${VERSION})
if (${BULK})
    set (exec ${exec}_BulkSynchronous)
else (${BULK})
    set (exec ${exec}_MultithreadedComm)
endif (${BULK})
if (${VECTO})
    set (exec ${exec}_VEC_${ARCHI})
elseif (${ARCHI} STREQUAL "MIC")
	set (exec ${exec}_${ARCHI})
endif (${VECTO})
if (${TREE})
    set (exec ${exec}_TreeCreation)
endif (${TREE})
if (${DEBUG})
    set (exec ${exec}_Debug)
endif (${DEBUG})
if (${OPTIMIZED})
    set (exec ${exec}_Opti)
endif (${OPTIMIZED})
if (${MATT})
    set (exec ${exec}_MATT)
endif (${MATT})
if (${PAPI})
    set (exec ${exec}_PAPI)
endif (${PAPI})
if (${VTUNE})
    set (exec ${exec}_VTune)
endif (${VTUNE})
if (${CILKVIEW})
    set (exec ${exec}_CilkView)
endif (${CILKVIEW})
set (exec ${exec}_${DISTRI}_${SHARED})
add_executable (
    ${exec}
    ${source_list}
)

# Link
set_property (TARGET ${exec} PROPERTY LINKER_LANGUAGE Fortran)
target_link_libraries (
    ${exec}
    ${DC_LIBRARIES}
)
if (${DISTRI} STREQUAL "XMPI")
    target_link_libraries (
        ${exec}
        ${MPI_LIBRARIES}
    )
elseif (${DISTRI} STREQUAL "GASPI")
    target_link_libraries (
        ${exec}
        ${GASPI_LIBRARIES}
    )
endif (${DISTRI} STREQUAL "XMPI")
if (${TREE})
    target_link_libraries (
        ${exec}
        ${METIS_LIBRARIES}
    )
endif (${TREE})
if (${VTUNE})
    target_link_libraries (
        ${exec}
        ${VTUNE_LIBRARIES}
    )
endif (${VTUNE})
