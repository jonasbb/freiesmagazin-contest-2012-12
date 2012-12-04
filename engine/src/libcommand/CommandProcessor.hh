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

#ifndef COMMANDPROCESSOR_HH
#define COMMANDPROCESSOR_HH

#include "ICommand.hh"

#include <string>
#include <vector>

// Vorwartsdeklarationen.
class ICommandContext;

/// Kommandoverarbeitung.
/**
 * Die Klasse empfaengt die Kommandos des Spielers und wendet
 * sie auch auf das Spiel an.
 */
class CommandProcessor
{
  public:
    /// Konstruktor.
    CommandProcessor();

    /// Destructor.
    ~CommandProcessor();

    /// Empfange Stringliste mit Befehlen.
    /**
     * Die Kommandos werden einzeln interpretiert, d.h. aus den
     * Strings werden echte Befehlsobjekte gemacht, die dann nur
     * ausgefuehrt werden koennen.
     * @param strCommands Liste der Kommandos als String.
     * @return true, wenn alle Kommandos interpretiert werden konnten.
     */
    bool interpretCommands( const std::vector<std::string>& strCommands );
    
    /// Wende Kommandos auf das Spiel an. 
    /**
     * @param context Spieldaten, die veraendert werden sollen.
     * @return true, wenn alle Kommandos angewendet werden konnten,
     * ohne dass es zu einem Fehler kam.
     */
    bool processCommands( ICommandContext& context ) const;

    /// Wende ein Kommando auf das Spiel an. 
    /**
     * @param index Index des Kommandos, das verarbeitet werden soll.
     * @param context Spieldaten, die veraendert werden sollen.
     * @return true, wenn alle Kommandos angewendet werden konnten,
     * ohne dass es zu einem Fehler kam.
     */
    bool processSingleCommand( const unsigned int index, ICommandContext& context ) const;

  private:
    /// Loescht alle gespeichert Kommandos.
    void clearCommands();
    
  private:
    /// Flag, ob die zuvor interpretierten Kommandos valide sind.
    bool mValid;

    /// Liste der Kommandos, die ausgefuehrt werden sollen.
    std::vector<ICommand*> mCommands;

};

#endif // COMMANDPROCESSOR_HH
