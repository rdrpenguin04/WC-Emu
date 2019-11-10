OFILES = src/main.o src/bus.o src/w65c816s.o src/components/ram.o src/components/rom.o src/components/charPort.o

CXXFLAGS := -pedantic -g -std=c++11
CFLAGS := -pedantic -g -std=c11
LDFLAGS := -g

TARGET=./wcEmu

all: $(TARGET)

$(TARGET): $(OFILES) Makefile
	$(CXX) -o $(TARGET) $(LDFLAGS) $(OFILES)

clean:
	rm -f $(OFILES) $(TARGET)

rebuild:
	make clean
	+make

run: $(TARGET)
	$(TARGET)
