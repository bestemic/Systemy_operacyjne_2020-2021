
.SUFFIXES: .c .cpp .o .x .h

DIR = `basename $(CURDIR)`

# Nazwy, ktorych bedziemy uzywac
NAME1 = main
NAME2 = biblioteka
NAME3 = wykluczenia

# Program wykonawczy
EXEC1 = $(NAME1).x
EXEC2 = $(NAME3).x

# Object files
OBJS1  = $(NAME1).o
OBJS2  = $(NAME2).o
OBJS3  = $(NAME3).o

# Pliki nagłówkowe
HEADS = $(NAME2).h

# Nazwa biblioteki
LIB_NAME = MojeFunkcje

# Katalog dla bibliotek
LIB_DIR = ./lib

# Biblioteka statyczna
LIB_STAT = lib$(LIB_NAME).a

# Pliki objektowe wchodzace do biblioteki
LIB_OBJS = $(OBJS2)


# Opcje kompilatora i linkera
CFLAGS = -Wall -std=c99 -pedantic -O -fPIC
LFLAGS = -Wall -std=c99 -pedantic -O -pthread

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

# Tworzenie bibliteki statycznej
$(LIB_STAT): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $?
	mkdir -p $(LIB_DIR)
	mv $(LIB_STAT) $(LIB_DIR)

# Reguły zależności dla programów z biblioteką statyczną
$(EXEC1): $(OBJS1) $(LIB_STAT) 
	$(LD) -o $@ $(LFLAGS) $(OBJS1) -L$(LIB_DIR) -l$(LIB_NAME)

$(EXEC2): $(OBJS3) $(LIB_STAT) 
	$(LD) -o $@ $(LFLAGS) $(OBJS3) -L$(LIB_DIR) -l$(LIB_NAME)

# Dodatkowe reguly zaleznosci plikow objectowych od naglowkowych, ktorych
# nie uwglednia regula wzorcowa (powyzej).
$(OBJS1): $(HEADS)
$(OBJS3): $(HEADS)

.PHONY: run

# Budowanie programu
run: $(EXEC1) $(EXEC2)

.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )

.SILENT: