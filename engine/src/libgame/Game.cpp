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

#include "Game.hh"
#include "FloodCard.hh"
#include "NoFloodCard.hh"
#include "PositionCard.hh"

#include <iostream>
#include <sstream>

// Konstruktor.
Game::Game()
: mGameBoard(), mPosCards(), mFloodCards(), mNumPosCardsDrawn(0)
{
}

// Destruktor.
Game::~Game()
{
    // Durchs Mischen landen alle Karten auf dem Nachziehstapel
    // und koennen danach mit getNextCard geholt und geloescht werden.
    mPosCards.shuffle();
    while( !mPosCards.isEmpty() )
    {
        PositionCard* cardP = mPosCards.getNextCard();
        delete cardP;
    }

    mFloodCards.shuffle();
    while( !mFloodCards.isEmpty() )
    {
        IFloodCard* cardP = mFloodCards.getNextCard();
        delete cardP;
    }
}

// Initialisiert das Spiel.
bool Game::init( const std::string& filename )
{
    bool init = false;
    
    mNumPosCardsDrawn = 0;
    if ( mGameBoard.load( filename ) &&
         setPlayerStartPosition() &&
         createPositionCards() &&
         createFloodCards() )
    {
        init = true;
    }

    return init;
}

// Gibt aktuelle Spielerposition zurueck.
const Position& Game::getPlayerPos() const
{
    return mPlayer.getPosition();
}

// Gibt zurueck, ob der Spieler verloren/untergegangen ist.
bool Game::hasPlayerLost() const
{
#ifdef DEBUG
    {
        std::ostringstream out;
        out << "(DD) Game::hasPlayerLost "
            << std::hex << this << std::dec
            << " Position: " << mPlayer.getPosition()
            << " Valid: " << mGameBoard.isValidPos( mPlayer.getPosition() )
            << " Lost: " << mGameBoard.isLost( mPlayer.getPosition() )
            << std::endl;
        std::clog << out.str();
    }
#endif


    return ( !mGameBoard.isValidPos( mPlayer.getPosition() ) ||
             mGameBoard.isLost( mPlayer.getPosition() ) );
}

// Holt die Informationen zum Spielbrett.
bool Game::getGameboardInfo( Position& size,
                             std::vector<std::string>& stringVector ) const
{
    bool retValue = false;
    
    if ( mGameBoard.getSize().isValid() )
    {
        size = mGameBoard.getSize();
        mGameBoard.print( stringVector );
        retValue = true;
    }

    return retValue;
}

// Setzt eine sinnvolle Spielerposition abhaengig vom Spielbrett.
bool Game::setPlayerStartPosition()
{
    bool posFound = false;

    Position pos;

    if ( mGameBoard.getSize().isValid() )
    {
        // Wir suchen das erste trockene Feld.
        for ( unsigned int jj = 1; jj <= mGameBoard.getSize().y(); jj++ )
        {
            for ( unsigned int ii = 1; ii <= mGameBoard.getSize().x(); ii++ )
            {
                pos.setPosition( ii,jj );

                if ( mGameBoard.isDry(pos) )
                {
                    posFound = true;
                    break;
                }
            }
            if ( posFound )
            {
                break;
            }
        }

        if ( !posFound )
        {
            // Es gab kein trockenes Feld auf dem Spielbrett.
            // Also suchen wir zumindest ein geflutetes, nicht
            // untergegangenes Feld.
            for ( unsigned int jj = 1; jj <= mGameBoard.getSize().y(); jj++ )
            {
                for ( unsigned int ii = 1; ii <= mGameBoard.getSize().x(); ii++ )
                {
                    pos.setPosition( ii,jj );
                    if ( mGameBoard.isFlooded( pos ) )
                    {
                        posFound = true;
                        break;
                    }
                }
                if ( posFound )
                {
                    break;
                }
            }
        }
    }
    else
    {
        std::ostringstream out;
        out << "(EE) Game::setPlayerStartPosition "
            << std::hex << this << std::dec
            << " Gameboard size "
            <<  mGameBoard.getSize()
            << " is not valid."
            << std::endl;
        std::cerr << out.str();
    }

    if ( !posFound )
    {
        // Kein valides Feld gefunden oder es kam zu einem Fehler.
        std::ostringstream out;
        out << "(EE) Game::setPlayerStartPosition "
            << std::hex << this << std::dec
            << " Did not find valid start position."
            << std::endl;
        std::cerr << out.str();
    }
    else
    {
#ifdef DEBUG
        std::ostringstream out;
        out << "(DD) Gameboard::searchStartPosition "
            << std::hex << this << std::dec
            << " Position: "
            << pos
            << " Valid: "
            << posFound
            << "."
            << std::endl;
        std::clog << out.str();        
#endif // DEBUG

        mPlayer.setPosition(pos);
    }

    return posFound;
}

