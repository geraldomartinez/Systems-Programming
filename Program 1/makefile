#Geraldo Martinez
#gm979351

.SUFFIXES: .c .o



CC = gcc



CFLAGS = -g

.c.o:
	$(CC) $(CFLAGS) -c $<

p1: p1.o insert_function.o functions.o
	gcc p1.o insert_function.o functions.o -o p1

p1.o:  struct_def.h constants.h prototype.h

insert_function.o: struct_def.h constants.h prototype.h

functions.o: struct_def.h constants.h prototype.h

#Target for removing unnecessary files.
clean:
	rm -f *.o core
