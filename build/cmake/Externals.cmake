##################################################
# XLNT - Excel parse library
##################################################
option(TESTS "Set to OFF to skip building test executable (in ./tests)" OFF)
option(STATIC "Set to ON to build xlnt as a static library instead of a shared library" ON)
add_subdirectory(${XLSRAP_EXTERNAL}/xlnt)

##################################################
# QT Framework
##################################################
if ("${QT_PATH}" STREQUAL "")
	# Set paths
	SET(QT_PATH ${XLSRAP_ROOT}/qt)
endif()

SET(QT_CMAKE_PATH ${QT_PATH}/lib/cmake)
SET(QTDIR ${QT_PATH})

# Append modules (from externals) to prefix path
SET(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} ${QT_CMAKE_PATH})
