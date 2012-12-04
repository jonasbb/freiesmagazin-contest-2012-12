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

#ifndef COMMANDWINDOW_HH
#define COMMANDWINDOW_HH

#include <QWidget>

// Vorwartsdeklaration
class CommandHandler;
class GameData;
class QCheckBox;
class QListWidget;
class QPushButton;

/// Darstellung und Verarbeitung der Bot-Befehle.
/**
 * Die Klasse kann eine Datei oeffnen und stellt deren Inhalt in
 * einem Fenster da. Es ist moeglich in der Datei zu iterieren bzw.
 * die Befehle darin abzuarbeiten.
 */
class CommandWindow : public QWidget
{
    Q_OBJECT

  public:
    /// Konstruktor.
    CommandWindow( QWidget* parent = 0 );

    /// Destruktor.
    virtual ~CommandWindow();

    /// Initialisiert das Kommando-Fenster.
    /**
     * @param dataP Zeiger auf die Spieldaten
     * @return true, wenn alles gut verlief. 
     */
    bool init( GameData* dataP );

    /// Datei oeffen und darstellen.
    /**
     * @param fileName Datei zum Oeffnen
     * @return true, wenn Datei geoeffnet werden konnte
     */
    bool openFile( const QString& fileName );

  signals:
    /// Signal, dass sich die Daten geaendert haben.
    void sig_dataChanged();

    /// Signal zum Oeffnen einer Datei im Hauptfenster.
    void sig_openFile();

  private slots:
    /// Starte die Kommandoverarbeitung von der aktuellen Zeile an.
    void slot_start();

    /// Stoppe Bearbeitung.
    void slot_stop();

    /// Setze Verarbeitung an Anfang.
    void slot_reset();

    /// Verarbeite alles bis zur ausgewaehlten Zeile (exklusive).
    void slot_gotoLine();

  private:
    /// Setzt den aktuellen Zeilenindex.
    void setIndex( const int index );
    
    /// Lasse das Spiel bis zu einer bestimmten Zeile (exklusive) laufen.
    void startUntilLine( const int index, const bool noUpdate );
    
  private:
    /// Zeiger auf den Kommandohandler.
    CommandHandler* mCommandHandlerP;

    /// Textfeld zur Anzeige der Datei mit den Kommandos.
    QListWidget* mCommandListP;

    /// Knopf zum automatisch Start und Ablauf.
    QPushButton *mStartButtonP;

    /// Knopf zum Anhalten des Ausfuehrung.
    QPushButton *mStopButtonP;

    /// Knopf zum Ruecksetzen auf den Beginn.
    QPushButton *mResetButtonP;

    /// Knopf zum Springen an eine bestimmte Stelle.
    QPushButton *mGotoButtonP;

    /// Checkbox zum Ein- und Ausschalten von Einzelschritt.
    QCheckBox *mSingleStepButtonP;

    /// Knopf zum Laden einer Datei.
    QPushButton *mOpenButtonP;

    /// Index in der Kommando-Liste, welcher Eintrag gerade aktiv ist.
    /**
     * Der Wert -1 bedeutet, dass keine Datei aktiv ist.
     */
    int mCommandIndex;

    /// Flag, dass ein Stop-Kommando im Ablauf ansteht.
    bool isStopCommand;
};

#endif // COMMANDWINDOW_HH

