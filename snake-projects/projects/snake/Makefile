######################################
# target
######################################
TARGET = $(shell basename $(CURDIR))

# default platform
PLATFORM ?= rpi_hat

# default action: build all
all: bin

######################################
# building variables
######################################
# debug build?
DEBUG = 1

# optimization
OPT =

#######################################
# paths
#######################################
# Build path
OUTPUT 	:= output

# define platform-independent code directory
COMMON  := common

# define platform-dependent code directory
PORT	:= port

# define drivers directory
DRIVERS	:= ../../drivers

ifeq ($(OS),Windows_NT)
FIXPATH = $(subst /,\,$1)
RM	:= rm -rf
MD	:= mkdir
else
FIXPATH = $1
RM 	:= rm -rf
MD	:= mkdir -p
endif

CFLAGS   = 
LDFLAGS  = 
ASFLAGS  = 
INCLUDES :=
AS_INCLUDES =
SOURCES  =
AS_SOURCES =

######################################
# source
######################################
# define the C source files
ifdef SAMPLE_FILE
include $(COMMON)/Makefile.sample
else
include $(COMMON)/Makefile.common
endif

# PORTS
include $(PORT)/$(PLATFORM)/Makefile.port

#######################################
# binaries
#######################################
# The gcc compiler bin path can be either defined in make command via GCC_PATH variable (> make GCC_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef GCC_PATH
CC = $(GCC_PATH)/$(PREFIX)gcc
AS = $(GCC_PATH)/$(PREFIX)gcc -x assembler-with-cpp
CP = $(GCC_PATH)/$(PREFIX)objcopy
SZ = $(GCC_PATH)/$(PREFIX)size
else
CC = $(PREFIX)gcc
AS = $(PREFIX)gcc -x assembler-with-cpp
CP = $(PREFIX)objcopy
SZ = $(PREFIX)size
endif
HEX = $(CP) -O ihex
BIN = $(CP) -O binary -S
 
#######################################
# CFLAGS
#######################################
ASFLAGS +=  $(AS_DEFS) $(AS_INCLUDES) $(OPT) -Wall -fdata-sections -ffunction-sections
CFLAGS += $(C_DEFS) $(INCLUDES) $(OPT) -Wall -Wno-unused-parameter -Wno-unused-function -Werror -Wextra -fdata-sections -ffunction-sections

#######################################
# INCLUDES
#######################################
# compile gcc flags

ifeq ($(DEBUG), 1)
CFLAGS += -g -gdwarf-2
endif

# Generate dependency information
CFLAGS += -MMD -MP -MF"$(@:%.o=%.d)"

#######################################
# build the application
#######################################
# list of objects
OBJECTS = $(addprefix $(OUTPUT)/,$(notdir $(SOURCES:.c=.o)))
vpath %.c $(sort $(dir $(SOURCES)))

# list of ASM program objects
OBJECTS += $(addprefix $(OUTPUT)/,$(notdir $(AS_SOURCES:.s=.o)))
vpath %.s $(sort $(dir $(AS_SOURCES)))

$(OUTPUT)/%.o: %.c Makefile | $(OUTPUT) 
	$(MD) $@.f
	$(RM) $@.f
	$(CC) -c $(CFLAGS) $< -o $@

$(OUTPUT)/%.o: %.s Makefile | $(OUTPUT)
	$(AS) -c $(CFLAGS) $< -o $@

$(OUTPUT):
	mkdir $@

$(OUTPUT)/$(TARGET)$(EXT): $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

#######################################
# dependencies
#######################################
-include $(wildcard $(OUTPUT)/*.d)

.PHONY: clean
#######################################
# clean up
#######################################
clean:
	$(RM) $(OUTPUT)
	@echo Cleanup complete!
