cmake_minimum_required(VERSION 3.16)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(physx2d VERSION 1.0 DESCRIPTION "Physx2D is a high performance 2D game engine library for C/C++")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

#----------- download all the submodules ---------------
find_package(Git QUIET)
if(GIT_FOUND AND EXISTS "${PROJECT_SOURCE_DIR}/.git")
    option(GIT_SUBMODULE "Check submodules during build" ON)
    if(GIT_SUBMODULE)
        message(STATUS "Submodule update")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
            RESULT_VARIABLE GIT_SUBMOD_RESULT)
        if(NOT GIT_SUBMOD_RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init failed with ${GIT_SUBMOD_RESULT}, please checkout submodules")
        endif()
    endif()
endif()
# ---------------check all the submodules ---------------
if(NOT EXISTS "${PROJECT_SOURCE_DIR}/external/glfw/CMakeLists.txt")
    message(FATAL_ERROR "GLFW submodule was not downloaded! GIT_SUBMODULE was turned off or failed. Please update submodules and try again")
endif()
# --------------module check finished ---------------------

file(GLOB_RECURSE SRC_FILES
    "src/*.cpp"
)
file(GLOB EXTERNALS
    "external/glad/src/glad.c"
    "external/stb/src/stb_image.cpp"
)

add_subdirectory(external/glfw)

configure_file(physx2d.pc.in physx2d.pc)
add_library(${PROJECT_NAME} SHARED ${SRC_FILES} ${EXTERNALS})

target_include_directories(${PROJECT_NAME} PUBLIC 
    ${PROJECT_BINARY_DIR}
    src
    external/glfw/include 
    external/glad/include
    external/stb/include
)
target_link_directories(${PROJECT_NAME}
    PRIVATE external/glfw/src
)
target_link_libraries(${PROJECT_NAME}
    glfw
)

if(APPLE)
    find_library(OPENGL_LIB OpenGL)
    target_link_libraries(Physx2D PRIVATE ${OPENGL_LIB})
endif()

#---------------- precompiled headers -----------------
target_precompile_headers(${PROJECT_NAME} PRIVATE src/pch.h)
set_source_files_properties(external/glad/src/glad.c external/stb/src/stb_image.cpp PROPERTIES SKIP_PRECOMPILE_HEADERS ON)

# ---------- Compiler definitions ----------------------

if (WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DPHSX2D_PLATFORM_WINDOWS)
    message("system : WIN32")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DPHSX2D_PLATFORM_LINUX)
    message("system : Linux")
elseif (APPLE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE -DPHSX2D_PLATFORM_APPLE)
    message("system : Apple")
endif()

target_compile_definitions(${PROJECT_NAME} PRIVATE
    $<$<CONFIG:Debug>:PHSX2D_DEBUG;PHSX2D_ASSERT_ENABLE>
    $<$<CONFIG:Release>:PHSX2D_RELEASE;PHSX2D_ASSERT_ENABLE>
    $<$<CONFIG:Dist>:PHSX2D_DIST;PHSX2D_ASSERT_ENABLE>
    -DPHSX2D_BUILD_SHARED_LIB
)
# Setting up the installation to put shared_library on lib direcory and headers on include directory
set(INSTALL_LIB_DIR ${CMAKE_BINARY_DIR}/physx2d/lib)
set(INSTALL_INCLUDE_DIR ${CMAKE_BINARY_DIR}/physx2d/include)

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/physx2d)
include(GNUInstallDirs)

install(TARGETS ${PROJECT_NAME}
    DESTINATION ${INSTALL_LIB_DIR}
)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/src/
    DESTINATION ${INSTALL_INCLUDE_DIR}
    FILES_MATCHING
    PATTERN "*.h"
)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/external/glfw/include/
    DESTINATION ${INSTALL_INCLUDE_DIR}
)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/external/glad/include/
    DESTINATION ${INSTALL_INCLUDE_DIR}
)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/external/stb/include/
    DESTINATION ${INSTALL_INCLUDE_DIR}
)

#install(TARGETS ${PROJECT_NAME} DESTINATION lib)
#install(DIRECTORY ${CMAKE_SOURCE_DIRECTORY}
#    DESTINATION include
#    FILES_MATCHING
#    PATTERN "*.h"
#)
