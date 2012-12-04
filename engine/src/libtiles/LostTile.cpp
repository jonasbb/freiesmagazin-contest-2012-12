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

#include "LostTile.hh"
#include "ITileContext.hh"
#include "TileType.hh"

// Konstruktor.
LostTile::LostTile( ITileContext * contextP )
  : BaseTile(contextP)
{
}

// Lege ein Feld trocken.
bool LostTile::drain()
{
    // Das Feld ist untergegangen, es kann nicht mehr trockengelegt werden.
    return true;
}

// Ueberflute ein Feld.
bool LostTile::flood()
{
    // Das Feld ist bereits untergegangen, es aendert sich nichts.
    return true;
}

// Prueft, ob das Feld noch trocken ist.
bool LostTile::isDry() const
{
    return false;
}

// Prueft, ob das Feld ueberflutet wurde.
bool LostTile::isFlooded() const
{
    return false;
}

// Prueft, ob das Feld schon untergegangen ist.
bool LostTile::isLost() const
{
    return true;
}

// Gibt Zeichen zur Ausgabe des Feldes zurueck.
char LostTile::print() const
{
    return '.';
}
