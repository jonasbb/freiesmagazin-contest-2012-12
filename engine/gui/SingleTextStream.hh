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

#ifndef SINGLETEXTSTREAM_HH
#define SINGLETEXTSTREAM_HH

#include "ITextStream.hh"

#include <string>

/// Dummy-Klasse zum Einlesen eines einzelnen Kommandos.
/**
 * Diese Klasse bedient nur das Interface ITextStream, sodass
 * ein MessageHandler den Strom entgegen nimmt und daraus etwas
 * lesen kann.
 * Die Idee ist, dass man in diese Datei schreibt, welche Zeile
 * man in der GUI verarbeiten will und dies wird dann abgearbeitet.
 * In der GUI hat man aber keinen Strom von Text, sondern immer
 * nur einzelnen Zeilen, die verarbeitet werden.
 */
class SingleTextStream : public ITextStream
{
  public:
    /// Konstruktor.
    SingleTextStream();

    /// Destruktor.
    virtual ~SingleTextStream();

    /// Liest die naechste Zeile Text ein.
    /**
     * Der Aufruf ist nicht blockierend. Nach der Ausgabe
     * wird der gespeicherte Text geleert.
     * @return true, wenn die empfangene Zeile nicht leer ist
     */
    virtual bool getline( std::string& text );

    /// Nicht verwenden!
    virtual void writeline( const std::string& text );

    /// Setzt eine Zeile Text, die dann gelesen werden kann.
    void setline( const std::string& text );

  private:
    /// Eine Zeile Text, die als "Strom" ausgegeben werden soll.
    std::string mText;
};

#endif // SINGLETEXTSTREAM_HH
