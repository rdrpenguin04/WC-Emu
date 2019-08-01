CXX := g++

OFILES=src/main.o

LDFLAGS :=

TARGET=wcEmu

all: wcEmu

$(TARGET): $(OFILES) | Makefile
	$(CXX) -o $(TARGET) $(LDFLAGS) $(OFILES)
