# qmake-File for the GUI

TEMPLATE      = app
QT           *= gui
CONFIG       -= release debug_and_release debug
CONFIG       *= qt console warn_on
CONFIG       *= release
TARGET        = gui
QMAKE_CXXFLAGS_DEBUG -= -DDEBUG

HEADERS       = CommandHandler.hh    \
                CommandWindow.hh     \
                GameArea.hh          \
                GameWindow.hh        \
                GameData.hh          \
                SingleTextStream.hh  \
                MessageProcessor.hh 
                
SOURCES       = CommandHandler.cpp   \
                CommandWindow.cpp    \
                GameArea.cpp         \
                GameWindow.cpp       \
                GameData.cpp         \
                SingleTextStream.cpp \
                MessageProcessor.cpp \
                main.cpp

INCLUDEPATH   = . \
                ../src/libtiles \
                ../src/libgame  \
                ../src/libbot
                
LIBS         += -L../src/libtiles \
                -L../src/libgame  \
                -L../src/libbot   \
                -lbot -lgame -ltiles

# install
target.path = .
sources.files = $$SOURCES $$HEADERS
sources.path = .
INSTALLS += target sources
