export CC=clang++
export EXECUTABLE_DIR=bin
export CPPFLAGS=-std=c++11 -Wall -Wextra

.PHONY: all
all: clean queens

queens: main.cpp
	mkdir -p $(EXECUTABLE_DIR)
	$(CC) $(CPPFLAGS) -o $(EXECUTABLE_DIR)/$@ $^

	echo "Compiled at $(EXECUTABLE_DIR)/$@."

windows: main.cpp
	@echo "Select build architecture:"
	@echo "1. x86 (32-bit)"
	@echo "2. x64 (64-bit)"
	@echo
	@while true; do \
		read -p "Enter your choice: " choice; \
		if [ "$$choice" -eq 1 ]; then \
			export ARCH="i686-w64-mingw32"; \
			break; \
		elif [ "$$choice" -eq 2 ]; then \
			export ARCH="x86_64-w64-mingw32"; \
			break; \
		else \
			echo "Invalid choice. Please enter 1 or 2."; \
		fi \
	done

	export CC="$$ARCH-g++"
	mkdir -p "$(EXECUTABLE_DIR)"; \
	$$CC ${CPPFLAGS} -o "$(EXECUTABLE_DIR)/queens.exe" main.cpp
	@echo "Compiled at $(EXECUTABLE_DIR)/queens.exe."

clean:
	rm -rf $(EXECUTABLE_DIR)
