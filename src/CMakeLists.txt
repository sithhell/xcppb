
# source files in root directory
FILE( GLOB sources *.cpp )
FILE( GLOB header *.hpp )

SET( xcppb_files ${sources} ${header} )

# source files in auth directory
FILE( GLOB sources auth/*.cpp )
FILE( GLOB header auth/*.hpp )

SET( xcppb_files ${xcppb_files} ${sources} ${header} )

# source files in detail directory
FILE( GLOB sources detail/*.cpp )
FILE( GLOB header detail/*.hpp )

SET( xcppb_files ${xcppb_files} ${sources} ${header} )

# source files in detail directory
FILE( GLOB sources setup/*.cpp )
FILE( GLOB header setup/*.hpp )

SET( xcppb_files ${xcppb_files} ${sources} ${header} )


ADD_LIBRARY( xcppb SHARED ${xcppb_files} )

TARGET_LINK_LIBRARIES( xcppb ${Boost_LIBRARIES} ${X11_LIBRARIES} )

FILE( GLOB compiler_sources xcbgen/grammar/*.cpp )
ADD_EXECUTABLE( compiler ${compiler_sources} xcbgen/compile.cpp )
TARGET_LINK_LIBRARIES( compiler ${Boost_LIBRARIES} )
