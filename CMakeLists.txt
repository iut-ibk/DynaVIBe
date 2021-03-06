CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(dynavibe)

FIND_PATH(DYNAMINDDEV DynaMindDevCmake.txt
	    PATHS   $ENV{DYNAMIND_DIR}/include
	    PATH_SUFFIXES dynamindcore/CMake)

IF(DYNAMIND_INCLUDE_DIR)
	MESSAGE(STATUS "Compiled from toolbox")
	MESSAGE(STATUS "DYNAMIND_INCLUDE_DIR ${DYNAMIND_INCLUDE_DIR}")
	SET (DYNAMIND_CORE_LIBRARY dynamindcore)
	SET (DYNAMIND_TOOLBOX_LIBRARY dynamindtoolbox)
        SET (DYNAMIND_EXTENSIONS_LIBRARY dynamind-extensions)
	MESSAGE(STATUS "${DYNAMIND_CORE_LIBRARY}")
ELSE()
	MESSAGE(STATUS "Compiled from stand alone")
	FIND_PATH(DYNAMINDDEV DynaMindDevCmake.txt
	PATHS $ENV{DYNAMIND_DIR}/include
	PATH_SUFFIXES dynamindcore/CMake)

	IF(DYNAMINDDEV)
		INCLUDE(${DYNAMINDDEV}/DynaMindDevCmake.txt)
	ELSE()
		MESSAGE(FATAL_ERROR "Could not find dynamind. Maybe not installed ?")
	ENDIF()

ENDIF()

INCLUDE_DIRECTORIES( ${DYNAMIND_INCLUDE_DIR})

IF(CMAKE_BUILD_TYPE STREQUAL Debug)
	MESSAGE(STATUS "Build Type = Debug")
	ADD_DEFINITIONS(-DDEBUG)
ELSE()
	MESSAGE(STATUS "Build Type = Release")
ENDIF()

IF(DYNAMIND_TOOLBOX_BUILD_DIR)
    SET(LIBRARY_OUTPUT_PATH ${DYNAMIND_TOOLBOX_BUILD_DIR}/Modules)
    SET(EXECUTABLE_OUTPUT_PATH ${DYNAMIND_TOOLBOX_BUILD_DIR}/Modules)
    SET(SCRIPT_PATH ${DYNAMIND_TOOLBOX_BUILD_DIR}/PythonModules )
ELSE()
    SET(LIBRARY_OUTPUT_PATH ${dynamind-sewer_BINARY_DIR})
    SET(EXECUTABLE_OUTPUT_PATH ${dynamind-sewer_BINARY_DIR})
    SET(SCRIPT_PATH ${dynamind-sewer_BINARY_DIR}/PythonModules )
ENDIF()

SET(Boost_USE_STATIC_LIBS        OFF)
SET(Boost_USE_MULTITHREADED      ON)
FIND_PACKAGE(Boost COMPONENTS graph system thread REQUIRED)

IF(Boost_FOUND)
    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS})
ENDIF()

IF(USEQT5)
    MESSAGE(STATUS "Using Qt5 for DynaVIBe")
    FIND_PACKAGE(Qt5Core)
    FIND_PACKAGE(Qt5Gui)
    FIND_PACKAGE(Qt5Widgets)
    INCLUDE_DIRECTORIES(${Qt5Core_INCLUDE_DIRS})
    INCLUDE_DIRECTORIES(${Qt5Gui_INCLUDE_DIRS})
    INCLUDE_DIRECTORIES(${Qt5Widgets_INCLUDE_DIRS})
ELSE()
    MESSAGE(STATUS "Using Qt4 for DynaVIBe")
    FIND_PACKAGE(Qt4 COMPONENTS QtCore QtGui REQUIRED)
    #ADD_DEFINITIONS(-DQT_NO_KEYWORDS)
    INCLUDE(${QT_USE_FILE})
ENDIF()

SET(CGAL_DONT_OVERRIDE_CMAKE_FLAGS "ON" CACHE BOOL "")
FIND_PACKAGE(CGAL QUIET COMPONENTS Core REQUIRED)

INCLUDE(${CGAL_USE_FILE})
INCLUDE_DIRECTORIES(${DYNAMIND_EXTENSIONS_INCLUDE_DIR})

FIND_PACKAGE(OpenMP)

IF(OPENMP_FOUND)
    SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
ENDIF()

#INCLUDE_DIRECTORIES(epanet/src)
#INCLUDE_DIRECTORIES(swmm/src)

ADD_SUBDIRECTORY(epanet)
ADD_SUBDIRECTORY(swmm)
ADD_SUBDIRECTORY(src)
MESSAGE(STATUS ${Boost_LIBRARIES})
