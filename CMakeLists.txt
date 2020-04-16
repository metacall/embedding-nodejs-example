#
#	MetaCall Embedding NodeJS Example by Parra Studios
#	An example of embedding NodeJS into C/C++.
#
#	Copyright (C) 2016 - 2020 Vicente Eduardo Ferrer Garcia <vic798@gmail.com>
#
#	Licensed under the Apache License, Version 2.0 (the "License");
#	you may not use this file except in compliance with the License.
#	You may obtain a copy of the License at
#
#		http://www.apache.org/licenses/LICENSE-2.0
#
#	Unless required by applicable law or agreed to in writing, software
#	distributed under the License is distributed on an "AS IS" BASIS,
#	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#	See the License for the specific language governing permissions and
#	limitations under the License.
#

cmake_minimum_required(VERSION 2.8)

project(metacall_embedding_nodejs_example)

# Include MetaCall library as a dependency
set(METACALL_VERSION 0.1.54)

include(ExternalProject)

ExternalProject_Add(metacall
	URL https://github.com/metacall/core/archive/v${METACALL_VERSION}.zip
	PREFIX ${CMAKE_CURRENT_BINARY_DIR}/metacall-v${METACALL_VERSION}
	CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR> -DNODEJS_CMAKE_DEBUG=On -DOPTION_BUILD_LOADERS_NODE=On -DOPTION_BUILD_DETOURS=Off -DOPTION_BUILD_SCRIPTS=Off -DOPTION_BUILD_TESTS=Off -DOPTION_BUILD_EXAMPLES=Off
	UPDATE_COMMAND ""
	INSTALL_DIR "${CMAKE_INSTALL_PREFIX}"
)

# Define MetaCall library target
add_library(libmetacall SHARED IMPORTED)

add_dependencies(libmetacall metacall)

set_property(
	TARGET libmetacall
	PROPERTY IMPORTED_LOCATION ${CMAKE_INSTALL_PREFIX}/lib/${CMAKE_SHARED_LIBRARY_PREFIX}metacall${CMAKE_SHARED_LIBRARY_SUFFIX}
)

# Define main executable target
add_executable(embedding_nodejs_example main.c)

target_link_libraries(embedding_nodejs_example libmetacall)

# Install main target
install(TARGETS embedding_nodejs_example DESTINATION bin)
