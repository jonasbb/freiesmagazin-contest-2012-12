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

#ifndef TILETYPE_HH
#define TILETYPE_HH

#include <ostream>

/// Typ eines Feldes zur Erstellung.
enum TileType
{
    // Trockenes Feld.
    TILETYPE_DRY,

    // Feld, was nur ueberflutet wurde (noch begehbar).
    TILETYPE_FLOODED,

    // Untergegangenes Feld.
    TILETYPE_LOST
};

/// Wandlungsroutine Enums -> String.
/**
 * @param type Enum
 * @return String
 */
char const * changeEnumToString( const TileType type );

/// Methode zur Ausgabe der Enums.
/**
 * @param stream Stream, indem geschrieben wird.
 * @param type Auszugebendes Enum
 * @return Ausgabestream.
 */
std::ostream& operator<<( std::ostream& stream, const TileType type );

#endif // TILETYPE_HH
