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

#include "SingleTextStream.hh"

// Konstruktor.
SingleTextStream::SingleTextStream()
{
}

// Destruktor.
SingleTextStream::~SingleTextStream()
{
}

// Liest die naechste Zeile Text ein.
bool SingleTextStream::getline( std::string& text )
{
    text = mText;
    mText.clear();
    return !mText.empty();
}

// Nicht verwenden!
void SingleTextStream::writeline( const std::string& /* text */ )
{
    // Soll nicht gerufen werden!
}

// Setzt eine Zeile Text, die dann gelesen werden kann.
void SingleTextStream::setline( const std::string& text )
{
    mText = text;
}
