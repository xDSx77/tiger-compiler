CXX=g++
CXXFLAGS=-Werror -Wall -Wextra -pedantic -std=c++17

SCANNER=scan.ll
PARSER=parse.yy
SRC_SCANNER=scan.cc
SRC_PARSER=parse.cc
BIN=tc

all: $(BIN) $(SRC_SCANNER) $(SRC_PARSER)

scan: $(SRC_SCANNER)

$(SRC_SCANNER): $(SCANNER)
	flex -o $@ $<

parse: $(SRC_PARSER)

$(SRC_PARSER): $(PARSER)
	bison -dv -o $@ $<

$(BIN): $(SRC_SCANNER) $(SRC_PARSER)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm $(BIN)

.PHONY: all clean scan parse
