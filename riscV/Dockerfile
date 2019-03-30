# icestorm riscv32i build chain for ice40up5k
FROM ubuntu:bionic
MAINTAINER Sven Braun <s.braun@mobileonly.com>

# setup ubuntu and add ecp5
RUN export DEBIAN_FRONTEND="noninteractive" && apt-get update  && apt-get -y install  build-essential autoconf sudo automake autotools-dev clang bison flex libreadline-dev libtool wget \
patchutils bc libexpat1-dev zlib1g-dev gawk tcl-dev libffi-dev git libmpc-dev libmpfr-dev libgmp-dev gawk texinfo gperf libtool mercurial \
graphviz xdot pkg-config python3 libeigen3-dev libftdi-dev php-cli curl gcc-arm-none-eabi telnet xxd cmake clang-format libpython3-dev qt5-default libboost-all-dev && \
cd /root && git clone https://github.com/cliffordwolf/icestorm.git icestorm && cd icestorm && make -j$(nproc) && make install && \
cd /root && git clone https://github.com/cseed/arachne-pnr.git arachne-pnr && cd arachne-pnr && make -j$(nproc) && make install  && \
cd /root && git clone https://github.com/cliffordwolf/yosys.git yosys && cd yosys && make -j$(nproc) && make install && \
cd /root && git clone https://github.com/cliffordwolf/icotools.git icotools && cd icotools && cd /root && \
cd /root && git clone https://github.com/YosysHQ/nextpnr.git nextpnr && cd nextpnr && cmake -DARCH=ice40  -DBUILD_PYTHON=OFF -DBUILD_GUI=OFF . && make && make install && cd /root && \
rm -Rf /root/icestorm && \
rm -Rf /root/yosys && \
rm -Rf /root/nextpnr && \
rm -Rf /root/arachne-pnr

# add ecp5
RUN export DEBIAN_FRONTEND="noninteractive" && \
cd /root && git clone --recursive https://github.com/SymbiFlow/prjtrellis.git prjtrellis && cd prjtrellis/libtrellis && cmake -DCMAKE_INSTALL_PREFIX=/usr . && make && make install && \
cd /root && git clone https://github.com/YosysHQ/nextpnr.git nextpnr && cd nextpnr && cmake -DARCH=ecp5 -DBUILD_PYTHON=OFF -DBUILD_GUI=OFF -DTRELLIS_ROOT=/usr/share/trellis . && make && make install && cd /root && \
rm -Rf /root/nextpnr

# add riscv32i compiler
RUN mkdir /opt/riscv32i  && cd /root  && \
git clone https://github.com/riscv/riscv-gnu-toolchain riscv-gnu-toolchain-rv32i && \
cd riscv-gnu-toolchain-rv32i && \
git checkout 411d134 && \
git submodule update --init --recursive && \
mkdir build; cd build && \
../configure --with-arch=rv32i --prefix=/opt/riscv32i && \
make -j$(nproc) && \
cd /root && \
rm -Rf /root/riscv-gnu-toolchain-rv32i  


ENV PATH="/opt/riscv32i/bin:${PATH}"

