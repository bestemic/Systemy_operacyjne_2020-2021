
.SUFFIXES: .c .cpp .o .x .h

DIR = `basename $(CURDIR)`

# Nazwy, ktorych bedziemy używać
NAME1 = main
NAME2 = producent
NAME3 = konsument
NAME4 = mem_bib
NAME5 = sem_bib
ARG1 = in.txt
ARG2 = out.txt

# Program wykonawczy
EXEC1s = $(NAME1)s.x
EXEC2s = $(NAME2)s.x
EXEC3s = $(NAME3)s.x
EXEC1d1 = $(NAME1)d1.x
EXEC2d1 = $(NAME2)d1.x
EXEC3d1 = $(NAME3)d1.x
EXEC1d2 = $(NAME1)d2.x
EXEC2d2 = $(NAME2)d2.x
EXEC3d2 = $(NAME3)d2.x

# Object files
OBJS1  = $(NAME1).o
OBJS2  = $(NAME2).o
OBJS3  = $(NAME3).o
OBJS4  = $(NAME4).o
OBJS5  = $(NAME5).o

# Pliki nagłówkowe
HEAD1 = $(NAME4).h
HEAD2 = $(NAME5).h
HEADS = $(HEAD1) $(HEAD2)

# Nazwa biblioteki
LIB_NAME = MojeFunkcje

# Katalog dla bibliotek
LIB_DIR = ./lib

# Biblioteka statyczna
LIB_STAT = lib$(LIB_NAME).a

# Biblioteka dzielona (shared library)
LIB_SHAR = lib$(LIB_NAME).so

# Pliki objektowe wchodzace do biblioteki
LIB_OBJS = $(OBJS4) $(OBJS5)

# Opcje kompilatora i linkera
CFLAGS = -Wall -std=gnu99 -pedantic -O -fPIC
LFLAGS = -Wall -std=gnu99 -pedantic -O -pthread -lrt

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
all: $(EXEC1s) $(EXEC2s) $(EXEC3s) $(EXEC1d1) $(EXEC2d1) $(EXEC3d1) $(EXEC1d2) $(EXEC2d2) $(EXEC3d2)

# Tworzenie bibliteki statycznej
$(LIB_STAT): $(LIB_OBJS)
	$(AR) $(ARFLAGS) $@ $?
	mkdir -p $(LIB_DIR)
	mv $(LIB_STAT) $(LIB_DIR)

# Tworzenie biblioteki dzielonej (shared library)
$(LIB_SHAR): $(LIB_OBJS) 
	$(LD) -shared -o $@ $(LFLAGS) $(LIB_OBJS)
	mkdir -p $(LIB_DIR)
	mv $(LIB_SHAR) $(LIB_DIR)

# Reguły zależności dla programów z biblioteką statyczną
$(EXEC1s): $(OBJS1) $(LIB_STAT) 
	$(LD) -o $@ $(LFLAGS) $(OBJS1) -L$(LIB_DIR) -l$(LIB_NAME)

$(EXEC2s): $(OBJS2) $(LIB_STAT) 
	$(LD) -o $@ $(LFLAGS) $(OBJS2) -L$(LIB_DIR) -l$(LIB_NAME)

$(EXEC3s): $(OBJS3) $(LIB_STAT) 
	$(LD) -o $@ $(LFLAGS) $(OBJS3) -L$(LIB_DIR) -l$(LIB_NAME)

# Plik wykonawczy z biblioteka dzielona - wersja 1       
$(EXEC1d1): $(OBJS1) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS1) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) -Wl,-R $(LIB_DIR)

$(EXEC2d1): $(OBJS2) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS2) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) -Wl,-R $(LIB_DIR)

$(EXEC3d1): $(OBJS3) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS3) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS) -Wl,-R $(LIB_DIR)

# Plik wykonawczy z biblioteka dzielona - wersja 2
$(EXEC1d2): $(OBJS1) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS1) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

$(EXEC2d2): $(OBJS2) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS2) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

$(EXEC3d2): $(OBJS3) $(LIB_SHAR)
	$(LD) -o $@ $(LFLAGS) $(OBJS3) -L$(LIB_DIR) -l$(LIB_NAME) $(LDLIBS)

# Dodatkowe reguly zaleznosci plikow obiektowych od naglowkowych, ktorych
# nie uwglednia regula wzorcowa (powyzej).
$(OBJS1): $(HEADS)
$(OBJS2): $(HEADS)
$(OBJS3): $(HEADS)

.PHONY: runs rund1 rund2 compare

# Uruchamianie programu z biblioteką statyczną
runs: $(EXEC1s) $(EXEC2s) $(EXEC3s)
	./$(EXEC1s) $(EXEC2s) $(EXEC3s) $(ARG1) $(ARG2)

# Uruchamianie z biblioteką dzieloną - wersja 1
rund1: $(EXEC1d1) $(EXEC2d1) $(EXEC3d1)
	./$(EXEC1d1) $(EXEC2d1) $(EXEC3d1) $(ARG1) $(ARG2)

# Uruchamianie programu z biblioteką dzieloną - wersja 2
rund2: $(EXEC1d2) $(EXEC2d2) $(EXEC3d2)
	( export LD_LIBRARY_PATH=${LIB_DIR}:${LD_LIBRARY_PATH}; \
	./$(EXEC1d2) $(EXEC2d2) $(EXEC3d2) $(ARG1) $(ARG2) )

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