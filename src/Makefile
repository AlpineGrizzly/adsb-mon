CC      = cc
CFLAGS  = -Wall -g
PROG    = adsbmon
LDFLAGS = -lrtlsdr
OBJS    = main.o


%.o: %.c $(OBJS)
	$(CC) $(CFLAGS) -c -o $@ $< 

all: $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) $(LDFLAGS) -o $(PROG)


clean:
	rm -rf $(PROG) *.o
