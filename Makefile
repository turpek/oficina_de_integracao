# Definição de variáveis
CXX      = g++
CXXFLAGS = -Wall -I. -DUNIT_TEST
SRC_DIR  = tetris
TEST_DIR = test
UNITY_DIR = Unity
BIN_DIR  = bin

# Arquivos-fonte
UNITY_SRC  = $(UNITY_DIR)/unity.c
TETRIS_SRC = $(SRC_DIR)/tetris.cpp
TEST_SRC   = $(TEST_DIR)/test_tetris.cpp

# Executáveis
TARGET     = $(BIN_DIR)/test_tetris

# Regra padrão (constroi o teste e executa)
all: $(TARGET)
	@echo "Compilação concluída. Executando os testes..."
	@./$(TARGET)

# Garante que o diretório bin exista
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# Compila o código principal e os testes
$(TARGET): $(UNITY_SRC) $(TETRIS_SRC) $(TEST_SRC) | $(BIN_DIR)
	@$(CXX) $(CXXFLAGS) $(UNITY_SRC) $(TETRIS_SRC) $(TEST_SRC) -o $(TARGET)

# Limpeza dos binários
clean:
	@rm -rf $(BIN_DIR)
	@echo "Arquivos de compilação limpos."

# Força a recompilação
force: clean all

