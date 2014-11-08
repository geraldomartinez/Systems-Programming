#Geraldo Martinez
#gm979351

.SUFFIXES: .c .o



CC = gcc



CFLAGS = -g

.c.o:
	$(CC) $(CFLAGS) -c $<

p2: p2.o text_to_binary.o binary_to_text.o binarySTATS.o
	gcc p2.o text_to_binary.o binary_to_text.o binarySTATS.o -o p2

p2.o:  constants.h prototypes.h

text_to_binary.o: constants.h prototypes.h

binary_to_text.o: constants.h prototypes.h

binarySTATS.o: constants.h prototypes.h

#Target for removing unnecessary files.
clean:
	rm -f *.o core
