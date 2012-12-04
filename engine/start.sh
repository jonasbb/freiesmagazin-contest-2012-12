#!/bin/bash

# Aufruf:
# ./start.sh FIELDNAME BOT [GUI]

if [ $# -ne 2 ]
then
    if [ $# -ne 3 ]
    then
        echo "Fehler: Es werden zwei oder drei Argumente erwartet!"
        echo "Aufruf:   $0 FIELDNAME BOT [OPTIONS]"
        echo "Beispiel: $0 \"fields/simple.txt\" \"bots/dummybot/bot\""
        echo "          $0 \"fields/simple.txt\" \"bots/dummybot/bot\" --log"
        exit 1
    fi
fi

FIELDNAME="$1"
BOT="$2"
OPTIONS="$3"

# Loesche alte Pipe (wirklich nur Pipes)
if [ -p pipe1 ]
then
    rm pipe1 || exit $?
fi

# Erstelle neue Pipe
mkfifo pipe1 || exit $?

# Pipe muss nun existieren
if [ ! -p pipe1 ]
then
    echo "Fehler: Pipe 1 existiert nicht!"
    exit 3
fi

# Starte Spiel
./game.bin $OPTIONS $FIELDNAME <(<pipe1 $BOT) pipe1 || exit $?
