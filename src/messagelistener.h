/**********************************************************************
 * Copyright 2015 ajalkane
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
#ifndef SMSLISTENER_H
#define SMSLISTENER_H

#include <QObject>
#include <QtDBus>

class MessageListener : public QObject
{
    Q_OBJECT

    QDBusConnection sessionBus;

    QString findMessageContent(const QDBusMessage &msg) const;
public:
    explicit MessageListener(QObject *parent = 0);

signals:
    void messageReceived(const QString &message) const;

private slots:
    void dbusMessageReceived(const QDBusMessage &msg) const;
};

#endif // SMSLISTENER_H
