CXX = g++
CXXFLAGS = -std=c++11 -Wall

SRCS = main.cpp PasswordManager.cpp
OBJS = $(SRCS:.cpp=.o)
EXEC = PasswordManagerApp

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@

main.o: main.cpp PasswordManager.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

PasswordManager.o: PasswordManager.cpp PasswordManager.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(EXEC)
