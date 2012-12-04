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

#include "PositionCard.hh"

#include <iostream>
#include <sstream>

// Konstruktor.
PositionCard::PositionCard( const Position& pos )
  : mPos(pos)
{
    if ( !mPos.isValid() )
    {
        std::ostringstream out;
        out << "(EE) PositionCard::PositionCard "
            << std::hex << this << std::dec
            << " Given position "
            << mPos
            << " is not valid."
            << std::endl;
        std::cerr << out.str();
    }
}

// Gibt die Position auf stdlog aus.
std::string PositionCard::print() const
{
    std::ostringstream out;
    out << this << " "
        << mPos;
    return out.str();
}
