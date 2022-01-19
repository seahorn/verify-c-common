
FROM seahorn/seahorn-llvm10:nightly
ENV SEAHORN=/home/usea/seahorn/bin/sea PATH="$PATH:/home/usea/seahorn/bin:/home/usea/bin"

## Install required pacakges
USER root
## Install latest cmake
RUN apt -y remove --purge cmake
RUN apt -y update
RUN apt -y install wget python3-pip
RUN pip3 install cmake --upgrade

# Install lastest dependencies (LLVM-10)
RUN apt -y install build-essential curl libcap-dev git \
    libncurses5-dev python-minimal python-pip unzip \ 
    libtcmalloc-minimal4 libgoogle-perftools-dev libsqlite3-dev doxygen
RUN apt -y install python3 python3-pip gcc-multilib g++-multilib \
    bison flex minisat
RUN apt -y install clang-10 llvm-10 llvm-10-dev llvm-10-tools
RUN update-alternatives --install /usr/bin/llvm-config llvm-config /usr/bin/llvm-config-10 10
RUN update-alternatives --config llvm-config

# Install symbiotic lastest
WORKDIR /home/usea
RUN git clone https://github.com/staticafi/symbiotic
RUN cd symbiotic && git checkout 792b3b8 && ./system-build.sh
ENV PATH="$PATH:/home/usea/symbiotic/install/bin"

# Remove redundant pkgs
WORKDIR /home/usea
RUN apt-get clean && \
    apt-get autoremove -y && \
    rm -rf /var/lib/apt/lists/*

## verify-c-common
USER usea
WORKDIR /home/usea

# assume we are run inside verify-c-common
RUN mkdir verify-c-common
COPY . verify-c-common

## clone aws-c-common repository
WORKDIR /home/usea/verify-c-common
RUN rm -rf aws-c-common && git clone https://github.com/awslabs/aws-c-common.git

WORKDIR /home/usea/verify-c-common/aws-c-common
RUN mkdir build && cd build && cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_INSTALL_PREFIX=$(pwd)/run ../ -GNinja && cmake --build . --target install

WORKDIR /home/usea/verify-c-common

RUN mkdir build && cd build && cmake -DSEA_LINK=llvm-link-10 -DCMAKE_C_COMPILER=clang-10 -DCMAKE_CXX_COMPILER=clang++-10 -DSEAHORN_ROOT=/home/usea/seahorn -DSEA_ENABLE_SYMBIOTIC=ON -DSEA_WITH_BLEEDING_EDGE=ON -Daws-c-common_DIR=$(pwd)/../aws-c-common/build/run/lib/aws-c-common/cmake/ ../ -GNinja && cmake --build .

## set default user and wait for someone to login and start running verification tasks
USER usea