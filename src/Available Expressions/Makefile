# Nome do executável
EXEC = available_expr

# Nome do arquivo-fonte
SRC = available_expressions.cpp

# Compilador e flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Regra padrão
all: $(EXEC)

$(EXEC): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(SRC)

# Limpeza de arquivos gerados
clean:
	rm -f $(EXEC)