
FROM seahorn/seahorn-llvm14:nightly

ENV SEAHORN=/home/usea/seahorn/bin/sea PATH="$PATH:/home/usea/seahorn/bin:/home/usea/bin"

## install required pacakges
USER root

## Install latest cmake
RUN apt -y remove --purge cmake
RUN apt -y update
RUN apt -y install wget python3-pip
RUN python3 -m pip install --upgrade pip
RUN pip3 install cmake --upgrade

## clone verify-c-common repository
USER usea
WORKDIR /home/usea

# assume we are run inside verify-c-common
RUN mkdir verify-c-common
COPY --chown=usea:usea . verify-c-common

## clone aws-c-common repository
WORKDIR /home/usea/verify-c-common
RUN rm -rf aws-c-common && git clone https://github.com/awslabs/aws-c-common.git

WORKDIR /home/usea/verify-c-common/aws-c-common
RUN rm -rf build && mkdir build && cd build && cmake -DCMAKE_C_COMPILER=clang-14 -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_INSTALL_PREFIX=$(pwd)/run ../ -GNinja && cmake --build . --target install

WORKDIR /home/usea/verify-c-common

RUN rm -Rf build && mkdir build && cd build && cmake -DSEA_LINK=llvm-link-14 -DCMAKE_C_COMPILER=clang-14 -DCMAKE_CXX_COMPILER=clang++-14 -DSEAHORN_ROOT=/home/usea/seahorn -Daws-c-common_DIR=$(pwd)/../aws-c-common/build/run/lib/aws-c-common/cmake/ ../ -GNinja && cmake --build .

## set default user and wait for someone to login and start running verification tasks
USER usea
