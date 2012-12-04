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

#ifndef GAME_HH
#define GAME_HH

#include "FloodCardDeck.hh"
#include "Gameboard.hh"
#include "IGame.hh"
#include "Player.hh"
#include "PositionCardDeck.hh"
#include "PositionCardPointerVector.hh"

#include <string>
#include <vector>

/// Spieldaten eines Spiels.
class Game : public IGame
{
  public:
    /// Konstruktor.
    Game();

    /// Destruktor.
    virtual ~Game();

    /// Initialisiert das Spiel.
    /**
     * Dies laedt ein Spielbrett und initialisiert alle Daten,
     * sodass das Spiel stattfinden kann.
     * @param filename Name des zu ladenden Spielbretts
     * @return true, wenn alles initialisiert werden konnte.
     */
    bool init( const std::string& filename );

    /// Gibt zurueck, ob der Spieler verloren/untergegangen ist.
    virtual bool hasPlayerLost() const;

    /// Gibt aktuelle Spielerposition zurueck.
    virtual const Position& getPlayerPos() const;

    /// Holt die Informationen zum Spielbrett.
    /**
     * @param size Groesse des Spielbretts.
     * @param stringVector Die einzelnen Zeilen des
     * Spielbretts.
     * @return true, wenn das Spielbrett valide ist
     */
    virtual bool getGameboardInfo( Position& size,
                           std::vector<std::string>& stringVector ) const;

    /// Ziehe eine bestimmte Anzahl von Positionskarten und ueberflute zugehoerige Felder.
    /**
     * @param floodedPositions Liste der ueberfluteten Felder
     * @return true, wenn genuegend Karten gezogen werden konnten
     */
    virtual bool drawPositionCardsAndFloodTiles( std::vector<Position>& floodedPositions );

    /// Ziehe neue Flutkarten.
    /**
     * @param numNewFloodCards Anzahl neu gezogener Flutkarten.
     * @return true, wenn alles okay ist
     */
    virtual bool drawFloodCards( unsigned int& numNewFloodCards );

    /// Bewegt den Spieler ein Feld nach rechts.
    virtual bool movePlayerEast();

    /// Bewegt den Spieler ein Feld nach oben.
    virtual bool movePlayerNorth();

    /// Bewegt den Spieler ein Feld nach unten.
    virtual bool movePlayerSouth();

    /// Bewegt den Spieler ein Feld nach links.
    virtual bool movePlayerWest();

    /// Lege das Feld, auf dem der Spieler steht, trocken.
    virtual bool drainTileCurrent();

    /// Lege das Feld rechts vom Spieler trocken.
    virtual bool drainTileEast();

    /// Lege das Feld unterhalb vom Spieler trocken.
    virtual bool drainTileNorth();

    /// Lege das Feld ueberhalb vom Spieler trocken.
    virtual bool drainTileSouth();

    /// Lege das Feld links vom Spieler trocken.
    virtual bool drainTileWest();
    
  private:
    /// Setzt eine sinnvolle Spielerposition abhaengig vom Spielbrett.
    /**
     * @return true, wenn ein Feld gefunden wurde
     */
    bool setPlayerStartPosition();

    /// Erstellt Positionskarten abhaengig vom Spielbrett.
    /**
     * @return true, wenn die Karten alle erstellt werden konnten
     */
    bool createPositionCards();

    /// Erstelle Flutkarten.
    /**
     * return true (immer)
     */
    bool createFloodCards();

  private:
    /// Spielbrett.
    Gameboard mGameBoard;

    /// Der aktive Spieler.
    Player mPlayer;

    /// Deck mit Positionskarten.
    /**
     * Die Positionskarten existieren fuer jedes Feld
     * des Spielbretts und werde gezogen, um einzelne Felder
     * zu ueberfluten.
     */
    PositionCardDeck mPosCards;

    /// Deck mit Flutkarten.
    /**
     * Jede gezogene Flutkarten erhoeht die Flut und damit
     * die Anzahl der zu ziehenden Positionskarten.
     */
    FloodCardDeck mFloodCards;

    /// Anzahl der zu ziehenden Positionskarten.
    unsigned int mNumPosCardsDrawn;
};

#endif // GAME_HH
