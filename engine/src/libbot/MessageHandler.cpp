/**
    (C) Copyright 2011,2012 Dominik Wagenfuehr

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

#include "MessageHandler.hh"
#include "EndMessage.hh"
#include "FloodMessage.hh"
#include "GameboardEndMessage.hh"
#include "GameboardLineMessage.hh"
#include "GameboardStartMessage.hh"
#include "IncrFloodMessage.hh"
#include "ITextStream.hh"
#include "StartMessage.hh"
#include "TextMessage.hh"

#include <iostream>
#include <sstream>

// Konstuktor.
MessageHandler::MessageHandler( ITextStream * textStream )
  : mGameboardStarted(false), mTextStream(textStream)
{
    if ( 0 == mTextStream )
    {
#ifdef DEBUG
        std::ostringstream out;
        out << "(EE) MessageHandler::MessageHandler "
            << std::hex << this << std::dec
            << " Pointer to stream is 0."
            << std::endl;
        std::cerr << out.str();
#endif
    }
}

// Empfaengt und prueft eine Nachricht.
bool MessageHandler::receiveMessage( IMessage*& msgPR )
{
    bool retValue = false;
    msgPR = 0;

#ifdef DEBUG
    std::ostringstream out;
    out << "(DD) MessageHandler::receiveMessage "
        << std::hex << this << std::dec
        << std::endl;
    std::clog << out.str();
#endif

    // Hole Nachricht ab.
    std::string message;
    if ( getTextStdin( message ) )
    {
        // Konvertiere Text in echte Nachricht.
        retValue = createMessage( msgPR, message );
    }

#ifdef DEBUG

    std::ostringstream out2;
    out2 << "(DD) MessageHandler::receiveMessage "
         << std::hex << this << std::dec
         << " Message: " << msgPR
         << " Return: "  << retValue
         << std::endl;
    std::clog << out2.str();
#endif

    return retValue;
}

// Sendet eine Nachricht nach STDOUT.
void MessageHandler::sendTextMessage( const std::string& message ) const
{
    if ( mTextStream )
    {
#ifdef DEBUG
        std::ostringstream out;
        out << "(DD) MessageHandler::sendTextMessage "
            << std::hex << this << std::dec
            << " '" << message << "'" << std::endl;
        std::clog << out.str();
#endif // DEBUG

        mTextStream->writeline( message );
    }
}

// Hole eine Nachricht vom STDIN ab.
bool MessageHandler::getTextStdin( std::string& message ) const
{
    bool retValue = false;

    if ( mTextStream )
    {
/*
#ifdef DEBUG
        std::ostringstream out;
        out << "(DD) MessageHandler::getTextStdin "
            << std::hex << this << std::dec
            << std::endl;
        std::clog << out.str();
#endif // DEBUG
* */

        // Sobald der Bot gestartet wird, wartet er auf eine Eingabe
        // auf STDIN vom Server.
        mTextStream->getline( message );

        if ( !message.empty() )
        {
#ifdef DEBUG
            std::ostringstream out;
            out << "(DD) MessageHandler::getTextStdin "
             << std::hex << this << std::dec
                << " '" << message << "'" << std::endl;
            std::clog << out.str();
#endif // DEBUG

            retValue = true;
        }
    }

    return retValue;
}

