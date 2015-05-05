###################################################
# VARIABLES
###################################################

# Project name
# -------------------------------------------------
NAME=libmy_malloc_`uname`.so
LINKNAME=libmy_malloc.so
TESTNAME=test

# Commands
# -------------------------------------------------
CC=gcc
CFLAGS=-W -Wall -Werror -Wextra -std=c11
RM=rm -rf

# Directories
# -------------------------------------------------
BINDIR=./bin
OBJDIR=./obj
LIBDIR=.
SRCDIR=./src

# Files
# -------------------------------------------------
TESTBIN=$(BINDIR)/$(TESTNAME)
LIB=$(LIBDIR)/$(NAME)
LIBLINK=$(LIBDIR)/$(LINKNAME)
SRC:=$(wildcard $(SRCDIR)/*.c)
OBJ:=$(patsubst %.c,%.o,$(SRC))


###################################################
# TARGETS
###################################################

# Default
# -------------------------------------------------
all: $(NAME)
	ln -s $(NAME) $(LINKNAME)

# Linking
# -------------------------------------------------
$(NAME): $(OBJDIR) $(OBJ)
	$(CC) $(CFLAGS) -shared -o $(LIB) $(OBJDIR)/*.o

# Object files
# -------------------------------------------------
%.o:%.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@ && mv $@ $(OBJDIR)

# Directories
# -------------------------------------------------
$(BINDIR):
	mkdir -p $(BINDIR)

$(OBJDIR):
	mkdir -p $(OBJDIR)

# Utils
# -------------------------------------------------
clean:
	$(RM) $(OBJDIR)

fclean: clean
	$(RM) $(BINDIR) $(LIB) $(LIBLINK)

re: fclean all

tests: re $(BINDIR)
	$(CC) $(CFLAGS) -g test/main.c $(LIB) -o $(TESTBIN)
	$(TESTBIN)
