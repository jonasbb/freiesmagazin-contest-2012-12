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

#ifndef POSITION_HH
#define POSITION_HH

#include <ostream>

/// Position bestehend aus zwei uint-Werten.
/**
 * Wert 0 bedeutet nicht intialisiert.
 */
class Position
{
  public:
    /// Standard-Konstruktor.
    /**
     * Setzt eine uninitialisierte Position (0,0).
     */
    Position();

    /// Konstruktor.
    /**
     * Ist ein Wert 0, ist die Position uninitialisiert.
     * @param x x-Position.
     * @param y y-Position.
     * Erstellt einen neue Position.
     */
    Position( const unsigned int x, const unsigned int y );

    /// Setzt eine neue Position.
    /**
     * Ist ein Wert 0, ist die Position uninitialisiert.
     * @param x x-Position.
     * @param y y-Position.
     */
    void setPosition( const unsigned int x, const unsigned int y );

    /// Gibt X-Position zurueck.
    unsigned int x() const;

    /// Gibt Y-Position zurueck.
    unsigned int y() const;

    /// Prueft, ob die Position initialisiert ist.
    /**
     * @return true, falls die Position != 0 ist.
     */
    bool isValid() const;

    /// Prueft, ob die Position kleiner gleich ist.
    /**
     * Kleiner gleich bedeutet, dass sowohl die
     * aktuelle x-Position als auch die y-Position
     * kleiner sein muss als die des uebergebene Wertes.
     * @param pos Zu vergleichende Position.
     * @return true, falls die aktuelle Position kleiner
     * gleich der uebergebenen ist.
     */
    bool operator<=( const Position& pos ) const;
    
  private:
    /// X-Position.
    unsigned int mX;

    /// Y-Position.
    unsigned int mY;
};

/// Methode zur Ausgabe der Position.
/**
 * @param stream Stream, indem geschrieben wird.
 * @param pos Auszugebende Position.
 * @return Ausgabestream.
 */
std::ostream& operator<<( std::ostream& stream, const Position& pos);

// INLINE ///////////////////////////////////////////////////////////

// Setzt eine neue Position.
inline
void Position::setPosition( const unsigned int x, const unsigned int y )
{
    mX = x;
    mY = y;
}

// Gibt X-Position zurueck.
inline
unsigned int Position::x() const
{
    return mX;
}

// Gibt Y-Position zurueck.
inline
unsigned int Position::y() const
{
    return mY;
}

// Prueft, ob die Position initialisiert ist.
inline
bool Position::isValid() const
{
    return ( ( mX > 0 ) && ( mY > 0 ) );
}

// Prueft, ob die Position kleiner gleich ist.
inline
bool Position::operator<=( const Position& pos ) const
{
    return ( ( mX <= pos.mX ) && ( mY <= pos.mY ) );
}

#endif // POSITION_HH
