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

#ifndef GAMEBOARDSTARTMESSAGE_HH
#define GAMEBOARDSTARTMESSAGE_HH

#include "IMessage.hh"
#include "MessageId.hh"
#include "Position.hh"

// Vorwaertsdeklarationen.
class IMessageOperator;

/// Spielbrett-Start-Nachricht.
/**
 * Es wird ab jetzt ein neues Spielbrett uebertragen bis die
 * Spielbrett-Ende-Nachricht kommt.
 */
class GameboardStartMessage : public IMessage
{
  public:
    /// Konstruktor.
    GameboardStartMessage( const Position& size );
  
    /// Destruktor.
    virtual ~GameboardStartMessage();

    /// Gibt die Id der Nachricht zurueck.
    virtual MessageId getId() const;

    /// Operiert auf einem Kontext.
    /**
     * @param oper Operator, auf dem operiert werden soll.
     * @return true, wenn die Operation angewendet werden konnte.
     */
    virtual bool operate( IMessageOperator& oper ) const;

    /// Gibt die Groesse des Spielfelds zurueck.
    const Position& getSize() const;

  private:
    /// Position des des ueberfluteten Feldes.
    Position mSize;
};

// INLINE ///////////////////////////////////////////////////////////

// Gibt die Groesse des Spielfelds zurueck.
inline
const Position& GameboardStartMessage::getSize() const
{
    return mSize;
}

#endif // GAMEBOARDSTARTMESSAGE_HH
