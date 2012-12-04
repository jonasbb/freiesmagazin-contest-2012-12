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

#ifndef MESSAGEPROCESSOR_HH
#define MESSAGEPROCESSOR_HH

#include "IMessageOperator.hh"
#include "Position.hh"

#include <string>
#include <vector>

// Vorwaertsdeklarationen.
class EndMessage;
class FloodMessage;
class GameboardEndMessage;
class GameboardLineMessage;
class GameboardStartMessage;
class GameData;
class IncrFloodMessage;
class StartMessage;
class TextMessage;

/// Verarbeitung von Nachrichten.
/**
 * Die Klasse empfaengt die vom Server geschickten Nachrichten
 * und extrahiert die Daten in die Datenklasse.
 */
class MessageProcessor : public IMessageOperator
{
  public:
    /// Konstruktor.
    MessageProcessor( GameData * dataP );
  
    /// Destruktor.
    virtual ~MessageProcessor();

    /// Werte zuruecksetzen.
    virtual void reset();

    /// Behandelt eine Start-Nachricht.
    /**
     * @param message Zu verarbeitende Nachricht.
     * @return true, wenn die Nachricht korrekt verarbeitet wurde
     */
    virtual bool operate( const StartMessage& message );

    /// Behandelt eine Flut-Nachricht.
    /**
     * @param message Zu verarbeitende Nachricht.
     * @return true, wenn die Nachricht korrekt verarbeitet wurde
     */
    virtual bool operate( const FloodMessage& message );

    /// Behandelt eine Steigende-Flut-Nachricht.
    /**
     * @param message Zu verarbeitende Nachricht.
     * @return true, wenn die Nachricht korrekt verarbeitet wurde
     */
    virtual bool operate( const IncrFloodMessage& message );

    /// Behandelt eine Ende-Nachricht.
    /**
     * @param message Zu verarbeitende Nachricht.
     * @return true, wenn die Nachricht korrekt verarbeitet wurde
     */
    virtual bool operate( const EndMessage& message );
    
    /// Behandelt eine Spielbrett-Start-Nachricht.
    /**
     * @param message Zu verarbeitende Nachricht.
     * @return true, wenn die Nachricht korrekt verarbeitet wurde
     */
    virtual bool operate( const GameboardStartMessage& message );

    /// Behandelt eine Spielbrett-Zeile-Nachricht.
    /**
     * @param message Zu verarbeitende Nachricht.
     * @return true, wenn die Nachricht korrekt verarbeitet wurde
     */
    virtual bool operate( const GameboardLineMessage& message );

    /// Behandelt eine Spielbrett-Ende-Nachricht.
    /**
     * @param message Zu verarbeitende Nachricht.
     * @return true, wenn die Nachricht korrekt verarbeitet wurde
     */
    virtual bool operate( const GameboardEndMessage& message );

    /// Behandelt eine Textnachricht.
    /**
     * @param message Zu verarbeitende Nachricht.
     * @return true, wenn die Nachricht korrekt verarbeitet wurde
     */
    virtual bool operate( const TextMessage& message );

  private:
    /// Behandle eine Bewegung.
    /**
     * @param direction Richtung, in die man sich bewegt.
     * @return true, wenn die Nachricht korrekt verarbeitet wurde
     */
    bool operateGo( const std::string& direction );

    /// Behandle eine Trockenlege-Aktion.
    /**
     * @param direction Richtung, wo man trockenlegen will.
     * @return true, wenn die Nachricht korrekt verarbeitet wurde
     */
    bool operateDry( const std::string& direction );

    /// Bewegt den Spieler ein Feld nach rechts.
    bool movePlayerEast();

    /// Bewegt den Spieler ein Feld nach oben.
    bool movePlayerNorth();

    /// Bewegt den Spieler ein Feld nach unten.
    bool movePlayerSouth();

    /// Bewegt den Spieler ein Feld nach links.
    bool movePlayerWest();

    /// Lege das Feld, auf dem der Spieler steht, trocken.
    bool drainTileCurrent();

    /// Lege das Feld rechts vom Spieler trocken.
    bool drainTileEast();

    /// Lege das Feld unterhalb vom Spieler trocken.
    bool drainTileNorth();

    /// Lege das Feld ueberhalb vom Spieler trocken.
    bool drainTileSouth();

    /// Lege das Feld links vom Spieler trocken.
    bool drainTileWest();
    
  private:
    /// Die Daten der GUI.
    GameData* mDataP;

    /// Flag, dass Spielfeld gerade uebertragen wird.
    bool mGameboardStarted;

    /// Zwischengespeicherte Spielbrettgroesse.
    Position mGameboardSize;

    /// Die einzelnen Zeilen des Spielbretts.
    std::vector<std::string> mGameboardStrings;
};

#endif // MESSAGEPROCESSOR_HH
