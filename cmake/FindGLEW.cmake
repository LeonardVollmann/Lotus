SET( GLEW_SEARCH_PATHS
	${GLEW_ROOT_DIR}
	./lib/glew
	$ENV{PROGRAMFILES}/GLEW
	#"$ENV{PROGRAMFILES(X86)}/GLEW"
	~/Library/Frameworks
	/Library/Frameworks
	/usr/local
	/usr
	/opt
	/sw
	/opt/local
	/opt/csw
)

FIND_PATH( GLEW_INCLUDE_DIRS
	NAMES
		GL/glew.h
	PATHS
		${GLEW_SEARCH_PATHS}
	PATH_SUFFIXES
		include
	DOC
		"The directory where GL/glew.h resides"
)

FIND_LIBRARY( GLEW_LIBRARIES
	NAMES
		glew GLEW libGLEW.a glew32 glew32s
	PATHS
		${GLEW_SEARCH_PATHS}
	PATH_SUFFIXES
		lib
		lib64
		lib/Release/Win32
		lib/Release/x64
	DOC
		"The GLEW library"
)

IF ( GLEW_INCLUDE_DIRS AND GLEW_LIBRARIES )
	SET( GLEW_FOUND TRUE )
	MESSAGE( STATUS "Looking for GLEW - found" )
ELSE ( GLEW_INCLUDE_DIRS AND GLEW_LIBRARIES )
	SET( GLEW_FOUND FALSE )
	MESSAGE( STATUS "Looking for GLEW - not found" )
ENDIF ( GLEW_INCLUDE_DIRS AND GLEW_LIBRARIES )