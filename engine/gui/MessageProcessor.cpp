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

#include "MessageProcessor.hh"

#include "EndMessage.hh"
#include "FloodMessage.hh"
#include "GameboardEndMessage.hh"
#include "GameboardLineMessage.hh"
#include "GameboardStartMessage.hh"
#include "GameData.hh"
#include "IncrFloodMessage.hh"
#include "StartMessage.hh"
#include "TextMessage.hh"

#include <iostream>
#include <sstream>

// Konstruktor.
MessageProcessor::MessageProcessor( GameData * dataP )
  : mDataP(dataP), mGameboardStarted(false), mGameboardSize(0,0)
{
    if ( 0 == mDataP )
    {
        std::ostringstream out;
        out << "(EE) MessageProcessor::MessageProcessor "
            << std::hex << this << std::dec
            << " GameData is 0!"
            << std::endl;
        std::cerr << out.str();
    }
}

// Destruktor.
MessageProcessor::~MessageProcessor()
{
    // Zeiger nicht loeschen, da aussen referenziert.
    mDataP = 0;
}

// Werte zuruecksetzen.
void MessageProcessor::reset()
{
    // Achtung: Die Daten setzen wir mit Absicht niecht zurueck.
    // Damit sie weiterhin angezeigt werden koennen.
    mGameboardStarted = false;
    mGameboardSize.setPosition(0,0);
    mGameboardStrings.clear();
}
    
// Behandelt eine Start-Nachricht.
bool MessageProcessor::operate( const StartMessage& message )
{
    bool retValue = false;

    if ( mDataP )
    {
        mDataP->numRound = message.getNumRound();
        mDataP->position = message.getPosition();
        retValue = true;
    }
    
    return retValue;
}

// Behandelt eine Flut-Nachricht.
bool MessageProcessor::operate( const FloodMessage& message )
{
    bool retValue = false;

    if ( mDataP )
    {
        mDataP->floodedField = message.getPosition();

        {
            std::ostringstream out;
            out << "(DD) MessageProcessor::operate FloodMessage "
                << std::hex << this << std::dec
                << " Flooding position "
                <<  mDataP->floodedField << "."
                << std::endl;
            std::clog << out.str();
        }

        // Feld auf dem Spielbrett ueberfluten.
        if ( mDataP->gameboard.isValidPos( mDataP->floodedField, true ) )
        {
            mDataP->gameboard.flood( mDataP->floodedField );
            retValue = true;
        }
        else
        {
            std::ostringstream out;
            out << "(WW) MessageProcessor::operate FloodMessage "
                << std::hex << this << std::dec
                << " Flooding outside gameboard on position "
                << mDataP->floodedField << "."
                << std::endl;
            std::cerr << out.str();
        }
        
        retValue = true;
    }
    
    return retValue;
}

// Behandelt eine Steigende-Flut-Nachricht.
bool MessageProcessor::operate( const IncrFloodMessage& message )
{
    bool retValue = false;

    if ( mDataP )
    {
        mDataP->floodCounter += message.getNumIncrFlood();
        retValue = true;
    }
    
    return retValue;
}

// Behandelt eine Ende-Nachricht.
bool MessageProcessor::operate( const EndMessage& /* message */ )
{
    bool retValue = false;

    if ( mDataP )
    {
        mDataP->isFinished = true;
        retValue = true;
    }
    
    return retValue;
}
    
// Behandelt eine Spielbrett-Start-Nachricht.
bool MessageProcessor::operate( const GameboardStartMessage& message )
{
    bool retValue = false;

    if ( mDataP )
    {
        mGameboardStarted = true;
        mGameboardStrings.clear();
        mGameboardSize = message.getSize();
        retValue = true;

#ifdef DEBUG
        std::ostringstream out;
        out << "(DD) MessageProcessor::operate GameboardStartMessage"
            << " Size: "
            << mGameboardSize
            << std::endl;
        std::clog << out.str();
#endif
    }
    
    return retValue;
}

// Behandelt eine Spielbrett-Zeile-Nachricht.
bool MessageProcessor::operate( const GameboardLineMessage& message )
{
    bool retValue = false;

    if ( mGameboardStarted )
    {
        mGameboardStrings.push_back( message.getLine() );
        retValue = true;
    }
    else
    {
        std::ostringstream out;
        out << "(EE) MessageProcessor::operate GameboardLineMessage"
            << std::hex << this << std::dec
            << " Gameboard transfer has not been started yet!"
            << std::endl;
        std::cerr << out.str();
    }
    
    return retValue;
}

// Behandelt eine Spielbrett-Ende-Nachricht.
bool MessageProcessor::operate( const GameboardEndMessage& /* message */ )
{
    bool retValue = false;
    
    if ( mGameboardStarted )
    {
        if ( mDataP )
        {
            retValue = mDataP->gameboard.create( mGameboardSize,
                                                 mGameboardStrings );
        }
        mGameboardStarted = false;
    }
    else
    {
        std::ostringstream out;
        out << "(EE) MessageProcessor::operate GameboardEndMessage"
            << std::hex << this << std::dec
            << " Gameboard transfer has not been started yet!"
            << std::endl;
        std::cerr << out.str();
    }
    
    return retValue;
}

