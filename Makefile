PROG = main.exe 
SRC = main.c safeinput.c date.c file.h file.c FileData.h Player.h Score.h scoreinput.h scoreinput.c
CFLAGS = -g
LIBS = 

all: $(PROG)

$(PROG): $(SRC)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SRC) $(LIBS) 

clean:
	rm -f $(PROG)

.PHONY: all clean