TARGET=hello_world

all:
	$(CROSS_COMPILE)$(CC) -c main.c
	$(CROSS_COMPILE)$(CC) main.o -o $(TARGET)

clean:
	rm -f *.o $(TARGET)
	
