
# Define o compilador C
CC := gcc

# Nome do arquivo final
BINARY := sudoku

# Estrutura de diretórios do código
BINDIR := .
BUILDDIR := build
INCDIR := include
SRCDIR := src

# Flags do compilador
CFLAGS := -Wall -I $(INCDIR)

# Flags do linker
LDFLAGS := 

# Nomes dos arquivos .o
NAMES := $(notdir $(basename $(wildcard $(SRCDIR)/*.c)))
OBJECTS := $(patsubst %,$(BUILDDIR)/%.o,$(NAMES))

# Regra para compilar e gerar o arquivo binário final
all: $(BINDIR)/$(BINARY)

$(BINDIR)/$(BINARY): $(OBJECTS)
	@ if [ ! -d $(BINDIR) ]; then mkdir -p $(BINDIR); fi
	$(CC) -o $@ $(OBJECTS) $(LDFLAGS)

# Regra para compilar os arquivos de objeto
$(BUILDDIR)/%.o: $(SRCDIR)/%.c | $(BUILDDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Cria o diretório build se ele não existir
$(BUILDDIR):
	@ mkdir -p $(BUILDDIR)

# Limpa os diretórios BIN e BUILD
.PHONY: clean
clean:
	rm -rf $(BUILDDIR) $(BINDIR)/$(BINARY)