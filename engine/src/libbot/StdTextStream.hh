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

#ifndef STDTEXTSTREAM_HH
#define STDTEXTSTREAM_HH

#include "ITextStream.hh"

#include <string>

/// Klasse zum Verarbeiten von Text.
/**
 * Die Klasse empfaengt Text von STDIN und sendet an STDOUT
 * mittels der normalen C++-Methoden aus std (blockierendes Lesen!).
 */
class StdTextStream : public ITextStream
{
  public:
    /// Destruktor.
    virtual ~StdTextStream();
  
    /// Holt eine Zeile mit Text von STDIN ab.
    /**
     * Achtung, Der Aufruf ist blockierend, d.h. die Methode
     * kehrt erst zurueck, wenn es wirklich etwas zu lesen gab.
     * @return true, wenn die empfangene Zeile nicht leer ist
     */
    virtual bool getline( std::string& text );

    /// Sendet eine Zeile nach STDOUT.
    virtual void writeline( const std::string& text );
};

#endif // STDTEXTSTREAM_HH
