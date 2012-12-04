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

#ifndef GAMEWINDOW_HH
#define GAMEWINDOW_HH

#include <QMainWindow>

// Vorwaertsdeklarationen.
class CommandWindow;
class GameArea;
class GameData;

/// Spielfenster.
/**
 * Dies ist eine einfache GUI, die das Spiel und den Fortgang
 * anzeigt. Nach dem Start können gespeicherte Datengerladen und die
 * Spielaktionen angezeigt werden.
 */
class GameWindow : public QMainWindow
{
    Q_OBJECT

  public:
    /// Konstruktor.
    GameWindow();

    /// Destruktor.
    virtual ~GameWindow();

    /// Initialisiert alle Fenster und Menus.
    /**
     * @param dataP Zeiger auf die Spieldaten
     * @return true, wenn alles gut verlief. Erst danach darf man
     * show() rufen.
     */
    bool init( GameData * dataP );

  private slots:
    /// Datei oeffen und darstellen.
    void slot_openFile();

  private:
    /// Spielbrett mit Feldern und Spieler.
    GameArea* mGameAreaP;

    /// Fenster zur Kommando-Verarbeitung.
    CommandWindow* mCommandWindow;
};

#endif // GAMEWINDOW_HH
