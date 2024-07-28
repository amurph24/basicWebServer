EXE = server

CC = gcc
CCFLAGS = -Wall -Wextra -pedantic-errors
BUILDDIR = build
SOURCEDIR = source
INCLUDEDIR = include
TESTDIR = test
# define required object files based on all .c files found in source
SOURCEFILES = $(shell find $(SOURCEDIR) -name *.c)
OBJFILES = $(patsubst %.c, $(BUILDDIR)/%.o, $(notdir $(SOURCEFILES)))

help:
	@echo "make $(EXE)	- compile an executable which runs the server"
	@echo "make clean 	- remove all object files and $(EXE) from $(BUILDDIR)"
	@echo "make quickstart	- create building blocks for a c project"
	@echo "make test	- (WIP) run unit tests"
	@echo "make help 	- display options for Makefile"

$(EXE): $(BUILDDIR)/$(EXE)
$(BUILDDIR)/$(EXE): $(OBJFILES)
	@mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) -o "$(BUILDDIR)/$(EXE)" $^

$(OBJFILES): $(BUILDDIR)/%.o: $(SOURCEDIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CCFLAGS) -I $(INCLUDEDIR) -c $< -o $@

clean:
	rm -f $(BUILDDIR)/*.o
	rm -f $(BUILDDIR)/$(EXE)

# TODO: implement somewhat standard testing rule
test:
	@echo "this doesn't do anything right now :("

quickstart:
	mkdir -p $(BUILDDIR) $(SOURCEDIR) $(INCLUDEDIR) $(TESTDIR)
	touch $(SOURCEDIR)/main.c
