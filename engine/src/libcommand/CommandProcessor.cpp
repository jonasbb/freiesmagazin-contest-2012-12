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

#include "CommandProcessor.hh"
#include "CommandInterpreter.hh"

#include <iostream>
#include <sstream>

// Konstruktor.
CommandProcessor::CommandProcessor()
: mValid(false)
{
    clearCommands();
}

// Destructor.
CommandProcessor::~CommandProcessor()
{
    clearCommands();
}

// Loescht alle gespeichert Kommandos.
void CommandProcessor::clearCommands()
{
    for ( size_t ii = 0; ii < mCommands.size(); ii++ )
    {
        delete mCommands[ii];
        mCommands[ii] = 0;
    }
    
    mCommands.resize(0);
    mValid = false;
}

// Empfange Stringliste mit Befehlen des Clients.
bool CommandProcessor::interpretCommands( const std::vector<std::string>& strCommands )
{
    bool retValue = false;

    // Loesche alte Befehle.
    clearCommands();

    if ( strCommands.size() == 3 )
    {
        mCommands.resize( strCommands.size() );

        retValue = true;

        for ( size_t ii = 0; ii < strCommands.size(); ii++ )
        {
            mCommands[ii] = CommandInterpreter::interpret( strCommands[ii] );

            if ( 0 == mCommands[ii] )
            {
                std::ostringstream out;
                out << "(EE) CommandProcessor::interpretCommands "
                    << std::hex << this << std::dec
                    << " Pointer to command is 0."
                    << std::endl;
                std::cerr << out.str();
                retValue = false;
                break;
            }
        }
    }
    else
    {
        std::ostringstream out;
        out << "(EE) CommandProcessor::interpretCommands "
            << std::hex << this << std::dec
            << " List should contain 3 elements but does contain "
            << strCommands.size()
            << "."
            << std::endl;
        std::cerr << out.str();
        retValue = false;
    }

    return retValue;    
}

// Wende Kommandos auf das Spiel an. 
bool CommandProcessor::processCommands( ICommandContext& context ) const
{
    bool retValue = false;
    
    if ( mCommands.size() == 3 )
    {
        retValue = true;

        for ( size_t ii = 0; ii < mCommands.size(); ii++ )
        {
            if ( mCommands[ii] )
            {
                // Wende das Kommando auf das Spiel an.
                mCommands[ii]->operate(context);
            }
            else
            {
                std::ostringstream out;
                out << "(EE) CommandProcessor::processCommands "
                    << std::hex << this << std::dec
                    << " Pointer to command is 0."
                    << std::endl;
                std::cerr << out.str();
                retValue = false;
                break;
            }
        }
    }
    else
    {
        std::ostringstream out;
        out << "(EE) CommandProcessor::processCommands "
            << std::hex << this << std::dec
            << " List should contain 3 elements but does contain "
            << mCommands.size()
            << "."
            << std::endl;
        std::cerr << out.str();
        retValue = false;
    }

    return retValue;
}

// Wende ein Kommando auf das Spiel an. 
bool CommandProcessor::processSingleCommand( const unsigned int index, ICommandContext& context ) const
{
    bool retValue = false;

    if ( index < mCommands.size() )
    {
        if ( mCommands[index] )
        {
            // Wende das Kommando auf das Spiel an.
            retValue = mCommands[index]->operate(context);
        }
        else
        {
            std::ostringstream out;
            out << "(EE) CommandProcessor::processSingleCommand "
                << std::hex << this << std::dec
                << " Pointer to command "
                << index
                << " is 0."
                << std::endl;
            std::cerr << out.str();
            retValue = false;
        }
    }
    else
    {
        std::ostringstream out;
        out << "(EE) CommandProcessor::processSingleCommand "
            << std::hex << this << std::dec
            << " Index " << index
            << " out of range for command list with size "
            << mCommands.size()
            << "."
            << std::endl;
        std::cerr << out.str();
        retValue = false;
    }

    return retValue;

}
