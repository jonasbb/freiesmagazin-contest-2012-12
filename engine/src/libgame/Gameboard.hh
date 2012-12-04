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

#ifndef GAMEBOARD_HH
#define GAMEBOARD_HH

#include "ITileContext.hh"
#include "Position.hh"

#include <string>
#include <vector>

/// Spielbrett mit Breite und Hoehe.
/**
 * Die linke obere Ecke liegt bei (1,1).
 */
class Gameboard
{
  public:
    /// Standard-Konstruktor.
    /**
     * Erstellt einen leeres/ungueltiges Spielfeld.
     */
    Gameboard();

    /// Destruktor.
    ~Gameboard();

    /// Laedt ein Spielbrett aus einer Datei.
    /**
     * Diese Methode muss in der Regel immer vor einer Benutzung
     * des Spielbretts gerufen werden, da nur so ein gueltiges
     * Spielbrett zustande kommen kann.
     * @param filename Dateiname der einzulesenden Datei
     * @return true, wenn die Datei korrekt eingelesen werden konnte
     */
    bool load( const std::string& filename );

    /// Erzeugt ein Spielbrett aus einer Stringliste.
    /**
     * @param size Groesse des Spielbretts (muss mit den Zeilen
     * uebereinstimmen).
     * @param lines Zeilen des Spielfelds
     * @return true, wenn das Spielbrett korrekt erstellt werden
     * konnte.
     */
    bool create( const Position& size,
                 const std::vector<std::string>& lines );
    
    /// Gibt die Groesse des Spielbretts zurueck.
    const Position& getSize() const;

    /// Lege ein Feld trocken.
    bool drain( const Position& pos );

    /// Ueberflute ein Feld.
    bool flood( const Position& pos );

    /// Prueft, ob das Feld noch trocken ist.
    bool isDry( const Position& pos ) const;

    /// Prueft, ob das Feld ueberflutet wurde.
    bool isFlooded( const Position& pos ) const;

    /// Prueft, ob das Feld schon untergegangen ist.
    bool isLost( const Position& pos ) const;

    /// Gibt das Spielbrett in Stringliste aus.
    void print( std::vector<std::string>& stringVector ) const;

    /// Gibt das Spielbrett auf stdlog aus.
    void print() const;

    /// Prueft, ob die Position fuer das Spielbrett valide ist.
    /**
     * Valide bedeutet, dass die Position innerhalb der
     * Spielbrettgrenzen liegt.
     * @param pos Zu pruefende Position
     * @param noError Wenn false, wird bei fehlerhafter Position ein
     * Fehlermeldung auf ausgegeben. Wenn true, wird diese Meldung
     * unterdrueckt. (Standard: false).
     * @return true, wenn die Position valide fuer das Spielbrett ist.
     */
    bool isValidPos( const Position& pos, const bool noError = false ) const;

  private:
    /// Liefert Position in interner Datenstruktur.
    /**
     * Die Position muss valide sein.
     */
    unsigned int getIntPos( const Position& pos ) const;

    /// Liefert Position in interner Datenstruktur.
    /**
     * Die Position x/y muss valide sein.
     */
    unsigned int getIntPos( const unsigned int x,
                            const unsigned int y ) const;

    /// Setzt neue Spielbrettgroesse und allokiert Speicher dafuer.
    /**
     * @param newSize Die neue Spielbrettgroesse.
     * @return TRUE, wenn die Position valide ist und der Speicher
     * allokiert werden konnte.
     */
    bool setSize( const Position& newSize );

    /// Extrahiert eine zweidimensionale Groesse aus der Zeile.
    /**
     * Die zwei Integer-Werte in der Zeile muessen durch ein
     * Leerzeichen getrennt sein.
     * @param size Die Groesse/Position.
     * @param line Die Zeile mit den zwei Integer-Werten.
     * @return TRUE, wenn die Position extrahiert werden konnte
     */
    bool extractSize( Position& size, const std::string& line ) const;

    /// Extrahiere Felder aus einer Zeiler.
    /**
     * Die Zeile muss dabei exakt so lang sein wie die Breite des
     * Spielbretts.
     * @param lineCounter Aktuelle Zeile, muss groesser gleich 1 sein.
     * @param line Zeile, wo jedes Zeichen fuer ein Feld steht.
     * @return TRUE, wenn die Felder korrekt extrahiert wurden
     */
    bool extractAndSetTiles( const unsigned int lineCounter,
                             const std::string& line );

    /// Kopierkonstruktor.
    /**
     * Das Spielbrett soll nicht kopiert werden, daher private.
     */
    Gameboard( const Gameboard& board );

    /// Zuweisungsoperator.
    /**
     * Das Spielbrett soll nicht kopiert werden, daher private.
     */
     Gameboard& operator=( const Gameboard& board );

  private:
  
    /// Vektor mit den einzelnen Feldern.
    /**
     * Die Felder werden als Vektor gespeichert, welcher
     * dann die zweidimensionale Struktur umsetzt.
     */
    std::vector<ITileContext*> mTiles;

    /// Breite und Hoehe des Spielbretts.
    Position mSize;
};

// INLINE ///////////////////////////////////////////////////////////

// Gibt die Groesse des Spielbretts zurueck.
inline
const Position& Gameboard::getSize() const
{
    return mSize;
}

#endif // GAMEBOARD_HH
