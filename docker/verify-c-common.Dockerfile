
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

## clone verify-c-common repository
USER usea
RUN git config --global user.email "person@place.com" && git config --global user.name "Name Thee"
WORKDIR /home/usea
#RUN git clone https://github.com/yvizel/verify-c-common.git 

# assume we are run inside verify-c-common
RUN mkdir verify-c-common
COPY . verify-c-common

## clone aws-c-common repository
WORKDIR /home/usea/verify-c-common
RUN rm -rf aws-c-common && git clone https://github.com/awslabs/aws-c-common.git

WORKDIR /home/usea/verify-c-common/aws-c-common
# apply patches from verify-c-common
RUN git am ../patch/*.patch
# build aws-c-common
RUN mkdir build && cd build && cmake -DCMAKE_C_COMPILER=clang-10 -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_INSTALL_PREFIX=$(pwd)/run ../ -GNinja && cmake --build . --target install

WORKDIR /home/usea/verify-c-common

RUN mkdir build && cd build && cmake -DSEA_LINK=llvm-link-10 -DCMAKE_C_COMPILER=clang-10 -DCMAKE_CXX_COMPILER=clang++-10 -DSEAHORN_ROOT=/home/usea/seahorn -DSEA_ENABLE_FUZZ=ON -Daws-c-common_DIR=$(pwd)/../aws-c-common/build/run/lib/aws-c-common/cmake/ ../ -GNinja && cmake --build .

## set default user and wait for someone to login and start running verification tasks
USER usea
