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

#include "Server.hh"

#include <iostream>
#include <sstream>

// Konstruktor.
Server::Server()
{
}

// Destruktor.
Server::~Server()
{
}

// Erstellt einen neuen Client und fuegt diesen zur Liste hinzu.
bool Server::createAndAddClient( const char* input, const char* output )
{
#ifdef DEBUG
    std::ostringstream out;
    out << "(DD) Server::createAndAddClient "
        << std::hex << this << std::dec
        << " New client "
        << input << " " << output
        << std::endl;
    std::clog << out.str();
#endif

    bool retValue = false;

    // Erstelle neuen Client.
    Client client( input, output );

    if ( client.isReady() )
    {
#ifdef DEBUG
        std::ostringstream out;
        out << "(DD) Server::createAndAddClient "
            << std::hex << this << std::dec
            << " Client "
            << input << " " << output
            << " is ready!"
            << std::endl;
        std::clog << out.str();
#endif

        // Der Client ist okay.
        // Das bedeutet, dass Eingabe und Ausgabestrom okay sind.

        // Fuege Client zur Liste aller Clients hinzu.
        mClients.push_back( client );
        retValue = true;
    }
    else
    {
        std::ostringstream out;
        out << "(EE) Server::createAndAddClient "
            << std::hex << this << std::dec
            << " New client "
            << input << " " << output
            << " is not ready!"
            << std::endl;
        std::cerr << out.str();
    }

    return retValue;
}

// Gibt die Anzahl der aktuell registrierten Clients zurueck.
size_t Server::getNumClients() const
{
    return mClients.size();
}

// Sendet eine Nachricht an einen Client.
bool Server::send( const size_t index, const std::string& message )
{
    bool retValue = false;

#ifdef DEBUG
    std::ostringstream out;
    out << "(DD) Server::send "
        << std::hex << this << std::dec
        << " Send '"
        << message
        << "' to client " << index
        << std::endl;
    std::clog << out.str();
#endif

    if ( 0 <= index && index < getNumClients() )
    {
        retValue = mClients[index].send( message );
    }
    else
    {
        std::ostringstream out;
        out << "(EE) Server::send "
            << std::hex << this << std::dec
            << " Index "
            << index
            << " out of boundaries "
            << "[0," << getNumClients()-1 << "]"
            << std::endl;
        std::cerr << out.str();
    }

#ifdef DEBUG
    std::ostringstream out1;
    out1 << "(DD) Server::send "
         << std::hex << this << std::dec
         << " "
         << retValue
         << std::endl;
    std::clog << out1.str();
#endif

    return retValue;
}

// Empfaengt eine Nachricht von einem Client.
bool Server::receive( const size_t index, std::string& message )
{
    bool retValue = false;

    if ( 0 <= index && index < getNumClients() )
    {
        retValue = mClients[index].receive( message );
    }
    else
    {
        std::ostringstream out;
        out << "(EE) Server::receive "
            << std::hex << this << std::dec
            << " Index "
            << index
            << " outside of boundaries "
            << "[0," << getNumClients()-1 << "]"
            << std::endl;
        std::cerr << out.str();
    }

    return retValue;
}
