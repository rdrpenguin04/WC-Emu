OFILES = src/main.o src/bus.o src/w65c816s.o

CXXFLAGS := -std=c++11
CFLAGS := -std=c11
LDFLAGS :=

TARGET=wcEmu

all: wcEmu

$(TARGET): $(OFILES) Makefile
	$(CXX) -o $(TARGET) $(LDFLAGS) $(OFILES)

clean:
	rm -f $(OFILES) $(TARGET)

rebuild:
	make clean
	+make
