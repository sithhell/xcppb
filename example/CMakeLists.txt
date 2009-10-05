
ADD_EXECUTABLE( connection_test connection_test.cpp )
TARGET_LINK_LIBRARIES( connection_test xcppb ${Boost_LIBRARIES} ${X11_LIBRARIES} )
