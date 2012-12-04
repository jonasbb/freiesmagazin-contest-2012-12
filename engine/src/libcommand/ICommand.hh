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

#ifndef ICOMMAND_HH
#define ICOMMAND_HH

/// Vorwaertsdeklaration
class ICommandContext;

/// Interface fuer ein Kommando.
/**
 * Das Kommando veraendert die Spieldaten entsprechend der
 * jeweiligen Realisisierung.
 */
class ICommand
{
  public:
    /// Destructor.
    virtual ~ICommand() { }

    /// Veraendere die Spieldaten entsprechen der Realisierung.
    virtual bool operate( ICommandContext& context ) const = 0;
};

#endif // ICOMMAND_HH
