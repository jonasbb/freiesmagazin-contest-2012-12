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

#ifndef COMMANDHANDLER_HH
#define COMMANDHANDLER_HH

// Vorwaertsdeklaration.
class GameData;
class IMessageOperator;
class MessageHandler;
class QString;
class SingleTextStream;

/// Verarbeitung von Nachrichten.
/**
 * Die Klasse empfaengt die vom Server geschickten Nachrichten
 * und extrahiert die Daten in die Datenklasse.
 */
class CommandHandler
{
  public:
    /// Konstruktor.
    CommandHandler();

    /// Destruktor.
    ~CommandHandler();

    /// Initialisiert das Kommando-Handling.
    /**
     * @param dataP Zeiger auf die Spieldaten
     * @return true, wenn alles gut verlief. 
     */
    bool init( GameData * dataP );

    /// Alle Daten zuruecksetzen.
    void reset();

    /// Verarbeite eine Nachricht (als Text).
    /**
     * @param messageStr Empfangene Nachricht als Text.
     * @return true, wenn die Nachricht Text enthielt, der verarbeitet
     * werden konnte und eine Aenderung bewirkte.
     */
    bool receiveAndHandleMessage( const QString& messageStr );

  private:
    /// Zeiger auf den Nachrichtenverarbeiter.
    IMessageOperator* mMessageOperatorP;

    /// Zeiger auf den Nachrichtenverteiler.
    MessageHandler* mMessageHandlerP;

    /// Zeiger auf den "Eingabestrom".
    SingleTextStream* mSingleTextStreamP;
};

#endif // COMMANDHANDLER_HH
