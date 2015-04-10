###################################################
# VARIABLES
###################################################

# Project name
# -------------------------------------------------
NAME=libmy_malloc_`uname`.so

# Commands
# -------------------------------------------------
CC=gcc
CFLAGS=-Wall -Wextra
RM=rm -rf

# Directories
# -------------------------------------------------
BINDIR=./bin
OBJDIR=./obj
SRCDIR=./src

# Files
# -------------------------------------------------
SRC:=$(wildcard $(SRCDIR)/*.c)
OBJ:=$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

###################################################
# TARGETS
###################################################

all:$(OBJ)

$(OBJ):$(SRC) $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

clean:
	$(RM) $(OBJDIR)
