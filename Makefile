CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra
TARGET = lab2
OBJS = main.o stack_asteroids.o set_operations.o array_stress.o tree_traversal.o hash_table.o lru_cache.o

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp stack_asteroids.h set_operations.h array_stress.h tree_traversal.h hash_table.h lru_cache.h
	$(CXX) $(CXXFLAGS) -c main.cpp

stack_asteroids.o: stack_asteroids.cpp stack_asteroids.h
	$(CXX) $(CXXFLAGS) -c stack_asteroids.cpp

set_operations.o: set_operations.cpp set_operations.h
	$(CXX) $(CXXFLAGS) -c set_operations.cpp

array_stress.o: array_stress.cpp array_stress.h
	$(CXX) $(CXXFLAGS) -c array_stress.cpp

tree_traversal.o: tree_traversal.cpp tree_traversal.h
	$(CXX) $(CXXFLAGS) -c tree_traversal.cpp

hash_table.o: hash_table.cpp hash_table.h
	$(CXX) $(CXXFLAGS) -c hash_table.cpp

lru_cache.o: lru_cache.cpp lru_cache.h
	$(CXX) $(CXXFLAGS) -c lru_cache.cpp

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean
