CC     = gcc
CFLAGS = -Wall -Wextra -ansi -pedantic -O2
OBJS   = main.o lista.o torcedor.o
PROG   = venda_ingressos

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $(PROG) $(OBJS)

main.o: main.c lista.h torcedor.h
lista.o: lista.c lista.h torcedor.h
torcedor.o: torcedor.c torcedor.h

run: $(PROG)
	./$(PROG) entrada.txt

clean:
	rm -f $(OBJS) $(PROG)
