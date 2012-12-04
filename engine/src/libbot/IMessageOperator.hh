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

#ifndef IMESSAGEOPERATOR_HH
#define IMESSAGEOPERATOR_HH

// Vorwaertsdeklarationen.
class EndMessage;
class FloodMessage;
class GameboardEndMessage;
class GameboardLineMessage;
class GameboardStartMessage;
class IncrFloodMessage;
class StartMessage;
class TextMessage;

/// Interface fuer einen Nachrichten-Operator.
/**
 * Der konkrete Operator (die konkrete Strategie) benoetigt
 * fuer jede konkrete Nachricht eine Methode, in der die
 * Nachricht verarbeitet wird.
 * Hiermit wird das Visitor-Pattern umgesetzt.
 */
class IMessageOperator
{
  public:
    /// Destruktor.
    virtual ~IMessageOperator() { }

    /// Werte zuruecksetzen.
    virtual void reset() = 0;
    
    /// Behandelt eine Start-Nachricht.
    /**
     * @param message Zu verarbeitende Nachricht.
     * @return true, wenn die Nachricht korrekt verarbeitet wurde
     */
    virtual bool operate( const StartMessage& message ) = 0;

    /// Behandelt eine Flut-Nachricht.
    /**
     * @param message Zu verarbeitende Nachricht.
     * @return true, wenn die Nachricht korrekt verarbeitet wurde
     */
    virtual bool operate( const FloodMessage& message ) = 0;

    /// Behandelt eine Steigende-Flut-Nachricht.
    /**
     * @param message Zu verarbeitende Nachricht.
     * @return true, wenn die Nachricht korrekt verarbeitet wurde
     */
    virtual bool operate( const IncrFloodMessage& message ) = 0;

    /// Behandelt eine Ende-Nachricht.
    /**
     * @param message Zu verarbeitende Nachricht.
     * @return true, wenn die Nachricht korrekt verarbeitet wurde
     */
    virtual bool operate( const EndMessage& message ) = 0;

    /// Behandelt eine Spielbrett-Start-Nachricht.
    /**
     * @param message Zu verarbeitende Nachricht.
     * @return true, wenn die Nachricht korrekt verarbeitet wurde
     */
    virtual bool operate( const GameboardStartMessage& message ) = 0;

    /// Behandelt eine Spielbrett-Zeile-Nachricht.
    /**
     * @param message Zu verarbeitende Nachricht.
     * @return true, wenn die Nachricht korrekt verarbeitet wurde
     */
    virtual bool operate( const GameboardLineMessage& message ) = 0;

    /// Behandelt eine Spielbrett-Ende-Nachricht.
    /**
     * @param message Zu verarbeitende Nachricht.
     * @return true, wenn die Nachricht korrekt verarbeitet wurde
     */
    virtual bool operate( const GameboardEndMessage& message ) = 0;

    /// Behandelt eine Textnachricht.
    /**
     * @param message Zu verarbeitende Nachricht.
     * @return true, wenn die Nachricht korrekt verarbeitet wurde
     */
    virtual bool operate( const TextMessage& message ) = 0;
};

#endif // IMESSAGEOPERATOR_HH
