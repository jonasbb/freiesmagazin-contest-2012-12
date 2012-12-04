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

#ifndef FLOODCARD_HH
#define FLOODCARD_HH

#include "IFloodCard.hh"

/// Flutkarte, die Flut steigen laesst.
class FloodCard : public IFloodCard
{
  public:
    /// Abfrage, ob Flut steigt.
    /**
     * @return true, wenn die Karte die Flut steigen laesst
     */
    virtual bool flood() const;

    /// Gibt den Typ auf stdlog aus.
    virtual std::string print() const;
};

#endif // FLOODCARD_HH
