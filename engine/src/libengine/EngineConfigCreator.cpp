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

#include "EngineConfigCreator.hh"
#include "EngineConfig.hh"

#include <string>
#include <cstring>
#include <iostream>
#include <sstream>

// Erstellt die Konfiguration fuer die Engine.
bool EngineConfigCreator::createConfig( EngineConfig& config,
                                        int& numParameters,
                                        char* parameters[] )
{
    // Der erste Parameter ist der Dateiname, den ignorieren wir.
    int paramIndex = 1;

    bool retValue = true;

    while ( paramIndex < numParameters )
    {
        if ( strncmp( parameters[paramIndex], "--", 2 ) == 0 )
        {
            // Es handelt sich um eine Option.
            
            if ( strcmp( parameters[paramIndex], "--log" ) == 0 )
            {
                // Logging ist aktiv.
                config.setLog(true);
                
                // Der Parameter wurde verarbeitet, "verschiebe" die
                // hinteren Parameter nach vorne.
                for ( int kk = paramIndex; kk < numParameters-1; kk++ )
                {
                    parameters[kk] = parameters[kk+1];
                }
                numParameters--;
            }
            else
            {
                // Unbekannte Option. Hier aufhoeren!
                std::ostringstream out;
                out << "(EE) EngineConfigCreator::createConfig "
                    << " Unknown option '"
                    << parameters[paramIndex]
                    << "'."
                    << std::endl;
                std::cerr << out.str();
                retValue = false;
                break;
            }
        }
        else
        {
            // Es handelt sich nicht um eine Option, daher ignorieren
            // wir das.
            paramIndex++;
        }
    }

    return retValue;
}
