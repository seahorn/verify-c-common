
FROM seahorn/seahorn-llvm10:nightly

ENV SEAHORN=/home/usea/seahorn/bin/sea PATH="$PATH:/home/usea/seahorn/bin:/home/usea/bin"

## install required pacakges
USER root

## clone verify-c-common repository
USER usea
WORKDIR /home/usea
RUN git clone https://github.com/yvizel/verify-c-common.git 

## clone trusty repository (takes a long time)
WORKDIR /home/usea/verify-c-common
RUN git clone https://github.com/awslabs/aws-c-common.git

WORKDIR /home/usea/verify-c-common/aws-c-common
RUN mkdir build && cd build

RUN cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 ../

WORKDIR /home/usea/verify-c-common
RUN ln -sf aws-c-common/build/compile_commands.json .

RUN mkdir build && cd build
RUN cmake -DSEA_LINK=llvm-link-10 -DCMAKE_C_COMPILER=clang-10 -DCMAKE_CXX_COMPILER=clang++-10 -DSEAHORN_ROOT=/home/usea/seahorn ../ -GNinja
RUN ninja

RUN ninja test

## set default user and wait for someone to login and start running verification tasks
USER usea
