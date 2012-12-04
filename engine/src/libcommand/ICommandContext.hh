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

#ifndef ICOMMANDCONTEXT_HH
#define ICOMMANDCONTEXT_HH

/// Interface fuer Kommandoverarbeitung von Spieldaten.
class ICommandContext
{
  public:
    /// Destructor.
    virtual ~ICommandContext() { }

    /// Bewegt den Spieler ein Feld nach rechts.
    virtual bool movePlayerEast() = 0;

    /// Bewegt den Spieler ein Feld nach oben.
    virtual bool movePlayerNorth() = 0;

    /// Bewegt den Spieler ein Feld nach unten.
    virtual bool movePlayerSouth() = 0;

    /// Bewegt den Spieler ein Feld nach links.
    virtual bool movePlayerWest() = 0;

    /// Lege das Feld, auf dem der Spieler steht, trocken.
    virtual bool drainTileCurrent() = 0;

    /// Lege das Feld rechts vom Spieler trocken.
    virtual bool drainTileEast() = 0;

    /// Lege das Feld unterhalb vom Spieler trocken.
    virtual bool drainTileNorth() = 0;

    /// Lege das Feld ueberhalb vom Spieler trocken.
    virtual bool drainTileSouth() = 0;

    /// Lege das Feld links vom Spieler trocken.
    virtual bool drainTileWest() = 0;
};

#endif // ICOMMANDCONTEXT_HH
