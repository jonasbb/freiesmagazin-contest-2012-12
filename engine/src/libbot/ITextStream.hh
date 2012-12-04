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

#ifndef ITEXTSTREAM_HH
#define ITEXTSTREAM_HH

#include <string>

/// Klasse zum Verarbeiten von Text.
/**
 * Die ist das Interface, um Text von STDIN zu empfangen bzw
 * an STDOUT zu senden. Wir benutzen nicht direkt STDIN und STDOUT,
 * da z.B. in einer GUI-Applikation ein normales std::getline
 * blockieren wuerde.
 */
class ITextStream
{
  public:
    /// Destruktor.
    virtual ~ITextStream() { };
  
    /// Holt eine Zeile mit Text von STDIN ab.
    /**
     * @return true, wenn die empfangene Zeile nicht leer ist
     */
    virtual bool getline( std::string& text ) = 0;

    /// Sendet eine Zeile Text nach STDOUT.
    virtual void writeline( const std::string& text ) = 0;
};

#endif // ITEXTSTREAM_HH
