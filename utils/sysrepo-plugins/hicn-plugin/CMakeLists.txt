#
# Copyright (c) 2019 Cisco and/or its affiliates.
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at:
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# set compiler options
set(CMAKE_EXPORT_COMPILE_COMMANDS 1)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -std=gnu99")
set(CMAKE_C_FLAGS_RELEASE "-DNDEBUG -O2")
set(CMAKE_C_FLAGS_DEBUG   "-g -O0")

cmake_minimum_required(VERSION 2.8)
project(sysrepo-vpp-plugins)

# Cmake find modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/../cmake")

find_package(VPP)
find_package(PkgConfig)
find_package(HicnPlugin)
find_package(Sysrepo)

#pkg_check_modules(SYSREPO libsysrepo)

# get sysrepo plugins directory from pkgconfig
if (NOT SR_PLUGINS_DIR)
    if (PKG_CONFIG_FOUND)
        execute_process(COMMAND ${PKG_CONFIG_EXECUTABLE} "--variable=SR_PLUGINS_DIR" "libsysrepo" OUTPUT_VARIABLE SR_PLUGINS_DIR)
        string(STRIP ${SR_PLUGINS_DIR} SR_PLUGINS_DIR)
    endif()
endif()
if (NOT SR_PLUGINS_DIR)
    message(FATAL_ERROR "Cannot get sysrepo plugins directory due to missing pkg-config, set SR_PLUGINS_DIR manually.")
endif()

# plugins sources
set(PLUGINS_SOURCES
    plugin/ietf/ietf_interface.c
    plugin/model/hicn_model.c
    plugin/model/tlock.c
    plugin/hicn_vpp_comm.c
    plugin/hicn_plugin.c
)

# build the source code into shared library
add_library(hicn SHARED ${PLUGINS_SOURCES})
target_include_directories(hicn PUBLIC ${VPP_INCLUDE_DIRS} ${HICNPLUGIN_INCLUDE_DIRS})
target_link_libraries(hicn ${SYSREPO_LIBRARIES} ${VPP_LIBRARIES} ${HICNPLUGIN_LIBRARIES})

#set_target_properties(hicn
#        PROPERTIES
#        LINKER_LANGUAGE C
#        INSTALL_RPATH ${VPP_HOME}/lib)

# install the plugin into plugins dir
install(TARGETS hicn DESTINATION ${SR_PLUGINS_DIR} COMPONENT hicn_sysrepo_plugin)
