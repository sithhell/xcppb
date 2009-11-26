
FILE( GLOB_RECURSE xcppb_sources *.cpp )
FILE( GLOB_RECURSE xcppb_header *.hpp )

SET( xcppb_files ${xcppb_sources} ${xcppb_header} )

SET( SUBDIRVAL "${SUBDIRVAL} blubb" )

ADD_LIBRARY( xcppb SHARED ${xcppb_files} )

TARGET_LINK_LIBRARIES( xcppb ${Boost_LIBRARIES} ${X11_LIBRARIES} )

ADD_EXECUTABLE( cppgen proto/cppgen.cpp )
TARGET_LINK_LIBRARIES( cppgen ${Boost_LIBRARIES} )
