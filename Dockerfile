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

FROM debian:buster-slim

# Image descriptor
LABEL copyright.name="Vicente Eduardo Ferrer Garcia" \
	copyright.address="vic798@gmail.com" \
	maintainer.name="Vicente Eduardo Ferrer Garcia" \
	maintainer.address="vic798@gmail.com" \
	vendor="MetaCall Inc." \
	version="0.1"

# Install dependencies
RUN apt-get update \
	&& apt-get install -y --no-install-recommends \
		build-essential \
		cmake \
		ca-certificates \
		git \
		nodejs \
		npm \
		python2.7 \
		node-gyp \
		unzip

# Set working directory to home
WORKDIR /root

# Force rebuild for latest version
ARG DISABLE_CACHE=0

# Clone and build the project
RUN git clone https://github.com/metacall/embedding-nodejs-example.git \
	&& mkdir embedding-nodejs-example/build && cd embedding-nodejs-example/build \
	&& cmake .. \
	&& cmake --build . --target install

# Run the executable
RUN export LOADER_LIBRARY_PATH="/usr/local/lib" \
	&& export LOADER_SCRIPT_PATH="`pwd`" \
	&& embedding_nodejs_example
