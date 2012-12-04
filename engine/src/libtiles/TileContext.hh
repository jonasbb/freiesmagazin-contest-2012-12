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

#ifndef TILECONTEXT_HH
#define TILECONTEXT_HH

#include "ITileContext.hh"
#include "TileType.hh"

// Vorwartsdeklarationen
class ITile;

/// Der Feld-Kontext.
/**
 * Der Feld-Kontext enthaelt ein einfaches Feld
 * und bietet Methoden an, dass die Felder sich
 * untereinander aendern koennen. Damit wird das
 * State-Pattern umgesetzt.
 * Daneben erbt der Kontext die Methoden des
 * Feldes.
 */
class TileContext : public ITileContext
{
  public:
    /// Konstruktor.
    TileContext();

    /// Destruktor.
    virtual ~TileContext();

    /// Setzt ein neues Feld.
    /**
     * @param tileP Das neu zu setzende Feld (darf nicht 0 sein)
     * @return true, wenn das neue Feld gesetzt werden konnte
     */
    virtual bool setTile( ITile * tileP );

    /// Liefert anhand des Typs ein neues Feld zurueck.
    /**
     * Der Rufer der Methode uebernimmt die Verantwortung ueber
     * das Feld und muss es auch enstprechend destruieren.
     * @param type Der Typ des zu erstellenden Feldes.
     * @return Ein neues Feld, passend zum Typ, oder 0, falls
     * der Typ unbekannt ist.
     */
    virtual ITile * createNewTile( const TileType type );

    /// Liefert anhand des Typs ein neues Feld zurueck.
    /**
     * Der Rufer der Methode uebernimmt die Verantwortung ueber
     * das Feld und muss es auch enstprechend destruieren.
     * @param type Der Typ des zu erstellenden Feldes.
     * @return Ein neues Feld, passend zum Typ, oder 0, falls
     * der Typ unbekannt ist.
     */
    virtual ITile * createNewTile( const char type );
    
    /// Lege ein Feld trocken.
    virtual bool drain();

    /// Ueberflute ein Feld.
    virtual bool flood();

    /// Prueft, ob das Feld noch trocken ist.
    virtual bool isDry() const;

    /// Prueft, ob das Feld ueberflutet wurde.
    virtual bool isFlooded() const;

    /// Prueft, ob das Feld schon untergegangen ist.
    virtual bool isLost() const;

    /// Gibt Zeichen zur Ausgabe des Feldes zurueck.
    virtual char print() const;

  private:
    /// Kopierkonstruktor.
    /**
     * Privat, da keine Kopie eines Feld-Zeigers erstellt werden
     * kann/soll.
     */
    TileContext( const TileContext& context );

    /// Zuweisungsoperator.
    /**
     * Privat, da keine Kopie eines Feld-Zeigers erstellt werden
     * kann/soll.
     */
    TileContext& operator=( const TileContext& context );

  private:
    /// Das aktuell gesetzte Feld.
    ITile * mTileP;

    /// Das zuletzt gesetzte Feld.
    /**
     * Dies ist notwendig, da das State-Pattern es erlaubt,
     * dass mit getTile() eine Methode gerufen wird, die wiederum
     * setTile() ruft und somit das aktuelle Feld ueberschreibt.
     * Wurde man das aktuelle Feld sofort destruieren, haette dies
     * merkwuerdige Auswirkungen.
     */
    ITile * mOldTileP;
};

#endif // TILECONTEXT_HH
