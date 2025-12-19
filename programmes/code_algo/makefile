SRCDIR     = src
INCLUDEDIR = include
BINDIR     = bin
TESTBINDIR = tests
EXEC       = textEnInstruction
EXEC_TEST  = testsUnitaires

# Choisir entre l'algo "chemin_bfs" OU "chemin_force_brute"
ALGORITHME = chemin_bfs

CC         = gcc
CFLAGS     = -Wall -Wextra -pedantic -g -std=c99 -I$(INCLUDEDIR) -I$(INCLUDEDIR)/$(ALGORITHME)
LDFLAGS    = -lm 
LDFLAGS_TEST = -lcunit

SOURCES_COMMUN = ville.c case.c direction.c IHM.c $(ALGORITHME)/chemin.c

SOURCES_APP    = $(ALGORITHME)/main.c

SOURCES_TEST   = tests/testsU.c

O_COMMUN = $(addprefix $(SRCDIR)/, $(SOURCES_COMMUN:.c=.o))
O_APP    = $(addprefix $(SRCDIR)/, $(SOURCES_APP:.c=.o))
O_TEST   = $(addprefix $(SRCDIR)/, $(SOURCES_TEST:.c=.o))


all : directories $(BINDIR)/$(EXEC)

tests : directories $(TESTBINDIR)/$(EXEC_TEST)

check : tests
	@echo "--- Lancement des tests ---"
	./$(TESTBINDIR)/$(EXEC_TEST)


$(BINDIR)/$(EXEC) : $(O_APP) $(O_COMMUN)
	@echo "Liaison de l'application : $@"
	$(CC) -o $@ $^ $(LDFLAGS)

$(TESTBINDIR)/$(EXEC_TEST) : $(O_TEST) $(O_COMMUN)
	@echo "Liaison des tests : $@"
	$(CC) -o $@ $^ $(LDFLAGS) $(LDFLAGS_TEST)

$(SRCDIR)/%.o : $(SRCDIR)/%.c
	@echo "Compilation de $<"
	$(CC) -o $@ -c $< $(CFLAGS)

directories:
	@mkdir -p $(BINDIR)
	@mkdir -p $(SRCDIR)
	@mkdir -p $(TESTBINDIR)

clean :
	rm -f $(SRCDIR)/*.o
	rm -f $(SRCDIR)/tests/*.o
	rm -f $(BINDIR)/$(EXEC)
	rm -f $(TESTBINDIR)/$(EXEC_TEST)
	rmdir $(BINDIR) 2>/dev/null || true
	rmdir $(TESTBINDIR) 2>/dev/null || true
