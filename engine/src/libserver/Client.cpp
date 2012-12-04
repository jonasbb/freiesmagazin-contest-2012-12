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

#include "Client.hh"

#include <iostream>
#include <sstream>

// Konstruktor.
Client::Client( const char* input, const char* output )
: mInString(input), mOutString(output)
{
    // Oeffne die Stroeme entsprechend der gespeicherten Namen.
    openStreams();
}

// Kopierkonstruktor.
Client::Client( const Client& client )
{
    *this = client;
}

// Destruktor.
Client::~Client()
{
    // Schließe beide Stroeme, falls sie offen sind.
    closeStreams();
}

// Zuweisungsoperator.
Client& Client::operator=( const Client& client )
{
    if ( this != &client )
    {
        // Wir koennen die Stroeme nicht direkt kopieren, sonden
        // muessen sie erneut oeffnen.
        closeStreams();

        // Kopiere die Stromnamen.
        mInString = client.mInString;
        mOutString = client.mOutString;

        // Oeffne die Stroeme entsprechend der gespeicherten Namen.
        openStreams();
    }

    return *this;
}


// Schließt Eingabe- und Ausgabestrom.
bool Client::closeStreams()
{
    // Schließe beide Stroeme, falls sie offen sind.
    if ( mInStream.is_open() )
    {
        mInStream.close();
    }

    if ( mOutStream.is_open() )
    {
        mOutStream.close();
    }

    return ( !mInStream.is_open() && !mOutStream.is_open() );
}

// Oeffnet Eingabe- und Ausgabestrom.
bool Client::openStreams()
{
    // Verbinde Strings mit den Dateistroemen.
    mInStream.open( mInString.c_str() );
    mOutStream.open( mOutString.c_str() );

    return ( mInStream.is_open() && mOutStream.is_open() );
}

// Sendet eine Nachricht an den Client.
bool Client::send( const std::string& message )
{
#ifdef DEBUG
    std::ostringstream out;
    out << "(DD) Client::send "
        << std::hex << this << std::dec
        << " '"
        << message
        << "'."
        << std::endl;
    std::clog << out.str() << std::flush;
#endif

    bool retValue = false;

    if ( isReadyForSending() )
    {
#ifdef DEBUG
        std::ostringstream out;
        out << "(DD) Client::send "
            << std::hex << this << std::dec
            << " Client is ready."
            << std::endl;
        std::clog << out.str() << std::flush;
#endif

        // Der Client ist sendebereit.
        mOutStream << message << std::endl << std::flush;

#ifdef DEBUG
        std::ostringstream out2;
        out2 << "(DD) Client::send "
            << std::hex << this << std::dec
            << " Sending finished."
            << std::endl;
        std::clog << out2.str() << std::flush;
#endif
        // Wir fragen sicherheitshalber noch einmal nach,
        // ob der Strom noch okay ist, falls es zu einem Fehler
        // beim Senden kam.
        retValue = isReadyForSending();
    }

#ifdef DEBUG
    std::ostringstream out2;
    out2 << "(DD) Client::send "
         << std::hex << this << std::dec
         << " Return "
         << retValue
         << std::endl;
    std::clog << out2.str() << std::flush;
#endif

    return retValue;
}

// Empfaengt eine Nachricht vom Client.
bool Client::receive( std::string& message )
{
#ifdef DEBUG
    std::ostringstream out;
    out << "(DD) Client::receive "
        << std::hex << this << std::dec
        << std::endl;
    std::clog << out.str() << std::flush;
#endif

    bool retValue = false;

    if ( isReadyForReceiving() )
    {
#ifdef DEBUG
        std::ostringstream out;
        out << "(DD) Client::receive "
            << std::hex << this << std::dec
            << " Client is ready."
            << std::endl;
        std::clog << out.str() << std::flush;
#endif

        // Versuche eine Nachricht zu lesen.
        getline ( mInStream, message );

#ifdef DEBUG
        std::ostringstream out2;
        out2 << "(DD) Client::receive "
             << std::hex << this << std::dec
             << " '"
             << message
             << "'."
             << std::endl;
        std::clog << out2.str() << std::flush;
#endif

        // Wir fragen sicherheitshalber noch einmal nach,
        // ob der Strom noch okay ist, falls es zu einem Fehler
        // beim Empfangen kam.
        retValue = isReadyForReceiving();
    }

#ifdef DEBUG
    std::ostringstream out2;
    out2 << "(DD) Client::receive "
         << std::hex << this << std::dec
         << " Return "
         << retValue
         << std::endl;
    std::clog << out2.str() << std::flush;
#endif

    return retValue;
}
