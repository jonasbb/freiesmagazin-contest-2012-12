/**
    (C) Copyright 2012 Dominik Wagenfuehr

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as
    published by the Free Software Foundation; either version 3 of the
    License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public
    License along with this program. If not, see
    <http://www.gnu.org/licenses/>.
*/

#ifndef TCARDDECK_HH
#define TCARDDECK_HH

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <deque>
#include <iostream>
#include <sstream>
#include <sys/time.h>

/// Template fuer einen Kartenstapel.
/**
 * Intern handelt es sich nicht um einen Kartenstapel, sondern
 * um einen Nachzieh- und einen Ablagestapel.
 * Wenn man bei der Initialisierung Karten zum Ablagestapel
 * hinzufuegt, muss man noch neu mischen, ansonsten bleibt der
 * Nachziehstapel leer.
 */
template <class CARD>
class TCardDeck
{
  public:
    /// Konstruktor.
    TCardDeck();
  
    /// Fuegt eine Karte zum Ablagestapel hinzu.
    /**
     * @param card Hinzuzufuegende Karte.
     * @see getNextCard
     */
    void addCard( const CARD& card );

    /// Liefert die oberste Karte vom Nachziehstapel.
    /**
     * Die Karte wird mit dem Aufruf vom Nachziehstapel entfernt
     * und kann mittels addCard auf dem Ablagestapel abgelegt
     * werden.
     * @return Die oberste Karte vom Stapel.
     * @see addCard
     */
    CARD getNextCard();

    /// Ist der Nachziehstapel leer.
    /**
     * @return true, wenn der Nachziehstapel leer ist
     */
    bool isEmpty() const;

    /// Ist der Nachziehstapel und Ablagestapel leer.
    /**
     * @return true, wenn der Nachziehstapel und der Ablagestapel
     * leer ist
     */
    bool isBothEmpty() const;

    /// Mischt den Ablagestapel und Nachziehstapel zusammen.
    /**
     * Die Methode fuegt alle Karten vom Ablagestapel zum
     * Nachziehstapel hinzu und mischt alles neu durch.
     */
    void shuffle();

    /// Mischt den Ablagestapel und legt in auf den Nachziehstapel.
    /**
     * Die Methode mischt zuerst den Ablagestapel neu und legt ihn
     * einfach den Nachziehstapel. Das heißt, die abgelegten Karten
     * werden zuerst wieder gezogen.
     */
    void shuffleUsed();

    /// Gibt beide Stapel auf stdlog aus.
    void print() const;

  private:
    /// Der Nachziehstapel.
    std::deque<CARD> mCards;

    /// Der Ablagestapel.
    std::deque<CARD> mUsedCards;
};

// Konstruktor.
template <typename CARD>
TCardDeck<CARD>::TCardDeck()
{
    // From http://stackoverflow.com/questions/322938/recommended-way-to-initialize-srand
    // The contest may be started several times a second.
    // so a simple srand ( time(NULL) ); is not enough!
    
    struct timeval curtime;
    gettimeofday(&curtime,NULL);

    // microsecond has 1 000 000
    // Assuming you did not need quite that accuracy
    // Also do not assume the system clock has that accuracy.
    srand((curtime.tv_sec * 1000) + curtime.tv_usec);
}

// Fuegt eine Karte unter den Stapel hinzu.
template <typename CARD>
void TCardDeck<CARD>::addCard( const CARD& card )
{
    mUsedCards.push_back( card );
}

// Liefert die oberste Karte vom Stapel.
template <typename CARD>
CARD TCardDeck<CARD>::getNextCard()
{
    CARD tempCard = mCards.front();
    mCards.pop_front();
    return tempCard;
}

// Ist der Kartenstapel leer.
template <typename CARD>
bool TCardDeck<CARD>::isEmpty() const
{
    return mCards.empty();
}

// Ist der Kartenstapel leer.
template <typename CARD>
bool TCardDeck<CARD>::isBothEmpty() const
{
    return mCards.empty() && mUsedCards.empty();
}

// Mischt den Ablagestapel und Nachziehstapel zusammen.
template <typename CARD>
void TCardDeck<CARD>::shuffle()
{
    // Benutzte Karten vom Ablage- zum Nachziehstapel legen.
    while ( !mUsedCards.empty() )
    {
        CARD tempCard = mUsedCards.back();
        mUsedCards.pop_back();
        mCards.push_front( tempCard );
    }

    // using built-in random generator:
    std::random_shuffle ( mCards.begin(), mCards.end() );
}

// Mischt den Ablagestapel und legt in auf den Nachziehstapel.
template <typename CARD>
void TCardDeck<CARD>::shuffleUsed()
{
    // using built-in random generator:
    std::random_shuffle ( mUsedCards.begin(), mUsedCards.end() );

    // Benutzte Karten vom Ablage- zum Nachziehstapel legen.
    while ( !mUsedCards.empty() )
    {
        CARD tempCard = mUsedCards.back();
        mUsedCards.pop_back();
        mCards.push_front( tempCard );
    }
}

// Gibt den Stapel auf stdlog aus.
template <typename CARD>
void TCardDeck<CARD>::print() const
{
    // std::deque<CARD>::const_iterator it;
    // Das kompiliert seltsamerweise nicht, mit <int> geht es.
    // Also iterieren wir manuell.

    std::ostringstream out;
    out << "(II) TCardDeck<CARD>::print"
        << " New Cards: " 
        << mCards.size()
        << std::endl;
    std::clog << out.str();

    for ( size_t ii = 0; ii < mCards.size(); ii++ )
    {
        std::ostringstream out;
        out << "(II) "
            << ii << " "
            << mCards.at(ii)->print()
            << std::endl;
        std::clog << out.str();
    }

    std::ostringstream out2;
    out2 << "(II) TCardDeck<CARD>::print"
         << " Used Cards: " 
         << mUsedCards.size()
         << std::endl;
    std::clog << out2.str();

    for ( size_t ii = 0; ii < mUsedCards.size(); ii++ )
    {
        std::ostringstream out;
        out << "(II) "
            << ii << " "
            << mUsedCards.at(ii)->print()
            << std::endl;
        std::clog << out.str();
    }
}

#endif // TCARDDECK_HH
