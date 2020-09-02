HEADERS = utilitaire.h evaluation.h gameplay.h globals.h ia.h interface.h
OBJECTS = utilitaire.o evaluation.o gameplay.o ia.o interface.o main.o
TARGET = othello

default: $(TARGET)

%.o: %.c $(HEADERS)
	gcc -c $< -o $@

othello: $(OBJECTS)
	gcc $(OBJECTS) -o $@

clean:
	rm -f *.o
	rm -f $(TARGET)
