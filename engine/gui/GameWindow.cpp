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

#include "GameWindow.hh"

#include "CommandHandler.hh"
#include "CommandWindow.hh"
#include "GameArea.hh"

#include <QAction>
#include <QBoxLayout>
#include <QFileDialog>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>

#include <iostream>
#include <sstream>

// Konstruktor.
GameWindow::GameWindow()
: QMainWindow(), mGameAreaP(0), mCommandWindow(0)
{
    setWindowTitle( tr("freiesMagazin: Lost Island") );

    resize( QSize( 800, 600 ) );
}

// Destruktor.
GameWindow::~GameWindow()
{
    // Alle Zeiger sind Eigentum des Windows und werden
    // automatisch geloescht.
}

// Initialisiert alle Fenster und Menus.
bool GameWindow::init( GameData* dataP )
{
    bool retValue = true;

    mGameAreaP = new GameArea(this);
    if ( !mGameAreaP )
    {
        std::ostringstream out;
        out << "(EE) GameWindow::init "
            << std::hex << this << std::dec
            << " GameArea is 0!"
            << std::endl;
        std::cerr << out.str();

        QMessageBox::critical( this, windowTitle(),
                               tr("GameArea is 0!"),
                               QMessageBox::Abort );
        return false;
    }

    mCommandWindow = new CommandWindow(this);
    if ( !mCommandWindow )
    {
        std::ostringstream out;
        out << "(EE) GameWindow::init "
            << std::hex << this << std::dec
            << " CommandWindow is 0!"
            << std::endl;
        std::cerr << out.str();

        QMessageBox::critical( this, windowTitle(),
                               tr("CommandWindow is 0!"),
                               QMessageBox::Abort );
        return false;
    }

    if ( !mGameAreaP->init( dataP ) )
    {
        return false;
    }

    if ( !mCommandWindow->init( dataP ) )
    {
        return false;
    }

    // Spielfeld-Update mit Spieldatenaenderung verbinden.
    connect(mCommandWindow, SIGNAL(sig_dataChanged()), mGameAreaP, SLOT(update()));
    connect(mCommandWindow, SIGNAL(sig_openFile()), this, SLOT(slot_openFile()));

    // Spielfeld initialisieren
    mGameAreaP->setMinimumSize( QSize( 200, 200 ) );
    mGameAreaP->setSizePolicy( QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding );

    // Textliste initialisieren
    mCommandWindow->setFixedWidth( 250 );

    // create menu
    QMenu* gameMenu = menuBar()->addMenu( tr("&Game") );
    // gameMenu->addAction( tr("Open game &file"), this, SLOT( slot_openFile() ) );
    // gameMenu->addSeparator();
    gameMenu->addAction( tr("&Quit"), this, SLOT( close() ) );

    // Alles in ein Layout stecken.
    QWidget *mainWindow = new QWidget(this);
    QBoxLayout* boxLayout = new QBoxLayout( QBoxLayout::LeftToRight );
    boxLayout->addWidget( mGameAreaP );
    boxLayout->addWidget( mCommandWindow );
    mainWindow->setLayout(boxLayout);

    // Hauptfenster festlegen.
    setCentralWidget(mainWindow);

    return retValue;
}

void GameWindow::slot_openFile()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file") );

    if ( !fileName.isNull() )
    {
        if ( !mCommandWindow->openFile( fileName ) )
        {
            QMessageBox::warning( this, windowTitle(),
                                   tr("Could not open file for reading!"),
                                   QMessageBox::Ok );
        }
    }
}
