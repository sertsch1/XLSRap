SET(CORE_SRCS
	XLSRap.cpp
)

SET(XLSRAP_LIB_NAME "xlsrap-lib")

add_library(${XLSRAP_LIB_NAME} STATIC ${CORE_SRCS})

target_include_directories(${XLSRAP_LIB_NAME}
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${XLSRAP_LIB_NAME} xlnt)