// Erstellt eine Nachricht aus einer Textnachricht.
bool MessageHandler::createMessage( IMessage*& msgPR, const std::string& message )
{
    bool retValue = false;
    msgPR = 0;

#ifdef DEBUG
    if ( !message.empty() )
    {
        std::ostringstream out;
        out << "(DD) MessageHandler::createMessage "
            << std::hex << this << std::dec
            << " create message '" << message << "'" << std::endl;
        std::clog << out.str();
    }
#endif // DEBUG

    if ( message.compare(0, 4, "(DD)") == 0 ||
         message.compare(0, 4, "(II)") == 0 )
    {
        // Debugging-Nachricht
        retValue = createTextMessage( msgPR, message );
    }
    else if ( message.compare(0, 5, "ROUND") == 0 )
    {
        // Start-Nachricht
        retValue = createStartMessage( msgPR, message.substr( 6 ) );
    }
    else if ( message.compare(0, 5, "FLOOD") == 0 )
    {
        // Flut-Nachricht.
        retValue = createFloodMessage( msgPR, message.substr( 6 ) );
    }
    else if ( message.compare(0, 9, "INCRFLOOD") == 0 )
    {
        // Flut-Steigt-Nachricht.
        retValue = createIncrFloodMessage( msgPR, message.substr( 10 ) );
    }
    else if ( message.compare("END") == 0 )
    {
        // Ende-Nachricht
        retValue = createEndMessage( msgPR );
    }
    else if ( message.compare(0, 14, "GAMEBOARDSTART") == 0 )
    {
        // Spielbrett-Start-Nachricht
        retValue = createGameboardStartMessage( msgPR, message.substr( 15 ) );
    }
    else if (  message.compare(0, 12, "GAMEBOARDEND") == 0 )
    {
        // Spielbrett-Ende-Nachricht
        retValue = createGameboardEndMessage( msgPR );
    }
    else if ( mGameboardStarted )
    {
        // Alle Zeilen zwischen Spielbrett-Start und -Ende werden
        // als Spielbrettzeilen interpretiert.
        retValue = createGameboardLineMessage( msgPR, message );
    }
    else
    {
        // Kommando nicht implementiert. Wir erstellen
        // eine Textnachricht, so dass der Client ggf.
        // entstprechend darauf reagieren kann.
        retValue = createTextMessage( msgPR, message );
    }

    if ( 0 == msgPR )
    {
        std::ostringstream out;
        out << "(EE) MessageHandler::createMessage "
            << std::hex << this << std::dec
            << " Pointer to message is 0."
            << std::endl;
        std::cerr << out.str();
    }

    return retValue;
}

// Erstellt eine Start-Nachricht.
bool MessageHandler::createStartMessage( IMessage*& msgPR, const std::string& param ) const
{
    bool retValue = false;
    msgPR = 0;

    // Aktuelle Runde und Position.
    unsigned int round = 0;
    unsigned int x = 0, y = 0;

    size_t pos = param.find(' ');

    if ( ( std::string::npos != pos ) &&
         ( 0 != pos ) &&
         ( param.length()-1 != pos ) )
    {
        // Der erste Wert ist die Runde.
        std::istringstream in( param.substr( 0, pos ) );
        in >> round;

        std::string cmdString = param.substr( pos+1 );
        pos = cmdString.find(',');

        if ( ( std::string::npos != pos ) &&
             ( 0 != pos ) &&
             ( cmdString.length()-1 != pos ) )
        {
            // Danach folgen x- und y-Position eines Feldes.
            std::istringstream in2( cmdString.substr( 0, pos ) );
            in2 >> x;

            std::istringstream in3( cmdString.substr( pos+1 ) );
            in3 >> y;
        }
        else
        {
            std::ostringstream out;
            out << "(EE) MessageHandler::createStartMessage "
                << std::hex << this << std::dec
                << " Cannot interpret line '"
                << cmdString
                << "'. Should be in format '3,5'."
                << std::endl;
            std::cerr << out.str();
        }
    }
    else
    {
        std::ostringstream out;
        out << "(EE) MessageHandler::createStartMessage "
            << std::hex << this << std::dec
            << " Cannot interpret line '"
            << param
            << "'. Should be in format '18 3,5'."
            << std::endl;
        std::cerr << out.str();
    }

    if ( ( round > 0 ) && ( x > 0 ) && ( y > 0 )  )
    {
        msgPR = new StartMessage( round, Position(x,y) );
        if ( 0 != msgPR )
        {
            retValue = true;
        }
    }
    else
    {
        std::ostringstream out;
        out << "(EE) MessageHandler::createStartMessage "
            << std::hex << this << std::dec
            << " Round " << round
            << " or position (" << x << "," << y << ")"
            << " is 0."
            << std::endl;
        std::cerr << out.str();
    }

    return retValue;
}

