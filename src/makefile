CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET_DIR = ..
TARGET = $(TARGET_DIR)/PasswordManagerApp
SRC = main.cpp PasswordManager.cpp

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

.PHONY: clean
clean:
	rm -f $(TARGET)
