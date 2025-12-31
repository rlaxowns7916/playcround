CC = gcc
CFLAGS = -Wall -g
INC = -I../../include

OBJDIR = ../../build/obj
LIBDIR = ../../build/lib

LIBNAME = ethernet
LIB_OBJS = $(OBJDIR)/ethernet.o
LIB     = $(LIBDIR)/lib$(LIBNAME).a

all: $(LIB)

# $@: 현재타킷, $^: 모든 의존성
$(LIB): $(LIB_OBJS)
	@mkdir -p $(LIBDIR)
	ar rcs $@ $^

# $<: 첫번쨰 의존성
$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(INC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(LIB_OBJS) $(LIB)