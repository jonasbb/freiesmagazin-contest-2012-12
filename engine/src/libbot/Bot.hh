/**
    (C) Copyright 2011,2012 Dominik Wagenfuehr

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

#ifndef BOT_HH
#define BOT_HH

// Vorwaertsdeklaration
class IStrategy;

/// Der Bot.
/**
 * Der Bot wartet auf das Startsignal vom Server auf STDIN und
 * gibt sein Angebot auf STDOUT ab. Die Strategie wird von aussen
 * mit dem Start des Spiels vorgegeben.
 */
class Bot
{
public:
    /// Konstruktor.
    Bot();

    /// Destructor.
    ~Bot();

    /// Startet ein neues Spiel mit der jeweiligen Strategie.
    /**
     * Die Strategie bestimmt, wie der Bot sich verhaelt und
     * anbietet bzw. wann er Angebote annimmt/ablehnt.
     * Ohne Strategie kann der Bot nicht korrekt funktionieren.
     * Die Strategie sollte vor dem Start definiert sein.
     * Achtung: Der Bot ist nicht Eigentuemer der Strategie
     * und darf sie daher nicht loeschen!
     * Es wird solange iteriert, bis die Strategie sagt, das
     * Spiel ist zu Ende.
     * @param strategyP Die zu verwendende Strategie.
     * @return true, wenn der Ablauf korrekt beendet wurde
     */
    bool start( IStrategy* strategyP );

private:
    /// Die zu verwendende Strategie bei jedem Spiel.
    IStrategy* mStrategyP;
};

#endif // BOT_HH
