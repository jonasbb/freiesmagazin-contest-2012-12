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

#ifndef INCRFLOODMESSAGE_HH
#define INCRFLOODMESSAGE_HH

#include "IMessage.hh"
#include "MessageId.hh"

// Vorwaertsdeklarationen.
class IMessageOperator;

/// Steigende-Flut-Nachricht.
/**
 * Die Flut steigt um den gespeicherten Wert, d.h. es werden so
 * viele zusaetzliche Felder ab der naechsten Runde ueberflutet.
 */
class IncrFloodMessage : public IMessage
{
  public:
    /// Konstruktor.
    IncrFloodMessage( const unsigned int num );
  
    /// Destruktor.
    virtual ~IncrFloodMessage();

    /// Gibt die Id der Nachricht zurueck.
    virtual MessageId getId() const;

    /// Operiert auf einem Kontext.
    /**
     * @param oper Operator, auf dem operiert werden soll.
     * @return true, wenn die Operation angewendet werden konnte.
     */
    virtual bool operate( IMessageOperator& oper ) const;

    /// Gibt zurueck, wie hoch die Fluch steigt.
    unsigned int getNumIncrFlood() const;

  private:
    /// Wert, wie hoch die Flut steigt.
    unsigned int mNumIncr;

};

// INLINE ///////////////////////////////////////////////////////////

// Gibt zurueck, wie hoch die Fluch steigt.
inline
unsigned int IncrFloodMessage::getNumIncrFlood() const
{
    return mNumIncr;
}

#endif // INCRFLOODMESSAGE_HH
