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

#include "TileFactory.hh"
#include "DryTile.hh"
#include "FloodedTile.hh"
#include "LostTile.hh"

#include <iostream>
#include <sstream>

// Erstellt ein neues Feld.
ITile * TileFactory::create( const TileType type, ITileContext * contextP )
{
    ITile * newTileP = 0;

    switch ( type )
    {
        case TILETYPE_DRY:
            newTileP = new DryTile( contextP );
            break;
        case TILETYPE_FLOODED:
            newTileP = new FloodedTile( contextP );
            break;
        case TILETYPE_LOST:
            newTileP = new LostTile( contextP );
            break;
        default:
            std::ostringstream out;
            out << "(EE) TileFactory::create "
                << " Unknown field type '"
                << type
                << "'."
                << std::endl;
            std::cerr << out.str();
            break;
    }

    if ( 0 == newTileP )
    {
        std::ostringstream out;
        out << "(EE) TileFactory::create "
            << " Field is 0 for type '"
            << type
            << "'."
            << std::endl;
        std::cerr << out.str();
    }

    return newTileP;
}

// Erstellt ein neues Feld.
ITile * TileFactory::create( const char type, ITileContext * contextP )
{
    ITile * newTileP = 0;
    
    switch ( type )
    {
        case '#':
            newTileP = create( TILETYPE_DRY, contextP );
            break;
        case 'o':
            newTileP = create( TILETYPE_FLOODED, contextP );
            break;
        case '.':
            newTileP = create( TILETYPE_LOST, contextP );
            break;
        default:
            std::ostringstream out;
            out << "(EE) TileFactory::create "
                << " Unknown field type '"
                << type
                << "'."
                << std::endl;
            std::cerr << out.str();
            break;
    }

    if ( 0 == newTileP )
    {
        std::ostringstream out;
        out << "(EE) TileFactory::create "
            << " Field is 0 for type '"
            << type
            << "'."
            << std::endl;
        std::cerr << out.str();
    }

    return newTileP;    
}