// Behandelt eine Textnachricht.
bool MessageProcessor::operate( const TextMessage& message  )
{
    bool retValue = false;

    // Es gibt zwei Textnachrichten mit GO und DRY, die die
    // GUI verarbeiten kann.
    const std::string cmdString = message.getText();

    size_t pos = cmdString.find(' ');

    if ( ( std::string::npos != pos ) &&
         ( 0 != pos ) &&
         ( cmdString.length()-1 != pos ) )
    {
        const std::string firstCmd = cmdString.substr( 0, pos );
        const std::string secondCmd = cmdString.substr( pos+1 );

        if ( 0 == firstCmd.compare( "GO" ) )
        {
            retValue = operateGo( secondCmd );
        }
        else if ( 0 == firstCmd.compare( "DRY" ) )
        {
            retValue = operateDry( secondCmd );
        }
        else if ( 0 == firstCmd.compare( "(II)" ) ||
                  0 == firstCmd.compare( "(DD)" ) )
        {
            // Dies ist eine Debug- oder Info-Ausgabe im Logfile, die
            // wir ignorieren wollen.
            retValue = true;
        }
        else
        {
            std::ostringstream out;
            out << "(EE) MessageProcessor::operate "
               << std::hex << this << std::dec
                << " Unknown command '"
                << firstCmd
                << "' from text message '"
                << cmdString
                << "'."
                << std::endl;
            std::cerr << out.str();
        }
    }
    else 
    {
        std::ostringstream out;
        out << "(EE) MessageProcessor::operate TextMessage "
            << std::hex << this << std::dec
            << "'" << message.getText() << "'."
            << " Cannot operate on text messages!"
            << std::endl;
        std::cerr << out.str();
    }
    
    return retValue;
}

// Behandle eine Bewegung.
bool MessageProcessor::operateGo( const std::string& direction )
{
    bool retValue = false;

    if ( 0 == direction.compare( "NORTH" ) )
    {
        retValue = movePlayerNorth();
    }
    else if ( 0 == direction.compare( "SOUTH" ) )
    {
        retValue = movePlayerSouth();
    }
    else if ( 0 == direction.compare( "EAST" ) )
    {
        retValue = movePlayerEast();
    }
    else if ( 0 == direction.compare( "WEST" ) )
    {
        retValue = movePlayerWest();
    }
    else if ( 0 == direction.compare( "CURRENT" ) )
    {
        // Spieler bleibt stehen.
        retValue = true;
    }
    else
    {
        std::ostringstream out;
        out << "(EE) MessageProcessor::operateGo "
            << std::hex << this << std::dec
            << " Unknown direction '"
            << direction
            << "'."
            << std::endl;
        std::cerr << out.str();
    }
    
    return retValue;
}

// Behandle eine Trockenlege-Aktion.
bool MessageProcessor::operateDry( const std::string& direction )
{
    bool retValue = false;

    if ( 0 == direction.compare( "NORTH" ) )
    {
        retValue = drainTileNorth();
    }
    else if ( 0 == direction.compare( "SOUTH" ) )
    {
        retValue = drainTileSouth();
    }
    else if ( 0 == direction.compare( "EAST" ) )
    {
        retValue = drainTileEast();
    }
    else if ( 0 == direction.compare( "WEST" ) )
    {
        retValue = drainTileWest();
    }
    else if ( 0 == direction.compare( "CURRENT" ) )
    {
        retValue = drainTileCurrent();
    }
    else
    {
        std::ostringstream out;
        out << "(EE) MessageProcessor::operateDry "
            << std::hex << this << std::dec
            << " Unknown direction '"
            << direction
            << "'."
            << std::endl;
        std::cerr << out.str();
    }
    
    return retValue;
}
    
// Bewegt den Spieler ein Feld nach rechts.
bool MessageProcessor::movePlayerEast()
{
    bool retValue = false;

    if ( mDataP )
    {
        const Position pos = mDataP->position;
        const Position newPos( pos.x()+1, pos.y() );

        if ( mDataP->gameboard.isValidPos( newPos, true ) )
        {
            mDataP->position = newPos;
            retValue = true;
        }
        else
        {
            std::ostringstream out;
            out << "(WW) MessageProcessor::movePlayerEast "
                << std::hex << this << std::dec
                << " Player is moving outside of board "
                << " from " << pos << " to " << newPos << "."
                << std::endl;
            std::cerr << out.str();
        }
    }

    return retValue;
}

// Bewegt den Spieler ein Feld nach oben.
bool MessageProcessor::movePlayerNorth()
{
    bool retValue = false;

    if ( mDataP )
    {
        const Position pos = mDataP->position;
        const Position newPos( pos.x(), pos.y()-1 );

        if ( mDataP->gameboard.isValidPos( newPos, true ) )
        {
            mDataP->position = newPos;
            retValue = true;
        }
        else
        {
            std::ostringstream out;
            out << "(WW) MessageProcessor::movePlayerNorth "
                << std::hex << this << std::dec
                << " Player is moving outside of board "
                << " from " << pos << " to " << newPos << "."
                << std::endl;
            std::cerr << out.str();
        }
    }

    return retValue;
}

