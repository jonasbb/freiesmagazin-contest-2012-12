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

#ifndef MESSAGEID_HH
#define MESSAGEID_HH

#include <ostream>

/// Identifikator einer Nachricht.
enum MessageId
{
    MESSAGE_ID_START,        // Eine neue Runde startet.
    MESSAGE_ID_FLOOD,        // Ein Feld wird geflutet.
    MESSAGE_ID_INCR_FLOOD,   // Die Flut steigt.
    MESSAGE_ID_END,          // Das Spiel ist zu Ende.
    MESSAGE_ID_GB_START,     // Ein neues Spielbrett wird uebertragen.
    MESSAGE_ID_GB_LINE,      // Eine Spielbrettzeile.
    MESSAGE_ID_GB_END,       // Ende des Spielbretts
    MESSAGE_ID_TEXT          // Reiner Text

};

/// Wandlungsroutine Enums -> String.
/**
 * @param type Enum
 * @return String
 */
char const * changeEnumToString( const MessageId type );

/// Methode zur Ausgabe der Enums.
/**
 * @param stream Stream, indem geschrieben wird.
 * @param type Auszugebendes Enum
 * @return Ausgabestream.
 */
std::ostream& operator<<( std::ostream& stream, const MessageId type );

#endif // MESSAGEID_HH
