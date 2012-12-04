/**
    (C) Copyright 2011,2012 Dominik Wagenfuehr

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

#include "Engine.hh"
#include "EngineConfig.hh"
#include "EngineConfigCreator.hh"
#include "Game.hh"
#include "Server.hh"

#include <iostream>
#include <sstream>
#include <cstdlib>

/// Hauptroutine.
/**
 * Es werden folgende Argumente erwartet
 * arg0: Programmname
 * arg1 - argX: Optionen
 * argX+1: Dateiname zum Spielbrett
 * argX+2: instream von Spieler 1
 * argX+3: outstream von Spieler 1
 * ...
 * Dem Server muss jeweils der Eingabe- und Ausgabestroms
 * eines Clients angegeben werden.
 * Die Idee für die Client-Verarbeitung kam von Frank Staehr:
 * http://www.freiesmagazin.de/mobil/freiesMagazin-2011-03.html
 * @param argc Anzahl der Argumente (immer > 0)
 * @param argv Die einzelnen Argumente.
 */
int main( int argc, char* argv[] )
{
#ifdef DEBUG
    {
        std::ostringstream out;
        out << "(DD) Begin of main"
            << std::endl;
        std::clog << out.str();
    }
#endif

#ifdef DEBUG
    for ( int kk = 0; kk < argc; kk++ )
    {
        std::ostringstream out;
        out << "(DD) main"
            << " Arg " << kk << ": "
            << argv[kk]
            << std::endl;
        std::clog << out.str();
    }
#endif

    // Rueckgabewert 0 = alles okay
    int retValue = 0;

    // Zuerst alle Optionen verarbeiten und als Konfiguration
    // speichern. Nach der Verarbeitung gibt es keine Optionen
    // mehr in der Aufrufzeile.
    EngineConfig config;
    if ( EngineConfigCreator::createConfig( config, argc, argv ) )
    {
#ifdef DEBUG
        for ( int kk = 0; kk < argc; kk++ )
        {
            std::ostringstream out;
            out << "(DD) main (w/o options)"
                << " Arg " << kk << ": "
                << argv[kk]
                << std::endl;
            std::clog << out.str();
        }
#endif

        if ( argc >= 2 && argc%2 == 0 )
        {
            // Wir haben eine gerade Anzahl an Argumenten.
            // Das erste Argument ist der Dateiname des Spielbretts.
            
            // Wir gehen davon aus, dass es sich bei den restlichen
            // Argumenten um jeweils einen Eingabe- und Ausgabestrom
            // per Client handelt.
            const int numClients = (argc-2)/2;

#ifdef DEBUG
            std::ostringstream out;
            out << "(DD) main"
                      << " Number of clients: "
                      << numClients
                      << std::endl;
            std::clog << out.str();
#endif

            bool errorOccured = false;

            if ( !errorOccured )
            {
                // Erstellt das Server-Objekt, welches die Kommunikation
                // mit den Clients uebernimmt.
                Server server;

                // extrahiere alle Clients
                for ( int ii = 0; ii < numClients; ii++ )
                {
                    // Die Kommunikation mit dem Client findet
                    // ueber einen Eingabe- und einen Ausgabestrom statt.
                    if ( !server.createAndAddClient( argv[2*ii+2], argv[2*ii+3] ) )
                    {
                        // Irgendwas ging bei der Erstellung des Clients.
                        // Verlasse Schleife.
                        errorOccured = true;
                        retValue = 2;
                        break;
                    }
                }

                if ( !errorOccured )
                {
                    // Erstellt das eigentliche Spiel, welches die Daten verwaltet.
                    Game game;
                    if ( !game.init( argv[1] ) )
                    {
                        errorOccured = true;
                        retValue = 3;
                    }

                    if ( !errorOccured )
                    {
                        // Erstellt die GameEngine, welche die Verwaltung des
                        // Spiels übernimmt.
                        // Der Server wird als Referenz uebergeben und die Clients
                        // darueber dann von der Engine gesteuert.
                        Engine engine( game, server, config );

                        // Alles okay, das Spiel kann starten.
                        if ( engine.startGame() )
                        {
                            // Gib Spielende mit Ergebnis aus.
                            std::ostringstream out;
                            out << "(II) ROUNDS: "
                                << engine.getNumRounds()
                                << std::endl;
                            std::cout << out.str();                
                        }
                        else
                        {
                            // Ein Fehler sollte schon zuvor ausgegeben worden sein.
                            retValue = 4;
                        }
                    }
                }
            }
        }
        else
        {
            std::ostringstream out;
            out << "Syntax ist:" << std::endl
                << argv[0]
                << " SPIELBRETTDATEI [CLIENTEINGABESTROM CLIENTAUSGABESTROM]"
                << std::endl;
            std::cerr << out.str();

            retValue = 1;
        }
    }
    else
    {
        // Ein Fehler sollte schon zuvor ausgegeben worden sein.
        retValue = 5;
    }

#ifdef DEBUG
    {
        std::ostringstream out;
        out << "(DD) End of main "
            << retValue
            << std::endl;
        std::clog << out.str();
    }
#endif

    return retValue;
}
