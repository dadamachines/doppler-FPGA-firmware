PROJ = FMTransmitter
PIN_DEF = FMTransmitter.pcf
DEVICE = up5k

all: $(PROJ).rpt $(PROJ).bin header

%.blif: %.v

	yosys -v 3 -p 'synth_ice40  -top top -blif $@' $<

%.asc: $(PIN_DEF) %.blif
	arachne-pnr -d 5k  -o $@ -p $^ -P sg48

header: $(PROJ).bin
	xxd -i $(PROJ).bin  > $(PROJ).h
	sed -i -r 's/unsigned/const unsigned/g' $(PROJ).h
	#cp $(PROJ).blif $(PROJ)_.blif

%.bin: %.asc
	icepack $< $@

%.rpt: %.asc
	icetime -d $(DEVICE) -mtr $@ $<

prog: $(PROJ).bin
	#iCEburn.py  -e -v -w  $<
	curl -F file=@FMTransmitter.bin http://10.0.1.40/fupload 

sudo-prog: $(PROJ).bin
	@echo 'Executing prog as root!!!'
	iCEburn.py  -e -v -w  $<

clean:
	rm -f $(PROJ).blif $(PROJ).asc $(PROJ).rpt $(PROJ).bin $(PROJ).h

.PHONY: all prog clean
