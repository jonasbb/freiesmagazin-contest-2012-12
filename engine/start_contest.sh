#!/bin/bash

# Aufruf:
# ./start_contest.sh $FIELDNAME $ANZAHL

if [ ! $# -eq 2 ]
then
    echo "Fehler: Es werden zwei Argumente erwartet!"
    echo "Aufruf:   $0 FELDNAME ANZAHL"
    echo "Beispiel: $0 \"fields/simple.txt\" 100"
    exit 1
fi

FIELDNAME="$1"
NUMITER="$2"

BOTS=( \
        "bots/dummybot/bot"
      )

for BOT in "${BOTS[@]}"
do
    echo "(II) BOT: $BOT"
    echo "(II) START `date`"
    for NUM in `seq 1 $NUMITER`
    do
        ./start.sh "$FIELDNAME" "$BOT" 
    done
    echo "(II) END `date`"
done



