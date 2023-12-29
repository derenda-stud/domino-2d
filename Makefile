
# I Makefile vengono usati per
#	1. automatizzare il processo di compilazione
#	2. ricompilare solo i file che sono cambiati
#	3. facilitare il processo di compilazione

# Le variabili permettono di non ripetere il codice

# Compilatore utilizzato
CC = gcc
# Percorso delle librerie
INCDIRS = -I/lib
# Percorso dei file sorgente
SRCDIR = src
# Percorso dei file oggetto
OBJDIR = obj
# Livello di ottimizzazione
OPT = -O2
# Parametri aggiuntivi
CFLAGS = $(OPT) -std=c99 --pedantic -Wall -g $(INCDIRS)

# File sorgente
CFILES  = $(addprefix $(SRCDIR)/, main.c struttura_dati.c modalita_interattiva.c)
# File oggetto
OBJECTS = $(addprefix $(OBJDIR)/, main.o struttura_dati.o modalita_interattiva.o)

# File binario
BINARY = iap

# Le regole del Makefile seguono la struttura [destinazione: dipendenze]

# [all] viene eseguita tramite il comando [make]
# -> Per costruire tutto necessito del file binario
all: $(BINARY)

# Funzionalita' delle wildcards [regex]:
# % --> Tutti i file con quell'estensione
# @ --> Fai riferimento alla destinazione
# ^ --> Fai riferimento alla dipendenza

# Per costruire il file binario necessito di tutti i file oggetto
$(BINARY): $(OBJECTS)
# Chiama il compilatore prendendo come argomenti i file oggetto creati
	$(CC) -o $@ $^

# -> Per costruire un file oggetto necessito dello stesso nome come sorgente
$(OBJDIR)/%.o: $(SRCDIR)/%.c
# Chiama il compilatore con gli appositi parametri sul file sorgente
	$(CC) $(CFLAGS) -c $^ -o $@

# La regola [clean] elilima i file oggetto utilizzati durante la compilazione
clean:
	rm -rf $(OBJECTS)