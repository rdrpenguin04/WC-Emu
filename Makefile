WCEMU_OFILES = src/main.o src/bus.o src/w65c816s.o src/components/ram.o src/components/rom.o src/components/charPort.o src/socket.o
WCCONNECT_OFILES = src/connect.o src/socket.o

CXXFLAGS := -pedantic -g -std=c++11
CFLAGS := -pedantic -g -std=c11
LDFLAGS := -g

WCEMU_TARGET = wcEmu
WCCONNECT_TARGET = wcConnect
TARGETS = $(WCEMU_TARGET) $(WCCONNECT_TARGET)

all: $(TARGETS)

$(WCEMU_TARGET): $(WCEMU_OFILES) Makefile
	$(CXX) -o $(WCEMU_TARGET) $(LDFLAGS) $(WCEMU_OFILES)

$(WCCONNECT_TARGET): $(WCCONNECT_OFILES) Makefile
	$(CXX) -o $(WCCONNECT_TARGET) $(LDFLAGS) $(WCCONNECT_OFILES)

clean:
	rm -f $(WCEMU_OFILES) $(WCCONNECT_OFILES) $(TARGETS)

rebuild:
	make clean
	+make

run-emu: $(WCEMU_TARGET)
	$(WCEMU_TARGET)
