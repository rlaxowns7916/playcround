CC = gcc
CFLAGS = -Wall -g
INC = -I../../include

OBJDIR = ../../build/obj
LIBDIR = ../../build/lib

LIBNAME = ip
LIBOBJS = $(OBJDIR)/ip.o
LIB     = $(LIBDIR)/lib$(LIBNAME).a

all: $(LIB)

$(LIB): $(LIBOBJS)
	@mkdir -p $(LIBDIR)
	ar rcs $@ $^

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(LIBOBJS) $(LIB) 