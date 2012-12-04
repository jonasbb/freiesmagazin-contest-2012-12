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

#include "DryTile.hh"
#include "ITileContext.hh"
#include "TileType.hh"

// Konstruktor.
DryTile::DryTile( ITileContext * contextP )
  : BaseTile(contextP)
{
}

// Lege ein Feld trocken.
bool DryTile::drain()
{
    // Das Feld ist bereits trocken, daher aendert sich nichts.
    return true;
}

// Ueberflute ein Feld.
bool DryTile::flood()
{
    // Das Feld wird ueberflutet.
    if ( mContextP )
    {
        return mContextP->setTile( mContextP->createNewTile( TILETYPE_FLOODED ) );
    }
    return false;
}

// Prueft, ob das Feld noch trocken ist.
bool DryTile::isDry() const
{
    return true;
}

// Prueft, ob das Feld ueberflutet wurde.
bool DryTile::isFlooded() const
{
    return false;
}

// Prueft, ob das Feld schon untergegangen ist.
bool DryTile::isLost() const
{
    return false;
}

// Gibt Zeichen zur Ausgabe des Feldes zurueck.
char DryTile::print() const
{
    return '#';
}
