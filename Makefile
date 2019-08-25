# Main Makefile
# Author: Michal Kukowski
# email: michalkukowski10@gmail.com

# Shell settings
MV    := mv
RM    := rm -rf
CP    := cp 2>/dev/null
AR    := ar rcs
WC    := wc
BC    := bc
GREP  := grep -q
AWK   := awk
MKDIR := mkdir -p

# Compiler settings
CC          ?= gcc

CC_STD      := -std=c99
CC_OPT      := -O3
CC_WARNINGS := -Wall -Wextra -pedantic -Wcast-align \
               -Winit-self -Wmissing-include-dirs \
               -Wredundant-decls -Wshadow -Wstrict-overflow=5 -Wundef  \
               -Wwrite-strings -Wpointer-arith -Wmissing-declarations \
               -Wuninitialized -Wold-style-definition -Wstrict-prototypes \
               -Wmissing-prototypes -Wswitch-default -Wbad-function-cast \
               -Wnested-externs -Wconversion -Wunreachable-code \


ifeq ($(CC),gcc)
CC_SYM      := -rdynamic
else ifeq ($(CC),clang)
CC_SYM      := -Wl,--export-dynamic
CC_WARNINGS += -Wgnu -Weverything -Wno-unused-command-line-argument -Wno-newline-eof -Wno-reserved-id-macro \
               -Wno-documentation -Wno-documentation-unknown-command -Wno-padded
endif

CC_FLAGS      := $(CC_STD) $(CC_WARNINGS) -Werror $(CC_OPT) $(CC_SYM)

PROJECT_DIR := $(shell pwd)

# Global directories
DIR_APP  := $(PROJECT_DIR)/app
DIR_SRC  := $(PROJECT_DIR)/src
DIR_INC  := $(PROJECT_DIR)/inc

# Verbose mode
ifeq ("$(origin V)", "command line")
    VERBOSE = $(V)
endif

ifndef VERBOSE
    VERBOSE = 0
endif

ifeq ($(VERBOSE),1)
    Q =
else
    Q = @
endif

# DEBUG MODE
ifeq ("$(origin D)", "command line")
    CC_FLAGS += -ggdb
endif

# Print functions
define print_info
    $(if $(Q), @echo "$(1)")
endef

define print_make
    $(if $(Q), @echo "[MAKE]        $(1)")
endef

define print_cc
    $(if $(Q), @echo "[CC]          $(1)")
endef

define print_bin
    $(if $(Q), @echo "[BIN]         $(1)")
endef

# Files
EXEC := main.out
SRC  := $(wildcard $(DIR_SRC)/*.c) $(wildcard $(DIR_APP)/*.c)
INC  := $(wildcard $(DIR_INC)/*.h)
OBJ  := $(SRC:%.c=%.o)

# PATHS
HEADERS := -I $(DIR_INC)
LIBS :=

# COMPILING
%.o: %.c $(INC)
	$(call print_cc,$<)
	$(Q)$(CC) $(CC_FLAGS) $(HEADERS) -c $< -o $@

all: $(EXEC)

.PHONY:$(EXEC)
$(EXEC): $(SRC) $(INC) $(OBJ)
	$(call print_bin,$@)
	$(Q)$(CC) $(CC_FLAGS) $(HEADERS) $(LIBS) $(OBJ) -o $@

.PHONY:clean
clean:
	$(call print_info,Cleaning)
	$(Q)$(RM) $(OBJ)
	$(Q)$(RM) $(EXEC)