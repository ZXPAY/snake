PROJECT = snake
RELEASE  = true

CC      = gcc
OBJCOPY = objcopy
OBJDUMP = objdump
SIZE    = size
NM      = nm

OBJDIR = obj
VPATH = ./src test
DEP_DIR  = ./inc

CSRC  = main.c snake.c keyboard_interrupt.c
DEBUG = 0
OBJ = $(patsubst %.c, %.o, $(CSRC))
OBJ := $(addprefix $(OBJDIR)/, $(OBJ))
OBJDEASSEMBLY = $(patsubst %.c, %.s, $(CSRC))
OBJDEASSEMBLY := $(addprefix $(OBJDIR)/, $(OBJDEASSEMBLY))

TEST_CSRC = test_random.c
TEST_OBJDIR = test/obj
TEST_OBJ = $(patsubst %.c, %.o, $(TEST_CSRC))
TEST_OBJ := $(addprefix $(TEST_OBJDIR)/, $(TEST_OBJ))

CFLAGS  = -std=c99 -Wall -O0
CFLAGS += -g$(DEBUG)
CFLAGS += $(addprefix -I, $(DEP_DIR))
ifeq ($(RELEASE),true)
CFLAGS += -DNDEBUG
else
CFLAGS += -DDEBUG
endif

all: $(PROJECT).exe $(PROJECT).sym $(PROJECT).lst test
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

$(TEST_OBJ) : $(TEST_OBJDIR)/%.o : %.c
	@echo ===== Build $@ =====
	@echo compile $<
	$(CC) $(CFLAGS) -c $< -o $@

test: $(TEST_OBJ)
	$(CC) $(CFLAGS) $(TEST_OBJ) -o test/test_random.exe

clean:
	@echo
	rm -f -r $(OBJDIR) | exit 0
	rm -f -r $(TEST_OBJDIR) | exit 0
	rm -f *.exe

.PHONY: clean

# Include the dependency files.
-include $(shell mkdir $(OBJDIR) 2>/dev/null) $(wildcard $(OBJDIR)/*.d)
-include $(shell mkdir $(TEST_OBJDIR) 2>/dev/null) $(wildcard $(TEST_OBJDIR)/*.d)