// Erstellt Positionskarten abhaengig vom Spielbrett.
bool Game::createPositionCards()
{
    bool errorOccured = false;
    
    if ( mGameBoard.getSize().isValid() )
    {
        Position pos;

        for ( unsigned int jj = 1; jj <= mGameBoard.getSize().y(); jj++ )
        {
            for ( unsigned int ii = 1; ii <= mGameBoard.getSize().x(); ii++ )
            {
                pos.setPosition( ii, jj );

                // Nur fuer trockene oder ueberflutete Felder
                // fuegen wir eine Positionskarte hinzu.
                if ( ( mGameBoard.isDry( pos ) ) ||
                     ( mGameBoard.isFlooded( pos ) ) )
                {
                    mPosCards.addCard( new PositionCard(pos) );
                }
            }
        }
    }
    else
    {
        std::ostringstream out;
        out << "(EE) Game::createPositionCards "
            << std::hex << this << std::dec
            << " Gameboard size "
            <<  mGameBoard.getSize()
            << " is not valid."
            << std::endl;
        std::cerr << out.str();

        errorOccured = true;
    }

    if ( errorOccured )
    {
        std::ostringstream out;
        out << "(EE) Game::createPositionCards "
            << std::hex << this << std::dec
            << " Error creating card std::deck."
            << std::endl;
        std::cerr << out.str();
    }
    else
    {
        // Karten mischen.
        mPosCards.shuffle();
        // mPosCards.print();

#ifdef DEBUG
        std::ostringstream out;
        out << "(DD) Game::createPositionCards (shuffle) "
            << std::hex << this << std::dec
            << std::endl;
        std::clog << out.str();
        // mPosCards.print();
#endif
    }

    return !errorOccured;
}

// Erstelle Flutkarten.
bool Game::createFloodCards()
{
    // Wir erstellen genau 10 Flutkarten, wobei 2
    // Flutkarten und 8 leere Karten dabei sind.

    for ( unsigned int ii = 0; ii < 8; ii++ )
    {
        mFloodCards.addCard( new NoFloodCard() );
    }
    for ( unsigned int ii = 8; ii < 10; ii++ )
    {
        mFloodCards.addCard( new FloodCard() );
    }

    // Karten mischen
    mFloodCards.shuffle();

    return true;
}
    
// Bewegt den Spieler ein Feld nach rechts.
bool Game::movePlayerEast()
{
    bool retValue = false;

    const Position pos = mPlayer.getPosition();
    const Position newPos( pos.x()+1, pos.y() );

    if ( mGameBoard.isValidPos( newPos, true ) )
    {
        mPlayer.setPosition( newPos );
        retValue = true;
    }
    else
    {
        std::ostringstream out;
        out << "(WW) Game::movePlayerEast "
            << std::hex << this << std::dec
            << " Player is moving outside of board "
            << " from " << pos << " to " << newPos << "."
            << std::endl;
        std::cerr << out.str();
        
        retValue = false;
    }

    return retValue;
}

