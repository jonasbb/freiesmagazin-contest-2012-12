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

#ifndef COMMANDINTERPRETER_HH
#define COMMANDINTERPRETER_HH

#include <string>

// Vorwaertsdeklarationen.
class ICommand;

/// Interpretation von Kommandos.
/**
 * Die Klasse interpretiert einen String und kreiert daraus ein
 * Kommando.
 * Dies ist das Simple-Factory-Pattern.
 */
class CommandInterpreter
{
  public:
    /// Interpretation von Kommandos.
    /**
     * @param cmdString Zu interpretierender String.
     * HMI-Kommando zu interpretieren (Standard: false).
     * @return Erstelltes Kommando oder Nullzeiger, wenn der
     * String nicht interpretiert werden konnte.
     */
    static ICommand* interpret( const std::string& cmdString );

  private:
    /// Interpretation einer Bewegung.
    /**
     * @param direction Richtung, in die man sich bewegt.
     * @return Erstelltes Kommando oder Nullzeiger, wenn der
     * String nicht interpretiert werden konnte.
     */
    static ICommand* interpretGo( const std::string& direction );

    /// Interpretation einer Trockenlege-Aktion.
    /**
     * @param direction Richtung, wo man trockenlegen will.
     * @return Erstelltes Kommando oder Nullzeiger, wenn der
     * String nicht interpretiert werden konnte.
     */
    static ICommand* interpretDry( const std::string& direction );

};

#endif // COMMANDINTERPRETER_HH
