CC = gcc
CFLAGS = -g -Wall
INC = -I../../include

OBJDIR = ../../build/obj
LIBDIR = ../../build/lib

LIBNAME = datastructure
LIB = $(LIBDIR)/lib$(LIBNAME).a
LIBOBJS = $(OBJDIR)/map.o

all : $(LIB)

$(LIB) : $(LIBOBJS)
	@mkdir -p $(LIBDIR)
	ar rcs $@ $^
$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(LIBOBJS) $(LIB)