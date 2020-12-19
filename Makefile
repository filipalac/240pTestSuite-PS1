CDLIC_FILE = /usr/local/psxsdk/share/licenses/infousa.dat

all: lz4compress audio tim compress_textures bin2c
	psx-gcc  -Wall -O3 -o 240p.elf 240p.c patterns.c tests.c font.c lz4.c textures.c help.c sg_string.c
	elf2exe 240p.elf 240p.exe
	cp 240p.exe binary
	systemcnf 240p.exe > binary/system.cnf
	mkisofs -o ./binary/240p.hsf -V 240pTestSuite -sysid PLAYSTATION binary
	cd ./binary && mkpsxiso 240p.hsf 240pTestSuitePS1-EMU.bin $(CDLIC_FILE);
	rm -f ./binary/240p.hsf
	rm -f 240p.elf
	rm -f 240p.exe
	###################
	psx-gcc  -Wall -O3 -DREAL_HW -o 240p.elf 240p.c patterns.c tests.c font.c lz4.c textures.c help.c sg_string.c
	elf2exe 240p.elf 240p.exe
	cp 240p.exe binary
	systemcnf 240p.exe > binary/system.cnf
	mkisofs -o ./binary/240p.hsf -V 240pTestSuite -sysid PLAYSTATION binary
	cd ./binary && mkpsxiso 240p.hsf 240pTestSuitePS1.bin $(CDLIC_FILE);
	rm -f ./binary/240p.hsf
	rm -f ./binary/240p.exe
	rm -f ./binary/system.cnf
	rm -f ./240p.elf
	rm -f ./240p.exe

lz4compress:
	gcc -Wall -O3 -o ./tools/lz4compress ./tools/lz4compress.c ./lz4.c ./lz4hc.c
audio:
	wav2vag ./resources/beep.wav ./resources/beep.raw -raw
