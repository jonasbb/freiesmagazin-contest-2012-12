# source files
SOURCES = Game.cpp      \
          Gameboard.cpp \
          Player.cpp

HEADERS = Game.hh       \
          Gameboard.hh  \
          IGame.hh      \
          Player.hh

OBJECTS = $(SOURCES:.cpp=.o)

OUTPUT = ./libgame.a

# include directories
INCLUDES = -I./ -I../libcommand/ -I../libcards/ -I../libtiles/

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

