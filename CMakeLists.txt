cmake_minimum_required(VERSION 3.24)

project(
	AllMenuZoom
	VERSION 1.0.0
	LANGUAGES CXX
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

list(APPEND CMAKE_IGNORE_PATH "${PROJECT_BINARY_DIR}")
list(APPEND CMAKE_MODULE_PATH
	"${PROJECT_SOURCE_DIR}/tools/Modules"
)
include(SKSEPlugin)

set(SKSE_USE_XBYAK OFF)

find_package(unordered_dense CONFIG REQUIRED)

find_path(CLIB_UTIL_INCLUDE_DIRS "ClibUtil/utils.hpp")
find_path(MERGEMAPPER_INCLUDE_DIRS "MergeMapperPluginAPI.h")
find_path(SRELL_INCLUDE_DIRS "srell.hpp")

SKSEPlugin_Add(
	${PROJECT_NAME}
	SOURCE_DIR src
	SOURCES
		.clang-format
		.editorconfig
		README.md
		vcpkg.json
	${MERGEMAPPER_INCLUDE_DIRS}/MergeMapperPluginAPI.cpp
	PRECOMPILE_HEADERS
		src/PCH/PCH.h
)

target_compile_features(
	${PROJECT_NAME}
	PRIVATE
		cxx_std_23
)

target_compile_definitions(
	${PROJECT_NAME}
	PRIVATE
		_UNICODE
)

target_include_directories(
	${PROJECT_NAME}
	PRIVATE
		${CMAKE_CURRENT_BINARY_DIR}/include
		${CMAKE_CURRENT_SOURCE_DIR}/src
		${CLIB_UTIL_INCLUDE_DIRS}
		${MERGEMAPPER_INCLUDE_DIRS}
		${SRELL_INCLUDE_DIRS}
)

target_link_libraries(
	${PROJECT_NAME}
	PRIVATE
        CommonLibSSE::CommonLibSSE
		unordered_dense::unordered_dense
)
