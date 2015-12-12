/**********************************************************************
 * Copyright 2015 Arto Jalkanen
 *
 * This file is part of Find My Jolla.
 *
 * Find My Jolla is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Find My Jolla is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Find My Jolla.  If not, see <http://www.gnu.org/licenses/>
**/
#ifndef CONTROLINTERFACE_H
#define CONTROLINTERFACE_H

#include <QObject>
#include <QList>
#include <QString>
#include <QStringList>

#include "preferences.h"

class ControlInterface : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.ajalkane.findmyjolla")
    Preferences *_preferences;

public:
    explicit ControlInterface(Preferences *preferences, QObject *parent = 0);
    virtual ~ControlInterface();

    // Return 0 if success
    int init();
signals:
    void activeChanged(bool isActive);
    void matchPhraseChanged(const QString &matchPhrase);
    void started();
    void stopped();
public slots:
    // Returns true if ringing restoring is active
    bool isActive() const;
    void setActive(bool active);
    QString matchPhrase() const;
    void setMatchPhrase(const QString &matchPhrase);
private:
    bool _started;
    void _preferencesChanged();
};

#endif // CONTROLINTERFACE_H
