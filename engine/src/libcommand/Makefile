# source files
SOURCES = CommandDryCurrent.cpp  \
          CommandDryEast.cpp     \
          CommandDryNorth.cpp    \
          CommandDrySouth.cpp    \
          CommandDryWest.cpp     \
          CommandGoCurrent.cpp   \
          CommandGoEast.cpp      \
          CommandGoNorth.cpp     \
          CommandGoSouth.cpp     \
          CommandGoWest.cpp      \
          CommandInterpreter.cpp \
          CommandProcessor.cpp

HEADERS = CommandDryCurrent.hh  \
          CommandDryEast.hh     \
          CommandDryNorth.hh    \
          CommandDrySouth.hh    \
          CommandDryWest.hh     \
          CommandGoCurrent.hh   \
          CommandGoEast.hh      \
          CommandGoNorth.hh     \
          CommandGoSouth.hh     \
          CommandGoWest.hh      \
          CommandInterpreter.hh \
          CommandProcessor.hh   \
          ICommand.hh           \
          ICommandContext.hh

OBJECTS = $(SOURCES:.cpp=.o)

OUTPUT = ./libcommand.a

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

