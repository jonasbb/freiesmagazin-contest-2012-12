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

#ifndef ENGINE_HH
#define ENGINE_HH

#include "EngineConfig.hh"

#include <string>
#include <vector>

/// Vorwaertsdeklaration
class IGame;
class IServer;

/// Spieleengine.
/**
 * Die Spieleengine steuert den gesamten Spielablauf,
 * erstellt und initialisiert alle benoetigten Objekte
 * und sendet und empfaengt Daten an und vom Client.
 */
class Engine
{
  public:
    /// Konstruktor.
    /**
     * @param game Referenz auf die Spieldaten.
     * @param server Referenz auf Server, der die Kommunikation uebernimmt.
     */
    Engine( IGame& game, IServer& server, const EngineConfig& config  );

    /// Destructor.
    ~Engine();

    /// Gibt Anzahl gespielter Runden zurueck.
    unsigned int getNumRounds() const;

    /// Startet ein Spiel.
    /**
     * Die startet das Spiel und kehrt erst zurueck
     * wenn der Spieler untergegangen ist.
     * @return true, falls das Spiel korrekt beendet wurde.
     */
    bool startGame();

  private:
    /// Prueft, ob der Spieler untergegangen ist.
    /**
     * Untergegangen bedeutet, dass der Spieler auf einem
     * untergegangenem Feld steht und damit das Spiel
     * verloren hat.
     * @return true, falls der Spieler untergegangen ist,
     * ansonsten false.
     */
    bool hasPlayerLost() const;

    /// Starte eine einzelne Runde.
    /**
     * @return true, falls alles okay ist.
     */
    bool startRound();

    /// Sende Spielbrett an Client.
    /**
     * @return true, falls alles okay ist.
     */
    bool sendGameboard();

    /// Sende Start-Kommando an den Spieler.
    /**
     * @return true, falls alles okay ist.
     */
    bool sendStartCommand();

    /// Empfange Antwort mit drei Befehlen des Clients.
    /**
     * @return true, falls alles okay ist.
     */
    bool receiveClientCommands( std::vector<std::string>& stringCommands );

    /// Ziehe Karten vom Positionskartenstapel und flute die Felder.
    /**
     * @return true, falls alles okay ist.
     */
    bool drawPositionsCardsAndFloodTiles();

    /// Ziehe Flutkarten.
    /**
     * @return true, falls alles okay ist.
     */
    bool drawFloodCards();

    /// Sende Nachricht an ersten Client.
    bool sendClient( const std::string& message );

    /// Schreibe Log-Nachricht (falls aktiv).
    void writeLog( const std::string& message ) const;

  private:

    /// Spieldaten fuer das Spiel (bereits initialisiert).
    /**
     * Es wird davon ausgegangen, dass die Spieldabei bereits
     * initialisiert wurden.
     */
    IGame& mGameR;

    /// Server, der die Kommunikation uebernimmt.
    /**
     * Der Server muss als Referenz von aussen uebergeben werden.
     */
    IServer& mServerR;

    /// Konfiguration fuer die Engine.
    EngineConfig mConfig;
    
    /// Anzahl des bisher gespielten Runden.
    unsigned int mRounds;
};

#endif // ENGINE_HH
