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

#include "CommandHandler.hh"
#include "GameData.hh"
#include "IMessage.hh"
#include "MessageHandler.hh"
#include "MessageProcessor.hh"
#include "SingleTextStream.hh"

#include <QString>

#include <iostream>
#include <sstream>

// Konstruktor.
CommandHandler::CommandHandler()
: mMessageOperatorP(0), mMessageHandlerP(0), mSingleTextStreamP(0)
{
}

// Destruktor.
CommandHandler::~CommandHandler()
{
    delete mMessageOperatorP;
    mMessageOperatorP = 0;
    
    delete mMessageHandlerP;
    mMessageHandlerP = 0;
    
    delete mSingleTextStreamP;
    mSingleTextStreamP = 0;
}

// Initialisiert das Kommando-Handling.
bool CommandHandler::init( GameData * dataP )
{
    bool retValue = true;

#ifdef DEBUG
    {
        std::ostringstream out;
        out << "(DD) CommandHandler::init "
            << std::hex << this << std::dec
            << " Begin"
            << std::endl;
        std::clog << out.str();
    }
#endif /* DEBUG */

    mMessageOperatorP = new MessageProcessor( dataP );
    if ( !mMessageOperatorP )
    {
        std::ostringstream out;
        out << "(EE) CommandHandler::init "
            << std::hex << this << std::dec
            << " MessageProcessor is 0!"
            << std::endl;
        std::cerr << out.str();
        return false;
    }

    mSingleTextStreamP = new SingleTextStream();
    if ( !mSingleTextStreamP )
    {
        std::ostringstream out;
        out << "(EE) CommandHandler::init "
            << std::hex << this << std::dec
            << " SingleTextStream is 0!"
            << std::endl;
        std::cerr << out.str();
        return false;
    }

    mMessageHandlerP = new MessageHandler(mSingleTextStreamP);
    if ( !mMessageHandlerP )
    {
        std::ostringstream out;
        out << "(EE) CommandHandler::init "
            << std::hex << this << std::dec
            << " MessageHandler is 0!"
            << std::endl;
        std::cerr << out.str();
        return false;
    }

#ifdef DEBUG
    {
        std::ostringstream out;
        out << "(DD) CommandHandler::init "
            << std::hex << this << std::dec
            << " End " << retValue
            << std::endl;
        std::clog << out.str();
    }
#endif /* DEBUG */

    return retValue;
}

// Alle Daten zuruecksetzen.
void CommandHandler::reset()
{
    mMessageOperatorP->reset();
}

// Verarbeite eine Nachricht (als Text).
bool CommandHandler::receiveAndHandleMessage( const QString& messageStr )
{
    bool retValue = true;
    
    IMessage * messageP = 0;

#ifdef DEBUG
    {
        std::ostringstream out;
        out << "(DD) CommandHandler::receiveAndHandleMessage "
            << std::hex << this << std::dec
            << " " << messageStr.toStdString()
            << std::endl;
        std::clog << out.str();
    }
#endif

    // Wir muessen den empfangenen Text erst in den Strom fuettern.
    mSingleTextStreamP->setline( messageStr.toStdString() );

    // Danach empfaengt der Messagehandler diesen auch.
    retValue = mMessageHandlerP->receiveMessage( messageP );

#ifdef DEBUG
    {
        std::ostringstream out;
        out << "(DD) CommandHandler::receiveAndHandleMessage "
            << std::hex << this << std::dec
            << " Message: " << messageP
            << " Return: "  << retValue
            << std::endl;
        std::clog << out.str();
    }
#endif

    if ( ( retValue ) && ( 0 != messageP ) )
    {
        // Verarbeite die Nachricht (Visitor-Pattern).
        retValue = messageP->operate( *mMessageOperatorP );

#ifdef DEBUG
        std::ostringstream out;
        out << "(DD) CommandHandler::receiveAndHandleMessage "
            << std::hex << this << std::dec
            << " Message: " << messageP->getId()
            << " Return: "  << retValue
            << std::endl;
        std::clog << out.str();
#endif

        // Nachricht wird nicht mehr benoetigt.
        delete messageP;
        messageP = 0;
    }
    // else: Eine leere/nicht vorhandene Nachricht ist okay.
    
    if ( !retValue )
    {
        std::ostringstream out;
        out << "(EE) CommandHandler::receiveAndHandleMessage "
            << std::hex << this << std::dec
            << " There was an error somewhere!"
            << std::endl;
        std::cerr << out.str();
    }

#ifdef DEBUG
    {
        std::ostringstream out;
        out << "(DD) CommandHandler::receiveAndHandleMessage "
            << std::hex << this << std::dec
            << " Return: "  << retValue
            << std::endl;
        std::clog << out.str();
    }
#endif

    return retValue;
}
