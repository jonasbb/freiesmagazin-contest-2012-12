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

#include "TileContext.hh"
#include "TileFactory.hh"
#include "ITile.hh"

#include <iostream>
#include <sstream>

// Konstruktor.
TileContext::TileContext()
  : mTileP(0), mOldTileP(0)
{
}

// Destruktor.
TileContext::~TileContext()
{
    delete mTileP;
    delete mOldTileP;
}

// Setzt ein neues Feld.
bool TileContext::setTile( ITile * tileP )
{
    bool valid = false;
    
    if ( 0 == tileP )
    {
        std::ostringstream out;
        out << "(EE) TileContext::setTile "
            << std::hex << this << std::dec
            << " Field is 0."
            << std::endl;
        std::cerr << out.str();
        valid = false;
    }
    else
    {
        // Altes Feld loeschen, da es nicht mehr benoetigt wird,
        // und dafuer das aktuelle sichern.
        delete mOldTileP;
        mOldTileP = mTileP;

        // Neues Feld setzen.
        mTileP = tileP;
        valid = true;
    }

    return valid;
}

// Liefert anhand des Typs ein neues Feld zurueck.
ITile * TileContext::createNewTile( const TileType type )
{
    return TileFactory::create( type, this );
}

// Liefert anhand des Typs ein neues Feld zurueck.
ITile * TileContext::createNewTile( const char type )
{
    return TileFactory::create( type, this );
}
    
// Lege ein Feld trocken.
bool TileContext::drain()
{
    if ( 0 != mTileP )
    {
        return mTileP->drain();
    }
    return false;
}

// Ueberflute ein Feld.
bool TileContext::flood()
{
    if ( 0 != mTileP )
    {
        return mTileP->flood();
    }

    return false;
}

// Prueft, ob das Feld noch trocken ist.
bool TileContext::isDry() const
{
    if ( 0 != mTileP )
    {
        return mTileP->isDry();
    }
    return false;
}

// Prueft, ob das Feld ueberflutet wurde.
bool TileContext::isFlooded() const
{
    if ( 0 != mTileP )
    {
        return mTileP->isFlooded();
    }
    return false;
}

// Prueft, ob das Feld schon untergegangen ist.
bool TileContext::isLost() const
{
    if ( 0 != mTileP )
    {
        return mTileP->isLost();
    }
    return false;
}

// Gibt Zeichen zur Ausgabe des Feldes zurueck.
char TileContext::print() const
{
    if ( 0 != mTileP )
    {
        return mTileP->print();
    }
    return ' ';
}
