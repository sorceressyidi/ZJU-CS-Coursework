objects = main.o BAS.o

main : $(objects)
	gcc -o main $(objects)

main.o : main.c BAS.h
	gcc -c main.c

BAS.o : BAS.c BAS.h
	gcc -c BAS.c

.PHONY : clean
clean : 
	-rm main $(objects)

