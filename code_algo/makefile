SRCDIR     = src
INCLUDEDIR = include
BINDIR     = bin
EXEC       = textEnInstruction
CC         = gcc
CFLAGS     = -Wall -Wextra -pedantic -g -std=c99 -I$(INCLUDEDIR)
LDFLAGS    = -lm 
C_SOURCES  = main.c IHM.c ville.c case.c direction.c chemin.c
O_OBJECTS  = $(addprefix $(SRCDIR)/, $(C_SOURCES:.c=.o))

all : directories $(BINDIR)/$(EXEC)

$(BINDIR)/$(EXEC) : $(O_OBJECTS)
	@echo "Liaison des objets pour créer $@"
	$(CC) -o $@ $^ $(LDFLAGS)

$(SRCDIR)/%.o : $(SRCDIR)/%.c
	@echo "Compilation de $<"
	$(CC) -o $@ -c $< $(CFLAGS)

directories:
	@mkdir -p $(BINDIR)
	@mkdir -p $(SRCDIR)

clean :
	@echo "Nettoyage des fichiers objets et de l'exécutable..."
	rm -f $(O_OBJECTS)
	rm -f $(BINDIR)/$(EXEC)
	rmdir $(BINDIR) 2>/dev/null || true
