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

#ifndef IGAME_HH
#define IGAME_HH

#include "ICommandContext.hh"
#include "PositionCardPointerVector.hh"

#include <string>
#include <vector>

// Vorwartsdeklarationen
class Position;

/// Interface fuer Spieldaten eines Spiels.
class IGame : public ICommandContext
{
  public:
    /// Destruktor.
    virtual ~IGame() { }

    /// Gibt zurueck, ob der Spieler verloren/untergegangen ist.
    virtual bool hasPlayerLost() const = 0;

    /// Gibt aktuelle Spielerposition zurueck.
    virtual const Position& getPlayerPos() const = 0;

    /// Holt die Informationen zum Spielbrett.
    /**
     * @param[out] size Groesse des Spielbretts.
     * @param[out] stringVector Die einzelnen Zeilen des
     * Spielbretts.
     * @return true, wenn das Spielbrett valide ist
     */
    virtual bool getGameboardInfo( Position& size,
                 std::vector<std::string>& stringVector ) const = 0;

    /// Ziehe eine bestimmte Anzahl von Positionskarten und ueberflute zugehoerige Felder.
    /**
     * @param floodedPositions Liste der ueberfluteten Felder
     * @return true, wenn genuegend Karten gezogen werden konnten
     */
    virtual bool drawPositionCardsAndFloodTiles( std::vector<Position>& floodedPositions ) = 0;

    /// Ziehe neue Flutkarten und fuehre diese ggf aus.
    /**
     * @param numNewFloodCards Anzahl gezogener, nicht leerer Flutkarten.
     * @return true, wenn alles okay ist
     */
    virtual bool drawFloodCards( unsigned int& numNewFloodCards ) = 0;
    
};

#endif // IGAME_HH
