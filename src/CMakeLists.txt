
FILE( GLOB_RECURSE xcppb_sources *.cpp )
FILE( GLOB_RECURSE xcppb_header *.hpp )

SET( xcppb_files ${xcppb_sources} ${xcppb_header} )

SET( SUBDIRVAL "${SUBDIRVAL} blubb" )

ADD_LIBRARY( xcppb SHARED ${xcppb_files} )

TARGET_LINK_LIBRARIES( xcppb ${Boost_LIBRARIES} ${X11_LIBRARIES} )

FILE( GLOB compiler_sources proto/grammar/*.cpp )
ADD_EXECUTABLE( compiler ${compiler_sources} proto/compile.cpp )
TARGET_LINK_LIBRARIES( compiler ${Boost_LIBRARIES} )
