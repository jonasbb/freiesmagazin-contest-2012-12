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

#include "CommandWindow.hh"

#include "CommandHandler.hh"

#include <QCoreApplication>
#include <QFile>
#include <QListWidget>
#include <QMessageBox>
#include <QPushButton>
#include <QCheckBox>
#include <QGridLayout>
#include <QTextStream>

#include <iostream>
#include <sstream>

// Konstruktor.
CommandWindow::CommandWindow( QWidget* parent )
: QWidget(parent), mCommandHandlerP(0), mCommandListP(0),
  mStartButtonP(0), mStopButtonP(0), mResetButtonP(0),
  mGotoButtonP(0), mSingleStepButtonP(0), mOpenButtonP(0),
  mCommandIndex(-1), isStopCommand(false)
{
}

// Destruktor.
CommandWindow::~CommandWindow()
{
    delete mCommandHandlerP;
    mCommandHandlerP = 0;

    // Die anderen Elemente sind Eigentum der GUI und werden
    // automatisch vernichtet.
}

// Initialisiert das Kommando-Fenster.
bool CommandWindow::init( GameData* dataP )
{
    bool retValue = true;

#ifdef DEBUG
    {
        std::ostringstream out;
        out << "(DD) CommandWindow::init "
            << std::hex << this << std::dec
            << " Begin"
            << std::endl;
        std::clog << out.str();
    }
#endif /* DEBUG */

    mCommandHandlerP = new CommandHandler();
    if ( !mCommandHandlerP )
    {
        std::ostringstream out;
        out << "(EE) CommandWindow::init "
            << std::hex << this << std::dec
            << " CommandHandler is 0!"
            << std::endl;
        std::cerr << out.str();

        QMessageBox::critical( this, windowTitle(),
                               tr("CommandHandler is 0!"),
                               QMessageBox::Abort );
        return false;
    }

    if ( !mCommandHandlerP->init( dataP ) )
    {
        return false;
    }

    mCommandListP = new QListWidget();
    if ( !mCommandListP )
    {
        std::ostringstream out;
        out << "(EE) CommandWindow::init "
            << std::hex << this << std::dec
            << " QListWidget is 0!"
            << std::endl;
        std::cerr << out.str();

        QMessageBox::critical( this, windowTitle(),
                               tr("QListWidget is 0!"),
                               QMessageBox::Abort );
        return false;
    }

    // Anwahl einzelner Zeilen moeglich.
    mCommandListP->setSelectionBehavior( QAbstractItemView::SelectItems );
    mCommandListP->setSelectionMode( QAbstractItemView::SingleSelection );

#ifdef DEBUG
    {
        std::ostringstream out;
        out << "(DD) CommandWindow::init "
            << std::hex << this << std::dec
            << " Creation complete "
            << std::endl;
        std::clog << out.str();
    }
#endif /* DEBUG */

    mStartButtonP = new QPushButton(tr("St&art"));
    mStopButtonP = new QPushButton( tr("St&op"));
    mResetButtonP = new QPushButton(tr("&Reset"));
    mGotoButtonP = new QPushButton(tr("&Go to line"));
    mSingleStepButtonP = new QCheckBox(tr("&Single step"));
    mOpenButtonP = new QPushButton(tr("Open game &file"));
    
    connect( mStartButtonP, SIGNAL(clicked()), this, SLOT(slot_start()) );
    connect( mStopButtonP, SIGNAL(clicked()), this, SLOT(slot_stop()) );
    connect( mResetButtonP, SIGNAL(clicked()), this, SLOT(slot_reset()) );
    connect( mGotoButtonP, SIGNAL(clicked()), this, SLOT(slot_gotoLine()) );
    connect( mOpenButtonP, SIGNAL(clicked()), this, SIGNAL(sig_openFile()) );

#ifdef DEBUG
    {
        std::ostringstream out;
        out << "(DD) CommandWindow::init "
            << std::hex << this << std::dec
            << " Buttons complete "
            << std::endl;
        std::clog << out.str();
    }
#endif /* DEBUG */

    QGridLayout *layout = new QGridLayout;
    layout->addWidget( mCommandListP, 0, 0, 1, 2 );
    layout->addWidget( mOpenButtonP, 1, 0 );
    layout->addWidget( mGotoButtonP, 1, 1 );
    layout->addWidget( mStartButtonP, 2, 0 );
    layout->addWidget( mSingleStepButtonP, 2, 1 );
    layout->addWidget( mStopButtonP, 3, 0 );
    layout->addWidget( mResetButtonP, 3, 1 );
    this->setLayout(layout);

    // Alles zuruecksetzen.
    slot_reset();

#ifdef DEBUG
    {
        std::ostringstream out;
        out << "(DD) CommandWindow::init "
            << std::hex << this << std::dec
            << " End " << retValue
            << std::endl;
        std::clog << out.str();
    }
#endif /* DEBUG */

    return retValue;
}

// Datei oeffen und darstellen.
bool CommandWindow::openFile( const QString& fileName )
{
    bool retValue = false;

    QFile file(fileName);

    if ( file.open(QIODevice::ReadOnly | QIODevice::Text) )
    {
        // Vorherigen Text loeschen und Zeile fuer Zeile
        // hinzufuegen.
        mCommandListP->clear();

        QTextStream in(&file);
        while ( !in.atEnd() )
        {
            mCommandListP->addItem( in.readLine() );
        }

        // Alles auf Anfang setzen.
        slot_reset();
        
        retValue = true;
    }
    else
    {
        std::ostringstream out;
        out << "(EE) CommandWindow::openFile "
            << std::hex << this << std::dec
            << " Could not open file '"
            << fileName.toStdString()
            << "' for reading."
            << std::endl;
        std::cerr << out.str();
    }

    return retValue;
}

