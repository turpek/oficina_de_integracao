# Definição de variáveis
CXX = g++
# CXX = clang++  ## FLAG para gerar o arquivo compile_commands.json para o linter do coc, para gerar use `bear -- make`
CXXFLAGS = -g -O0 -std=c++17 -Wall -MMD -MP -I. -I./tetris -I./mock -I./lib -I./Unity -I./test -DUNIT_TEST -DENABLE_TEST -DARDUINO=150
SRC_DIR  = tetris
TEST_DIR = test
UNITY_DIR = Unity
BIN_DIR  = bin
DEP_DIR = lib

# Arquivos-fonte
UNITY_SRC  = $(UNITY_DIR)/unity.c
TETRIS_SRC = $(SRC_DIR)/tetris.cpp
TEST_SRC   = $(TEST_DIR)/test_utils.cpp $(TEST_DIR)/test_tetris.cpp
DEP_SRC = $(DEP_DIR)/Chrono.cpp $(DEP_DIR)/GButton.cpp

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
$(TARGET): $(UNITY_SRC) $(DEP_SRC) $(TETRIS_SRC) $(TEST_SRC) | $(BIN_DIR)
	@$(CXX) $(CXXFLAGS) $(UNITY_SRC) $(DEP_SRC) $(TETRIS_SRC) $(TEST_SRC) -o $(TARGET)


# Limpeza dos binários
clean:
	@rm -rf $(BIN_DIR)
	@echo "Arquivos de compilação limpos."
