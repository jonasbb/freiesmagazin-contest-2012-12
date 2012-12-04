/**
    (C) Copyright 2011,2012 Dominik Wagenfuehr

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

#ifndef PLAYER_HH
#define PLAYER_HH

#include "Position.hh"

/// Spieler.
/**
 * Dies ist die Spielerklasse fuer die Spieleengine,
 * nicht die fuer den Bot. Hier wird nur die ueberlebte
 * Runde gespeichert und die Position des Spielers
 * auf dem Spielbrett.
 */
class Player
{
  public:
    /// Konstruktor.
    /**
     * Erstellt einen neuen Spieler.
     */
    Player();

    /// Setzt eine neue Position des Spielers.
    /**
     * Es gibt keine Methode, um den Spieler zu bewegen,
     * da nicht geprueft werden kann, ob eine Bewegung
     * legal ist. Dies kann nur in Verbindung mit dem
     * Spielbrett geprueft werden.
     * @param pos Neue Position.
     */
    void setPosition( const Position& pos );

    /// Aktuelle Position des Spielers.
    const Position& getPosition() const;

  private:
    /// Aktuelle Position des Spielers.
    Position mPosition;
};

// INLINE ///////////////////////////////////////////////////////////

// Setzt eine neue Position des Spielers.
inline
void Player::setPosition( const Position& pos )
{
    mPosition = pos;
}

// Aktuelle Position des Spielers.
inline
const Position& Player::getPosition() const
{
    return mPosition;
}

#endif // PLAYER_HH
