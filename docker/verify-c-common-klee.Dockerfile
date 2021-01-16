
FROM seahorn/seahorn-llvm10:nightly
ENV SEAHORN=/home/usea/seahorn/bin/sea PATH="$PATH:/home/usea/seahorn/bin:/home/usea/bin"

## install required pacakges
USER root
## Install latest cmake
RUN apt -y remove --purge cmake
RUN apt -y update
RUN apt -y install wget
RUN wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null
RUN apt-add-repository 'deb https://apt.kitware.com/ubuntu/ bionic main'
RUN apt -y update
RUN apt -y install cmake

# Install lastest dependencies (LLVM-10)
RUN apt -y install build-essential curl libcap-dev git \
    libncurses5-dev python-minimal python-pip unzip \ 
    libtcmalloc-minimal4 libgoogle-perftools-dev libsqlite3-dev doxygen
RUN apt -y install python3 python3-pip gcc-multilib g++-multilib \
    bison flex minisat
RUN apt -y install clang-10 llvm-10 llvm-10-dev llvm-10-tools  

# Install stp
WORKDIR /home/usea/tmp
RUN rm -rf stp && git clone https://github.com/stp/stp.git
RUN cd stp && mkdir build && cd build && cmake .. && cmake --build .\
    && cmake --install .

# Install uclibc
RUN rm -rf klee-uclibc && git clone https://github.com/klee/klee-uclibc.git
RUN cd klee-uclibc && ./configure --make-llvm-lib --with-llvm-config /usr/bin/llvm-config-10 && make -j2

# Install klee-lastest
WORKDIR /home/usea/tmp
RUN rm -rf klee && git clone https://github.com/klee/klee.git
RUN cd klee && mkdir build && cd build && cmake \
  -DENABLE_SOLVER_STP=ON \
  -DENABLE_POSIX_RUNTIME=ON \
  -DENABLE_KLEE_UCLIBC=ON \
  -DKLEE_UCLIBC_PATH=../../klee-uclibc \
  -DENABLE_UNIT_TESTS=ON \
  -DLLVM_CONFIG_BINARY=/usr/bin/llvm-config-10 \
  -DENABLE_UNIT_TESTS=OFF \
  -DLLVMCC=/usr/bin/clang-10 \
  -DBUILD_SHARED_LIBS:BOOL=OFF \
  .. && make && make install

# Remove redundant pkgs
WORKDIR /home/usea
RUN apt-get clean && \
    apt-get autoremove -y && \
    rm -rf /var/lib/apt/lists/*

## verify-c-common
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
RUN mkdir build && cd build && cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_INSTALL_PREFIX=$(pwd)/run ../ -GNinja && cmake --build . --target install

WORKDIR /home/usea/verify-c-common

RUN mkdir build && cd build && cmake -DSEA_LINK=llvm-link-10 -DCMAKE_C_COMPILER=clang-10 -DCMAKE_CXX_COMPILER=clang++-10 -DSEAHORN_ROOT=/home/usea/seahorn -DSEA_ENABLE_FUZZ=ON -DSEA_ENABLE_KLEE=ON -Daws-c-common_DIR=$(pwd)/../aws-c-common/build/run/lib/aws-c-common/cmake/ ../ -GNinja && cmake --build .

## set default user and wait for someone to login and start running verification tasks
USER usea