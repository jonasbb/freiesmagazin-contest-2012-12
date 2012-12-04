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

#ifndef SERVER_HH
#define SERVER_HH

#include "Client.hh"
#include "IServer.hh"

#include <vector>

/// Server.
/**
 * Der Server haelt die Verbindungen (Ein- und Ausgabestrom)
 * zu allen Clients. Zusaetzlich wird die gesamte Kommunikation
 * der Engine ueber den Server abgewickelt.
 * Auf die Clients kann man ueber eine ID zugreifen, wobei die
 * Client-IDs aufsteigend sortiert sind und mit dem Index in der
 * Liste übereinstimmen. Das heißt Client 1 hat ID 0, Client 2 hat
 * ID 1 ...
 */
class Server : public IServer
{
  public:

    /// Constructor.
    /**
     * Erstellt eine leere Liste mit Clients, die dann per
     * createAndAddClient gefuellt werden kann.
     */
    Server();

    /// Destruktor.
    virtual ~Server();

    /// Erstellt einen neuen Client und fuegt diesen zur Liste hinzu.
    /**
     * Aus dem Eingabe- und Ausgabestrom wird ein Client erstellt,
     * mit dem man dann kommunizieren kann.
     * @param input Eingabestrom.
     * @param output Ausgabestrom
     * @return true, falls der Client erstellt und hinzugefuegt
     * werden konnte.
     */
    virtual bool createAndAddClient( const char* input, const char* output );

    /// Gibt die Anzahl der aktuell registrierten Clients zurueck.
    virtual size_t getNumClients() const;

    /// Sendet eine Nachricht an einen Client.
    /**
     * Falls die Nachricht nicht gesendet werden konnte, z.B.
     * weil der Ausgabestrom nicht geoeffnet wird oder wenn
     * danach ein Fehler gemeldet wird.
     * @param index Index des Clients (startet bei 0).
     * @param[in] message Nachricht, die gesendet werden soll.
     * @return true, falls die Nachricht korrekt gesendet wurde.
     */
    virtual bool send( const size_t index, const std::string& message );

    /// Empfaengt eine Nachricht von einem Client.
    /**
     * Dies ist ein Polling-Mechanismus, der einfach versucht
     * etwas vom Client zu lesen. Falls dieser nichts liefert,
     * wird ein leerer String zurueckgegeben.
     * Nur im Fehlerfall ist der Rueckgabewert false.
     * @param index Index des Clients (startet bei 0).
     * @param[out] message Nachricht, die empfangen wurde.
     * @return true, falls die Nachricht empfangen werden konnte
     */
    virtual bool receive( const size_t index, std::string& message );
    
  private:

    /// Liste aller registrierten Clients.
    std::vector<Client> mClients;
};

#endif // SERVER_HH