tim:
	bmp2tim ./textures/grid224.bmp ./patterns/grid224.tim 4 -org=320,0 -noblack -clut=912,480
	bmp2tim textures/grid240.bmp patterns/grid240.tim 4 -org=448,0 -noblack -clut=912,481
	bmp2tim textures/grid256.bmp patterns/grid256.tim 4 -org=576,0 -noblack -clut=912,482
	bmp2tim textures/gridw256224.bmp patterns/gridw256224.tim 4 -org=320,0 -noblack -clut=912,480
	bmp2tim textures/gridw256240.bmp patterns/gridw256240.tim 4 -org=448,0 -noblack -clut=912,481
	bmp2tim textures/gridw256256.bmp patterns/gridw256256.tim 4 -org=576,0 -noblack -clut=912,482
	bmp2tim textures/SMPTE100.bmp patterns/SMPTE100.tim 4 -org=320,0 -clut=912,480
	bmp2tim textures/SMPTE75.bmp patterns/SMPTE75.tim 4 -org=640,0   -clut=912,481
	bmp2tim textures/EBU100.bmp patterns/EBU100.tim 4 -org=320,0 -clut=912,480
	bmp2tim textures/EBU75.bmp patterns/EBU75.tim 4 -org=640,0 -clut=912,481
	bmp2tim textures/colorgray.bmp patterns/colorgray.tim 4 -org=320,0 -clut=912,480
	bmp2tim textures/colorbleed.bmp patterns/colorbleed.tim 4 -org=640,256 -clut=912,480
	bmp2tim textures/colorbleedchk.bmp patterns/colorbleedchk.tim 4 -org=640,0 -clut=912,481
	bmp2tim textures/color.bmp patterns/color.tim 8 -org=320,0 -clut=768,485
	bmp2tim textures/colorgrid.bmp patterns/colorgrid.tim 8 -org=640,0 -clut=768,486
	bmp2tim textures/colorgridw256.bmp patterns/colorgridw256.tim 8 -org=640,0 -clut=768,486
	bmp2tim textures/pluge.bmp patterns/pluge.tim 4 -org=320,0 -clut=912,480
	bmp2tim textures/linearity.bmp patterns/linearity.tim 4 -org=320,0 -noblack -clut=912,480
	bmp2tim textures/linearity224.bmp patterns/linearity224.tim 4 -org=448,0 -noblack -clut=912,481
	bmp2tim textures/linearity240pal.bmp patterns/linearity240pal.tim 4 -org=576,0 -noblack -clut=912,483
	bmp2tim textures/linearityw256224.bmp patterns/linearityw256224.tim 4 -org=448,0 -noblack -clut=912,481
	bmp2tim textures/linearityw256224pal.bmp patterns/linearityw256224pal.tim 4 -org=576,0 -noblack -clut=912,483
	bmp2tim textures/linearitygriddot.bmp patterns/linearitygriddot.tim 4 -org=1000,256 -noblack -clut=912,482
	bmp2tim textures/grayramp.bmp patterns/grayramp.tim 8 -org=320,0 -clut=768,480
	bmp2tim textures/sharpness.bmp patterns/sharpness.tim 4 -org=320,0 -clut=912,480
	bmp2tim textures/sharpness224.bmp patterns/sharpness224.tim 4 -org=448,0 -clut=912,481
	bmp2tim textures/sharpnessw256224.bmp patterns/sharpnessw256224.tim 4 -org=448,0 -clut=912,481
	bmp2tim textures/sharpnessw256240.bmp patterns/sharpnessw256240.tim 4 -org=320,0 -clut=912,480
	bmp2tim textures/lingrid.bmp patterns/lingrid.tim 4 -org=704,0 -noblack -clut=912,487
	bmp2tim textures/checkerboard.bmp patterns/checkerboard.tim 4 -org=896,256  -clut=912,480
	bmp2tim textures/circle.bmp patterns/circle.tim 4 -org=320,0  -noblack -clut=912,480
	bmp2tim textures/numbers.bmp patterns/numbers.tim 4 -org=640,0 -mpink -clut=912,484
	#############################
	bmp2tim textures/sonicsky.bmp patterns/sonicsky.tim 4 -org=832,256  -clut=912,499
	bmp2tim textures/sonicback1.bmp patterns/sonicback1.tim 4 -org=640,0  -clut=912,481
	bmp2tim textures/sonicback2.bmp patterns/sonicback2.tim 4 -org=640,128  -clut=912,482
	bmp2tim textures/sonicback3.bmp patterns/sonicback3.tim 4 -org=640,256  -clut=912,483
	bmp2tim textures/sonicback4.bmp patterns/sonicback4.tim 4 -org=640,384  -clut=912,484
	#############################
	bmp2tim textures/sonicfloor.bmp patterns/sonicfloor.tim 4 -org=768,256 -noblack -clut=912,485
	bmp2tim textures/kiki.bmp patterns/kiki.tim 4 -org=704,0 -clut=912,486
	bmp2tim textures/motoko.bmp patterns/motoko.tim 8 -org=768,0 -clut=768,480
	bmp2tim textures/striped.bmp patterns/striped.tim 4 -org=1016,424 -mpink -clut=912,487
	bmp2tim textures/buzzbomber.bmp patterns/buzzbomber.tim 4 -org=1004,384 -mpink -clut=912,490
	bmp2tim textures/buzzbombershadow.bmp patterns/buzzbombershadow.tim 4 -org=1016,384 -mpink -clut=912,491
	bmp2tim textures/shadow.bmp patterns/shadow.tim 4 -org=1004,424 -mpink -clut=912,492
	bmp2tim textures/convergence.bmp patterns/convergence.tim 4 -org=320,0 -noblack -clut=912,490
	bmp2tim textures/font.bmp patterns/font.tim 4 -mpink -org=960,256  -clut=960,321
	bmp2tim textures/lagper.bmp patterns/lagper.tim 4 -mpink -org=992,424  -clut=912,490
	bmp2tim textures/back.bmp patterns/back.tim 4 -org=944,0  -clut=960,510
	bmp2tim textures/backw256.bmp patterns/backw256.tim 4 -org=960,0  -clut=960,510
	bmp2tim textures/gillian.bmp patterns/gillian.tim 4 -org=1008,256 -mpink -clut=960,511
