CC=g++
CFLAGS=-c -Wall -fopenmp
LDFLAGS=-fopenmp
SOURCES=graph.cpp solution.cpp greedy.cpp fullsearch.cpp graphs.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=graphs

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *.o $(EXECUTABLE)
