# Doppler_FPGA_Firmware


## build
the icestorm toolchain can be easy build with docker.

```
git clone https://github.com/noscene/Doppler_FPGA_Firmware
cd Doppler_FPGA_Firmware/doppler_simple_io
# this part need some times
docker build -t icestorm  icestorm/

#
export MOUNTPOINT=`pwd`
docker run -it -v $MOUNTPOINT:/PRJ icestorm  bash
```

now we are in the container

```
cd PRJ/doppler_simple_io/
make
ls -l
```

now we have this bitstream doppler_simple_io.bin and also
as header doppler_simple_io.h


## build with risc-v support

```
git clone https://github.com/noscene/Doppler_FPGA_Firmware
cd Doppler_FPGA_Firmware
# this part need some times
docker build -t riscv  riscv/

#
export MOUNTPOINT=`pwd`
docker run -it -v $MOUNTPOINT:/PRJ riscv  bash
export PATH=/opt/riscv32i/bin:$PATH
```