compress_textures:
	./tools/lz4compress ./patterns/grid224.tim ./patterns/grid224.lz4
	./tools/lz4compress ./patterns/grid240.tim ./patterns/grid240.lz4
	./tools/lz4compress ./patterns/grid256.tim ./patterns/grid256.lz4
	./tools/lz4compress ./patterns/gridw256224.tim ./patterns/gridw256224.lz4
	./tools/lz4compress ./patterns/gridw256240.tim ./patterns/gridw256240.lz4
	./tools/lz4compress ./patterns/gridw256256.tim ./patterns/gridw256256.lz4
	./tools/lz4compress ./patterns/SMPTE100.tim ./patterns/SMPTE100.lz4
	./tools/lz4compress ./patterns/SMPTE75.tim ./patterns/SMPTE75.lz4
	./tools/lz4compress ./patterns/EBU100.tim ./patterns/EBU100.lz4
	./tools/lz4compress ./patterns/EBU75.tim ./patterns/EBU75.lz4
	./tools/lz4compress ./patterns/colorgray.tim ./patterns/colorgray.lz4
	./tools/lz4compress ./patterns/colorbleed.tim ./patterns/colorbleed.lz4
	./tools/lz4compress ./patterns/colorbleedchk.tim ./patterns/colorbleedchk.lz4
	./tools/lz4compress ./patterns/color.tim ./patterns/color.lz4
	./tools/lz4compress ./patterns/colorgrid.tim ./patterns/colorgrid.lz4
	./tools/lz4compress ./patterns/colorgridw256.tim ./patterns/colorgridw256.lz4
	./tools/lz4compress ./patterns/pluge.tim ./patterns/pluge.lz4
	./tools/lz4compress ./patterns/linearity.tim ./patterns/linearity.lz4
	./tools/lz4compress ./patterns/linearity224.tim ./patterns/linearity224.lz4
	./tools/lz4compress ./patterns/linearity240pal.tim ./patterns/linearity240pal.lz4
	./tools/lz4compress ./patterns/linearityw256224.tim ./patterns/linearityw256224.lz4
	./tools/lz4compress ./patterns/linearityw256224pal.tim ./patterns/linearityw256224pal.lz4
	./tools/lz4compress ./patterns/linearitygriddot.tim ./patterns/linearitygriddot.lz4
	./tools/lz4compress ./patterns/grayramp.tim ./patterns/grayramp.lz4
	./tools/lz4compress ./patterns/sharpness.tim ./patterns/sharpness.lz4
	./tools/lz4compress ./patterns/sharpness224.tim ./patterns/sharpness224.lz4
	./tools/lz4compress ./patterns/sharpnessw256240.tim ./patterns/sharpnessw256240.lz4
	./tools/lz4compress ./patterns/sharpnessw256224.tim ./patterns/sharpnessw256224.lz4
	./tools/lz4compress ./patterns/lingrid.tim ./patterns/lingrid.lz4
	./tools/lz4compress ./patterns/checkerboard.tim ./patterns/checkerboard.lz4
	./tools/lz4compress ./patterns/sonicsky.tim ./patterns/sonicsky.lz4
	./tools/lz4compress ./patterns/sonicsky.tim ./patterns/sonicsky.lz4
	./tools/lz4compress ./patterns/sonicback1.tim ./patterns/sonicback1.lz4
	./tools/lz4compress ./patterns/sonicback2.tim ./patterns/sonicback2.lz4
	./tools/lz4compress ./patterns/sonicback3.tim ./patterns/sonicback3.lz4
	./tools/lz4compress ./patterns/sonicback4.tim ./patterns/sonicback4.lz4
	./tools/lz4compress ./patterns/sonicfloor.tim ./patterns/sonicfloor.lz4
	./tools/lz4compress ./patterns/kiki.tim ./patterns/kiki.lz4
	./tools/lz4compress ./patterns/motoko.tim ./patterns/motoko.lz4
	./tools/lz4compress ./patterns/striped.tim ./patterns/striped.lz4
	./tools/lz4compress ./patterns/buzzbomber.tim ./patterns/buzzbomber.lz4
	./tools/lz4compress ./patterns/buzzbombershadow.tim ./patterns/buzzbombershadow.lz4
	./tools/lz4compress ./patterns/shadow.tim ./patterns/shadow.lz4
	./tools/lz4compress ./patterns/font.tim ./patterns/font.lz4
	./tools/lz4compress ./patterns/circle.tim ./patterns/circle.lz4
	./tools/lz4compress ./patterns/numbers.tim ./patterns/numbers.lz4
	./tools/lz4compress ./patterns/lagper.tim ./patterns/lagper.lz4
	./tools/lz4compress ./patterns/back.tim ./patterns/back.lz4
	./tools/lz4compress ./patterns/backw256.tim ./patterns/backw256.lz4
	./tools/lz4compress ./patterns/gillian.tim ./patterns/gillian.lz4
	./tools/lz4compress ./patterns/convergence.tim ./patterns/convergence.lz4
