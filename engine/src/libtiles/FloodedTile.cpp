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

#include "FloodedTile.hh"
#include "ITileContext.hh"
#include "TileType.hh"

// Konstruktor.
FloodedTile::FloodedTile( ITileContext * contextP )
  : BaseTile(contextP)
{
}

// Lege ein Feld trocken.
bool FloodedTile::drain()
{
    // Das Feld wird trocken gelegt.
    if ( mContextP )
    {
        return mContextP->setTile( mContextP->createNewTile( TILETYPE_DRY ) );
    }
    return false;
}

// Ueberflute ein Feld.
bool FloodedTile::flood()
{
    // Das Feld geht unter.
    if ( mContextP )
    {
        return mContextP->setTile( mContextP->createNewTile( TILETYPE_LOST ) );
    }
    return false;
}

// Prueft, ob das Feld noch trocken ist.
bool FloodedTile::isDry() const
{
    return false;
}

// Prueft, ob das Feld ueberflutet wurde.
bool FloodedTile::isFlooded() const
{
    return true;
}

// Prueft, ob das Feld schon untergegangen ist.
bool FloodedTile::isLost() const
{
    return false;
}

// Gibt Zeichen zur Ausgabe des Feldes zurueck.
char FloodedTile::print() const
{
    return 'o';
}
