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

#ifndef CLIENT_HH
#define CLIENT_HH

#include <fstream>
#include <string>

/// Client.
/**
 * Der Client haelt einen Eingabe- und einen Ausgabestrom,
 * über die man mit ihm kommunizieren kann.
 */
class Client
{
  public:

    /// Konstruktor.
    /**
     * Erstellt einen neuen Client mit einem Eingabe-
     * und einem Ausgabestrom. Wenn die Erstellung okay
     * ist, liefert die Methode isReady() true zurueck.
     * @param input Eingabestrom
     * @param output Ausgabestrom
     */
    Client( const char* input, const char* output );

    /// Kopierkonstruktor.
    Client( const Client& client );

    /// Destruktor.
    ~Client();

    /// Zuweisungsoperator.
    Client& operator=( const Client& client );

    /// Prueft, ob er Client bereits ist zum Senden und Empfangen.
    /**
     * Es wird dabei abgefragt, ob die Stroeme geoeffnet sind.
     * @return true, falls der Client bereit ist.
     */
    bool isReady() const;

    /// Sendet eine Nachricht an den Client.
    /**
     * Falls die Nachricht nicht gesendet werden konnte, z.B.
     * weil der Ausgabestrom nicht geoeffnet wird oder wenn
     * danach ein Fehler gemeldet wird.
     * @param[in] message Nachricht, die gesendet werden soll.
     * @return true, falls die Nachricht korrekt gesendet wurde.
     */
    bool send( const std::string& message );

    /// Empfaengt eine Nachricht vom Client.
    /**
     * Dies ist ein Polling-Mechanismus, der einfach versucht
     * etwas vom Client zu lesen. Falls dieser nichts liefert,
     * wird ein leerer String zurueckgegeben.
     * Nur im Fehlerfall ist der Rueckgabewert false.
     * @param[out] message Nachricht, die empfangen wurde.
     * @return true, falls die Nachricht empfangen werden konnte
     */
    bool receive( std::string& message );
    
  private:

    /// Schließt Eingabe- und Ausgabestrom.
    /**
     * @return true, falls die Stroeme geschlossen wurden (oder schon
     * geschlossen waren)
     */
    bool closeStreams();

    /// Oeffnet Eingabe- und Ausgabestrom.
    /**
     * Beide Stroeme werden anhand der gespeicherten Namen
     * m_inString und m_outString geoeffnet.
     * @return true, falls die Stroeme geoeffnet werden konnten.
     */
    bool openStreams();

    /// Prueft, ob er Client bereits ist zum Senden.
    /**
     * Es wird dabei abgefragt, ob der Ausgabestrom geoeffnet ist.
     * @return true, falls der Client bereit ist.
     */
    bool isReadyForSending() const;

    /// Prueft, ob er Client bereits ist zum Empfangen.
    /**
     * Es wird dabei abgefragt, ob der Eingabestrom geoeffnet ist.
     * @return true, falls der Client bereit ist.
     */
    bool isReadyForReceiving() const;

  private:

    /// Eingabestrom.
    std::ifstream mInStream;

    /// Eingabestrom.
    std::ofstream mOutStream;

    /// String, mit dem der Eingabestrom geoeffnet wurde.
    std::string mInString;

    /// String, mit dem der Ausgabestrom geoeffnet wurde.
    std::string mOutString;
    
};

// INLINE ///////////////////////////////////////////////////////////

// Prueft, ob er Client bereits ist zum Senden und Empfangen.
inline
bool Client::isReady() const
{
    return ( isReadyForSending() &&  isReadyForReceiving() );
}

// Prueft, ob er Client bereits ist zum Senden.
inline
bool Client::isReadyForSending() const
{
    return ( mOutStream.is_open() && !mOutStream.fail() );
}

// Prueft, ob er Client bereits ist zum Empfangen.
inline
bool Client::isReadyForReceiving() const
{
    return ( mInStream.is_open() && !mInStream.fail() );
}

#endif // CLIENT_HH
