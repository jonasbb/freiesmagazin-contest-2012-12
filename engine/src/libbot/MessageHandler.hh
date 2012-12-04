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

#ifndef MESSAGEHANDLER_HH
#define MESSAGEHANDLER_HH

#include <string>

// Vorwaertsdeklarationen.
class IMessage;
class ITextStream;

/// Klasse zum Empfang und Versand von Nachrichten.
/**
 * Die Klasse empfaengt und sendet Nachrichten.
 * Der Empfang geschieht dabei ueber ein extra Interface.
 */
class MessageHandler
{
  public:
    /// Konstruktor.
    MessageHandler( ITextStream * textStream );
  
    /// Empfaengt eine Nachricht.
    /**
     * Der Rufer der Methode wird Besitzer der Nachricht und muss
     * sich ggf. um deren Zerstoerung nach der Verarbeitung kuemmern.
     * @param[out] Zeiger auf eine neue Nachricht oder 0, falls
     * es keine gab.
     * @return false, falls es zu einem Fehler kam.
     */
    bool receiveMessage( IMessage*& msgPR );

    /// Sendet eine Textnachricht nach STDOUT.
    /**
     * @param[ message Zu sendende Nachricht.
     */
    void sendTextMessage( const std::string& message ) const;

private:

    /// Hole eine Textnachricht vom STDIN ab.
    /**
     * @param[out] message Empfangene Nachricht.
     * @return true, wenn die empfangene Nachricht nicht leer ist.
     */
    bool getTextStdin( std::string& message ) const;

    /// Erstellt eine Nachricht aus einer Textnachricht.
    /**
     * @param[out] Zeiger auf eine neue Nachricht oder 0, falls
     * es keine gab.
     * @param[in] message Empfangene Nachricht.
     * @return false, falls es zu einem Fehler kam.
     */
    bool createMessage( IMessage*& msgPR, const std::string& message );

    /// Erstellt eine Start-Nachricht.
    /**
     * @param[out] Zeiger auf die neue Nachricht.
     * @param[in] param Empfangene Parameter
     * @return false, falls es zu einem Fehler kam.
     */
    bool createStartMessage( IMessage*& msgPR, const std::string& param ) const;

    /// Erstellt eine Flut-Nachricht.
    /**
     * @param[out] Zeiger auf die neue Nachricht.
     * @param[in] param Empfangene Parameter
     * @return false, falls es zu einem Fehler kam.
     */
    bool createFloodMessage( IMessage*& msgPR, const std::string& param ) const;

    /// Erstellt eine Flut-Steigt-Nachricht.
    /**
     * @param[out] Zeiger auf die neue Nachricht.
     * @param[in] param Empfangene Parameter
     * @return false, falls es zu einem Fehler kam.
     */
    bool createIncrFloodMessage( IMessage*& msgPR, const std::string& param ) const;

    /// Erstellt eine Ende-Nachricht.
    /**
     * @param[out] Zeiger auf die Nachricht.
     * @return false, falls es zu einem Fehler kam.
     */
    bool createEndMessage( IMessage*& msgPR ) const;

    /// Erstellt eine Spielbrett-Start-Nachricht.
    /**
     * @param[out] Zeiger auf die Nachricht.
     * @param[in] param Empfangene Parameter
     * @return false, falls es zu einem Fehler kam.
     */
    bool createGameboardStartMessage( IMessage*& msgPR, const std::string& param );

    /// Erstellt eine Spielbrett-Zeilen-Nachricht.
    /**
     * @param[out] Zeiger auf die Nachricht.
     * @param[in] param Empfangene Parameter
     * @return false, falls es zu einem Fehler kam.
     */
    bool createGameboardLineMessage( IMessage*& msgPR, const std::string& param ) const;

    /// Erstellt eine Spielbrett-Ende-Nachricht.
    /**
     * @param[out] Zeiger auf die Nachricht.
     * @return false, falls es zu einem Fehler kam.
     */
    bool createGameboardEndMessage( IMessage*& msgPR );

    /// Erstellt eine Textnachricht.
    /**
     * @param[out] Zeiger auf die Nachricht.
     * @param[in] param Empfangene Parameter
     * @return false, falls es zu einem Fehler kam.
     */
    bool createTextMessage( IMessage*& msgPR, const std::string& param ) const;

  private:
    /// Flag, ob gerade ein Spielbrett uebertragen wird.
    /**
     * Das Flag ist immer true zwischen einer Spielbrett-Start-
     * und einer Spielbrett-Ende-Nachricht.
     */
    bool mGameboardStarted;

    /// Zeiger auf einen Stream zum Auslesen und Schreiben von Daten.
    ITextStream * mTextStream;
};

#endif // MESSAGEHANDLER_HH
