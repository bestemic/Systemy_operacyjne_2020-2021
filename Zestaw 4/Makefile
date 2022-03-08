
.SUFFIXES: .c .cpp .o .x .h

DIR = `basename $(CURDIR)`

# Nazwy, ktorych bedziemy uzywac
NAME1 = main
ARG1 = in.txt
ARG2 = out.txt

# Program wykonawczy
EXEC1 = $(NAME1).x

# Object files
OBJS1  = $(NAME1).o

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
all: $(EXEC1)

$(EXEC1): $(OBJS1)
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: run rund runc compare

# Zbuduj program $(EXEC1)
run: $(EXEC1) 

# Zbuduj program $(EXEC1) i uruchom z domyślnymi argumentami
rund: $(EXEC1)
	./$(EXEC1) $(ARG1) $(ARG2)

# Zbuduj program z domyślnymi argumentami i porównaj pliki
runc: rund compare

# Porównaj pliki $(ARG1) $(ARG2)
compare: 
	diff -s $(ARG1) $(ARG2)

.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}

# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )

.SILENT: