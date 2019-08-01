OFILES = src/main.o src/bus.o

CFLAGS := -std=c++11
LDFLAGS := -std=c++11

TARGET=wcEmu

all: wcEmu

$(TARGET): $(OFILES) Makefile
	$(CXX) -o $(TARGET) $(LDFLAGS) $(OFILES)

clean:
	rm -f $(OFILES) $(TARGET)