bin2c:
	bin2c grid224 < patterns/grid224.lz4 > ./patterns/grid224.c
	bin2c grid240 < patterns/grid240.lz4 > ./patterns/grid240.c
	bin2c grid256 < patterns/grid256.lz4 > ./patterns/grid256.c
	bin2c gridw256224 < patterns/gridw256224.lz4 > ./patterns/gridw256224.c
	bin2c gridw256240 < patterns/gridw256240.lz4 > ./patterns/gridw256240.c
	bin2c gridw256256 < patterns/gridw256256.lz4 > ./patterns/gridw256256.c
	bin2c SMPTE100 < patterns/SMPTE100.lz4 > ./patterns/SMPTE100.c
	bin2c SMPTE75 < patterns/SMPTE75.lz4 > ./patterns/SMPTE75.c
	bin2c EBU100 < patterns/EBU100.lz4 > ./patterns/EBU100.c
	bin2c EBU75 < patterns/EBU75.lz4 > ./patterns/EBU75.c
	bin2c colorgray < patterns/colorgray.lz4 > ./patterns/colorgray.c
	bin2c colorbleed < patterns/colorbleed.lz4 > ./patterns/colorbleed.c
	bin2c colorbleedchk < patterns/colorbleedchk.lz4 > ./patterns/colorbleedchk.c
	bin2c color < patterns/color.lz4 > ./patterns/color.c
	bin2c colorgrid < patterns/colorgrid.lz4 > ./patterns/colorgrid.c
	bin2c colorgridw256 < patterns/colorgridw256.lz4 > ./patterns/colorgridw256.c
	bin2c pluge < patterns/pluge.lz4 > ./patterns/pluge.c
	bin2c linearity < patterns/linearity.lz4 > ./patterns/linearity.c
	bin2c linearity224 < patterns/linearity224.lz4 > ./patterns/linearity224.c
	bin2c linearity240pal < patterns/linearity240pal.lz4 > ./patterns/linearity240pal.c
	bin2c linearityw256224 < patterns/linearityw256224.lz4 > ./patterns/linearityw256224.c
	bin2c linearityw256224pal < patterns/linearityw256224pal.lz4 > ./patterns/linearityw256224pal.c
	bin2c linearitygriddot < patterns/linearitygriddot.lz4 > ./patterns/linearitygriddot.c
	bin2c grayramp < patterns/grayramp.lz4 > ./patterns/grayramp.c
	bin2c sharpness < patterns/sharpness.lz4 > ./patterns/sharpness.c
	bin2c sharpness224 < patterns/sharpness224.lz4 > ./patterns/sharpness224.c
	bin2c sharp256240 < patterns/sharpnessw256240.lz4 > ./patterns/sharpnessw256240.c
	bin2c sharp256224 < patterns/sharpnessw256224.lz4 > ./patterns/sharpnessw256224.c
	bin2c lingrid < patterns/lingrid.lz4 > ./patterns/lingrid.c
	bin2c checkerboard < patterns/checkerboard.lz4 > ./patterns/checkerboard.c
	bin2c sonicsky < patterns/sonicsky.lz4 > ./patterns/sonicsky.c
	bin2c sonicback1 < patterns/sonicback1.lz4 > ./patterns/sonicback1.c
	bin2c sonicback2 < patterns/sonicback2.lz4 > ./patterns/sonicback2.c
	bin2c sonicback3 < patterns/sonicback3.lz4 > ./patterns/sonicback3.c
	bin2c sonicback4 < patterns/sonicback4.lz4 > ./patterns/sonicback4.c
	bin2c sonicfloor < patterns/sonicfloor.lz4 > ./patterns/sonicfloor.c
	bin2c kiki < patterns/kiki.lz4 > ./patterns/kiki.c
	bin2c motoko < patterns/motoko.lz4 > ./patterns/motoko.c
	bin2c striped < patterns/striped.lz4 > ./patterns/striped.c
	bin2c buzzbomber < patterns/buzzbomber.lz4 > ./patterns/buzzbomber.c
	bin2c buzzbombershadow < patterns/buzzbombershadow.lz4 > ./patterns/buzzbombershadow.c
	bin2c shadow < patterns/shadow.lz4 > ./patterns/shadow.c
	bin2c font < patterns/font.lz4 > ./patterns/font.c
	bin2c circle < patterns/circle.lz4 > ./patterns/circle.c
	bin2c numbers < patterns/numbers.lz4 > ./patterns/numbers.c
	bin2c lagper < patterns/lagper.lz4 > ./patterns/lagper.c
	bin2c back < patterns/back.lz4 > ./patterns/back.c
	bin2c backw256 < patterns/backw256.lz4 > ./patterns/backw256.c
	bin2c beep < resources/beep.raw> ./resources/beep.h
	bin2c gillian < patterns/gillian.lz4> ./patterns/gillian.c
	bin2c convergence < patterns/convergence.lz4> ./patterns/convergence.c

