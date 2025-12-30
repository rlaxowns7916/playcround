CC     = gcc
CFLAGS = -Wall -g
INC    = ../include
LDFLAGS = -L../build/lib -lioutil

TARGET = app
OBJS = main.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -I$(INC) $(CFLAGS)  -c $<

clean:
	rm -f *.o $(TARGET)