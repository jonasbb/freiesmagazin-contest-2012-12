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

#ifndef TEXTMESSAGE_HH
#define TEXTMESSAGE_HH

#include "IMessage.hh"
#include "MessageId.hh"

#include <string>

// Vorwaertsdeklarationen.
class IMessageOperator;

/// Textnachricht.
/**
 * Einfache Textnachricht.
 */
class TextMessage : public IMessage
{
  public:
    /// Konstruktor.
    TextMessage( const std::string& line );
  
    /// Destruktor.
    virtual ~TextMessage();

    /// Gibt die Id der Nachricht zurueck.
    virtual MessageId getId() const;

    /// Operiert auf einem Kontext.
    /**
     * @param oper Operator, auf dem operiert werden soll.
     * @return true, wenn die Operation angewendet werden konnte.
     */
    virtual bool operate( IMessageOperator& oper ) const;

    /// Gibt den Text der Nachricht zurueck.
    const std::string& getText() const;

  private:
    /// Der gespeicherte Text.
    std::string mText;
};

// INLINE ///////////////////////////////////////////////////////////

// Gibt den Text der Nachricht zurueck.
inline
const std::string& TextMessage::getText() const
{
    return mText;
}

#endif // TEXTMESSAGE_HH
