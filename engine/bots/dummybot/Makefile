# source files
SOURCES = Strategy.cpp     \
          StrategyData.cpp \
          main.cpp

HEADERS = Strategy.hh      \
          StrategyData.hh

OBJECTS = $(SOURCES:.cpp=.o)

OUTPUT = ./bot

# include directories
INCLUDES = -I./ -I../../src/libbot/

# C++ compiler flags (-g -O2 -Wall -DDEBUG)
CXXFLAGS = -O3 -Wall

# compiler
CXX = g++

# library paths
LIBS = -L./ -L../../src/libbot/ -lbot

# compile flags
LDFLAGS = 

# implementation

all: lib $(OUTPUT)

lib:
	cd ../../src/libbot && make && cd ../../bots/dummybot

$(OUTPUT): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(OUTPUT) $(OBJECTS) $(LIBS) $(LDFLAGS)

$(OBJECTS): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(SOURCES)

clean:
	cd ../../src/libbot && make clean && cd ../../bots/dummybot && \
	rm -f $(OBJECTS) $(OUTPUT)

