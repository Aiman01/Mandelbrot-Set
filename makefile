OUT = output

VPATH = src 

CC = gcc
CFLAGS = -g
LDFLAGS = -LExternalResources\Libs -lglfw3  -lopengl32 -lgdi32 -lGlad

LINK_TARGET = main.exe
SRC = $(wildcard src/*.c)
OBJS = $(SRC:.c=.o)
HEADERS = $(wildcard src/*.h)

REBUILDABLES =$(OBJS) $(LINK_TARGET)


all: clearMainObj $(LINK_TARGET) 
	@echo all done

$(LINK_TARGET): $(OBJS) $(HEADERS)
	@$(CC) -o $(OUT)\$@ $^ $(CFLAGS) $(LDFLAGS)

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<

clearMainObj:
	@del /f src\\$(LINK_TARGET:.exe=.o)

%.dep: %.c
	@gcc -M $(CFLAGS) $< > $@

include $(OBJS:.o=.dep)

#-----------------
$(shell mkdir $(OUT))
#-----------------
