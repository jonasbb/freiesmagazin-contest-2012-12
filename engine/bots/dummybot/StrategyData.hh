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

#ifndef STRATEGYDATA_HH
#define STRATEGYDATA_HH

#include "Position.hh"

/// Daten fuer eine konkrete Strategie
/**
 * Die Klasse haelt alle Daten, die der Strategie wichtig sind
 * (Datenkapselung). Der Einfachheit halber koennen die Attribute
 * direkt von der Strategie verwendet werden.
 * Fuer eine eigene Strategie ist dies die richtige Stelle, um neue
 * Daten hinzufuegen.
 */
class StrategyData
{
  public:
    /// Konstruktor.
    StrategyData();
  
    /// Aktuelle Runde.
    unsigned int numRound;
  
    /// Position des Bots.
    Position position;

    /// Zuletzt ueberflutetes Feld.
    Position floodedField;

    /// Flutzaehler.
    unsigned int floodCounter;
};

#endif // STRATEGYDATA_HH
