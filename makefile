PROJECT = snake

CC      = gcc
OBJCOPY = objcopy
OBJDUMP = objdump
SIZE    = size
NM      = nm

OBJDIR = obj
VPATH = ./src
DEP_DIR  = ./inc

CSRC  = snake.c keyboard_interrupt.c
DEBUG	= 0
OBJ = $(patsubst %.c, %.o, $(CSRC))
OBJ := $(addprefix $(OBJDIR)/, $(OBJ))
OBJDEASSEMBLY = $(patsubst %.c, %.s, $(CSRC))
OBJDEASSEMBLY := $(addprefix $(OBJDIR)/, $(OBJDEASSEMBLY))

CFLAGS  = -std=c99 -Wall -O0
CFLAGS += -g$(DEBUG)
CFLAGS += $(addprefix -I, $(DEP_DIR))

all: $(PROJECT).exe $(PROJECT).sym $(PROJECT).lst
	@echo complete

%.exe : $(OBJ)
	@echo ===== Build $@ =====
	$(CC) $(CFLAGS) $(OBJ) -o $@
	rm $(OBJ)
	@echo ===== Done =====

$(OBJ) : $(OBJDIR)/%.o : %.c
	@echo ===== Build $@ =====
	@echo compile $<
	$(CC) $(CFLAGS) -c $< -o $@

%.sym: %.exe
	@echo
	$(NM) -n $< > $(OBJDIR)/$@

%.lst: %.exe
	@echo
	$(OBJDUMP) -D $< > $(OBJDIR)/$@

test:
	@echo $(CSRC)
	@echo $(OBJ)
	@echo $(CFLAGS)

clean:
	@echo
	rm -f -r $(OBJDIR) | exit 0
	rm -f *.exe

.PHONY: clean

# Include the dependency files.
-include $(shell mkdir $(OBJDIR) 2>/dev/null) $(wildcard $(OBJDIR)/*.d)
