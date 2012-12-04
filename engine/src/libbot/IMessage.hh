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

#ifndef IMESSAGE_HH
#define IMESSAGE_HH

#include "MessageId.hh"

// Vorwaertsdeklarationen.
class IMessageOperator;

/// Interface fuer eine Nachricht.
/**
 * Die abgeleitete Nachricht fuehrt in der Regel neue
 * Attribute ein und Methoden, diese abzufragen.
 * Hiermit wird das Visitor-Pattern umgesetzt.
 */
class IMessage
{
  public:
    /// Destruktor.
    virtual ~IMessage() { }

    /// Gibt die Id der Nachricht zurueck.
    virtual MessageId getId() const = 0;

    /// Operiert auf einem Kontext.
    /**
     * Die konkrete Nachricht muss die Methode implementieren
     * und nur die jeweilige Methode des Operators aufrufen,
     * um die Nachricht zu verarbeiten.
     * @param oper Operator, auf dem operiert werden soll.
     * @return true, wenn die Operation angewendet werden konnte.
     */
    virtual bool operate( IMessageOperator& oper ) const = 0;
    
};

#endif // IMESSAGE_HH
