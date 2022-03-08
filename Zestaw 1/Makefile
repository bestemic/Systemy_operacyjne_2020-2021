
.SUFFIXES: .c .cpp .o .x .h

DIR = `basename $(CURDIR)`

# Nazwy, ktorych bedziemy uzywac
NAME1 = prog_a
NAME2 = prog_b
NAME3 = prog_c
NAME4 = prog_d
NAME5 = prog_e

# Program wykonawczy
EXEC1 = $(NAME1).x
EXEC2 = $(NAME2).x
EXEC3 = $(NAME3).x
EXEC4 = $(NAME4).x
EXEC5 = $(NAME5).x

#Object files
OBJS1  = $(NAME1).o
OBJS2  = $(NAME2).o
OBJS3  = $(NAME3).o
OBJS4  = $(NAME4).o
OBJS5  = $(NAME5).o

# Opcje kompilatora i linkera
CFLAGS = -Wall -pedantic -O -fPIC
LFLAGS = -Wall -pedantic -O

# Kompilator i linker
CO = gcc
LD = $(CO)

# Reguła wzorcowa
%.o: %.c
	$(CO) $(CFLAGS) -c $<

#Reguły zależności
.PHONY: all
all: $(EXEC1) $(EXEC2) $(EXEC3) $(EXEC4) $(EXEC5)

$(EXEC1): $(OBJS1)
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC2): $(OBJS2)
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC3): $(OBJS3)
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC4): $(OBJS4)
	$(LD) -o $@ $(LFLAGS) $^

$(EXEC5): $(OBJS5)
	$(LD) -o $@ $(LFLAGS) $^

.PHONY: run1 run2 run3 run4 run5

# Uruchom program $(EXEC1); najpierw sprawdz, czy kod wykonawczy jest aktualny
run1: $(EXEC1)
	./$(EXEC1)

# Uruchom program $(EXEC2); najpierw sprawdz, czy kod wykonawczy jest aktualny
run2: $(EXEC2)
	./$(EXEC2)

# Uruchom program $(EXEC3); najpierw sprawdz, czy kod wykonawczy jest aktualny
run3: $(EXEC3)
	./$(EXEC3)

# Uruchom program $(EXEC4); najpierw sprawdz, czy kod wykonawczy jest aktualny
run4: $(EXEC4)
	./$(EXEC4)

# Uruchom program $(EXEC5); najpierw sprawdz, czy kod wykonawczy jest aktualny
run5: $(EXEC5)
	./$(EXEC5)

.PHONY: clean tar
clean:                                                     
	rm -f *.o  *~ *.a *.so *.x core core* a.out; rm -rf ${LIB_DIR}
# Archiwizacja i kompresja
tar: clean
	(cd ../; tar -cvzf $(DIR).tar.gz  $(DIR) )

.SILENT: