CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

SRC = main.cpp SchemaManager.cpp Table.cpp BufferManager.cpp
OBJ = $(SRC:.cpp=.o)
EXE = dbms

all: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(OBJ) -o $(EXE)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXE)
