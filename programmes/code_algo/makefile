SRCDIR     = src
INCLUDEDIR = include
BINDIR     = bin
TESTBINDIR = tests
EXEC       = textEnInstruction
EXEC_TEST  = testsUnitaires
DOC_DIR    = doc

ALGORITHME = chemin_bfs

CC         = gcc
CFLAGS     = -Wall -Wextra -pedantic -g -std=c99 -I$(INCLUDEDIR) -I$(INCLUDEDIR)/$(ALGORITHME)
LDFLAGS    = -lm 
LDFLAGS_TEST = -lcunit

SOURCES_COMMUN = ville.c case.c direction.c IHM.c $(ALGORITHME)/chemin.c

DOXYFILE = Doxyfile

SOURCES_APP    = $(ALGORITHME)/main.c
SOURCES_TEST   = tests/testsU.c

O_COMMUN = $(addprefix $(SRCDIR)/, $(SOURCES_COMMUN:.c=.o))
O_APP    = $(addprefix $(SRCDIR)/, $(SOURCES_APP:.c=.o))
O_TEST   = $(addprefix $(SRCDIR)/, $(SOURCES_TEST:.c=.o))

all : directories $(BINDIR)/$(EXEC)

tests : directories $(TESTBINDIR)/$(EXEC_TEST)

check : tests
	./$(TESTBINDIR)/$(EXEC_TEST)
	
doc: directories $(DOXYFILE)
	doxygen $(DOXYFILE)

$(BINDIR)/$(EXEC) : $(O_APP) $(O_COMMUN)
	$(CC) -o $@ $^ $(LDFLAGS)

$(TESTBINDIR)/$(EXEC_TEST) : $(O_TEST) $(O_COMMUN)
	$(CC) -o $@ $^ $(LDFLAGS) $(LDFLAGS_TEST)

$(SRCDIR)/%.o : $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS)
	
$(DOXYFILE):
	doxygen -g
	@sed -i 's|^PROJECT_NAME.*$$|PROJECT_NAME           = "PI Smart Robot"|' $(DOXYFILE)
	@sed -i 's|^OUTPUT_LANGUAGE.*$$|OUTPUT_LANGUAGE        = French|' $(DOXYFILE)
	@sed -i 's|^INPUT.*$$|INPUT                  = ../../README.md $(SRCDIR) $(INCLUDEDIR)|' $(DOXYFILE)
	@sed -i 's|^USE_MDRIP_AS_MAIN_PAGE.*$$|USE_MDRIP_AS_MAIN_PAGE = YES|' $(DOXYFILE)
	@sed -i 's|^RECURSIVE.*$$|RECURSIVE              = YES|' $(DOXYFILE)
	@sed -i 's|^OUTPUT_DIRECTORY.*$$|OUTPUT_DIRECTORY       = $(DOC_DIR)|' $(DOXYFILE)
	@sed -i 's|^GENERATE_LATEX.*$$|GENERATE_LATEX         = YES|' $(DOXYFILE)
	@sed -i 's|^HAVE_DOT.*$$|HAVE_DOT               = YES|' $(DOXYFILE)
	@sed -i 's|^UML_LOOK.*$$|UML_LOOK               = YES|' $(DOXYFILE)
	@sed -i 's|^CALL_GRAPH.*$$|CALL_GRAPH             = YES|' $(DOXYFILE)
	@sed -i 's|^CALLER_GRAPH.*$$|CALLER_GRAPH           = YES|' $(DOXYFILE)
	@sed -i 's|^OPTIMIZE_OUTPUT_FOR_C.*$$|OPTIMIZE_OUTPUT_FOR_C   = YES|' $(DOXYFILE)
	@sed -i 's|^EXTRACT_ALL.*$$|EXTRACT_ALL            = YES|' $(DOXYFILE)
	@sed -i 's|^EXTRACT_PRIVATE.*$$|EXTRACT_PRIVATE         = YES|' $(DOXYFILE)
	@sed -i 's|^TYPEDEF_HIDES_STRUCT.*$$|TYPEDEF_HIDES_STRUCT    = YES|' $(DOXYFILE)

directories:
	mkdir -p $(BINDIR)
	mkdir -p $(SRCDIR)
	mkdir -p $(TESTBINDIR)

clean :
	rm -fR ./$(DOC_DIR)
	rm -f ./$(DOXYFILE)
	rm -f $(SRCDIR)/*.o
	rm -f $(SRCDIR)/$(ALGORITHME)/*.o
	rm -f $(SRCDIR)/tests/*.o
	rm -f $(BINDIR)/$(EXEC)
	rm -f $(TESTBINDIR)/$(EXEC_TEST)
	rmdir $(BINDIR) 2>/dev/null || true
	rmdir $(TESTBINDIR) 2>/dev/null || true
