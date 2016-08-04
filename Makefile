TITLE_ID = MEMCRDSWP
TARGET = memcardswap
OBJS   = main.o

LIBS = 

PREFIX  = arm-vita-eabi
CC      = $(PREFIX)-gcc
CFLAGS  = -Wl,-q -Wall -O3
ASFLAGS = $(CFLAGS)

all: $(TARGET).vpk

%.vpk: eboot.bin
	vita-mksfoex -s TITLE_ID=$(TITLE_ID) "$(TARGET)" param.sfo
	vita-pack-vpk -s param.sfo -b eboot.bin $@

eboot.bin: $(TARGET).velf
	vita-make-fself $< eboot.bin

%.velf: %.elf
	vita-elf-create $< $@

%.elf: $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

clean:
	@rm -rf *.velf *.elf *.vpk $(OBJS) param.sfo eboot.bin
