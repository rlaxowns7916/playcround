CC      = gcc
CFLAGS  = -Wall -g -fPIC
INC     = ../../include
LDFLAGS_SO = -shared

OBJDIR = ../../build/obj
LIBDIR = ../../build/lib

LIBNAME = ioutil
LIB_OBJS = $(OBJDIR)/read.o
LIB     = $(LIBDIR)/lib$(LIBNAME).so

all: $(LIB)

# 공유 라이브러리: build/lib 아래로 생성
# @는 명령은 실행하되, 화면 출력X
$(LIB): $(LIB_OBJS)
	@mkdir -p $(LIBDIR)
	$(CC) $(LDFLAGS_SO) -o $@ $^

# 객체 파일: build/obj 아래로 생성
$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

clean:
	rm -rf $(LIB)