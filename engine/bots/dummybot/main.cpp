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

#include "Bot.hh"
#include "Strategy.hh"

#include <iostream>
#include <sstream>

int main( int argc, char* argv[] )
{
    int retValue = 0;

    // Der Bot ist immer der Gleiche.
    Bot bot;

    // Die Strategy muss dann ggf. angepasst werden.
    Strategy strategy;

    // Starte ein neues Spiel.
    if ( !bot.start( &strategy ) )
    {
        retValue = 1;
    }

    if ( 0 != retValue )
    {
        std::ostringstream out;
        out << "(EE) Bot main "
            << " There was an error somewhere!"
            << std::endl;
        std::cerr << out.str();
    }
    
    return retValue;
}
