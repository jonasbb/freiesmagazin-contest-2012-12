#include "Gameboard.hh"

#include "TileContext.hh"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>

// Konstruktor.
Gameboard::Gameboard()
  : mSize(0,0)
{
}

// Destruktor.
Gameboard::~Gameboard()
{
}

// Laedt ein Spielbrett aus einer Datei.
bool Gameboard::load( const std::string& filename )
{
    bool retValue = false;

    // Datei oeffnen
    std::ifstream infile;

    infile.open( filename.c_str() );
    if ( infile.is_open() )
    {
        char charLine[1000];
        std::string line;
        unsigned int lineCounter = 0;

        retValue = true;

        while( infile.good() )
        {
            infile.getline(charLine, 1000);
            line = charLine;

            if ( !line.empty() )
            {
                if ( 0 == lineCounter )
                {
                    Position newSize;
                    if ( !extractSize( newSize, line ) )
                    {
                        retValue = false;
                        break;
                    }
                    if ( !setSize( newSize ) )
                    {
                        retValue = false;
                        break;
                    }
                }
                else
                {
                    if ( !extractAndSetTiles( lineCounter, line ) )
                    {
                        retValue = false;
                        break;
                    }
                }
                lineCounter++;
            }
            else
            {
                // Eine leere Zeile steht fuer das Ende der Datei.

                // Der Zeilencounter muss am Ende der Spielbrettgroesse
                // plus 1 entsprechend.
                if ( mSize.y()+1 != lineCounter )
                {
                    std::ostringstream out;
                    out << "(EE) Gameboard::load "
                        << std::hex << this << std::dec
                        << " Number of read lines "
                        << lineCounter
                        << " does not equal value y = "
                        << mSize
                        << "."
                        << std::endl;
                    std::cerr << out.str();
                    retValue = false;
                }
                break;
            }
        }

        // Datei schließen.
        infile.close();

    }
    else
    {
        std::ostringstream out;
        out << "(EE) Gameboard::load "
            << std::hex << this << std::dec
            << " Could not open file "
            << filename
            << "."
            << std::endl;
        std::cerr << out.str();
    }
    
    return retValue;
}

// Erzeugt ein Spielbrett aus einer Stringliste.
bool Gameboard::create( const Position& size,
                        const std::vector<std::string>& lines )
{
    bool retValue = false;

#ifdef DEBUG
    std::ostringstream out;
    out << "(DD) Gameboard::create "
        << std::hex << this << std::dec
        << " Size: "
        << size
        << std::endl;
    std::cerr << out.str();
#endif

    if ( lines.size() == size.y() )
    {
        if ( setSize( size ) )
        {
            retValue = true;
            for ( unsigned int jj = 0; jj < size.y(); jj++ )
            {
                if ( lines[jj].length() == size.x() )
                {
                    if ( !extractAndSetTiles( jj+1, lines[jj] ) )
                    {
                        retValue = false;
                        break;
                    }
                }
                else
                {
                    std::ostringstream out;
                    out << "(EE) Gameboard::create "
                        << std::hex << this << std::dec
                        << " Line "
                        << jj
                        << " has length "
                        << lines[jj].length()
                        << "; differs from board with "
                        << size.x()
                        << "."
                        << std::endl;
                    std::cerr << out.str();
                    retValue = false;
                    break;
                }
            } // for jj
        }
    }
    else
    {
        std::ostringstream out;
        out << "(EE) Gameboard::create "
            << std::hex << this << std::dec
            << " Height of game board "
            << size.y()
            << " does not equal number of lines "
            << lines.size()
            << "."
            << std::endl;
        std::cerr << out.str();
    }

#ifdef DEBUG
    std::ostringstream out2;
    out2 << "(DD) Gameboard::create "
         << std::hex << this << std::dec
         << " Return: "
         << retValue
         << std::endl;
    std::cerr << out2.str();
#endif
    
    return retValue;
}

// Lege ein Feld trocken.
bool Gameboard::drain( const Position& pos )
{
    if ( isValidPos( pos ) )
    {
        return mTiles[ getIntPos( pos ) ]->drain();
    }
    return false;
}

