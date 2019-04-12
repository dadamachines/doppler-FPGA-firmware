PROJ = doppler_4x4led_pwm
PIN_DEF = doppler_4x4led_pwm.pcf
DEVICE = up5k

all: $(PROJ).rpt $(PROJ).bin header copyheader

%.blif: %.v
	yosys -v 3 -p 'synth_ice40  -top top -blif $@' $<

%.asc: $(PIN_DEF) %.blif
	arachne-pnr -d 5k  -o $@ -p $^ -P sg48

header: $(PROJ).bin
	cp $(PROJ).bin bitstream.bin
	xxd -c 32 -i bitstream.bin  > $(PROJ).h
	sed -i -r 's/unsigned/const unsigned/g' $(PROJ).h
	#cp $(PROJ).blif $(PROJ)_.blif

copyheader: $(PROJ).h
	cp $(PROJ).h ./Plasma/bitstream.h

%.bin: %.asc
	icepack $< $@

%.rpt: %.asc
	icetime -d $(DEVICE) -mtr $@ $<

clean:
	rm -f $(PROJ).blif $(PROJ).asc $(PROJ).rpt $(PROJ).bin $(PROJ).h

.PHONY: all prog clean
