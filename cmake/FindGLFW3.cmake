SET( GLFW3_SEARCH_PATHS
  ${GLFW3_ROOT_DIR}
  ./lib/glfw3
  $ENV{PROGRAMFILES}/GLFW3
  #"$ENV{PROGRAMFILES(X86)}/GLFW3"
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /opt
  /sw
  /opt/local
  /opt/csw
)

FIND_PATH( GLFW3_INCLUDE_DIRS
  NAMES
    GLFW/glfw3.h
  PATHS
    ${GLFW3_SEARCH_PATHS}
  PATH_SUFFIXES
    include
  DOC
    "The directory where GLFW/glfw3.h resides"
)

FIND_LIBRARY( GLFW3_LIBRARIES
  NAMES
    glfw3 GLFW3 libglfw3.dylib
  PATHS
    ${GLFW3_SEARCH_PATHS}
  PATH_SUFFIXES
    lib
    lib64
    lib/Release/Win32
    lib/Release/x64
  DOC
    "The GLFW3 library"
)

IF ( GLFW3_INCLUDE_DIRS AND GLFW3_LIBRARIES )
  SET( GLFW3_FOUND TRUE )
  MESSAGE( STATUS "Looking for GLFW3 - found" )
ELSE ( GLFW3_INCLUDE_DIRS AND GLFW3_LIBRARIES )
  SET( GLFW3_FOUND FALSE )
  MESSAGE( STATUS "Looking for GLFW3 - not found" )
ENDIF ( GLFW3_INCLUDE_DIRS AND GLFW3_LIBRARIES )