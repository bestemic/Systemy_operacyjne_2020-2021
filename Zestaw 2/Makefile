
.SUFFIXES: .c .cpp .o .x .h

DIR = `basename $(CURDIR)`
NAME1 = main
NAME2 = procinfo

EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x

OBJS1  = $(NAME1).o
OBJS2  = $(NAME2).o

# Opcje kompilatora i linkera
CFLAGS = -Wall -pedantic -O -fPIC
LFLAGS = -Wall -pedantic -O

# Kompilator i linker
CO = gcc
LD = $(CO)

# Reguła wzorcowa
%.o: %.c
	$(CO) $(CFLAGS) -c $<

.PHONY: all
all: $(EXEC1) $(EXEC2)

$(EXEC1): $(OBJS1)
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC2): $(OBJS2)
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: run
run: $(EXEC1) $(EXEC2)
	./$(EXEC1) $(EXEC2)

.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}

# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )

.SILENT: