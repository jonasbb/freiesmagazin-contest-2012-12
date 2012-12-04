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

#include "TileType.hh"

char const * const TileTypeTab[] =
{
    "DRY",
    "FLOODED",
    "LOST"
};

// Wandlungsroutine Enums -> String.
char const * changeEnumToString( const TileType type )
{
    return TileTypeTab[(int)type];
}

// Methode zur Ausgabe der Enums.
std::ostream& operator<<( std::ostream& stream, const TileType type )
{
    stream << changeEnumToString(type);
    return stream;
}
