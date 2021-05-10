FROM leonsou/bionic-smack:latest as smack
FROM seahorn/seahorn-llvm10:nightly
ENV SEAHORN=/home/usea/seahorn/bin/sea PATH="$PATH:/home/usea/seahorn/bin:/home/usea/bin"

## install required pacakges
USER root
COPY --from=smack /home/usea/smack-toolchain /home/usea/smack-toolchain

## Install latest cmake
RUN apt -y remove --purge cmake
RUN apt -y update
RUN apt -y install wget
RUN wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null
RUN apt-add-repository 'deb https://apt.kitware.com/ubuntu/ bionic main'
RUN apt -y update
RUN apt -y install cmake

## Install dotnet
RUN wget https://packages.microsoft.com/config/ubuntu/20.04/packages-microsoft-prod.deb -O packages-microsoft-prod.deb
RUN dpkg -i packages-microsoft-prod.deb
RUN apt -y update
RUN apt -y install dotnet-sdk-3.1

# Build and Install smack
WORKDIR /home/usea/smack-toolchain/smack
RUN rm -rf build && mkdir build
RUN cd build && cmake -DCMAKE_C_COMPILER=clang-10 -DCMAKE_CXX_COMPILER=clang++-10 -DCMAKE_BUILD_TYPE=Debug .. -G Ninja \
    && ninja install

# Remove redundant pkgs
WORKDIR /home/usea
RUN apt-get clean && \
    apt-get autoremove -y && \
    rm -rf /var/lib/apt/lists/*

## verify-c-common
USER usea
WORKDIR /home/usea
#RUN git clone https://github.com/seahorn/verify-c-common.git 

# assume we are run inside verify-c-common
RUN mkdir verify-c-common
COPY . verify-c-common

## clone aws-c-common repository
WORKDIR /home/usea/verify-c-common
RUN rm -rf aws-c-common && git clone https://github.com/awslabs/aws-c-common.git

WORKDIR /home/usea/verify-c-common/aws-c-common
RUN mkdir build && cd build && cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DCMAKE_INSTALL_PREFIX=$(pwd)/run ../ -GNinja && cmake --build . --target install

WORKDIR /home/usea/verify-c-common

RUN mkdir build && cd build && cmake -DSEA_LINK=llvm-link-10 -DCMAKE_C_COMPILER=clang-10 -DCMAKE_CXX_COMPILER=clang++-10 -DSEAHORN_ROOT=/home/usea/seahorn -DSEA_ENABLE_SMACK=ON -DSMACK_ENABLE_NO_MEM_SPLIT=ON ../ -GNinja && cmake --build .

# Add smack envinronment
RUN echo "source /home/usea/smack-toolchain/smack.environment" >> ~/.bashrc

## set default user and wait for someone to login and start running verification tasks
USER usea