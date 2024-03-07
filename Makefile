TARGET=mips-sim
CXX=g++
CXXFLAGS=-Wall
OBJECTS=mips-sim.o code.o word.o register.o cpu.o dataMemory.o cache1.o cache2.o

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^
mips-sim.o: mips-sim.cpp
	$(CXX) $(CXXFLAGS) -c $^
code.o: code.cpp
	$(CXX) $(CXXFLAGS) -c $^
word.o: word.cpp
	$(CXX) $(CXXFLAGS) -c $^
register.o: register.cpp
	$(CXX) $(CXXFLAGS) -c $^
cpu.o: cpu.cpp
	$(CXX) $(CXXFLAGS) -c $^
dataMemory.o: dataMemory.cpp
	$(CXX) $(CXXFLAGS) -c $^
cache1.o: cache1.cpp
	$(CXX) $(CXXFLAGS) -c $^
cache2.o: cache2.cpp
	$(CXX) $(CXXFLAGS) -c $^
clean:
	rm $(OBJECTS) $(TARGET)