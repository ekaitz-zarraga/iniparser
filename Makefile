# Compile with gcc with flags
CC	= gcc
CFLAGS	= -Wall -g

# Create .a file (archive)
AR	= ar
ARFLAGS	= cr

# Separate directory for .o files
OBJDIR	= build
# Directory for sources
SRCDIR	= src

# Object names. Uses basenm to create full names
BASENM	= iniparse
OBJS	= $(addsuffix .o, $(addprefix $(OBJDIR)/, $(BASENM)) )

# Target library file
TARGET = libiniparser.a

INSTALL_PREFIX	?= /usr
HEADERS	= include/iniparse.h

all: $(TARGET)

# TARGET need all the objects
$(TARGET): $(OBJS)
	$(AR) $(ARFLAGS) $(TARGET) $(OBJS)

# Objects need each object file which needs according .c file
$(OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ -c $<

# Remove build directory and target file
clean:
	rm -rf $(OBJDIR) $(TARGET)

install: all
	# Install headers
	mkdir -p $(INSTALL_PREFIX)/include/iniparser/
	cp $(HEADERS) $(INSTALL_PREFIX)/include/iniparser/
	# Install library
	mkdir -p $(INSTALL_PREFIX)/lib/iniparser/
	cp $(TARGET) $(INSTALL_PREFIX)/lib/iniparser/

uninstall:
	rm -rf $(INSTALL_PREFIX)/include/iniparser/
	rm -rf $(INSTALL_PREFIX)/lib/iniparser/

.PHONY: all clean install
