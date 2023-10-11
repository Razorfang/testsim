CXX := g++
CXX_FLAGS := -Wall -Wextra -std=c++17 -ggdb

BIN := bin
SRC := src
INCLUDE := include
EXE := device

all: $(BIN)/$(EXE)

$(BIN)/$(EXE): $(SRC)/*.cpp $(INCLUDE)/*.h
	$(CXX) $(CXX_FLAGS) -I$(INCLUDE) $^ -o $@

clean:
	rm -f $(BIN)/* 
