# icestorm Installation
FROM ubuntu:bionic
MAINTAINER Sven Braun <s.braun@mobileonly.com>
#EXPOSE 80 3306
RUN export DEBIAN_FRONTEND="noninteractive" && apt-get update  && apt-get -y install  build-essential autoconf sudo automake autotools-dev clang bison flex libreadline-dev libtool wget \
patchutils bc libexpat1-dev zlib1g-dev gawk tcl-dev libffi-dev git libmpc-dev libmpfr-dev libgmp-dev gawk texinfo gperf libtool mercurial \
graphviz xdot pkg-config python3 libftdi-dev php-cli curl gcc-arm-none-eabi telnet xxd cmake clang-format libpython3-dev qt5-default libboost-all-dev && \
cd /root && git clone https://github.com/cliffordwolf/icestorm.git icestorm && cd icestorm && make -j$(nproc) && make install && \
cd /root && git clone https://github.com/cseed/arachne-pnr.git arachne-pnr && cd arachne-pnr && make -j$(nproc) && make install  && \
cd /root && git clone https://github.com/cliffordwolf/yosys.git yosys && cd yosys && make -j$(nproc) && make install && \
cd /root && git clone https://github.com/cliffordwolf/icotools.git icotools && cd icotools && cd /root && \
cd /root && git clone https://github.com/YosysHQ/nextpnr.git nextpnr && cd nextpnr && cmake -DARCH=ice40  -DBUILD_PYTHON=OFF -DBUILD_GUI=OFF . && make && make install && cd /root && \
rm -Rf /root/icestorm && \
rm -Rf /root/yosys && \
rm -Rf /root/nextpnr && \
rm -Rf /root/arachne-pnr
