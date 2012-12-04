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

#include "GameArea.hh"

#include "Gameboard.hh"
#include "GameData.hh"
#include "Player.hh"

#include <QColor>
#include <QList>
#include <QPainter>
#include <QPoint>

#include <iostream>
#include <sstream>

// Konstruktor.
GameArea::GameArea( QWidget *parent )
: QWidget(parent), mDataP(0)
{
    // create player
    mPlayer.moveTo(4.0,3.0);
    mPlayer.cubicTo(4.0,1, 6.0,1.0, 6.0,3.0);
    mPlayer.cubicTo(10.0,3.5, 10.0,5.5, 7.0,5.0);
    mPlayer.lineTo(8.666,7.5);
    mPlayer.quadTo(9.0,8.0,8.0,8.0);
    mPlayer.lineTo(6.0,8.0);
    mPlayer.lineTo(5.0,7.0);
    mPlayer.lineTo(4.0,8.0);
    mPlayer.lineTo(2.0,8.0);
    mPlayer.quadTo(1.0,8.0,1.333,7.5);
    mPlayer.lineTo(3.0,5.0);
    mPlayer.cubicTo(0.0,5.5, 0.0,3.5, 4.0,3.0);
    

    // general data
    const double fontFactor = 0.6;
    mGeneralNoPen.setStyle( Qt::NoPen );
    mGeneralTextPen.setColor( palette().text().color() );
    mGeneralDarkPen.setColor( palette().dark().color() );
    mGeneralNoBrush.setStyle( Qt::NoBrush );
    mGeneralSolidBrush.setStyle( Qt::SolidPattern );
    mGeneralRect.setRect( 0.0, 0.0, 10.0, 10.0 );
    mGeneralFont = font();
    mGeneralFont.setPointSize( mGeneralFont.pointSize() * fontFactor );
    
    // set default sizes
    mSquareSize = QSizeF( 10.0, 10.0 );
    mSquareFactor = QPointF( 1.0, 1.0 );
    
    // set background color as default white
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

// Destruktor.
GameArea::~GameArea()
{
    mDataP = 0;
}

// Initialisiert das Spielfeld.
bool GameArea::init( const GameData* dataP )
{
    bool retValue = false;
    
    if ( dataP )
    {
        mDataP = dataP;
        retValue = true;
    }
    else
    {
        std::ostringstream out;
        out << "(EE) GameArea::init "
            << std::hex << this << std::dec
            << " GameData is 0!"
            << std::endl;
        std::cerr << out.str();
    }

    return retValue;
}

// Das Event zeichnet alle Daten neu.
void GameArea::paintEvent(QPaintEvent* /*event*/)
{
    QPainter painter(this);
    painter.setRenderHints( painter.renderHints() | QPainter::Antialiasing );

    if ( calculateSquareSizeAndFactorFromGameboard() )
    {
#ifdef DEBUG
        {
            std::ostringstream out;
            out << "(DD) GameArea::paintEvent "
                << std::hex << this << std::dec
                << std::endl;
            std::clog << out.str();
        }
#endif
        paintGameboard( painter );
        paintPlayer( painter );
    }
}

// Zeichnet Spielbrett.
void GameArea::paintGameboard( QPainter& painter )
{
    {
        std::ostringstream out;
        out << "(DD) GameArea::paintGameboard "
            << std::hex << this << std::dec
            << " " << std::hex << mDataP << std::dec
            << std::endl;
        std::clog << out.str();
    }
    if ( mDataP )
    {
        const Position& size = mDataP->gameboard.getSize();

        {
            std::ostringstream out;
            out << "(DD) GameArea::paintGameboard "
                << std::hex << this << std::dec
                << " " << size
                << std::endl;
            std::clog << out.str();
        }
        
        QPoint pos;

         // write numbers
        for ( unsigned int ii = 1; ii <= size.x(); ii++ )
        {
            pos.setX(ii);
            pos.setY(0);

            painter.save();
                painter.translate( pos.x()*mSquareSize.width(),
                                   pos.y()*mSquareSize.height() );
                painter.scale( mSquareFactor.x(), mSquareFactor.y() );

                painter.setFont( mGeneralFont );
                painter.setPen( mGeneralTextPen );
                painter.setBrush( mGeneralNoBrush );
                painter.drawText( mGeneralRect, Qt::AlignCenter,
                                  QString::number( ii ) );
            painter.restore();
        }

        for ( unsigned int jj = 1; jj <= size.y(); jj++ )
        {
            pos.setX(0);
            pos.setY(jj);

            painter.save();
                painter.translate( pos.x()*mSquareSize.width(),
                                   pos.y()*mSquareSize.height() );
                painter.scale( mSquareFactor.x(), mSquareFactor.y() );

                painter.setFont( mGeneralFont );
                painter.setPen( mGeneralTextPen );
                painter.setBrush( mGeneralNoBrush );
                painter.drawText( mGeneralRect, Qt::AlignCenter,
                                  QString::number( jj ) );
            painter.restore();
        }

        painter.save();
        painter.translate( mSquareSize.width(), mSquareSize.height() );

        for ( unsigned int ii = 1; ii <= size.x(); ii++ )
        {
            for ( unsigned int jj = 1; jj <= size.y(); jj++ )
            {
                // create position
                Position pos(ii,jj);

                // paint single field
                paintField( painter, pos );
            }
        }

        painter.restore();

        painter.setPen( mGeneralDarkPen );
        painter.setBrush( mGeneralNoBrush );
        painter.drawRect( mAreaRect );
    }
}

// Zeichnet ein einzelnes Feld des Spielbretts.
void GameArea::paintField( QPainter& painter, const Position& pos )
{
    if ( mDataP && mDataP->gameboard.isValidPos( pos ) )
    {
        painter.save();
            painter.translate( (pos.x()-1)*mSquareSize.width(),
                               (pos.y()-1)*mSquareSize.height() );
            painter.scale( mSquareFactor.x(), mSquareFactor.y() );
            painter.setPen( mGeneralNoPen );

            if ( mDataP->gameboard.isDry( pos ) )
            {
                mGeneralSolidBrush.setColor( QColor(215,128,0) );
            }
            else if ( mDataP->gameboard.isFlooded( pos ) )
            {
                mGeneralSolidBrush.setColor( QColor(0,180,255) );
            }
            else if ( mDataP->gameboard.isLost( pos ) )
            {
                mGeneralSolidBrush.setColor( QColor(0,0,255) );
            }
            else
            {
                mGeneralSolidBrush.setColor( QColor(255,255,255) );
            }
            
            painter.setBrush( mGeneralSolidBrush );
            painter.drawRect( mGeneralRect );
        painter.restore();
    }
}

// Zeichnet den Spieler.
void GameArea::paintPlayer( QPainter& painter, const bool updatePos )
{
    if ( mDataP )
    {
        painter.save();
            painter.translate( mSquareSize.width(),
                               mSquareSize.height() );

            const Position& pos = mDataP->position;

            // if we want to update the position of the player we will
            // redraw the field he's standing on.
            if ( updatePos )
            {
                paintField( painter, pos );
            }

            painter.save();
                painter.translate( (pos.x()-1)*mSquareSize.width(),
                                   (pos.y()-1)*mSquareSize.height() );
                painter.scale( mSquareFactor.x(), mSquareFactor.y() );
                painter.setPen( mGeneralDarkPen );
                mGeneralSolidBrush.setColor( QColor(30,30,30) );
                painter.setBrush( mGeneralSolidBrush );
                painter.drawPath( mPlayer );
            painter.restore();
        
        painter.restore();
    }
}

// Berechne Anzeigegroesse fuer das Spielbrett.
bool GameArea::calculateSquareSizeAndFactorFromGameboard()
{
    bool ok = false;

    if ( mDataP )
    {
        // get width and height of map
        const Position& size = mDataP->gameboard.getSize();

        if ( size.x() > 0 && size.y() > 0 &&
             width() > 0 && height() > 0 )
        {
            // if one of these values is 0 we would not see anything

            // Depending on the current dimension of the widget
            // we will calculate the least fitting square for the map.
            double numW = width() * 1.0 / (size.x()+1);
            double numH = height() * 1.0 / (size.y()+1);

            if ( numW < numH )
            {
                // the width is the limiting element
                numH = numW;
            }
            else
            {
                // the height is the limiting element
                numW = numH;
            }

            mSquareSize.setWidth( numW );
            mSquareSize.setHeight( numH );
            mSquareFactor.setX( numW / 10.0 );
            mSquareFactor.setY( numH / 10.0 );

            // set game area rectangle
            mAreaRect.setRect( mSquareSize.width(), mSquareSize.height(),
                               ((size.x())*numW)-1, ((size.y())*numH)-1 );

            ok = true;
        }
    }

    return ok;
}
