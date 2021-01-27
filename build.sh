#!/bin/bash

# Logging Log4Cxx Framework for our test application main.cpp

# might need to install libapr1-dev libaprutil1-dev
# Install OpenSSL (needed to build cmake 3.19)
yum -y install openssl-devel

# Install CMake 3.19.3
# cmake: https://github.com/Kitware/CMake/releases
pushd / \
    && wget https://github.com/Kitware/CMake/releases/download/v3.19.3/cmake-3.19.3.tar.gz \
    && tar -xvf cmake-3.19.3.tar.gz \
    && pushd cmake-3.19.3 \
    && ./bootstrap \
    && make \
    && make install
    && popd
    && popd

# # Install apr 1.x
# # apr and apr-util lib: https://apr.apache.org/download.cgi
# pushd / \
#     && wget https://apache.claz.org//apr/apr-1.7.0.tar.gz \
#     && tar -zxvf apr-1.7.0.tar.gz \
#     && pushd apr-1.7.0 \
#     && ./configure \
#     && make \
#     && make install \
#     && popd \
#     && popd

# # Install expat lib, needed for apr-util
# yum -y install expat-devel

# # Install apr-util 1.x
# pushd / \
#     && wget https://apache.claz.org//apr/apr-util-1.6.1.tar.gz \
#     && tar -zxvf apr-util-1.6.1.tar.gz \
#     && pushd apr-util-1.6.1 \
#     && ./configure --with-apr=/usr/local/apr \
#     && make \
#     && make install \
#     && popd \
#     && popd

# APR_INCLUDE_DIR (missing: APR_LIBRARIES)
# Note: updated /logging-log4cxx/src/cmake/FindAPR.cmake with path to apr-1-config executable
# , which for apr 1.7 is located /usr/local/apr/bin/

# APR_UTIL_INCLUDE_DIR (missing: APR_UTIL_LIBRARIES)
# Note: updated /logging-log4cxx/src/cmake/FindAPR-Util.cmake with path to apu-1-config executable
# , which for apr-util 1.6.1 is located /usr/local/apr/bin/

# The above 2 comments were potential solutions when building apr 1.7 and apr-util 1.6.1 from scratch

# Alternatively, install apr and apr-util using the command as follows:
# apr 1.6.3 installed
# apr-util 1.6.1
# apr-util-openssl 1.6.1
yum -y install apr apr-devel apr-util apr-util-devel

git clone http://gitbox.apache.org/repos/asf/logging-log4cxx.git
yum -y install gzip zip
cd logging-log4cxx
mkdir build
cd build

cmake ../

make
make install