// Ueberflute ein Feld.
bool Gameboard::flood( const Position& pos )
{
    if ( isValidPos( pos ) )
    {
        return mTiles[ getIntPos( pos ) ]->flood();
    }
    return false;
}

// Prueft, ob das Feld noch trocken ist.
bool Gameboard::isDry( const Position& pos ) const
{
    if ( isValidPos( pos ) )
    {
        return mTiles[ getIntPos( pos ) ]->isDry();
    }
    return false;
}

// Prueft, ob das Feld ueberflutet wurde.
bool Gameboard::isFlooded( const Position& pos ) const
{
    if ( isValidPos( pos ) )
    {
        return mTiles[ getIntPos( pos ) ]->isFlooded();
    }
    return false;
}

// Prueft, ob das Feld schon untergegangen ist.
bool Gameboard::isLost( const Position& pos ) const
{
    if ( isValidPos( pos ) )
    {
        return mTiles[ getIntPos( pos ) ]->isLost();
    }
    return false;
}

// Prueft, ob die Position fuer das Spielbrett valide ist.
bool Gameboard::isValidPos( const Position& pos, const bool noError ) const
{
    bool valid = false;

    // Achtung: Position faengt bei (1,1) an.
    if ( pos.isValid() && pos <= mSize )
    {
        const unsigned int tPos = getIntPos( pos );
        if ( 0 != mTiles[tPos] )
        {
            valid = true;
        }
        else
        {
            std::ostringstream out;
            out << "(EE) Gameboard::isValidPos "
                << std::hex << this << std::dec
                << " Tile context is 0 at position "
                << pos
                << "."
                << std::endl;
            std::cerr << out.str();
        }        
    }
    else if ( !noError )
    {
        std::ostringstream out;
        out << "(EE) Gameboard::isValidPos "
            << std::hex << this << std::dec
            << " Invalid position "
            << pos
            << " for boardsize "
            << mSize
            << "."
            << std::endl;
        std::cerr << out.str();
    }
    
    return valid;
}

// Liefert Position in interner Datenstruktur.
unsigned int Gameboard::getIntPos( const Position& pos ) const
{
    // Achtung: Position faengt bei (1,1) an.
    return getIntPos( pos.x(), pos.y() );
}

// Liefert Position in interner Datenstruktur.
unsigned int Gameboard::getIntPos( const unsigned int x,
                                   const unsigned int y ) const
{
    // Achtung: Position faengt bei (1,1) an.
    return (y-1)*(mSize.x()) + (x-1);
}

// Setzt neue Spielbrettgroesse und allokiert Speicher dafuer.
bool Gameboard::setSize( const Position& newSize )
{
    bool valid = false;

    if ( newSize.isValid() )
    {
        // Durch die alte Liste iterieren und Speicher aufraeumen.
        for ( unsigned int ii = 0; ii < mSize.x() * mSize.y(); ii++ )
        {
            delete mTiles[ii];
            mTiles[ii] = 0;
        }

        // Neue Groesse setzen.
        mSize = newSize;
        mTiles.resize( mSize.x() * mSize.y() );

        for ( unsigned int ii = 0; ii < mSize.x() * mSize.y(); ii++ )
        {
            mTiles[ii] = new TileContext();
        }

        valid = true;
    }
    else
    {
        std::ostringstream out;
        out << "(EE) Gameboard::setSize "
            << std::hex << this << std::dec
            << " Invalid size "
            << newSize
            << "."
            << std::endl;
        std::cerr << out.str();        
        valid = false;
    }

    return valid;
}

