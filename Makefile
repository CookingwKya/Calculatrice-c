# Variables
CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -Iinclude
LDFLAGS = -lm
SRCDIR = src
OBJDIR = obj
SOURCES = $(wildcard $(SRCDIR)/*.c)
OBJECTS = $(SOURCES:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
TARGET = calculatrice

# Règle principale
all: $(TARGET)

# Créer l'exécutable
$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

# Compiler les fichiers .c en .o
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Créer le dossier obj s'il n'existe pas
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Nettoyer
clean:
	rm -rf $(OBJDIR) $(TARGET)

# Recompiler tout
rebuild: clean all

.PHONY: all clean rebuild