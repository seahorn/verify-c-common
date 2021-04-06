FROM ubuntu:18.04

## install required pacakges
USER root

RUN apt-get update && apt -y install software-properties-common
RUN add-apt-repository 'ppa:ubuntu-toolchain-r/test'
RUN apt-get update && \
    apt-get install -y python3 python3-pip gcc-10 g++-10 ninja-build gnuplot \
    flex bison make wget git libwww-perl patch ccache libc6-dev-i386 libc6-dev jq cmake && \
    apt-get clean

RUN pip3 install jinja2 voluptuous

# RUN wget https://github.com/diffblue/cbmc/releases/download/cbmc-5.21.0/ubuntu-18.04-cbmc-5.21.0-Linux.deb
# RUN dpkg -i ubuntu-18.04-cbmc-5.21.0-Linux.deb

WORKDIR /home/
RUN git clone https://github.com/diffblue/cbmc.git
RUN cd cbmc && git checkout develop && \
    make DOWNLOADER='wget' -C src minisat2-download && \
    make -C src CXX=g++-10 -j8
RUN mkdir bin

WORKDIR /home/cbmc/bin
ENV CBMCSRCDIR=/home/cbmc/src
ENV USRBINPATH='/usr/bin'
RUN cp ${CBMCSRCDIR}/goto-analyzer/goto-analyzer ${USRBINPATH}
RUN cp ${CBMCSRCDIR}/goto-cc/goto-cc ${USRBINPATH}
RUN cp ${CBMCSRCDIR}/goto-instrument/goto-instrument ${USRBINPATH}
RUN cp ${CBMCSRCDIR}/goto-diff/goto-diff ${USRBINPATH}
RUN cp ${CBMCSRCDIR}/cbmc/cbmc ${USRBINPATH}
# ENV PATH="/home/cbmc/bin:${PATH}"

WORKDIR /home/
RUN rm -rf aws-c-common && git clone https://github.com/awslabs/aws-c-common.git
RUN cd aws-c-common/verification/cbmc && git checkout main && \
    git submodule init && git submodule update

WORKDIR /home/aws-c-common/verification/cbmc/proofs/scripts/
COPY scripts/run_aws_res.py .

WORKDIR /home/aws-c-common/verification/cbmc/proofs/