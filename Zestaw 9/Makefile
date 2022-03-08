
.SUFFIXES: .c .cpp .o .x .h

DIR = `basename $(CURDIR)`

# Nazwy, ktorych bedziemy uzywac
NAME1 = main

# Program wykonawczy
EXEC1 = $(NAME1).x

# Object files
OBJS1  = $(NAME1).o

# Opcje kompilatora i linkera
CFLAGS = -Wall -std=c99 -pedantic -O -fPIC
LFLAGS = -Wall -std=c99 -pedantic -O -lpthread

# Kompilator i linker
CO = gcc
LD = $(CO)

# Reguła wzorcowa
%.o: %.c
	$(CO) $(CFLAGS) -c $<

# Reguły zależności
.PHONY: all
all: $(EXEC1)

$(EXEC1): $(OBJS1)
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: build

# Zbuduj program $(EXEC1)
build: $(EXEC1)

.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}

# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )

.SILENT: