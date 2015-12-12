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
#ifndef QMLBACKEND_H
#define QMLBACKEND_H

#include <QObject>
#include <QString>

#include "controlclient.h"

class QmlBackend : public QObject
{
    Q_OBJECT
    ControlClient *_controlClient;

    bool _daemonActive;
    bool _daemonRunning;
    QString _matchPhrase;

    Q_PROPERTY(bool daemonActive READ isActive WRITE setActive NOTIFY activeChanged)
    Q_PROPERTY(bool daemonRunning READ daemonRunning NOTIFY daemonRunningChanged)
    Q_PROPERTY(QString matchPhrase READ matchPhrase WRITE setMatchPhrase NOTIFY matchPhraseChanged)
    void _initDaemonState();
public:
    explicit QmlBackend(ControlClient *controlClient, QObject *parent = 0);

    bool isActive() const;
    void setActive(bool isActive);
    bool daemonRunning() const;
    inline QString matchPhrase() const { return _matchPhrase; }
    void setMatchPhrase(const QString &matchPhrase);

signals:
    void activeChanged();
    void daemonRunningChanged();
    void matchPhraseChanged();

public slots:
    void daemonActiveChanged(bool active);
    void daemonStarted();
    void daemonStopped();
    void matchPhraseChanged(const QString &matchPhrase);
    inline bool isJollaStoreCrippled() const {
#ifdef JOLLA_STORE_CRIPPLED
        return true;
#else
        return false;
#endif
    }

};

#endif // QMLBACKEND_H
