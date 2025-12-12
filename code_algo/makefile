SRCDIR     = src
INCLUDEDIR = include
BINDIR     = bin
# Nouveau dossier de destination pour l'exécutable de test (à la racine)
TESTBINDIR = tests

# Noms des exécutables
EXEC       = textEnInstruction
EXEC_TEST  = testsUnitaires

CC         = gcc
CFLAGS     = -Wall -Wextra -pedantic -g -std=c99 -I$(INCLUDEDIR)
LDFLAGS    = -lm 
LDFLAGS_TEST = -lcunit

# --- 1. FICHIERS COMMUNS ---
SOURCES_COMMUN = ville.c case.c direction.c chemin.c IHM.c

# --- 2. FICHIER PRINCIPAL (Jeu) ---
SOURCES_APP    = main.c

# --- 3. FICHIER TEST (Source) ---
# Le fichier source est dans src/tests/
SOURCES_TEST   = tests/testsU.c

# --- GÉNÉRATION DES LISTES D'OBJETS ---
O_COMMUN = $(addprefix $(SRCDIR)/, $(SOURCES_COMMUN:.c=.o))
O_APP    = $(addprefix $(SRCDIR)/, $(SOURCES_APP:.c=.o))
O_TEST   = $(addprefix $(SRCDIR)/, $(SOURCES_TEST:.c=.o))

# --- CIBLES ---

# "make" tout court ne construit que le jeu (comportement standard)
all : directories $(BINDIR)/$(EXEC)

# "make tests" construit l'exécutable dans le dossier tests/ de la racine
tests : directories $(TESTBINDIR)/$(EXEC_TEST)

# "make check" construit et lance l'exécutable situé dans tests/
check : tests
	@echo "--- Lancement des tests ---"
	./$(TESTBINDIR)/$(EXEC_TEST)

# --- LIAISON (LINKING) ---

# Application (Va dans bin/)
$(BINDIR)/$(EXEC) : $(O_APP) $(O_COMMUN)
	@echo "Liaison de l'application : $@"
	$(CC) -o $@ $^ $(LDFLAGS)

# Tests (Va dans tests/)
$(TESTBINDIR)/$(EXEC_TEST) : $(O_TEST) $(O_COMMUN)
	@echo "Liaison des tests : $@"
	$(CC) -o $@ $^ $(LDFLAGS) $(LDFLAGS_TEST)

# --- COMPILATION (.c -> .o) ---
# Fonctionne pour src/ville.c ET src/tests/testsU.c
$(SRCDIR)/%.o : $(SRCDIR)/%.c
	@echo "Compilation de $<"
	$(CC) -o $@ -c $< $(CFLAGS)

# --- SETUP & CLEAN ---
directories:
	@mkdir -p $(BINDIR)
	@mkdir -p $(SRCDIR)
	@mkdir -p $(TESTBINDIR)

clean :
	@echo "Nettoyage..."
	rm -f $(SRCDIR)/*.o
	rm -f $(SRCDIR)/tests/*.o
	rm -f $(BINDIR)/$(EXEC)
	rm -f $(TESTBINDIR)/$(EXEC_TEST)
	rmdir $(BINDIR) 2>/dev/null || true
	rmdir $(TESTBINDIR) 2>/dev/null || true