// Bewegt den Spieler ein Feld nach oben.
bool Game::movePlayerNorth()
{
    bool retValue = false;

    const Position pos = mPlayer.getPosition();
    const Position newPos( pos.x(), pos.y()-1 );

    if ( mGameBoard.isValidPos( newPos, true ) )
    {
        mPlayer.setPosition( newPos );
        retValue = true;
    }
    else
    {
        std::ostringstream out;
        out << "(WW) Game::movePlayerNorth "
            << std::hex << this << std::dec
            << " Player is moving outside of board "
            << " from " << pos << " to " << newPos << "."
            << std::endl;
        std::cerr << out.str();
        
        retValue = false;
    }

    return retValue;
}

// Bewegt den Spieler ein Feld nach unten.
bool Game::movePlayerSouth()
{
    bool retValue = false;

    const Position pos = mPlayer.getPosition();
    const Position newPos( pos.x(), pos.y()+1 );

    if ( mGameBoard.isValidPos( newPos, true ) )
    {
        mPlayer.setPosition( newPos );
        retValue = true;
    }
    else
    {
        std::ostringstream out;
        out << "(WW) Game::movePlayerSouth "
            << std::hex << this << std::dec
            << " Player is moving outside of board "
            << " from " << pos << " to " << newPos << "."
            << std::endl;
        std::cerr << out.str();
        
        retValue = false;
    }

    return retValue;
}

// Bewegt den Spieler ein Feld nach links.
bool Game::movePlayerWest()
{
    bool retValue = false;

    const Position pos = mPlayer.getPosition();
    const Position newPos( pos.x()-1, pos.y() );

    if ( mGameBoard.isValidPos( newPos, true ) )
    {
        mPlayer.setPosition( newPos );
        retValue = true;
    }
    else
    {
        std::ostringstream out;
        out << "(WW) Game::movePlayerWest "
            << std::hex << this << std::dec
            << " Player is moving outside of board "
            << " from " << pos << " to " << newPos << "."
            << std::endl;
        std::cerr << out.str();
        
        retValue = false;
    }

    return retValue;
}

// Lege das Feld, auf dem der Spieler steht, trocken.
bool Game::drainTileCurrent()
{
    bool retValue = false;

    const Position pos = mPlayer.getPosition();
    const Position newPos( pos.x(), pos.y() );

    if ( mGameBoard.isValidPos( newPos, true ) )
    {
        retValue = mGameBoard.drain( newPos );
    }
    else
    {
        std::ostringstream out;
        out << "(WW) Game::drainTileCurrent "
            << std::hex << this << std::dec
            << " Field is not valid at position "
            << newPos << "."
            << std::endl;
        std::cerr << out.str();
        
        retValue = false;
    }

    return retValue;
}

// Lege das Feld rechts vom Spieler trocken.
bool Game::drainTileEast()
{
    bool retValue = false;

    const Position pos = mPlayer.getPosition();
    const Position newPos( pos.x()+1, pos.y() );

    if ( mGameBoard.isValidPos( newPos, true ) )
    {
        retValue = mGameBoard.drain( newPos );
    }
    else
    {
        std::ostringstream out;
        out << "(WW) Game::drainTileCurrent "
            << std::hex << this << std::dec
            << " Field is not valid at position "
            << newPos << "."
            << std::endl;
        std::cerr << out.str();
        
        retValue = false;
    }

    return retValue;
}

// Lege das Feld unterhalb vom Spieler trocken.
bool Game::drainTileNorth()
{
    bool retValue = false;

    const Position pos = mPlayer.getPosition();
    const Position newPos( pos.x(), pos.y()-1 );

    if ( mGameBoard.isValidPos( newPos, true ) )
    {
        retValue = mGameBoard.drain( newPos );
    }
    else
    {
        std::ostringstream out;
        out << "(WW) Game::drainTileCurrent"
            << std::hex << this << std::dec
            << " Field is not valid at position "
            << newPos << "."
            << std::endl;
        std::cerr << out.str();
        
        retValue = false;
    }

    return retValue;
}

