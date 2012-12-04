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

#ifndef ITILECONTEXT_HH
#define ITILECONTEXT_HH

#include "ITile.hh"
#include "TileType.hh"

/// Interface fuer den Feld-Kontext.
/**
 * Der Feld-Kontext enthaelt ein einfaches Feld
 * und bietet Methoden an, dass die Felder sich
 * untereinander aendern koennen. Damit wird das
 * State-Pattern umgesetzt.
 * Daneben erbt der Kontext die Methoden des
 * Feldes.
 */
class ITileContext : public ITile
{
  public:
    /// Destruktor.
    virtual ~ITileContext() { }

    /// Setzt ein neues Feld.
    /**
     * @param tileP Das neu zu setzende Feld.
     */
    virtual bool setTile( ITile * tileP ) = 0;

    /// Liefert anhand des Typs ein neues Feld zurueck.
    /**
     * Der Rufer der Methode uebernimmt die Verantwortung ueber
     * das Feld und muss es auch enstprechend destruieren.
     * @param type Der Typ des zu erstellenden Feldes.
     * @return Ein neues Feld, passend zum Typ, oder 0, falls
     * der Typ unbekannt ist.
     */
    virtual ITile * createNewTile( const TileType type ) = 0;

    /// Liefert anhand des Typs ein neues Feld zurueck.
    /**
     * Der Rufer der Methode uebernimmt die Verantwortung ueber
     * das Feld und muss es auch enstprechend destruieren.
     * @param type Der Typ des zu erstellenden Feldes.
     * @return Ein neues Feld, passend zum Typ, oder 0, falls
     * der Typ unbekannt ist.
     */
    virtual ITile * createNewTile( const char type ) = 0;

};

#endif // ITILECONTEXT_HH