emulator: lz4compress audio tim compress_textures bin2c
	psx-gcc  -Wall -O3 -o 240p.elf 240p.c patterns.c tests.c font.c lz4.c textures.c help.c sg_string.c
	elf2exe 240p.elf 240p.exe
	cp 240p.exe binary
	systemcnf 240p.exe > binary/system.cnf
	mkisofs -o ./binary/240p.hsf -V 240pTestSuite -sysid PLAYSTATION binary
	cd ./binary && mkpsxiso 240p.hsf 240pTestSuitePS1-EMU.bin $(CDLIC_FILE);
	rm -f ./binary/240p.hsf
	rm -f 240p.elf
	rm -f 240p.exe

psx: lz4compress audio tim compress_textures bin2c
	psx-gcc  -Wall -O3 -DREAL_HW -o 240p.elf 240p.c patterns.c tests.c font.c lz4.c textures.c help.c sg_string.c
	elf2exe 240p.elf 240p.exe
	cp 240p.exe binary
	systemcnf 240p.exe > binary/system.cnf
	mkisofs -o ./binary/240p.hsf -V 240pTestSuite -sysid PLAYSTATION binary
	cd ./binary && mkpsxiso 240p.hsf 240pTestSuitePS1.bin $(CDLIC_FILE);
	rm -f ./binary/240p.hsf
	rm -f 240p.elf
	rm -f 240p.exe

clean:
	rm -f 240pTestSuitePS1.bin 240pTestSuitePS1.cue 240p.exe 240p.elf
	rm -r binary/*
	rm -r patterns/*