// Lege das Feld ueberhalb vom Spieler trocken.
bool Game::drainTileSouth()
{
    bool retValue = false;

    const Position pos = mPlayer.getPosition();
    const Position newPos( pos.x(), pos.y()+1 );

    if ( mGameBoard.isValidPos( newPos, true ) )
    {
        retValue = mGameBoard.drain( newPos );
    }
    else
    {
        std::ostringstream out;
        out << "(WW) Game::drainTileCurrent"
            << std::hex << this << std::dec
            << " Field is not valid at position "
            << newPos << "."
            << std::endl;
        std::cerr << out.str();
        
        retValue = false;
    }

    return retValue;
}

// Lege das Feld links vom Spieler trocken.
bool Game::drainTileWest()
{
    bool retValue = false;

    const Position pos = mPlayer.getPosition();
    const Position newPos( pos.x()-1, pos.y() );

    if ( mGameBoard.isValidPos( newPos, true ) )
    {
        retValue = mGameBoard.drain( newPos );
    }
    else
    {
        std::ostringstream out;
        out << "(WW) Game::drainTileCurrent"
            << std::hex << this << std::dec
            << " Field is not valid at position "
            << newPos << "."
            << std::endl;
        std::cerr << out.str();
        
        retValue = false;
    }

    return retValue;
}

// Ziehe eine bestimmte Anzahl von Positionskarten und ueberflute zugehoerige Felder.
bool Game::drawPositionCardsAndFloodTiles( std::vector<Position>& floodedPositions )
{
    bool retValue = true;

#ifdef DEBUG
    {
        std::ostringstream out;
        out << "(DD) Game::drawPositionCardsAndFloodTiles Begin "
            << std::hex << this << std::dec
            << " Num: " << mNumPosCardsDrawn
            << std::endl;
        std::clog << out.str();
    }
#endif

    unsigned int counter = 0;
    floodedPositions.clear();

    while ( counter < mNumPosCardsDrawn )
    {
        // Wir machen weiter, bis wir genuegend Positionen gezogen haben.
        if ( mPosCards.isEmpty() )
        {
            // Der Nachziehstapel ist leer.
#ifdef DEBUG
            {
                std::ostringstream out;
                out << "(DD) Game::drawPositionCardsAndFloodTiles "
                    << std::hex << this << std::dec
                    << " Position cards draw deck is empty!"
                    << std::endl;
                std::clog << out.str();
            }
#endif
            if ( mPosCards.isBothEmpty() )
            {
                // Sowohl der Nachziehstapel, als auch der Ablagestapel
                // sind leer.
#ifdef DEBUG
                std::ostringstream out;
                out << "(DD) Game::drawPositionCardsAndFloodTiles "
                    << std::hex << this << std::dec
                    << " Both decks are empty!"
                    << std::endl;
                std::clog << out.str();
#endif
                break;
            }
            else
            {
                // Es sind noch Karten auf dem Ablagestapel, also
                // mische neu.
                mPosCards.shuffle();
            }
        }

        if ( mPosCards.isEmpty() )
        {
            // Wir haben wirklich keine einzige Karte mehr zum Ziehen.
            // Dann brechen wir hier ab. Das ist aber okay.
            retValue = true;
            break;
        }
        else
        {
            // Karte ziehen.
            PositionCard* cardP = mPosCards.getNextCard();
            if ( cardP )
            {
                // Wir ueberfluten das Feld und speichern uns die Position.
                const Position& pos = cardP->getPos();

#ifdef DEBUG
                {
                    std::ostringstream out;
                    out << "(DD) Game::drawPositionCardsAndFloodTiles "
                        << std::hex << this << std::dec
                        << " Flood: " << pos
                        << std::endl;
                    std::clog << out.str();
                    // mPosCards.print();
                    // mGameBoard.print();
                }
#endif
                    
                // Flute das Feld mit der Position der Karte.
                mGameBoard.flood( pos );
                counter++;
                floodedPositions.push_back( pos );

#ifdef DEBUG
                {
                    std::ostringstream out;
                    out << "(DD) Game::drawPositionCardsAndFloodTiles "
                        << std::hex << this << std::dec
                        << " Flood done!"
                        << std::endl;
                    std::clog << out.str();
                    // mPosCards.print();
                    // mGameBoard.print();
                }
#endif

                // Wenn das Feld nun nicht verloren ist, fuegt
                // man die Positionskarte zum Ablagestapel hinzu,
                // sodass sie spaeter wieder gezogen werden kann.
                if ( !mGameBoard.isLost( pos ) )
                {
#ifdef DEBUG
                    {
                        std::ostringstream out;
                        out << "(DD) Game::drawPositionCardsAndFloodTiles "
                            << std::hex << this << std::dec
                            << " Tile is not lost! Add card again!"
                            << std::endl;
                        std::clog << out.str();
                    }
#endif

                    mPosCards.addCard( cardP );
                }
                
#ifdef DEBUG
                {
                    std::ostringstream out;
                    out << "(DD) Game::drawPositionCardsAndFloodTiles "
                        << std::hex << this << std::dec
                        << " After adding!"
                        << std::endl;
                    std::clog << out.str();
                    // mPosCards.print();
                }
#endif
            }
            else
            {
                std::ostringstream out;
                out << "(EE) Game::drawPositionCardsAndFloodTiles "
                    << std::hex << this << std::dec
                    << " Pointer to position card is 0!"
                    << std::endl;
                std::cerr << out.str();
                retValue = false;
                break;
            }
        }
    } // while

#ifdef DEBUG
    {
        std::ostringstream out;
        out << "(DD) Game::drawPositionCardsAndFloodTiles End "
            << std::hex << this << std::dec
            << " Num: " << counter
            << std::endl;
            
        std::clog << out.str();
    }
#endif

    return retValue;
}

