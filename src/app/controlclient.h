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
#ifndef CONTROLCLIENT_H
#define CONTROLCLIENT_H

#include <QObject>
#include <QList>
#include <QtDBus/QtDBus>

class ControlClient : public QObject
{
    Q_OBJECT

    QDBusInterface *dbus_iface;
public:
    explicit ControlClient(QObject *parent = 0);
    ~ControlClient();

    bool isActive() const;
    void setActive(bool isActive);
    QString matchPhrase() const;
    void setMatchPhrase(const QString &matchPhrase);

    // Returns QDBusError::ErrorType of last call. 0 is no error.
    int lastError() const;
signals:
    void activeChanged(bool);
    void matchPhraseChanged(const QString &matchPhrase);
    void started();
    void stopped();
public slots:
};

#endif // CONTROLCLIENT_H
