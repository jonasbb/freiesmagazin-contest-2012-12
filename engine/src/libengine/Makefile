# source files
SOURCES = EngineConfig.cpp             \
          EngineConfigCreator.cpp      \
          Engine.cpp

HEADERS = EngineConfig.hh              \
          EngineConfigCreator.hh       \
          Engine.hh

OBJECTS = $(SOURCES:.cpp=.o)

OUTPUT = ./libengine.a

# include directories
INCLUDES = -I./ -I../libgame/ -I../libcommand/ -I../libcards/ -I../libtiles/ -I../libserver/

# C++ compiler flags (-g -O2 -Wall -DDEBUG)
CXXFLAGS = -O3 -Wall

ifdef DEBUG
   CXXFLAGS += -g -DDEBUG
endif

# compiler
CXX = g++

# library paths
LIBS = -L./

# compile flags
LDFLAGS = 

# implementation

all: $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	ar rcs $(OUTPUT) $(OBJECTS)

$(OBJECTS): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(SOURCES)

clean:
	rm -f $(OBJECTS) $(OUTPUT)

