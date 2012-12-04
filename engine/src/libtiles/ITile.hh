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

#ifndef ITILE_HH
#define ITILE_HH

/// Interface fuer ein einzelnes Feld auf dem Spielbrett.
class ITile
{
  public:
    /// Destruktor.
    virtual ~ITile() { }

    /// Lege ein Feld trocken.
    virtual bool drain() = 0;

    /// Ueberflute ein Feld.
    virtual bool flood() = 0;

    /// Prueft, ob das Feld noch trocken ist.
    virtual bool isDry() const = 0;

    /// Prueft, ob das Feld ueberflutet wurde.
    virtual bool isFlooded() const = 0;

    /// Prueft, ob das Feld schon untergegangen ist.
    virtual bool isLost() const = 0;

    /// Gibt Zeichen zur Ausgabe des Feldes zurueck.
    virtual char print() const = 0;   
};

#endif // ITILE_HH
