all:projet_cheval projet_0

projet_cheval : projet_cheval.o 
	gcc projet_cheval.o -o projet_cheval
    
projet_cheval.o:projet_cheval.c
	gcc -c projet_cheval.c
    
projet_0 : projet_0.o 
	gcc projet_0.o -o projet_0
    
projet_0.o:projet_0.c
	gcc -c projet_0.c
    
clean:
	-rm *.o