// Starte die Kommandoverarbeitung von der aktuellen Zeile an.
void CommandWindow::slot_start()
{
    // Wenn wir am Ende der Datei sind, dann resetten wir zuerst alles.
    if ( mCommandIndex >=  mCommandListP->count() )
    {
        slot_reset();
    }
    
    if ( mSingleStepButtonP->isChecked() )
    {
        // Der Einzelschritt-Knopf ist angehakt, wir hoeren nach
        // einer Zeile auf.
        startUntilLine( mCommandIndex+1, false );
    }
    else
    {
        // Wir iterieren ganz langsam von der aktuellen Position
        // bis zum Ende der Liste, falls uns nichts vorher aufhaelt.
        startUntilLine( mCommandListP->count(), false );
    }
}

// Stoppe Bearbeitung.
void CommandWindow::slot_stop()
{
    // Wir setzen nur das Stop-Kommando auf true, was
    // dafuer sorgen sollte, dass die Iteration abbricht.
    isStopCommand = true;
}

// Setze Verarbeitung an Anfang.
void CommandWindow::slot_reset()
{
    mCommandHandlerP->reset();

    if ( mCommandListP->count() > 0 )
    {
        // Index zurueck auf 0 setzen.
        setIndex(0);

        // Knoepfe setzen.
        mStartButtonP->setDisabled(false);
        mStopButtonP->setDisabled(true);
        mResetButtonP->setDisabled(true);
        mSingleStepButtonP->setDisabled(false);
        mGotoButtonP->setDisabled(false);
        mOpenButtonP->setDisabled(false);    
        isStopCommand = false;    
    }
    else
    {
        // Wir haben nichts geladen.
        setIndex(-1);
        
        // Knoepfe setzen.
        mStartButtonP->setDisabled(true);
        mStopButtonP->setDisabled(true);
        mResetButtonP->setDisabled(true);
        mSingleStepButtonP->setDisabled(true);
        mGotoButtonP->setDisabled(true);
        mOpenButtonP->setDisabled(false);    
        isStopCommand = false;
    }
}

// Verarbeite alles bis zur ausgewaehlten Zeile (exklusive).
void CommandWindow::slot_gotoLine()
{
    // Hole die aktuell ausgewaehlte Zeile.
    const int currentRow = mCommandListP->currentRow();

    if ( currentRow > mCommandIndex )
    {
        // Die angesteuerte Zeile liegt hinter der aktuellen.
        // Wir koennen diese also normal ansteuern.
        startUntilLine( currentRow, true );
    }
    else  if ( currentRow < mCommandIndex )
    {
        // Die angesteuerte Zeile liegt vor der aktuellen.
        // Wir muessen also zuerst das Spiel zuruecksetzen.
        slot_reset();
        startUntilLine( currentRow, true );
    }
}

// Setzt den aktuellen Zeilenindex.
void CommandWindow::setIndex( const int index )
{
    mCommandIndex = index;

    if ( 0 <= mCommandIndex && mCommandIndex < mCommandListP->count() )
    {
        // Die gesetzte Zeile auswaehlen.
        mCommandListP->setCurrentRow( mCommandIndex );
    }
}

// Lasse das Spiel bis zu einer bestimmten Zeile (exklusive) laufen.
void CommandWindow::startUntilLine( const int index, const bool noUpdate )
{
    // Effektiv ist jetzt nur noch der Stop-Knopf erlaubt.
    mStartButtonP->setDisabled(true);
    mStopButtonP->setDisabled(false);
    mResetButtonP->setDisabled(true);
    mSingleStepButtonP->setDisabled(true);
    mGotoButtonP->setDisabled(true);
    mOpenButtonP->setDisabled(true);

    // Wir laufen bis zum Index bzw. bis zum Ende der Liste,
    // falls nichts anderes angegeben ist.
    while ( mCommandIndex < index &&
            mCommandIndex < mCommandListP->count() &&
            !isStopCommand )
    {
        if ( !noUpdate )
        {
            // Aktuelle Zeile anwaehlen.
            setIndex(mCommandIndex);
        }
            
        // Aktuelle Zeile verarbeiten.
        bool retValue = mCommandHandlerP->receiveAndHandleMessage(
                            mCommandListP->item(mCommandIndex)->text() );

        if ( !retValue )
        {
            // Es kam zu einem Fehler.
            std::ostringstream out;
            out << "(EE) CommandWindow::start "
                << std::hex << this << std::dec
                << " Error handling message!"
                << std::endl;
            std::cerr << out.str();

            QMessageBox::warning( this, tr("CommandWindow"),
                                  tr("Error handling message in current line!"),
                                  QMessageBox::Ok );
            break;
        }
        else
        {
            if ( !noUpdate )
            {
                // Signal senden, dass sich die Daten geaendert haben.
                sig_dataChanged();
            }
            mCommandIndex++;
            
            // GUI-Ereignisse verarbeiten.
            QCoreApplication::processEvents();
        }
    }

    // Mindestens einmal am Ende muessen wir ein Signal fuer das Update senden.
    setIndex(mCommandIndex);
    sig_dataChanged();

    // Wir haben angehalten. Knoepfe zuruecksetzen.
    // Hinweis: Reset ist jetzt erlaubt.
    mStartButtonP->setDisabled(false);
    mStopButtonP->setDisabled(true);
    mResetButtonP->setDisabled(false);
    mSingleStepButtonP->setDisabled(false);
    mGotoButtonP->setDisabled(false);
    mOpenButtonP->setDisabled(false);
    isStopCommand = false;
}
