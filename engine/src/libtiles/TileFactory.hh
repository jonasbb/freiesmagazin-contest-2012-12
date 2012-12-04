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

#ifndef TILEFACTORY_HH
#define TILEFACTORY_HH

#include "TileType.hh"

// Vorwaertsdeklarationen
class ITile;
class ITileContext;

/// Fabrik zur Erstellung von Felder.
/**
 * Die Fabrik erstellt je nach uebergebenem Typ eine bestimmte
 * Art von Feld.
 */
class TileFactory
{
  public:
    /// Erstellt ein neues Feld.
    /**
     * @param type Der Typ des zu erstellenden Feldes.
     * @param contextP Der Kontext, in dem das erzeugte Feld
     * existieren soll.
     * @return Das neu erstellte Feld, oder 0, falls der Typ
     * unbekannt ist.
     */
    static ITile * create( const TileType type, ITileContext * contextP );
    
    /// Erstellt ein neues Feld.
    /**
     * @param type Der Typ des zu erstellenden Feldes als Zeichen.
     * @param contextP Der Kontext, in dem das erzeugte Feld
     * existieren soll.
     * @return Das neu erstellte Feld, oder 0, falls der Typ
     * unbekannt ist.
     */
    static ITile * create( const char type, ITileContext * contextP );    
};

#endif // TILEFACTORY_HH
