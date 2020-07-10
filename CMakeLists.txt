#-------------------------------------------------------------------------------------------
#   Corsac Entity Component System
#   Copyright (C) 2020 Vladisalv Fedotov <survereignty@gmail.com>
#-------------------------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.17.3)
project(Corsac_ECS
            VERSION 1.0.1
            DESCRIPTION "ECS for Corsac2D"
            LANGUAGES CXX
)

#-------------------------------------------------------------------------------------------
# Library definition
#-------------------------------------------------------------------------------------------
file(GLOB TARGET_SRC "./src/*.cpp")
add_library(${PROJECT_NAME} STATIC ${TARGET_SRC})
set_target_properties( ${PROJECT_NAME}
		PROPERTIES
		CXX_STANDARD 17
		CXX_STANDARD_REQUIRED ON
)

#-------------------------------------------------------------------------------------------
# Include dirs
#-------------------------------------------------------------------------------------------
target_include_directories(${PROJECT_NAME} PUBLIC include)

#-------------------------------------------------------------------------------------------
# EASTL
#-------------------------------------------------------------------------------------------
set(EASTL_ROOT_DIR ${CMAKE_SOURCE_DIR}/lib/EASTL)
target_include_directories (${PROJECT_NAME} PUBLIC ${EASTL_ROOT_DIR}/include)
target_include_directories (${PROJECT_NAME} PUBLIC ${EASTL_ROOT_DIR}/test/packages/EAAssert/include)
target_include_directories (${PROJECT_NAME} PUBLIC ${EASTL_ROOT_DIR}/test/packages/EABase/include/Common)
target_include_directories (${PROJECT_NAME} PUBLIC ${EASTL_ROOT_DIR}/test/packages/EAMain/include)
target_include_directories (${PROJECT_NAME} PUBLIC ${EASTL_ROOT_DIR}/test/packages/EAStdC/include)
target_include_directories (${PROJECT_NAME} PUBLIC ${EASTL_ROOT_DIR}/test/packages/EATest/include)
target_include_directories (${PROJECT_NAME} PUBLIC ${EASTL_ROOT_DIR}/test/packages/EAThread/include)

if (WIN32)
    set(EASTL_LIBRARY debug ${EASTL_ROOT_DIR}/build/Debug/EASTL.lib optimized ${EASTL_ROOT_DIR}/build/Release/EASTL.lib)
elseif (UNIX)
    set(EASTL_LIBRARY debug ${EASTL_ROOT_DIR}/build/libEASTL.a optimized ${EASTL_ROOT_DIR}/build/libEASTL.a)
else ()
	message (FATAL_ERROR "What this OS?")
endif ()

add_custom_target(NatVis SOURCES ${EASTL_ROOT_DIR}/doc/EASTL.natvis)

#-------------------------------------------------------------------------------------------
# Dependencies
#-------------------------------------------------------------------------------------------
target_link_libraries(${PROJECT_NAME} PUBLIC ${EASTL_LIBRARY})

