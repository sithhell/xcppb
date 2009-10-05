CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

SET (CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS ON)
SET (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMakeModules)

PROJECT( xcppb )

IF ( CMAKE_COMPILER_IS_GNUCXX )
	ADD_DEFINITIONS ( "-pedantic-errors -Wall -Wextra"
							#"-Wconversion"
							#"-Wfloat-equal -Wredundant-decls -Wstrict-null-sentinel -Winit-self"
							"-Woverloaded-virtual -Wnon-virtual-dtor -Wctor-dtor-privacy"
							#"-Wsign-promo -Wstrict-aliasing=1 -Wmissing-declarations"
							#							"-Wold-style-cast"
							"-Wno-long-long -ansi" )

	IF( ENABLE_DEBUG_WARNINGS )
		SET ( CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG}" -Wpadded -Weffc++" )
	ENDIF()

	SET ( CMAKE_CXX_FLAGS_RELEASE "-O3 -fomit-frame-pointer -DNDEBUG" )

	SET (CMAKE_REQUIRED_FLAGS "-Wall -Werror -pedantic")

ENDIF( CMAKE_COMPILER_IS_GNUCXX )

INCLUDE_DIRECTORIES( ${CMAKE_SOURCE_DIR}/include )

SET( LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib )
SET( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin )

FIND_PACKAGE( Boost 1.35.0 COMPONENTS
	system
	thread )

IF( NOT Boost_FOUND )
	MESSAGE( STATUS "Boost not found!" )
ENDIF()

IF( Boost_INCLUDE_DIR )
	INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )
ELSE()
	MESSAGE( STATUS "Boost headers not found. You will have to specify them in your build environment or you can use -DBOOST_ROOT= or -DBoost_INCLUDE_DIR to tell cmake where your boost installation is." )
ENDIF()

IF( Boost_LIBRARY_DIRS )
	LINK_DIRECTORIES( ${Boost_LIBRARY_DIRS} )
ELSE()
	MESSAGE(STATUS "Boost libraries not found. Please set -DBoost_LIBRARY_DIR manually.")
ENDIF()

FIND_PACKAGE( X11 )

IF( NOT X11_FOUND )
	MESSAGE( STATUS "X11 not found!" )
ENDIF()

IF( X11_INCLUDE_DIR )
	INCLUDE_DIRECTORIES( ${X11_INCLUDE_DIR} )
ENDIF()

ADD_SUBDIRECTORY( src )
ADD_SUBDIRECTORY( example )
