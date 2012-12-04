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

#ifndef ENGINECONFIG_HH
#define ENGINECONFIG_HH

/// Konfiguration fuer die Engine.
class EngineConfig
{
  public:
    /// Standard-Konstruktor.
    /**
     * Per Standard ist das Logging deaktiviert.
     */
    EngineConfig();

    /// De-/Aktiviert das Logging in der Engine.
    /**
     * @param activateLog Falls true wird das Logging
     * aktiviert, ansonsten deaktiviert.
     */
    void setLog( const bool activateLog );

    /// Gibt zurueck, ob das Logging aktiv ist.
    bool isLog() const;

  private:
    /// Flag, ob das Logging aktiv ist.
    bool mActiveLog;
};

// INLINE ///////////////////////////////////////////////////////////

// De-/Aktiviert das Logging im Engine.
inline
void EngineConfig::setLog( const bool activateLog )
{
    mActiveLog = activateLog;
}

// Gibt zurueck, ob das Logging aktiv ist.
inline
bool EngineConfig::isLog() const
{
    return mActiveLog;
}

#endif // ENGINECONFIG_HH
