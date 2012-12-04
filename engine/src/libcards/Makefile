# source files
SOURCES = FloodCard.cpp       \
          NoFloodCard.cpp     \
          Position.cpp        \
          PositionCard.cpp

HEADERS = FloodCard.hh        \
          FloodCardDeck.hh    \
          IFloodCard.hh       \
          NoFloodCard.hh      \
          Position.hh         \
          PositionCard.hh     \
          PositionCardDeck.hh \
          PositionCardPointerVector.hh \
          TCardDeck.hh

OBJECTS = $(SOURCES:.cpp=.o)

OUTPUT = ./libcards.a

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

