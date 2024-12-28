cmake_minimum_required(VERSION 3.5)
project(vcam-service)

configure_file(
	"${CMAKE_CURRENT_SOURCE_DIR}/module.def.in"
	"${CMAKE_CURRENT_BINARY_DIR}/module.def")

set(MODULE_DESCRIPTION "Virtual Camera Service")

include_directories(${CMAKE_CURRENT_BINARY_DIR}/..)

set(libdshowcapture_SOURCES
	libdshowcapture/source/log.cpp
	libdshowcapture/source/dshow-base.cpp
	libdshowcapture/source/dshow-enum.cpp
	libdshowcapture/source/dshow-formats.cpp
	libdshowcapture/source/dshow-media-type.cpp
	libdshowcapture/source/output-filter.cpp)

set(libdshowcapture_HEADERS
	libdshowcapture/source/ComPtr.hpp
	libdshowcapture/source/CoTaskMemPtr.hpp
	libdshowcapture/source/log.hpp
	libdshowcapture/source/dshow-base.hpp
	libdshowcapture/source/dshow-enum.hpp
	libdshowcapture/source/dshow-formats.hpp
	libdshowcapture/source/dshow-media-type.hpp
	libdshowcapture/source/output-filter.hpp
	libdshowcapture/dshowcapture.hpp)

set(vcam-service_SOURCES
	"${CMAKE_CURRENT_BINARY_DIR}/module.def"
	sleepto.cpp
	placeholder.cpp
	module.cpp
	filter.cpp
	shared_memory_queue.cpp
	nv12_scale.cpp)

set(vcam-service_HEADERS
	sleepto.h
	filter.hpp
	shared_memory_queue.h
	nv12_scale.h)

if(MSVC)
	add_compile_options("$<IF:$<CONFIG:Debug>,/MTd,/MT>")
endif()

source_group("libdshowcapture\\Source Files" FILES ${libdshowcapture_SOURCES})
source_group("libdshowcapture\\Header Files" FILES ${libdshowcapture_HEADERS})

set(CMAKE_MODULE_LINKER_FLAGS "${MAKE_MODULE_LINKER_FLAGS} /ignore:4104")

add_library(vcam-service MODULE
			${libdshowcapture_SOURCES}
			${libdshowcapture_HEADERS}
			${vcam-service_SOURCES}
			${vcam-service_HEADERS})

target_link_libraries(vcam-service
					  setupapi
					  winmm
					  strmiids
					  gdiplus)

set_target_properties(vcam-service PROPERTIES OUTPUT_NAME "vcam-service")
