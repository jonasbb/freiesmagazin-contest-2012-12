# source files
SOURCES = BaseTile.cpp    \
          DryTile.cpp     \
          FloodedTile.cpp \
          LostTile.cpp    \
          TileContext.cpp \
          TileFactory.cpp \
          TileType.cpp

HEADERS = BaseTile.hh     \
          FloodedTile.hh  \
          ITile.hh        \
          TileFactory.hh  \
          DryTile.hh      \
          ITileContext.hh \
          LostTile.hh     \
          TileContext.hh  \
          TileType.hh

OBJECTS = $(SOURCES:.cpp=.o)

OUTPUT = ./libtiles.a

# include directories
INCLUDES = -I./

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

