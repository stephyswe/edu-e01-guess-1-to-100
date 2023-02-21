PROG = main.exe 
SRC = main.c safeinput.c date.c file.c FileData.h Player.h Score.h
CFLAGS = -g
LIBS = 

all: $(PROG)

$(PROG): $(SRC)
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) $(SRC)  $(LIBS) 

clean:
	rm -f $(PROG)

.PHONY: all clean