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

#include "Strategy.hh"

#include "EndMessage.hh"
#include "FloodMessage.hh"
#include "GameboardEndMessage.hh"
#include "GameboardLineMessage.hh"
#include "GameboardStartMessage.hh"
#include "IncrFloodMessage.hh"
#include "StartMessage.hh"
#include "TextMessage.hh"

#include <iostream>
#include <sstream>

// Konstruktor.
Strategy::Strategy()
  : mData(), mIsFinished(false), mGameboardStarted(false)
{ }

// Destruktor.
Strategy::~Strategy()
{ }

// Werte zuruecksetzen.
void Strategy::reset()
{
}
    
// Behandelt eine Start-Nachricht.
bool Strategy::operate( const StartMessage& message )
{
    mData.numRound = message.getNumRound();
    mData.position = message.getPosition();

    // Hier muss nun die Berechnung der Befehle, die an
    // den Server gesendet werden sollen, starten.
    return calcCommands();
}

// Behandelt eine Flut-Nachricht.
bool Strategy::operate( const FloodMessage& message )
{
    mData.floodedField = message.getPosition();
    return true;
}

// Behandelt eine Steigende-Flut-Nachricht.
bool Strategy::operate( const IncrFloodMessage& message )
{
    mData.floodCounter += message.getNumIncrFlood();
    return true;
}

// Behandelt eine Ende-Nachricht.
bool Strategy::operate( const EndMessage& /* message */ )
{
    mIsFinished = true;
    return true;
}
    
// Behandelt eine Spielbrett-Start-Nachricht.
bool Strategy::operate( const GameboardStartMessage& message )
{
    mGameboardStarted = true;
    return true;
}

// Behandelt eine Spielbrett-Zeile-Nachricht.
bool Strategy::operate( const GameboardLineMessage& /* message */ )
{
    bool retValue = false;

    if ( mGameboardStarted )
    {
        // Zeile interpretieren ...
        retValue = true;
    }
    else
    {
        std::ostringstream out;
        out << "(EE) Strategy::operate GameboardLineMessage"
            << std::hex << this << std::dec
            << " Gameboard transfer has not been started yet!"
            << std::endl;
        std::cerr << out.str();
        retValue = false;
    }
    
    return retValue;
}

// Behandelt eine Spielbrett-Ende-Nachricht.
bool Strategy::operate( const GameboardEndMessage& message )
{
    mGameboardStarted = false;
    return true;
}

// Behandelt eine Textnachricht.
bool Strategy::operate( const TextMessage& message  )
{
    std::ostringstream out;
    out << "(EE) " << "Strategy::operate TextMessage "
        << std::hex << this << std::dec
        << "'" << message.getText() << "'."
        << " Cannot operate on text messages!"
        << std::endl;
    std::cerr << out.str();
    
    return false;
}

// Fragt ab, ob Kommandos zur Verfuegung stehen.
bool Strategy::isCommandsAvailable( std::vector<std::string>& cmdList )
{
    bool isAvail = false;

    cmdList.clear();
    if ( 3 == mCommandList.size() )
    {
        // Nur, wenn exakt drei Kommandos anstehen, werden diese
        // uebermittelt.
        cmdList = mCommandList;
        isAvail = true;

        // Nach dem Kopieren sollte man die Kommandos unbedingt
        // loeschen, damit bei der naechsten Abfrage nicht aus
        // Versehen noch Kommandos anstehen.
        mCommandList.clear();
    }

    return isAvail;
}

// Gibt zurueck, ob das Spiel zu Ende sein soll.
bool Strategy::isEnd() const
{
    return mIsFinished;
}

// Berechne die drei Aktionen, die spaeter ausgegeben werden sollen.
bool Strategy::calcCommands()
{
    // Dummy-maessig setzen wir alle drei Kommandos auf
    // "GO CURRENT",  was einem Stillstehen entspricht.
    // Man kann z.B. auch einfach nur "DRY CURRENT" machen,
    // damit ueberlebt geringfuegig laenger.
    mCommandList.resize(3);
    mCommandList[0] = "GO CURRENT";
    mCommandList[1] = "GO CURRENT";
    mCommandList[2] = "GO CURRENT";

    // Bei einer echten Strategy findet hier natuerlich eine ganz
    // komplizierte Berechnung statt ...

    return true;
}
