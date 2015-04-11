###################################################
# VARIABLES
###################################################

# Project name
# -------------------------------------------------
NAME=libmy_malloc_`uname`.so
LINKNAME=libmy_malloc.so

# Commands
# -------------------------------------------------
CC=gcc
CFLAGS=-W -Wall -Werror -Wextra -std=c11
RM=rm -rf

# Directories
# -------------------------------------------------
BINDIR=./bin
OBJDIR=./obj
SRCDIR=./src

# Files
# -------------------------------------------------
BIN=$(BINDIR)/$(NAME)
SRC:=$(wildcard $(SRCDIR)/*.c)
OBJ:=$(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

###################################################
# TARGETS
###################################################

all:$(NAME)
	cd $(BINDIR); ln -s $(NAME) $(LINKNAME); cd ..

# Linking
# -------------------------------------------------
$(NAME):$(OBJ) $(BINDIR)
	$(CC) $(CFLAGS) -shared -o $(BIN) $(OBJ)

# Object files
# -------------------------------------------------
$(OBJ):$(SRC) $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Directories
# -------------------------------------------------
$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

# Utils
# -------------------------------------------------
clean:
	$(RM) $(OBJDIR) $(BINDIR)
