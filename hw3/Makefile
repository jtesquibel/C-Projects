CXX = g++
CPPFLAGS = -g -Wall
BIN_DIR = bin
GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

all: $(BIN_DIR)/prob2 $(BIN_DIR)/prob3 $(BIN_DIR)/prob4

$(BIN_DIR)/prob2: $(BIN_DIR)/.dirstamp $(BIN_DIR)/llistint.o
	$(CXX) $(CPPFLAGS) llistintTest.cpp $(BIN_DIR)/llistint.o -o $@

$(BIN_DIR)/llistint.o: src/llistint.cpp lib/llistint.h
	$(CXX) $(CPPFLAGS) -c src/llistint.cpp -o $@

$(BIN_DIR)/prob3: $(BIN_DIR)/.dirstamp $(BIN_DIR)/setint.o $(BIN_DIR)/llistint.o
	$(CXX) $(CPPFLAGS) test.cpp $(BIN_DIR)/setint.o $(BIN_DIR)/llistint.o -o $@

$(BIN_DIR)/setint.o: src/setint.cpp lib/setint.h
	$(CXX) $(CPPFLAGS) -c src/setint.cpp -o $@

$(BIN_DIR)/prob4: $(BIN_DIR)/.dirstamp $(BIN_DIR)/alistint.o
	$(CXX) $(CPPFLAGS) stlmap.cpp $(BIN_DIR)/alistint.o -o $@

$(BIN_DIR)/alistint.o: src/alistint.cpp lib/alistint.h
	$(CXX) $(CPPFLAGS) -c src/alistint.cpp -o $@

.PHONY: clean copytest

copytest: $(BIN_DIR)/llistintTest
	-@$(BIN_DIR)/llistintTest
	-@echo "--- All Tested!---"

clean:
	rm -rf $(BIN_DIR)

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp