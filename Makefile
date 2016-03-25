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

install: #TODO
	# copy ./include/* in /usr/include/iniparse/
	# copy $(TARGET) in /usr/lib/iniparse
	echo "Not implemented yet"

.PHONY: all clean install
