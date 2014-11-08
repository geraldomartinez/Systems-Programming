#Geraldo Martinez
#gm979351

.SUFFIXES: .c .o



CC = gcc



CFLAGS = -g

.c.o:
	$(CC) $(CFLAGS) -c $<

all: p5a p5b

p5a: p5a_main.o
	gcc p5a_main.o -o p5a
	
p5b: p5b_main.o p5b_functions.o
	gcc p5b_main.o p5b_functions.o -o p5b


#Target for removing unnecessary files.
clean:
	rm -f *.o core