// Extrahiert eine zweidimensionale Groesse aus der Zeile.
bool Gameboard::extractSize( Position& size, const std::string& line ) const
{
    bool valid = false;
    
    size.setPosition(0,0);

    // Suche Leerzeichen als Trennzeichen.
    size_t pos = line.find(' ');

    // Wir brauchen mindestens drei Zeichen "x y", x,y aus N.
    if ( (line.length() >= 3 ) &&
         ( std::string::npos != pos ) &&
         ( 0 != pos ) &&
         ( line.length()-1 != pos ) )
    {
        int x = atoi( line.substr( 0, pos ).c_str() );
        int y = atoi( line.substr( pos+1 ).c_str() );

#ifdef DEBUG
        std::ostringstream out;
        out << "(DD) Gameboard::extractSize "
            << std::hex << this << std::dec
            << " Size: "
            << "(" << x << "," << y << ")"
            << "."
            << std::endl;
        std::clog << out.str();        
#endif // DEBUG

        if ( ( x > 0 ) && ( y > 0 ) )
        {
            size.setPosition( (unsigned int)x, (unsigned int)y );
            valid = true;
        }
        else
        {
            std::ostringstream out;
            out << "(EE) Gameboard::extractSize "
                << std::hex << this << std::dec
                << " Size: "
                << "(" << x << "," << y << ")"
                << " must be positive."
                << " From line: '"
                << line.c_str()
                << "'."
                << std::endl;
            std::cerr << out.str();
            valid = false;
        }
    }
    else
    {
        std::ostringstream out;
        out << "(EE) Gameboard::extractSize "
            << std::hex << this << std::dec
            << " Could not extract size from line '"
            << line.c_str()
            << "'; must be in format '5 3'."
            << std::endl;
        std::cerr << out.str();
        valid = false;
    }
    
    return valid;
}

// Extrahiere Felder aus einer Zeiler.
bool Gameboard::extractAndSetTiles( const unsigned int lineCounter,
                                    const std::string& line )
{
    bool valid = false;

    if ( ( 1 <= lineCounter ) && ( lineCounter <= mSize.y() ) )
    {
        if ( line.length() == mSize.x() )
        {
            valid = true;
            Position pos;
            
            for ( size_t ii = 0; ii < line.length(); ii++ )
            {
                pos.setPosition( ii+1, lineCounter );
                if ( isValidPos(pos) )
                {
                    const unsigned int tPos = getIntPos(pos);

                    if ( !mTiles[tPos]->setTile( mTiles[tPos]->createNewTile( line[ii] ) ) )
                    {
                        valid = false;
                        break;
                    }
                }
                else
                {
                    valid = false;
                    break;
                }
            }
        }
        else
        {
            std::ostringstream out;
            out << "(EE) Gameboard::extractAndSetTiles "
                << std::hex << this << std::dec
                << " Line length "
                << line.length()
                << " does not equal board with "
                << mSize.x()
                << " in line "
                << lineCounter+1
                << ": '"
                << line
                << "'."
                << std::endl;
            std::cerr << out.str();
            valid = false;
        }
    }
    else
    {
        std::ostringstream out;
        out << "(EE) Gameboard::extractAndSetTiles "
            << std::hex << this << std::dec
            << " Invalid line counter "
            << lineCounter
            << " for board height "
            << mSize.y()
            << "."
            << std::endl;
        std::cerr << out.str();
        valid = false;
    }

    return valid;
}

// Gibt das Spielbrett in Stringliste aus.
void Gameboard::print( std::vector<std::string>& stringVector ) const
{
    stringVector.resize(0);

    if ( mSize.isValid() )
    {
        stringVector.resize( mSize.y() );
        for ( unsigned int jj = 1; jj <= mSize.y(); jj++ )
        {
            std::ostringstream out;
            for ( unsigned int ii = 1; ii <= mSize.x(); ii++ )
            {
                const unsigned int tPos = getIntPos(ii,jj);
                if ( mTiles[tPos] )
                {
                    out << mTiles[tPos]->print();
                }
                else
                {
                    out << " ";
                }
            }
            stringVector[jj-1] = out.str();
        }
    }
}

// Gibt das Spielbrett auf stdlog aus.
void Gameboard::print() const
{
    if ( mSize.isValid() )
    {
        for ( unsigned int jj = 1; jj <= mSize.y(); jj++ )
        {
            std::ostringstream out;
            out << "(II) ";
            for ( unsigned int ii = 1; ii <= mSize.x(); ii++ )
            {
                const unsigned int tPos = getIntPos(ii,jj);
                if ( mTiles[tPos] )
                {
                    out << mTiles[tPos]->print();
                }
                else
                {
                    out << " ";
                }
            }
            std::clog << out.str() << std::endl;
        }
    }
}
