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

#ifndef DRYTILE_HH
#define DRYTILE_HH

#include "BaseTile.hh"

// Vorwartsdeklaration.
class ITileContext;

/// Trockenes Feld.
class DryTile : public BaseTile
{
  public:
    /// Konstruktor.
    DryTile( ITileContext * contextP );

    /// Lege ein Feld trocken.
    virtual bool drain();

    /// Ueberflute ein Feld.
    virtual bool flood();

    /// Prueft, ob das Feld noch trocken ist.
    virtual bool isDry() const;

    /// Prueft, ob das Feld ueberflutet wurde.
    virtual bool isFlooded() const;

    /// Prueft, ob das Feld schon untergegangen ist.
    virtual bool isLost() const;

    /// Gibt Zeichen zur Ausgabe des Feldes zurueck.
    virtual char print() const; 
};

#endif // DRYTILE_HH
