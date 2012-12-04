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

#ifndef FLOODMESSAGE_HH
#define FLOODMESSAGE_HH

#include "IMessage.hh"
#include "MessageId.hh"
#include "Position.hh"

// Vorwaertsdeklarationen.
class IMessageOperator;

/// Flut-Nachricht.
/**
 * Die Flut-Nachricht gibt an, welche Felder auf dem Spielbrett
 * ueberflutet werden und damit ggf. untergehen, falls sie zuvor
 * schon ueberflutet waren.
 */
class FloodMessage : public IMessage
{
  public:
    /// Konstruktor.
    FloodMessage( const Position& pos );
  
    /// Destruktor.
    virtual ~FloodMessage();

    /// Gibt die Id der Nachricht zurueck.
    virtual MessageId getId() const;

    /// Operiert auf einem Kontext.
    /**
     * @param oper Operator, auf dem operiert werden soll.
     * @return true, wenn die Operation angewendet werden konnte.
     */
    virtual bool operate( IMessageOperator& oper ) const;

    /// Gibt Feldposition zurueck.
    const Position& getPosition() const;

  private:
    /// Position des des ueberfluteten Feldes.
    Position mPosition;
};

// INLINE ///////////////////////////////////////////////////////////

// Gibt Feldposition zurueck.
inline
const Position& FloodMessage::getPosition() const
{
    return mPosition;
}

#endif // FLOODMESSAGE_HH
