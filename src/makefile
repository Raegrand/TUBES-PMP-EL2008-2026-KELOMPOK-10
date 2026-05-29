CC       := gcc
CFLAGS   := -g -Wall -Iheader

# Where to put .o files
BUILDDIR := build

# Source files (in top-level and c/ subdir)
SRCS     := $(wildcard *.c) $(wildcard c/*.c) $(wildcard c/ADT/*.c)

# Object files go under build/, preserving subdirs
OBJS     := $(SRCS:%.c=$(BUILDDIR)/%.o)

# Final executable
TARGET   := main

# Default target: build the exe
all: $(TARGET)

# Link step: depend on all .o files
$(TARGET): $(OBJS)
	@echo "Linking object files..."
	$(CC) $(CFLAGS) -o $@ $^

# Pattern rule to compile any .c → .o
# $< is the source, $@ is the target
$(BUILDDIR)/%.o: %.c
	@echo "Compiling $< → $@"
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up
.PHONY: clean
# This target is used to compile all the source files in the src directory and link them together.
clean:
	rm -rf build
	rm -f $(TARGET)
	rm -f *.o
	rm -f *.out
	rm -f *.exe
	rm -f *.a
	rm -f *.so
	rm -f *.dll
	rm -f *.dSYM
	rm -f *.pdb
	rm -f *.ilk
	rm -f *.idb
	rm -f *.lib
	rm -f *.exp