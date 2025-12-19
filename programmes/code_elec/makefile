SRCDIR     = src
INCLUDEDIR = include
BINDIR     = bin
EXEC       = robot

CC         = gcc
CFLAGS = -Wall -Wextra -pedantic -g -std=c99 -D_POSIX_C_SOURCE=200809L -I$(INCLUDEDIR)


LDFLAGS    = -lwiringPi -lpthread -lwiringPiDev -lm 

SOURCES_MODULES = lcd_bip.c rgb_sensor.c lecture_instruction.c commande_final.c configurer.c pastille_detect.c

SOURCES_APP    = main.c

O_MODULES = $(addprefix $(SRCDIR)/, $(SOURCES_MODULES:.c=.o))
O_APP     = $(addprefix $(SRCDIR)/, $(SOURCES_APP:.c=.o))


all : directories $(BINDIR)/$(EXEC)

$(BINDIR)/$(EXEC) : $(O_APP) $(O_MODULES)
	@echo "Liaison de l'application robot : $@"
	$(CC) -o $@ $^ $(LDFLAGS)

$(SRCDIR)/%.o : $(SRCDIR)/%.c
	@echo "Compilation de $<"
	$(CC) -o $@ -c $< $(CFLAGS)

directories:
	@mkdir -p $(BINDIR)
	@mkdir -p $(SRCDIR)
	@mkdir -p $(INCLUDEDIR)

clean :
	@echo "Nettoyage des fichiers générés..."
	rm -f $(SRCDIR)/*.o
	rm -f $(BINDIR)/$(EXEC)
	rmdir $(BINDIR) 2>/dev/null || true
