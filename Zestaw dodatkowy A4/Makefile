
.SUFFIXES: .c .cpp .o .x .h

DIR = `basename $(CURDIR)`

# Nazwy, ktorych bedziemy uzywac
NAME1 = serwer
NAME3 = klient

# Program wykonawczy
EXEC1 = $(NAME1).x
EXEC2 = $(NAME3).x

# Object files
OBJS1  = $(NAME1).o
OBJS3  = $(NAME3).o

# Opcje kompilatora i linkera
CFLAGS = -Wall -std=c99 -pedantic -O -fPIC
LFLAGS = -Wall -std=c99 -pedantic -O -lrt

# Kompilator i linker
CO = gcc
LD = $(CO)

# Program-archiwizer do tworzenia bibliotek statycznych
AR = ar

# Opcje archiwizera
ARFLAGS = rsv

# Reguły wzorcowe
%.o: %.c %.h
	$(CO) $(CFLAGS) -c $<

%.o: %.c
	$(CO) $(CFLAGS) -c $<

# Reguły zależności
.PHONY: all
all: $(EXEC1) $(EXEC2)

$(EXEC1): $(OBJS1)
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC2): $(OBJS3)
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: run

# Uruchamianie programu
run: $(EXEC1) $(EXEC2)
	xterm -hold -title SERWER -bg SandyBrown -e ./$(EXEC1) &
	xterm -hold -title KONSUMENT1 -bg DarkOliveGreen2 -e ./$(EXEC2) &
	xterm -hold -title KONSUMENT2 -bg DarkOliveGreen2 -e ./$(EXEC2) 

.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )

.SILENT: