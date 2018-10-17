PACKAGE = gomoku

# Build info
EXE         = $(PACKAGE)
CDEBUG      = -O2
CXXFLAGS    = $(CDEBUG) -Wall -Wextra $(CFLAGS_PLATFORM)
LDFLAGS     = -lncurses $(LDFLAGS_PLATFORM)
INCLUDESDIR = -I"src/"

# Project source files
CFILES   = $(shell find src -type f -name '*.c')
CXXFILES = $(shell find src -type f -name '*.cpp')
OBJECTS  = $(CFILES:.c=.o) \
           $(CXXFILES:.cpp=.o)

$(EXE): $(OBJECTS) $(ENGINE_OBJECTS)
	# Linking...
	$(CXX) $(OBJECTS) $(ENGINE_OBJECTS) -o bin/$(EXE) $(LDFLAGS)

src/%.o: src/%.cpp
	# Compiling $<...
	$(CXX) $(CXXFLAGS) $(CDEBUG) $< -c -o $@ $(INCLUDESDIR)

run: dirs $(EXE)
	# Running...
	./bin/$(EXE)

clean:
	# Cleaning object files...
	rm -f $(OBJECTS)
	rm -f bin/$(EXE)

dirs:
	mkdir -p bin

