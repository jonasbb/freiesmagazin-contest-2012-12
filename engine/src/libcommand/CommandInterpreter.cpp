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

#include "CommandInterpreter.hh"

#include "CommandDryCurrent.hh"
#include "CommandDryEast.hh"
#include "CommandDryNorth.hh"
#include "CommandDrySouth.hh"
#include "CommandDryWest.hh"
#include "CommandGoCurrent.hh"
#include "CommandGoEast.hh"
#include "CommandGoNorth.hh"
#include "CommandGoSouth.hh"
#include "CommandGoWest.hh"

#include <iostream>
#include <sstream>

ICommand* CommandInterpreter::interpret( const std::string& cmdString )
{
    // Moegliche Befehle sind:
    // GO oder DRY zusammen mit einer Richtung
    // NORTH, SOUTH, WEST, EAST und CURRENT
    // Das heisst, es ist immer ein Leerzeichen als Separator.

    ICommand* commandP = 0;

    size_t pos = cmdString.find(' ');

    if ( ( std::string::npos != pos ) &&
         ( 0 != pos ) &&
         ( cmdString.length()-1 != pos ) )
    {
        const std::string firstCmd = cmdString.substr( 0, pos );
        const std::string secondCmd = cmdString.substr( pos+1 );

        if ( 0 == firstCmd.compare( "GO" ) )
        {
            commandP = interpretGo( secondCmd );
        }
        else if ( 0 == firstCmd.compare( "DRY" ) )
        {
            commandP = interpretDry( secondCmd );
        }
        else
        {
            std::ostringstream out;
            out << "(EE) CommandInterpreter::interpret "
                << " Unknown command '"
                << firstCmd
                << "' from line '"
                << cmdString
                << "'."
                << std::endl;
            std::cerr << out.str();
        }
    }
    else 
    {
        std::ostringstream out;
        out << "(EE) CommandInterpreter::interpret "
            << " Could not interpretet line '"
            << cmdString
            << "'."
            << std::endl;
        std::cerr << out.str();
    }

    return commandP;
}

// Interpretation einer Bewegung.
ICommand* CommandInterpreter::interpretGo( const std::string& direction )
{
    ICommand* commandP = 0;

    if ( 0 == direction.compare( "NORTH" ) )
    {
        commandP = new CommandGoNorth();
    }
    else if ( 0 == direction.compare( "SOUTH" ) )
    {
        commandP = new CommandGoSouth();
    }
    else if ( 0 == direction.compare( "EAST" ) )
    {
        commandP = new CommandGoEast();
    }
    else if ( 0 == direction.compare( "WEST" ) )
    {
        commandP = new CommandGoWest();
    }
    else if ( 0 == direction.compare( "CURRENT" ) )
    {
        commandP = new CommandGoCurrent();
    }
    else
    {
        std::ostringstream out;
        out << "(EE) CommandInterpreter::interpretGo "
            << " Unknown direction '"
            << direction
            << "'."
            << std::endl;
        std::cerr << out.str();
    }
    
    return commandP;
}

// Interpretation einer Trockenlege-Aktion.
ICommand* CommandInterpreter::interpretDry( const std::string& direction )
{
    ICommand* commandP = 0;

    if ( 0 == direction.compare( "NORTH" ) )
    {
        commandP = new CommandDryNorth();
    }
    else if ( 0 == direction.compare( "SOUTH" ) )
    {
        commandP = new CommandDrySouth();
    }
    else if ( 0 == direction.compare( "EAST" ) )
    {
        commandP = new CommandDryEast();
    }
    else if ( 0 == direction.compare( "WEST" ) )
    {
        commandP = new CommandDryWest();
    }
    else if ( 0 == direction.compare( "CURRENT" ) )
    {
        commandP = new CommandDryCurrent();
    }
    else
    {
        std::ostringstream out;
        out << "(EE) CommandInterpreter::interpretDry "
            << " Unknown direction '"
            << direction
            << "'."
            << std::endl;
        std::cerr << out.str();
    }
    
    return commandP;
}
