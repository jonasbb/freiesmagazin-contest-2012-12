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

#include "GameboardStartMessage.hh"
#include "IMessageOperator.hh"

// Konstruktor.
GameboardStartMessage::GameboardStartMessage( const Position& size )
  : mSize(size)
{
}

// Destruktor.
GameboardStartMessage::~GameboardStartMessage()
{
}

// Gibt die Id der Nachricht zurueck.
MessageId GameboardStartMessage::getId() const
{
    return MESSAGE_ID_GB_START;
}

// Operiert auf einem Kontext.
bool GameboardStartMessage::operate( IMessageOperator& oper ) const
{
    return oper.operate( *this );
}
