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

#ifndef BASETILE_HH
#define BASETILE_HH

#include "ITile.hh"

// Vorwaertsdeklarationen
class ITileContext;

/// Basisklasse fuer ein Feld.
/**
 * Die Basisklasse speichert den Kontext, in dem das
 * Feld existiert. Auf die Art kann das State-Pattern
 * umgesetzt werden.
 * Die Basisklasse waere normalerweise nicht notwendig,
 * so muss der Kontext-Zeiger aber nicht in jedem
 * konkreten Feld gespeichert werden.
 */
class BaseTile : public ITile
{
  public:
    /// Konstruktor.
    /**
     * @param contextP Der Kontext, in dem das Feld existiert
     */
    BaseTile( ITileContext * contextP );

    /// Destruktor.
    virtual ~BaseTile();

    // Kopierkonstruktor und Assignment-Operator muessen
    // nicht implementiert werden, da der Kontext direkt
    // kopiert werden kann ohne negative Auswirkungen.

  protected:
    /// Status des Feldes.
    ITileContext * mContextP;
};

#endif // BASETILE_HH
