all: tracker.c
	gcc -g -Wall -o tracker tracker.c

clean:
	$(RM) tracker
