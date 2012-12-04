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

#ifndef STARTMESSAGE_HH
#define STARTMESSAGE_HH

#include "IMessage.hh"
#include "MessageId.hh"
#include "Position.hh"

// Vorwaertsdeklarationen.
class IMessageOperator;

/// Start-Nachricht.
/**
 * Die Start-Nachricht enthaelt die aktuelle Runde und Position
 * des Bots. Sie ist der Anlass, dass der Bot drei Aktionen
 * berechnet.
 */
class StartMessage : public IMessage
{
  public:
    /// Konstruktor.
    StartMessage( const unsigned int numRound, const Position& pos );
  
    /// Destruktor.
    virtual ~StartMessage();

    /// Gibt die Id der Nachricht zurueck.
    virtual MessageId getId() const;

    /// Operiert auf einem Kontext.
    /**
     * @param oper Operator, auf dem operiert werden soll.
     * @return true, wenn die Operation angewendet werden konnte.
     */
    virtual bool operate( IMessageOperator& oper ) const;

    /// Gibt Rundenzahl zurueck.
    unsigned int getNumRound() const;

    /// Gibt Botposition zurueck.
    const Position& getPosition() const;

  private:
    /// Nummer der aktuellen Runde.
    unsigned int mNumRound;

    /// Position des Bots.
    Position mPosition;
};

// INLINE ///////////////////////////////////////////////////////////

// Gibt Rundenzahl zurueck.
inline
unsigned int StartMessage::getNumRound() const
{
    return mNumRound;
}

// Gibt Botposition zurueck.
inline
const Position& StartMessage::getPosition() const
{
    return mPosition;
}

#endif // STARTMESSAGE_HH
