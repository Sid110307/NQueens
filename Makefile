CC=clang++
EXECUTABLE_DIR=bin
CPPFLAGS=-std=c++11 -Wall -Wextra

.PHONY: all
all: clean queens

queens: main.cpp
	mkdir -p $(EXECUTABLE_DIR)
	$(CC) $(CPPFLAGS) -o $(EXECUTABLE_DIR)/$@ $^
	./$(EXECUTABLE_DIR)/$@

clean:
	rm -rf $(EXECUTABLE_DIR)

