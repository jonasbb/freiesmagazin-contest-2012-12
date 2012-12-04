# source files
SOURCES = Bot.cpp                   \
          EndMessage.cpp            \
          FloodMessage.cpp          \
          GameboardEndMessage.cpp   \
          GameboardLineMessage.cpp  \
          GameboardStartMessage.cpp \
          IncrFloodMessage.cpp      \
          MessageHandler.cpp        \
          MessageId.cpp             \
          Position.cpp              \
          StartMessage.cpp          \
          StdTextStream.cpp         \
          TextMessage.cpp

HEADERS = Bot.hh                    \
          EndMessage.hh             \
          FloodMessage.hh           \
          GameboardEndMessage.hh    \
          GameboardLineMessage.hh   \
          GameboardStartMessage.hh  \
          IncrFloodMessage.hh       \
          IMessage.hh               \
          IMessageOperator.hh       \
          IStrategy.hh              \
          ITextStream.hh            \
          MessageHandler.hh         \
          MessageId.hh              \
          Position.hh               \
          StartMessage.hh			\
          StdTextStream.hh          \
          TextMessage.hh

OBJECTS = $(SOURCES:.cpp=.o)

OUTPUT = ./libbot.a

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

