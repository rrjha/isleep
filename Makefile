TARGET := isleep

# Set build machine env, default=ARM-Linux. Uncomment below for windows
#BUILDENV=Win
# gcc binaries to use
ifeq ($(BUILDENV),Win)
CC = "C:\gcc-linaro\bin\arm-linux-gnueabihf-gcc.exe"
LD = "C:\gcc-linaro\bin\arm-linux-gnueabihf-gcc.exe"
else
DTC = dtc
CC = gcc
LD = gcc
endif

# rm is part of yagarto-tools
REMOVE = rm -f

INCLUDES = ..
OBJDIR = src
DTBODIR = overlays

CFLAGS  += -O0 
CFLAGS  += -g 
CFLAGS  += -I.
CFLAGS  += -I$(INCLUDES)
LDFLAGS +=

SRC :=	src/accel.c \
	src/temp.c \
	src/bbbclient.c \
	libs/src/core.c \
	libs/src/spi.c

DTS :=	overlays/BB-SPI0-01-00A0.dts

OBJ := $(SRC:.c=.o)
DTBO := $(DTS:.dts=.dtbo)

# for a better output
MSG_EMPTYLINE = . 
MSG_COMPILING = ---COMPILE---
MSG_COMPILING_OVERLAY = ---COMPILE DT OVERLAY--- 
MSG_LINKING = ---LINK--- 
MSG_SUCCESS = ---SUCCESS--- 

all: $(TARGET) $(DTBO)
.PHONY: all

# Link
$(TARGET): $(OBJ)
	@echo $(MSG_EMPTYLINE)
	@echo $(MSG_LINKING)
	$(LD) -o $@ $^ $(LDFLAGS)
	@echo $(MSG_EMPTYLINE)

# Compile
.c.o:
	@echo $(MSG_EMPTYLINE)
	@echo $(MSG_COMPILING) $<
	$(CC) -c -o $@ $< $(CFLAGS)

%.dtbo: %.dts
	@echo $(MSG_EMPTYLINE)
	@echo $(MSG_COMPILING_OVERLAY) $<
	$(DTC) -O dtb -o $@ -b 0 -@ $<
	@echo $(MSG_SUCCESS) $(PROJECT)

.PHONY: clean
clean:
	$(REMOVE) $(OBJDIR)/*.o $(DTBODIR)/*.dtbo $(TARGET)

