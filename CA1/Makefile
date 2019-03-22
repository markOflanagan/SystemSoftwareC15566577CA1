myprog :	ca.o backup.o transfer.o audit.o
	gcc -o myprog  ca.o backup.o transfer.o audit.o

ca.o :	ca.c ca.h
	gcc -c ca.c

backup.o :	backup.c  ca.h
	gcc -c backup.c

audit.o :	audit.c ca.h
	gcc -c audit.c

transfer.o :	transfer.c ca.h
	gcc -c transfer.c

clean :
	rm myprog  ca.o backup.o transfer.o audit.o





