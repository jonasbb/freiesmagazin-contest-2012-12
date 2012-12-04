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

#ifndef GAMEBOARDLINEMESSAGE_HH
#define GAMEBOARDLINEMESSAGE_HH

#include "IMessage.hh"
#include "MessageId.hh"

#include <string>

// Vorwaertsdeklarationen.
class IMessageOperator;

/// Spielbrett-Zeile-Nachricht.
/**
 * Nach dem Spielbrett-Start werden die einzelnen Zeilen des
 * Spielbrett hierueber uebertragen.
 */
class GameboardLineMessage : public IMessage
{
  public:
    /// Konstruktor.
    GameboardLineMessage( const std::string& line );
  
    /// Destruktor.
    virtual ~GameboardLineMessage();

    /// Gibt die Id der Nachricht zurueck.
    virtual MessageId getId() const;

    /// Operiert auf einem Kontext.
    /**
     * @param oper Operator, auf dem operiert werden soll.
     * @return true, wenn die Operation angewendet werden konnte.
     */
    virtual bool operate( IMessageOperator& oper ) const;

    /// Gibt die Spielbrettzeile zurueck.
    const std::string& getLine() const;

  private:
    /// Eine Zeile des Spielbretts.
    std::string mLine;
};

// INLINE ///////////////////////////////////////////////////////////

// Gibt die Spielbrettzeile zurueck.
inline
const std::string& GameboardLineMessage::getLine() const
{
    return mLine;
}

#endif // GAMEBOARDLINEMESSAGE_HH
