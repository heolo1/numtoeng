# generic makefile i made to drag into basically any tiny project i have

define DIR_RULE
./$1/:
	mkdir -p $$@
endef

# $1 is the full relative path, $2 is compiler, $3 is any includes
define SRC_RULE
-include $(BLD_DIR)/$1.d
$(BLD_DIR)/$1.o: $1 | $(BLD_DIR)/$(shell dirname $1)/
	$($2) -I$(INCL_DIR) $(addprefix -I,$3) -c -MMD -MF $(BLD_DIR)/$1.d -o $$@ $$< $($(2)FLAGS)
endef

# $1 is dir, $2 is ext
define GET_FILES
$(shell find $1 -type f -not -path "*/.*" -name "*.$2")
endef

SHELL     := /bin/sh
CC        := gcc
CPPFLAGS  := -Wall -pedantic -Ofast
CCFLAGS   := $(CPPFLAGS) -std=c17
PRJ_NAME  := $(notdir $(abspath .))

SRC_DIR   := ./src
INCL_DIR  := ./include
BLD_DIR   := ./build
BIN_DIR   := ./bin

TARGET    := $(BIN_DIR)/$(PRJ_NAME)

SRCS     := $(call GET_FILES,$(SRC_DIR),c)
SRC_DIRS  := $(shell dirname $(SRCS) | sort -u)

# for now, we just assume that each main contains some header files and some source files, and that they are not indexed into a src and include directory.

.SUFFIXES: .cpp .hpp .o .d .a
.PHONY: all clean run test

all: $(TARGET)

test:

clean:
	- rm -rf ./$(BLD_DIR) ./$(BIN_DIR)

$(eval $(call DIR_RULE,$(BIN_DIR)))
$(foreach DIR,$(SRC_DIRS),$(eval $(call DIR_RULE,$(BLD_DIR)/$(DIR))))
$(foreach SRC,$(SRCS),$(eval $(call SRC_RULE,$(SRC),CC)))

$(TARGET): $(patsubst %,$(BLD_DIR)/%.o,$(SRCS)) | $(dir $(TARGET))
	$(CC) -o $@ $^ $(CCFLAGS)

run: $(TARGET)
	@ $<