// Erstellt eine Flut-Nachricht.
bool MessageHandler::createFloodMessage( IMessage*& msgPR, const std::string& param ) const
{
    bool retValue = false;
    msgPR = 0;

    // Feld-Position.
    unsigned int x = 0, y = 0;

    size_t pos = param.find(',');

    if ( ( std::string::npos != pos ) &&
         ( 0 != pos ) &&
         ( param.length()-1 != pos ) )
    {
        // Danach folgen x- und y-Position eines Feldes.
        std::istringstream in2( param.substr( 0, pos ) );
        in2 >> x;

        std::istringstream in3( param.substr( pos+1 ) );
        in3 >> y;
    }
    else
    {
        std::ostringstream out;
        out << "(EE) MessageHandler::createFloodMessage "
            << std::hex << this << std::dec
            << " Cannot interpret line '"
            << param
            << "'. Should be in format '3,5'."
            << std::endl;
        std::cerr << out.str();
    }

    if ( ( x > 0 ) && ( y > 0 )  )
    {
        msgPR = new FloodMessage( Position(x,y) );
        if ( 0 != msgPR )
        {
            retValue = true;
        }
    }
    else
    {
        std::ostringstream out;
        out << "(EE) MessageHandler::createFloodMessage "
            << std::hex << this << std::dec
            << " Position (" << x << "," << y << ")"
            << " is 0."
            << std::endl;
        std::cerr << out.str();
    }

    return retValue;
}

// Erstellt eine Flut-Steigt-Nachricht.
bool MessageHandler::createIncrFloodMessage( IMessage*& msgPR, const std::string& param ) const
{
    bool retValue = false;
    msgPR = 0;

    // Flutzaehler.
    unsigned int incrFlood = 0;

    std::istringstream in( param );
    in >> incrFlood;

    msgPR = new IncrFloodMessage( incrFlood);
    if ( 0 != msgPR )
    {
        retValue = true;
    }

    return retValue;
}

// Erstellt eine Ende-Nachricht.
bool MessageHandler::createEndMessage( IMessage*& msgPR ) const
{
    bool retValue = false;
    msgPR = 0;

    // Bot soll beendet werden.
    msgPR = new EndMessage();
    if ( 0 != msgPR )
    {
        retValue = true;
    }

    return retValue;
}

// Erstellt eine Spielbrett-Start-Nachricht.
bool MessageHandler::createGameboardStartMessage( IMessage*& msgPR, const std::string& param )
{
    bool retValue = false;
    msgPR = 0;

    // Feld-Position.
    unsigned int x = 0, y = 0;

    size_t pos = param.find(',');

    if ( ( std::string::npos != pos ) &&
         ( 0 != pos ) &&
         ( param.length()-1 != pos ) )
    {
        // Danach folgen x- und y-Position eines Feldes.
        std::istringstream in2( param.substr( 0, pos ) );
        in2 >> x;

        std::istringstream in3( param.substr( pos+1 ) );
        in3 >> y;
    }
    else
    {
        std::ostringstream out;
        out << "(EE) MessageHandler::createGameboardStartMessage "
            << std::hex << this << std::dec
            << " Cannot interpret line '"
            << param
            << "'. Should be in format '3,5'."
            << std::endl;
        std::cerr << out.str();
    }

    if ( ( x > 0 ) && ( y > 0 )  )
    {
        // Spielbrettuebertragung startet
        mGameboardStarted = true;
        msgPR = new GameboardStartMessage( Position(x,y) );
        if ( 0 != msgPR )
        {
            retValue = true;
        }
    }
    else
    {
        std::ostringstream out;
        out << "(EE) MessageHandler::createGameboardStartMessage "
            << std::hex << this << std::dec
            << " Size (" << x << "," << y << ")"
            << " is 0."
            << std::endl;
        std::cerr << out.str();
    }

    return retValue;
}

// Erstellt eine Spielbrett-Zeilen-Nachricht.
bool MessageHandler::createGameboardLineMessage( IMessage*& msgPR, const std::string& param ) const
{
    bool retValue = false;
    msgPR = 0;

    msgPR = new GameboardLineMessage( param );
    if ( 0 != msgPR )
    {
        retValue = true;
    }

    return retValue;
}

// Erstellt eine Spielbrett-Ende-Nachricht.
bool MessageHandler::createGameboardEndMessage( IMessage*& msgPR )
{
    bool retValue = false;
    msgPR = 0;

    // Spielbrett-Uebertragung ist zu Ende.
    mGameboardStarted = false;
    msgPR = new GameboardEndMessage();
    if ( 0 != msgPR )
    {
        retValue = true;
    }

    return retValue;
}

// Erstellt eine Textnachricht.
bool MessageHandler::createTextMessage( IMessage*& msgPR, const std::string& param ) const
{
    bool retValue = false;
    msgPR = 0;

    msgPR = new TextMessage( param );
    if ( 0 != msgPR )
    {
        retValue = true;
    }

    return retValue;
}
