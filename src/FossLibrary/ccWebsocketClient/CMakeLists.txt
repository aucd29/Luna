# CMake Version
CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

# Project Name
PROJECT(ccWebsocketClient)

# Configuration

include_directories( ./ ../../Library ../../FossLibrary)

file(GLOB SRC_FILES 
	src/*.cpp
	src/lib_easywsclient/*.cpp
)

add_library (ccWebsocketClient
	${SRC_FILES}
)
