# Doppler_FPGA_Firmware


## build
The icestorm toolchain can be easy build with docker.
Docker its like a virtual machine.
The image contains a little linux with complete toolchain to
generate a bitstream for ice40 fpgas from verilog src code and also a arm compiler.
The bitstream will generate as binary and c header to 
include this in arduino/samd51 part.

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
This docker file contains the icestorm part and a compiler
for risc v when you want running a riscv mcu on the fpga.
```
git clone https://github.com/noscene/Doppler_FPGA_Firmware
cd Doppler_FPGA_Firmware
# this part need some times
docker build -t riscv  riscV/

#
export MOUNTPOINT=`pwd`
docker run -it -v $MOUNTPOINT:/PRJ riscv  bash
```


