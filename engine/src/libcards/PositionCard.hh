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

#ifndef POSITIONCARD_HH
#define POSITIONCARD_HH

#include "Position.hh"

#include <string>

/// Karte mit Positionswert.
/**
 * Zu jedem Feld des Spielbretts gibt es eine Karte mit
 * der entsprechenden Position, die spaeter dann nach
 * und nach gezogen werden und die jeweiligen Felder
 * ueberfluten.
 */
class PositionCard
{
  public:
    /// Konstruktor.
    /**
     * Die Position muss gueltig sein, d.h. eine Position
     * ungleich 0 haben.
     */
    PositionCard( const Position& pos );
   
    /// Gibt den Positionswert der Karte zurueck.
    const Position& getPos() const;

    /// Gibt die Position auf stdlog aus.
    std::string print() const;

  private:
    /// Positionswert der Karte.
    Position mPos;
};

// INLINE ///////////////////////////////////////////////////////////

// Gibt den Positionswert der Karte zurueck.
inline
const Position& PositionCard::getPos() const
{
    return mPos;
}

#endif // POSITIONCARD_HH
