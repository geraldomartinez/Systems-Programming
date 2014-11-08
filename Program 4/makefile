#Geraldo Martinez
#gm979351

.SUFFIXES: .c .o



CC = gcc



CFLAGS = -g

.c.o:
	$(CC) $(CFLAGS) -c $<

p4: p4.o pass_one.o functions.o errors.o pass_two.o R_format.o I_format.o J_format.o
	gcc p4.o pass_one.o functions.o errors.o pass_two.o R_format.o I_format.o J_format.o -o p4

p4.o:  constants.h structs.h prototypes.h oc_table.h

pass_one.o: constants.h structs.h prototypes.h oc_table.h

functions.o: constants.h structs.h prototypes.h oc_table.h

errors.o: constants.h structs.h prototypes.h oc_table.h

pass_two.o: constants.h structs.h prototypes.h oc_table.h

R_format.o: constants.h 

I_format.o: constants.h 

J_format.o: constants.h 

#Target for removing unnecessary files.
clean:
	rm -f *.o core
