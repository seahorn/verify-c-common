FROM seahorn/seahorn-llvm10:nightly

ENV SEAHORN=/home/usea/seahorn/bin/sea PATH="$PATH:/home/usea/seahorn/bin:/home/usea/bin"

## install required pacakges
USER root

## Install latest cmake
RUN apt -y remove --purge cmake
RUN apt -y update
RUN apt -y install wget python3-pip
RUN python3 -m pip install --upgrade pip
RUN pip3 install cmake --upgrade

# Install dependencies (Python and LLVM Cov Tools)
RUN apt -y install python3
RUN apt -y install clang-10 llvm-10 llvm-10-dev llvm-10-tools lcov

## clone verify-c-common repository
USER usea
WORKDIR /home/usea
#RUN git clone https://github.com/yvizel/verify-c-common.git 

# assume we are run inside verify-c-common
RUN mkdir verify-c-common
COPY . verify-c-common

## clone aws-c-common repository
WORKDIR /home/usea/verify-c-common
RUN rm -rf aws-c-common && git clone https://github.com/awslabs/aws-c-common.git

WORKDIR /home/usea/verify-c-common/aws-c-common
RUN mkdir build && cd build && cmake -DCMAKE_C_COMPILER=clang-10 \
  -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
  -DCMAKE_INSTALL_PREFIX=$(pwd)/run \
  -DCMAKE_C_FLAGS='-fsanitize=fuzzer-no-link,address,undefined -fprofile-instr-generate -fcoverage-mapping' \
  ../ -GNinja && \
  cmake --build . --target install

WORKDIR /home/usea/verify-c-common

RUN mkdir build && cd build && cmake -DSEA_LINK=llvm-link-10 -DCMAKE_C_COMPILER=clang-10 -DCMAKE_CXX_COMPILER=clang++-10 -DSEAHORN_ROOT=/home/usea/seahorn -DSEA_ENABLE_FUZZ=ON -Daws-c-common_DIR=$(pwd)/../aws-c-common/build/run/lib/aws-c-common/cmake/ ../ -GNinja && cmake --build .

USER root