// Bewegt den Spieler ein Feld nach unten.
bool MessageProcessor::movePlayerSouth()
{
    bool retValue = false;

    if ( mDataP )
    {
        const Position pos = mDataP->position;
        const Position newPos( pos.x(), pos.y()+1 );

        if ( mDataP->gameboard.isValidPos( newPos, true ) )
        {
            mDataP->position = newPos;
            retValue = true;
        }
        else
        {
            std::ostringstream out;
            out << "(WW) MessageProcessor::movePlayerSouth "
                << std::hex << this << std::dec
                << " Player is moving outside of board "
                << " from " << pos << " to " << newPos << "."
                << std::endl;
            std::cerr << out.str();
        }
    }

    return retValue;
}

// Bewegt den Spieler ein Feld nach links.
bool MessageProcessor::movePlayerWest()
{
    bool retValue = false;

    if ( mDataP )
    {
        const Position pos = mDataP->position;
        const Position newPos( pos.x()-1, pos.y() );

        if ( mDataP->gameboard.isValidPos( newPos, true ) )
        {
            mDataP->position = newPos;
            retValue = true;
        }
        else
        {
            std::ostringstream out;
            out << "(WW) MessageProcessor::movePlayerWest "
                << std::hex << this << std::dec
                << " Player is moving outside of board "
                << " from " << pos << " to " << newPos << "."
                << std::endl;
            std::cerr << out.str();
        }
    }

    return retValue;
}

// Lege das Feld, auf dem der Spieler steht, trocken.
bool MessageProcessor::drainTileCurrent()
{
    bool retValue = false;

    if ( mDataP )
    {
        const Position pos = mDataP->position;
        const Position newPos( pos.x(), pos.y() );

        if ( mDataP->gameboard.isValidPos( newPos, true ) )
        {
            retValue = mDataP->gameboard.drain( newPos );
        }
        else
        {
            std::ostringstream out;
            out << "(WW) MessageProcessor::drainTileCurrent "
                << std::hex << this << std::dec
                << " Field is not valid at position "
                << newPos << "."
                << std::endl;
            std::cerr << out.str();
        }
    }

    return retValue;
}

// Lege das Feld rechts vom Spieler trocken.
bool MessageProcessor::drainTileEast()
{
    bool retValue = false;

    if ( mDataP )
    {
        const Position pos = mDataP->position;
        const Position newPos( pos.x()+1, pos.y() );

        if ( mDataP->gameboard.isValidPos( newPos, true ) )
        {
            retValue = mDataP->gameboard.drain( newPos );
        }
        else
        {
            std::ostringstream out;
            out << "(WW) MessageProcessor::drainTileCurrent "
                << std::hex << this << std::dec
                << " Field is not valid at position "
                << newPos << "."
                << std::endl;
            std::cerr << out.str();
        }
    }

    return retValue;
}

// Lege das Feld unterhalb vom Spieler trocken.
bool MessageProcessor::drainTileNorth()
{
    bool retValue = false;

    if ( mDataP )
    {
        const Position pos = mDataP->position;
        const Position newPos( pos.x(), pos.y()-1 );

        if ( mDataP->gameboard.isValidPos( newPos, true ) )
        {
            retValue = mDataP->gameboard.drain( newPos );
        }
        else
        {
            std::ostringstream out;
            out << "(WW) MessageProcessor::drainTileCurrent"
                << std::hex << this << std::dec
                << " Field is not valid at position "
                << newPos << "."
                << std::endl;
            std::cerr << out.str();
        }
    }

    return retValue;
}

// Lege das Feld ueberhalb vom Spieler trocken.
bool MessageProcessor::drainTileSouth()
{
    bool retValue = false;

    if ( mDataP )
    {
        const Position pos = mDataP->position;
        const Position newPos( pos.x(), pos.y()+1 );

        if ( mDataP->gameboard.isValidPos( newPos, true ) )
        {
            retValue = mDataP->gameboard.drain( newPos );
        }
        else
        {
            std::ostringstream out;
            out << "(WW) MessageProcessor::drainTileCurrent"
                << std::hex << this << std::dec
                << " Field is not valid at position "
                << newPos << "."
                << std::endl;
            std::cerr << out.str();
        }
    }

    return retValue;
}

// Lege das Feld links vom Spieler trocken.
bool MessageProcessor::drainTileWest()
{
    bool retValue = false;

    if ( mDataP )
    {
        const Position pos = mDataP->position;
        const Position newPos( pos.x()-1, pos.y() );

        if ( mDataP->gameboard.isValidPos( newPos, true ) )
        {
            retValue = mDataP->gameboard.drain( newPos );
        }
        else
        {
            std::ostringstream out;
            out << "(WW) MessageProcessor::drainTileCurrent"
                << std::hex << this << std::dec
                << " Field is not valid at position "
                << newPos << "."
                << std::endl;
            std::cerr << out.str();
        }
    }

    return retValue;
}
