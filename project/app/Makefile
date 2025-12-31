CC     = gcc
CFLAGS = -Wall -g
INC    = -I../include
LDFLAGS = -L../build/lib -lioutil -lpcap -lethernet

OBJDIR = ../build/obj
LIBDIR = ../build/lib
APPDIR = ../build/app

TARGET = $(APPDIR)/app
OBJ = $(OBJDIR)/main.o

all: $(TARGET)

$(TARGET): $(OBJ)
	@mkdir -p $(APPDIR)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(INC) $(CFLAGS)  -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJ)