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

#ifndef COMMANDGOEAST_HH
#define COMMANDGOEAST_HH

#include "ICommand.hh"

/// Vorwaertsdeklaration
class ICommandContext;

/// Kommando, um den Spieler ein Feld nach rechts zu bewegen.
class CommandGoEast : public ICommand
{
  public:
    /// Destructor.
    virtual ~CommandGoEast();

    /// Veraendere die Spieldaten entsprechen der Realisierung.
    virtual bool operate( ICommandContext& context ) const;
};

#endif // COMMANDGOEAST_HH
