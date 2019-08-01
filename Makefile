OFILES = src/main.o src/bus.o

CXXFLAGS := -std=c++11
LDFLAGS :=

TARGET=wcEmu

all: wcEmu

$(TARGET): $(OFILES) Makefile
	$(CXX) -o $(TARGET) $(LDFLAGS) $(OFILES)

clean:
	rm -f $(OFILES) $(TARGET)
