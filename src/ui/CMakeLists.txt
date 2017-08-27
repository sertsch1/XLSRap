# Source files
SET(XLSRAP_UI_SRCS
	Main.cpp
	mainwindow.cpp
	XLSModel.cpp
	XLSItem.cpp
)

SET(XLSRAP_UI_HEADERS
	mainwindow.h
	XLSModel.h
	XLSItem.h
)

SET(XLSRAP_UI_FILES
	mainwindow.ui
)

# Find includes in corresponding build directories
SET(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
SET(CMAKE_AUTOMOC ON)

# Target name
SET(XLSRAP_PROJECT_NAME "xlsrap-ui")

# Find the qt packages
find_package(Qt5Widgets)
find_package(Qt5Core)

# Generate code from ui files
qt5_wrap_ui(UI_HEADERS ${XLSRAP_UI_FILES})

# Tell CMake to create the helloworld executable
add_executable(${XLSRAP_PROJECT_NAME} WIN32 ${UI_HEADERS} ${XLSRAP_UI_SRCS} ${XLSRAP_UI_HEADERS})

# Get core location
get_target_property(QtCore_location Qt5::Core LOCATION)

# Linked libraries
target_link_libraries(${XLSRAP_PROJECT_NAME}  
	Qt5::Widgets
	Qt5::Core
	xlsrap-lib  # XLSRap core library
)

# Windows specific build steps
if(WIN32)
    # Run winddeployqt if it can be found
    find_program(WINDEPLOYQT_EXECUTABLE NAMES windeployqt HINTS ${QTDIR} ENV QTDIR PATH_SUFFIXES bin)
    add_custom_command(TARGET ${XLSRAP_PROJECT_NAME} POST_BUILD
    COMMAND ${WINDEPLOYQT_EXECUTABLE} $<TARGET_FILE:${XLSRAP_PROJECT_NAME}>)
endif()