// Ziehe neue Flutkarten.
bool Game::drawFloodCards( unsigned int& numNewFloodCards )
{
    bool retValue = true;

#ifdef DEBUG
    {
        std::ostringstream out;
        out << "(DD) Game::drawFloodCards Begin "
            << std::hex << this << std::dec
            << " numCards: " << mNumPosCardsDrawn
            << std::endl;
        std::clog << out.str();
    }
#endif

    numNewFloodCards = 0;

    if ( mFloodCards.isEmpty() )
    {
        // Wir haben keine Karten mehr zum ziehen.
        // Also mische wir neu.
        mFloodCards.shuffle();
    }
        
    // Wir ziehen eine Karte.
    for ( unsigned int ii = 0; ii < 1; ii++ )
    {
        IFloodCard* cardP = mFloodCards.getNextCard();
        
        if ( cardP )
        {
            if ( cardP->flood() )
            {
                // Diese Karte erhoeht die Flut.
                numNewFloodCards++;
            }
            // Karte wieder auf den Ablagestapel legen.
            mFloodCards.addCard( cardP );
        }
        else
        {
            std::ostringstream out;
            out << "(EE) Game::drawFloodCards"
                << std::hex << this << std::dec
                << " Pointer to flood card is 0!"
                << std::endl;
            std::cerr << out.str();
            retValue = false;
            break;
        }
    }

    if ( numNewFloodCards > 0 )
    {
        // Die Flut ist gestiegen, damit wird der Ablagestapel
        // der Positionskarten neu gemischt und auf den
        // Nachziehstapel gelegt.

#ifdef DEBUG
        {
            std::ostringstream out;
            out << "(DD) Game::drawFloodCards Before "
                << std::hex << this << std::dec
                << std::endl;
            std::clog << out.str();
            // mPosCards.print();
        }
#endif
        mPosCards.shuffleUsed();
#ifdef DEBUG
        {
            std::ostringstream out;
            out << "(DD) Game::drawFloodCards After "
                << std::hex << this << std::dec
                << std::endl;
            std::clog << out.str();
            // mPosCards.print();
        }
#endif
    }

    // Erhoehe Zaehler um die Anzahl gezogener Flutkarten.
    mNumPosCardsDrawn += numNewFloodCards;

#ifdef DEBUG
    {
        std::ostringstream out;
        out << "(DD) Game::drawFloodCards End "
            << std::hex << this << std::dec
            << " numCards: " << mNumPosCardsDrawn
            << " numNew: " << numNewFloodCards 
            << std::endl;
        std::clog << out.str();
    }
#endif

    return retValue;
}
