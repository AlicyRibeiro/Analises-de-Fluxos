CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -O2 -g -Iinc

SRC_DIR = src
OBJ_DIR = obj

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRCS))


INPUTS := $(wildcard tests/*.in)
OUTPUTS := $(patsubst tests/%.in, tests/%.out, $(INPUTS))

TARGET = exe

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Regra para gerar arquivos de saída para cada input
tests/%.out: tests/%.in $(TARGET)
	./$(TARGET) < $< > $@


# Rodar todos os testes
test: $(OUTPUTS)
	@echo "Todos os testes executados. Saídas em tests/*.out"

clean:
	rm -rf $(OBJ_DIR)/*.o $(TARGET)
	rm -f $(TARGET) tests/*.out

.PHONY: all clean test

