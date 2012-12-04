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

#ifndef GAMEDATA_HH
#define GAMEDATA_HH

#include "Gameboard.hh"
#include "Position.hh"

/// Spieldaten fuer die Anzeige.
/**
 * Die Klasse haelt alle Daten, die fuer die GUI wichtig sind
 * (Datenkapselung). Der Einfachheit halber koennen die Attribute
 * direkt verwendet werden.
 */
class GameData
{
  public:
    /// Konstruktor.
    GameData();

    /// Aktuelle Runde.
    unsigned int numRound;
  
    /// Position des Spielers.
    Position position;

    /// Spielbrett.
    Gameboard gameboard;

    /// Zuletzt ueberflutetes Feld.
    Position floodedField;

    /// Flutzaehler.
    unsigned int floodCounter;

    /// Flag, dass das Spiel zu Ende ist.
    bool isFinished;
};

#endif // GAMEDATA_HH
