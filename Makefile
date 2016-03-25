CC	= gcc
CFLAGS	= -Wall -g

AR	= ar
ARFLAGS	= cr

OBJDIR	= build
SRCDIR	= src

BASENM	= iniparse
OBJS	= $(addsuffix .o, $(addprefix $(OBJDIR)/, $(BASENM)) )

TARGET = libiniparser.a

all: $(TARGET)

$(TARGET): $(OBJS)
	$(AR) $(ARFLAGS) $(TARGET) $(OBJS)

$(OBJS): $(OBJDIR)/%.o: $(SRCDIR)/%.c
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(OBJDIR) $(TARGET)

.PHONY: all clean install
