CXX=g++
CXXFLAGS=-Werror -Wall -Wextra -pedantic -std=c++17

LEXER=scan.cc
PARSER=parse.cc
BIN=tc

all: $(BIN)

$(BIN): $(LEXER) $(PARSER)
	$(CXX) $(CXXFLAGS) -o $(BIN) $(LEXER) $(PARSER)

clean:
	rm $(BIN)

.PHONY: all clean
