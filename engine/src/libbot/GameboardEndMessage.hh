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

#ifndef GAMEBOARDENDMESSAGE_HH
#define GAMEBOARDENDMESSAGE_HH

#include "IMessage.hh"
#include "MessageId.hh"

// Vorwaertsdeklarationen.
class IMessageOperator;

/// Spielbrett-Ende-Nachricht.
/**
 * Das Spielbrett wurde komplett uebertragen.
 */
class GameboardEndMessage : public IMessage
{
  public:
    /// Konstruktor.
    GameboardEndMessage();
  
    /// Destruktor.
    virtual ~GameboardEndMessage();

    /// Gibt die Id der Nachricht zurueck.
    virtual MessageId getId() const;

    /// Operiert auf einem Kontext.
    /**
     * @param oper Operator, auf dem operiert werden soll.
     * @return true, wenn die Operation angewendet werden konnte.
     */
    virtual bool operate( IMessageOperator& oper ) const;
};

#endif // GAMEBOARDENDMESSAGE_HH
