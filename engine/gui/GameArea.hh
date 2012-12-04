/**
    (C) Copyright 2010,2012 Dominik Wagenfuehr

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

#ifndef GAMEAREA_HH
#define GAMEAREA_HH

#include <QBrush>
#include <QFont>
#include <QPainterPath>
#include <QPen>
#include <QPointF>
#include <QRectF>
#include <QSizeF>
#include <QWidget>

// Vorwartsdeklaration
class GameData;
class Position;
class QPainter;
class QPaintEvent;

/// Klasse, um Spielbrett und Spieler darzustellen.
class GameArea : public QWidget
{
Q_OBJECT

public:
    /// Konstruktor.
    GameArea( QWidget* parent = 0 );

    /// Destruktor.
    virtual ~GameArea();

    /// Initialisiert das Spielfeld.
    /**
     * @param dataP Zeiger auf die Spieldaten
     * @return true, wenn alles gut verlief. 
     */
    bool init( const GameData* dataP );
    
protected:
    /// Das Event zeichnet alle Daten neu.
    void paintEvent(QPaintEvent *event);

private:
    /// Zeichnet Spielbrett.
    void paintGameboard( QPainter& painter );

    /// Zeichnet ein einzelnes Feld des Spielbretts.
    void paintField( QPainter& painter, const Position& pos );

    /// Zeichnet den Spieler.
    void paintPlayer( QPainter& painter, const bool updatePos = false );

    /// Berechne Anzeigegroesse fuer das Spielbrett.
    /**
     * Abhaengig von der Groesse des Spielbretts und der Groesse
     * des Fensters muss die Anzeige so skaliert werden, dass sie
     * komplett in das Fenster passt.
     * Die Methode berechnet die Groesse eines Feldes und
     * den Skalierungsfaktor fuer alle Objekte.
     * @return true, wenn der Wert berechnet werden konnte.
     */
    bool calculateSquareSizeAndFactorFromGameboard();
    
private:

    /// Zeiger auf die Daten, die die GUI darstellen soll.
    const GameData* mDataP;

    /// Die Spielfigur.
    QPainterPath mPlayer;

    /// Groesse eines Spielfeldes.
    /**
     * Jedesmal wenn ein PaintEvent kommt, wird die Groesse neu
     * berechnet. Sie gibt an, wie groß ein einzelnes Spielfeld
     * sein soll.
     */
    QSizeF mSquareSize;

    /// Skalierungsfaktor.
    /**
     * Faktor, um ein Standardfeld mit 10x10 Pixel
     * auf die aktuell Spielfeldgroesse zu skalieren.
     */
    QPointF mSquareFactor;

    // Allgemeine Daten
    QPen mGeneralNoPen;
    QPen mGeneralTextPen;
    QPen mGeneralDarkPen;
    QBrush mGeneralNoBrush;
    QBrush mGeneralSolidBrush;
    QRectF mGeneralRect;
    QFont mGeneralFont;
    QRectF mAreaRect;
};

#endif // GAMEAREA_HH

