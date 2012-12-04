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

#include "StartMessage.hh"
#include "IMessageOperator.hh"

// Konstruktor.
StartMessage::StartMessage( const unsigned int numRound, const Position& pos )
  : mNumRound(numRound), mPosition(pos)
{
}

// Destruktor.
StartMessage::~StartMessage()
{
}

// Gibt die Id der Nachricht zurueck.
MessageId StartMessage::getId() const
{
    return MESSAGE_ID_START;
}
    
// Operiert auf einem Kontext.
bool StartMessage::operate( IMessageOperator& oper ) const
{
    return oper.operate( *this );
}
