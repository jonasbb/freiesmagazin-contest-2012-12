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

#ifndef ISTRATEGY_HH
#define ISTRATEGY_HH

#include "IMessageOperator.hh"

#include <string>
#include <vector>

/// Interface fuer eine Strategie.
/**
 * Die konkrete Strategie muss sowohl die Kommandos berechnen,
 * als auch alle konkreten Nachrichten als Operator verarbeiten.
 * Dies realisiert das Strategy-Pattern.
 */
class IStrategy : public IMessageOperator
{
  public:
    /// Destruktor.
    virtual ~IStrategy() { };

    /// Fragt ab, ob Kommandos zur Verfuegung stehen.
    /**
     * Die Methode wird vom Bot nach dem Empfang jeder (!)
     * Nachricht gerufen. In der Regel stoesst die Start-Nachricht
     * die Berechnung an. Stehen Kommandos zur Verfuegung, muessen
     * diese gleich in die cmdList eingetragen werden.
     * @param[out] cmdList Liste mit exakt drei Kommandos, die
     * der Bot ausfuehren soll.
     * @return false, falls keine Kommandos abgeholt werden konnten
     */
    virtual bool isCommandsAvailable( std::vector<std::string>& cmdList ) = 0;

    /// Gibt zurueck, ob das Spiel zu Ende sein soll.
    /**
     * Die Methode wird vom Bot nach dem Empfang jeder (!)
     * Nachricht gerufen. In der Regel wird true geliefert, nachdem
     * die Ende-Nachricht empfangen wurde. Ggf. aber auch, wenn es
     * zu einem internen Fehler kam und der Bot die Abarbeitung
     * abbrechen soll.
     * @return true, wenn der Bot stoppen soll
     */
    virtual bool isEnd() const = 0;
};

#endif // ISTRATEGY_HH
