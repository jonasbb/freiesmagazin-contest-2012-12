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

#ifndef STRATEGY_HH
#define STRATEGY_HH

#include "IStrategy.hh"
#include "StrategyData.hh"

#include <string>
#include <vector>

// Vorwaertsdeklarationen.
class EndMessage;
class FloodMessage;
class GameboardEndMessage;
class GameboardLineMessage;
class GameboardStartMessage;
class IncrFloodMessage;
class StartMessage;
class TextMessage;

/// Die konkrete Strategie.
/**
 * Fuer eine echte Strategie muessen die Methoden in der
 * Implementierung entsprechend angepasst werden.
 */
class Strategy : public IStrategy
{
  public:
    /// Konstruktor.
    Strategy();
  
    /// Destruktor.
    virtual ~Strategy();

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

    /// Fragt ab, ob Kommandos zur Verfuegung stehen.
    /**
     * Die Methode wird vom Bot nach dem Empfang jeder (!)
     * Nachricht gerufen. In der Regel stoesst die Start-Nachricht
     * die Berechnung an. Stehen Kommandos zur Verfuegung, muessen
     * diese gleich in die cmdList eingetragen werden.
     * @param[out] cmdList Liste mit exakt drei Kommandos, die
     * der Bot ausfuehren soll.
     * @return false, falls keine Kommandos abgeholt werden konnten
     */
    virtual bool isCommandsAvailable( std::vector<std::string>& cmdList );

    /// Gibt zurueck, ob das Spiel zu Ende sein soll.
    /**
     * Die Methode wird vom Bot nach dem Empfang jeder (!)
     * Nachricht gerufen. In der Regel wird true geliefert, nachdem
     * die Ende-Nachricht empfangen wurde. Ggf. aber auch, wenn es
     * zu einem internen Fehler kam und der Bot die Abarbeitung
     * abbrechen soll.
     * @return true, wenn der Bot stoppen soll
     */
    virtual bool isEnd() const;

  private:
    /// Berechne die drei Aktionen, die spaeter ausgegeben werden sollen.
    /**
     * @return true, wenn die Berechnung korrekt verlief.
     */
    bool calcCommands();

  private:
    /// Die Strategie-Daten.
    StrategyData mData;

    /// Liste mit den drei Aktionen des Bots.
    std::vector<std::string> mCommandList;

    /// Flag, dass die Strategie nicht weiter aufgerufen werden soll.
    bool mIsFinished;

    /// Flag, dass Spielfeld gerade uebertragen wird.
    bool mGameboardStarted;
};

#endif // STRATEGY_HH
