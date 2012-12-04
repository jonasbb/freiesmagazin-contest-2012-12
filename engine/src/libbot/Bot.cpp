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

#include "Bot.hh"

#include "IMessage.hh"
#include "IStrategy.hh"
#include "MessageHandler.hh"
#include "StdTextStream.hh"

#include <iostream>
#include <sstream>

// Konstruktor.
Bot::Bot()
: mStrategyP(0)
{
#ifdef DEBUG
    std::ostringstream out;
    out << "(DD) Bot::Bot "
        << std::hex << this << std::dec
        << std::endl;
    std::clog << out.str();
#endif // DEBUG
}

// Destructor.
Bot::~Bot()
{
    mStrategyP = 0;
    
#ifdef DEBUG
    std::ostringstream out;
    out << "(DD) Bot::~Bot "
        << std::hex << this << std::dec
        << std::endl;
    std::clog << out.str();
#endif // DEBUG
}

// Startet ein neues Spiel mit der jeweiligen Strategie.
bool Bot::start( IStrategy* strategyP )
{
    // Neue Strategie setzen.
    mStrategyP = strategyP;

    bool retValue = false;

    if ( mStrategyP )
    {
        StdTextStream textStream;
        MessageHandler msgHandler( &textStream );
        std::vector<std::string> cmdList;
        IMessage * message = 0;

        do
        {
            // Nachrichten empfangen.
            retValue = msgHandler.receiveMessage( message );

            if ( retValue )
            {
                if ( 0 != message )
                {
                    // Verarbeite die Nachricht (Visitor-Pattern).
                    retValue = message->operate( *mStrategyP );

#ifdef DEBUG
                    std::ostringstream out;
                    out << "(DD) Bot::start "
                        << std::hex << this << std::dec
                        << " Message: " << message->getId()
                        << " Return: "  << retValue
                        << std::endl;
                    std::clog << out.str();
#endif

                    // Nachricht wird nicht mehr benoetigt.
                    delete message;
                    message = 0;

                    if ( retValue )
                    {
                        if ( mStrategyP->isCommandsAvailable( cmdList ) )
                        {
                            for ( size_t ii = 0; ii < cmdList.size(); ii++ )
                            {
                                msgHandler.sendTextMessage( cmdList[ii] );
                            }
                        }

                        if ( mStrategyP->isEnd() )
                        {
                            // Die Strategie will nicht mehr weitermachen.
                            break;
                        }
                    }
                }
                // else: Eine leere/nicht vorhandene Nachricht ist okay.
            }
        } while ( retValue );

        if ( message )
        {
            delete message;
            message = 0;
        }

        if ( !retValue )
        {
            std::ostringstream out;
            out << "(EE) Bot::start "
                << std::hex << this << std::dec
                << " There was an error somewhere!"
                << std::endl;
            std::cerr << out.str();
        }
    }
    else
    {
        std::ostringstream out;
        out << "(EE) Bot::start "
            << std::hex << this << std::dec
            << " Pointer to strategy is 0!"
            << std::endl;
        std::cerr << out.str();
    }

    return retValue;
}
