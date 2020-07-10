#-------------------------------------------------------------------------------------------
# Copyright (C) Corsac Engine All rights reserved.
#-------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.0.0)
project(Corsac_ECS VERSION 1.0.0)
include_directories (${CMAKE_SOURCE_DIR}/include)

#-------------------------------------------------------------------------------------------
# EASTL
#-------------------------------------------------------------------------------------------
set(EASTL_ROOT_DIR ${CMAKE_SOURCE_DIR}/lib/EASTL)
include_directories (${EASTL_ROOT_DIR}/include)
include_directories (${EASTL_ROOT_DIR}/test/packages/EAAssert/include)
include_directories (${EASTL_ROOT_DIR}/test/packages/EABase/include/Common)
include_directories (${EASTL_ROOT_DIR}/test/packages/EAMain/include)
include_directories (${EASTL_ROOT_DIR}/test/packages/EAStdC/include)
include_directories (${EASTL_ROOT_DIR}/test/packages/EATest/include)
include_directories (${EASTL_ROOT_DIR}/test/packages/EAThread/include)

if (WIN32)
    set(EASTL_LIBRARY debug ${EASTL_ROOT_DIR}/build/Debug/EASTL.lib optimized ${EASTL_ROOT_DIR}/build/Release/EASTL.lib)
    message (STATUS "Это Windows")
elseif (UNIX)
    set(EASTL_LIBRARY debug ${EASTL_ROOT_DIR}/build/libEASTL.a optimized ${EASTL_ROOT_DIR}/build/libEASTL.a)
    message (STATUS "Это Unix")
else ()
	message (FATAL_ERROR "Неизвестная система")
endif ()

add_custom_target(NatVis SOURCES ${EASTL_ROOT_DIR}/doc/EASTL.natvis)

message (STATUS "EASTL -> is include!")

file(GLOB TARGET_SRC "./src/*.cpp" "./include/*.h")
add_library(${PROJECT_NAME} ${TARGET_SRC})
set_target_properties( ${PROJECT_NAME}
		PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED ON
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC ${EASTL_LIBRARY}
)



