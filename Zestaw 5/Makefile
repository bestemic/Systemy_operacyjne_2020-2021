
.SUFFIXES: .c .cpp .o .x .h

DIR = `basename $(CURDIR)`

# Nazwy, ktorych bedziemy uzywac
NAME1 = main
NAME2 = producent
NAME3 = konsument
ARG1 = in.txt
ARG2 = out.txt
FIFO = potok

# Program wykonawczy
EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x
EXEC3 = $(NAME3).x

# Object files
OBJS1  = $(NAME1).o
OBJS2  = $(NAME2).o
OBJS3  = $(NAME3).o

# Opcje kompilatora i linkera
CFLAGS = -Wall -std=c99 -pedantic -O -fPIC
LFLAGS = -Wall -std=c99 -pedantic -O

# Kompilator i linker
CO = gcc
LD = $(CO)

# Reguła wzorcowa
%.o: %.c
	$(CO) $(CFLAGS) -c $<

#Reguły zależności
.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3)

$(EXEC1): $(OBJS1)
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC2): $(OBJS2)
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC3): $(OBJS3)
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: run rund runc compare createfifo removefifo runt runfull

# Zbuduj program $(EXEC1)
run: $(EXEC1) $(EXEC2) $(EXEC3)

# Zbuduj program $(EXEC1) i uruchom z domyślnymi argumentami
rund: $(EXEC1) $(EXEC2) $(EXEC3)
	./$(EXEC1) $(ARG1) $(ARG2)

# Zbuduj program z domyślnymi argumentami i porównaj pliki
runc: rund compare

# Porównaj pliki $(ARG1) $(ARG2)
compare: 
	diff -s $(ARG1) $(ARG2)

# Utwórz potok nazwany o nazwie $(FIFO)
createfifo:
	mkfifo -m 0644 $(FIFO)

# Usuń potok nazwany o nazwie $(FIFO)
removefifo:
	rm -f $(FIFO)

# Uruchom program producenta i konsumenta w oddzielnych terminalach
runt: $(EXEC2) $(EXEC3)
	xterm -hold -title PRODUCENT -e ./$(EXEC2) $(ARG1) $(FIFO) &
	xterm -hold -title KONSUMENT -e ./$(EXEC3) $(ARG2) $(FIFO) 

# Utwórz potok nazwany, uruchom programy w oddzielnych terminalach, porównaj pliki, usuń potok
runfull: createfifo runt compare removefifo

.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}

# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )

.SILENT: