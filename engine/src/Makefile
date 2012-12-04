# source files
SOURCES = main.cpp

OBJECTS = $(SOURCES:.cpp=.o)

OUTPUT = ../game.bin

# include directories
INCLUDES = -I./ -I./libengine/ -I./libgame/ -I./libcommand/ -I./libcards/ -I./libtiles/ -I./libserver/

# C++ compiler flags (-g -O2 -Wall -DDEBUG)
CXXFLAGS = -O3 -Wall

ifdef DEBUG
   CXXFLAGS += -g -DDEBUG
endif

# compiler
CXX = g++

# library paths
LIBS = -L./  -L./libengine/ -L./libgame/ -L./libcommand/ -L./libcards/ -L./libtiles/ -L./libserver/ -lengine -lgame -lcommand -lcards -ltiles -lserver

# compile flags
LDFLAGS = 

# implementation

all:
	make server  && \
	make tiles   && \
	make cards   && \
	make command && \
	make game    && \
	make engine  && \
	make bot     && \
	rm -f $(OBJECTS) $(OUTPUT) && \
	make output

server:
	cd libserver  && make && cd ..

tiles:
	cd libtiles   && make && cd ..

cards:
	cd libcards   && make && cd ..

command:
	cd libcommand && make && cd ..

game:
	cd libgame    && make && cd ..

engine:
	cd libengine  && make && cd ..

bot:
	cd libbot  && make && cd ..

output: $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(OUTPUT) $(OBJECTS) $(LIBS) $(LDFLAGS)

$(OBJECTS): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $(SOURCES)

clean:
	cd libserver  && make clean && cd .. && \
	cd libtiles   && make clean && cd .. && \
	cd libcards   && make clean && cd .. && \
	cd libcommand && make clean && cd .. && \
	cd libgame    && make clean && cd .. && \
	cd libengine  && make clean && cd .. && \
	cd libbot     && make clean && cd .. && \
	rm -f $(OBJECTS) $(OUTPUT)

