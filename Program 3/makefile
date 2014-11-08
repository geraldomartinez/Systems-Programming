#Geraldo Martinez
#gm979351

.SUFFIXES: .c .o



CC = gcc



CFLAGS = -g

.c.o:
	$(CC) $(CFLAGS) -c $<

p3: p3.o nattr.o tuplen.o infattr.o count.o project.o fileExist.o select_fun.o
	gcc p3.o nattr.o tuplen.o infattr.o count.o project.o fileExist.o select_fun.o -o p3

p3.o:  constants.h prototypes.h

nattr.o:  constants.h prototypes.h

tuplen.o:  constants.h prototypes.h

infattr.o:  constants.h prototypes.h

count.o:  constants.h prototypes.h

project.o:  constants.h prototypes.h

fileExist.o:  constants.h prototypes.h

select.o:  constants.h prototypes.h

#Target for removing unnecessary files.
clean:
	rm -f *.o core
