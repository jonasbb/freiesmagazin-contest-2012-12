/**
    (C) Copyright 2011 Dominik Wagenfuehr

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

#include "Engine.hh"

#include "CommandProcessor.hh"
#include "IGame.hh"
#include "IServer.hh"
#include "PositionCardPointerVector.hh"

#include <iostream>
#include <sstream>
#include <vector>

// Konstruktor
Engine::Engine( IGame& game, IServer& server, const EngineConfig& config )
: mGameR(game), mServerR(server), mConfig(config), mRounds(0)
{
}

// Destruktor.
Engine::~Engine()
{
}

// Gibt Anzahl gespielter Runden zurueck.
unsigned int Engine::getNumRounds() const
{
    return mRounds;
}

// Startet ein Spiel.
bool Engine::startGame()
{
    bool retValue = false;

    // Pruefe, ob am Server die korrekte Anzahl von Spieler
    // angemeldet ist.
    if ( mServerR.getNumClients() == 1 )
    {
#ifdef DEBUG
        std::ostringstream out3;
        out3 << "(DD) Engine::startGame "
             << std::hex << this << std::dec
             << " Send gameboard."
             << std::endl;
        std::clog << out3.str();
#endif

        mRounds = 0;

        // Sende zuerst das Spielbrett an den Client.
        retValue = sendGameboard();

#ifdef DEBUG
        std::ostringstream out2;
        out2 << "(DD) Engine::startGame "
             << std::hex << this << std::dec
             << " Start game loop."
             << std::endl;
        std::clog << out2.str();
#endif

        // Wiederhole einen Vorgang bis der Spieler
        // mit dem Feld untergegangen ist.
        while ( retValue && !mGameR.hasPlayerLost() )
        {
            // Starte neue Runde.
            retValue = startRound();
        }

        // Das Spiel ist vorbei, sende END an den Client.
        sendClient( "END" );
    }
    else
    {
        std::ostringstream out;
        out << "(EE) Engine::startGame "
            << std::hex << this << std::dec
            << " Number of clients "
            << mServerR.getNumClients()
            << " must be 1."
            << std::endl;
        std::cerr << out.str();
    }

    return retValue;
}

// Starte eine einzelne Runde.
bool Engine::startRound()
{
    bool retValue = false;

    // Erhoehe Rundezaehler.
    mRounds++;

#ifdef DEBUG
    std::ostringstream out;
    out << "(DD) Engine::startRound "
        << std::hex << this << std::dec
        << " Round: " << mRounds
        << std::endl;
    std::clog << out.str();
#endif

    // Sende START an Client.
    if ( sendStartCommand() )
    {
        // Empfange Liste mit Kommandos vom Client.
        std::vector<std::string> stringCommands(3);
        if ( receiveClientCommands(stringCommands) )
        {
            CommandProcessor commandProc;
            if ( commandProc.interpretCommands( stringCommands ) )
            {
                // Wir muessen die Kommandos alle einzeln verarbeiten,
                // weil es sein kann, dass der Bot illegale Bewegungen
                // macht. Dann muessen wir sofort stoppen und duerfen
                // den Rest nicht ausfuehren.
                bool commandError = false;
                
                for ( unsigned int ii = 0; ii < stringCommands.size(); ii++ )
                {
                    if ( !commandProc.processSingleCommand( ii, mGameR ) )
                    {
                        // Es kam irgendwie zu einem Fehler, wir brechen
                        // die Bearbeitung ab.
                        commandError = true;
                        break;
                    }
                    else
                    {
                        writeLog( stringCommands[ii] );

                        // Wenn der Bot jetzt auf ein untergegangenes
                        // Feld gelaufen ist, arbeiten wir den Rest der
                        // Kommandos nicht mehr ab, da der Bot tot ist.
                        if ( mGameR.hasPlayerLost() )
                        {
                            break;
                        }
                    }
                }

                if ( commandError )
                {
                    // Es kam zu einem Fehler.
                    retValue = false;
                }
                else
                {
                    // Nur wenn die Bot-Befehle korrekt verarbeitet wurden,
                    // zieht man neue Flutkarten und ueberflutet Felder.
                    retValue = false;
                
                    if ( drawFloodCards() )
                    {
                        if ( drawPositionsCardsAndFloodTiles() )
                        {
                            retValue = true;
                        }
                    }
                }
            }
        }
    }

#ifdef DEBUG
    std::ostringstream out2;
    out2 << "(DD) Engine::startRound "
         << std::hex << this << std::dec
         << " Return " << retValue
         << std::endl;
    std::clog << out2.str();
#endif

    return retValue;
}

// Sende Start-Kommando an Spieler.
bool Engine::sendStartCommand()
{
    // Sende Rundenanzahl an beide Bots.
    std::ostringstream roundStr;
    roundStr << mRounds
             << " "
             << mGameR.getPlayerPos().x()
             << ","
             << mGameR.getPlayerPos().y();
    return sendClient( "ROUND " + roundStr.str() );
}

// Empfange Antwort mit drei Befehlen des Clients.
bool Engine::receiveClientCommands( std::vector<std::string>& stringCommands )
{
    bool retValue = false;

    stringCommands.resize(3);
    
    if ( mServerR.receive( 0, stringCommands[0] ) &&
         mServerR.receive( 0, stringCommands[1] ) &&
         mServerR.receive( 0, stringCommands[2] ) )
    {
        // Empfangen hat geklappt.
        retValue = true;

#ifdef DEBUG
        std::ostringstream out;
        out << "(DD) Engine::receiveClientCommands "
            << std::hex << this << std::dec
            << " Receiving commands '"
            << stringCommands[0]
            << "|"
            << stringCommands[1]
            << "|"
            << stringCommands[2]
            << "'."
            << std::endl;
        std::clog << out.str();
#endif
    }

    return retValue;
}

// Ziehe Karten vom Positionskartenstapel und flute die Felder.
bool Engine::drawPositionsCardsAndFloodTiles()
{
    bool retValue = false;

    std::vector<Position> floodedPositions;

    if ( mGameR.drawPositionCardsAndFloodTiles( floodedPositions ) )
    {
        retValue = true;

        for ( size_t ii = 0; ii < floodedPositions.size(); ii++ )
        {
            if ( floodedPositions[ii].isValid() )
            {
                std::ostringstream cardStr;
                cardStr << floodedPositions[ii].x()
                         << ","
                         << floodedPositions[ii].y();
                if ( !sendClient( "FLOOD " + cardStr.str() ) )
                {
                    retValue = false;
                    break;
                }

                // Achtung: Zeiger nicht loeschen, da es nur eine
                // Kopie ist!
            }
            else
            {
                std::ostringstream out;
                out << "(EE) Engine::drawPositionsCardsAndFloodTiles "
                    << std::hex << this << std::dec
                    << " Flooded position "
                    << floodedPositions[ii]
                    << " is not valid!"
                    << std::endl;
                std::cerr << out.str();
                retValue = false;
                break;
            }
        }
    }

    return retValue;
}

// Ziehe Flutkarten.
bool Engine::drawFloodCards()
{
    bool retValue = false;

    // Zaehle wie viele neue Flutkarten es gibt.
    unsigned int numNewFloodCards = 0;
    if ( mGameR.drawFloodCards( numNewFloodCards ) )
    {
        std::ostringstream cardStr;
        cardStr << numNewFloodCards;
        if ( sendClient( "INCRFLOOD " + cardStr.str() ) )
        {
            retValue = true;
        }
    }

    return retValue;
}

// Sende Spielbrett an Client.
bool Engine::sendGameboard()
{
    bool retValue = false;

    std::vector<std::string> gameboardStrings;
    Position size;

    if ( mGameR.getGameboardInfo( size, gameboardStrings ) )
    {
        std::ostringstream stringStart;
        stringStart << "GAMEBOARDSTART "
                    << size.x() << "," << size.y();

        std::ostringstream stringEnd;
        stringEnd << "GAMEBOARDEND";

        if ( sendClient( stringStart.str() ) )
        {
            retValue = true;

            for ( size_t ii = 0; ii < gameboardStrings.size(); ii++ )
            {
                if ( !sendClient( gameboardStrings[ii] ) )
                {
                    retValue = false;
                    break;
                }
            }

            if ( retValue )
            {
                if ( sendClient( stringEnd.str() ) )
                {
                    retValue = true;
                }
            }
        }
    }

    return retValue;
}

// Sende Nachricht an ersten Client (und Controller, falls existent).
bool Engine::sendClient( const std::string& message )
{
    writeLog( message );
    return mServerR.send( 0, message );
}

// Schreibe Log-Nachricht (falls aktiv).
void Engine::writeLog( const std::string& message ) const
{
    if ( mConfig.isLog() )
    {
        // Logging ist aktiv.
        std::ostringstream out;
        out << message << std::endl;
        std::clog << out.str();
    }
}
