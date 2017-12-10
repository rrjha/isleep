TARGET := isleep

# Set build machine env, default=ARM-Linux. Uncomment below for windows
#BUILDENV=Win
# gcc binaries to use
ifeq ($(BUILDENV),Win)
CC = "C:\gcc-linaro\bin\arm-linux-gnueabihf-gcc.exe"
LD = "C:\gcc-linaro\bin\arm-linux-gnueabihf-gcc.exe"
else
CC = gcc
LD = gcc
endif

# rm is part of yagarto-tools
REMOVE = rm -f

INCLUDES = ..
OBJDIR = src

CFLAGS  += -O0 
CFLAGS  += -g 
CFLAGS  += -I.
CFLAGS  += -I$(INCLUDES)
LDFLAGS +=


SRC := src/accel.c \
    src/temp.c
    src/glue.c

OBJ := $(SRC:.c=.o)

# for a better output
MSG_EMPTYLINE = . 
MSG_COMPILING = ---COMPILE--- 
MSG_LINKING = ---LINK--- 
MSG_SUCCESS = ---SUCCESS--- 

all: $(TARGET)
.PHONY: all

# Link
$(TARGET): $(OBJ)
    @echo $(MSG_EMPTYLINE)
    @echo $(MSG_LINKING)
    $(LD) -o $@ $^ $(LDFLAGS)
    @echo $(MSG_EMPTYLINE)
    @echo $(MSG_SUCCESS) $(PROJECT)

# Compile
.cpp.o:
    @echo $(MSG_EMPTYLINE)
    @echo $(MSG_COMPILING) $<
    $(CC) -c -o $@ $< $(CFLAGS)

.PHONY: clean
clean:
    $(REMOVE) $(OBJDIR)/*.o $(TARGET)

