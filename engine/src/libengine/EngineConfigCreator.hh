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

#ifndef ENGINECONFIGCREATOR_HH
#define ENGINECONFIGCREATOR_HH

// Vorwaertsdeklaration.
class EngineConfig;

/// Erstellt die Konfiguration fuer die Engine.
class EngineConfigCreator
{
  public:
    /// Erstellt die Konfiguration fuer die Engine.
    /**
     * Anhand der Uebergabeparameter wird die Enginekonfiguration
     * ausgelesen. Alle verarbeiteten Werte werden dann aus der
     * Parameterliste entfernt.
     * @param[out] config - Enginekonfiguration, die gesetzt wird.
     * Wenn es keine spezielle Konfiguration gibt, bleiben die alten
     * Werte unveraendert.
     * @param[inout] numParameters - Anzahl der Uebergabeparameter
     * @param[inout] parameters - Liste mit allen Uebergabeparameters
     * @return true, wenn die Konfiguration komplett gesetzt werden
     * konnte, oder false, wenn unbekannte Optionen gesetzt wurden
     */
    static bool createConfig( EngineConfig& config,
                              int& numParameters,
                              char* parameters[] );
};

#endif // ENGINECONFIGCREATOR_HH
