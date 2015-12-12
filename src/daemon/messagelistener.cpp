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
#include <QtDBus>
#include <QDebug>

#include "messagelistener.h"

#define DBUS_INTERFACE "org.freedesktop.Telepathy.Channel.Interface.Messages"
#define DBUS_MEMBER_NAME "MessageReceived"
#define DBUS_ENTRY_WITH_MESSAGE "content"

MessageListener::MessageListener(const Preferences *preferences, const DisplayAlarm *displayAlarm, QObject *parent) :
    QObject(parent), _preferences(preferences), _displayAlarm(displayAlarm), sessionBus(QDBusConnection::sessionBus())
{
    if (!sessionBus.connect("", "", DBUS_INTERFACE, DBUS_MEMBER_NAME, this, SLOT(dbusMessageReceived(const QDBusMessage &)))) {
        qDebug() << Q_FUNC_INFO << "Error registering signal listener" << sessionBus.lastError().type();
    } else {
        qDebug() << Q_FUNC_INFO << "Signal listener created successfully";
    }
}

void
MessageListener::dbusMessageReceived(const QDBusMessage &msg) const {
    if (!_preferences->isActive) {
        qDebug() << Q_FUNC_INFO << "Not active, ignoring message";
        return;
    }

    qDebug() << Q_FUNC_INFO << "Received message" << msg;
    qDebug() << Q_FUNC_INFO << "Received message arguments: " << msg.arguments().size();

    QString content = findMessageContent(msg);
    if (content.isNull()) {
        qWarning() << Q_FUNC_INFO << "No content found from message";
    } else {
        QString match = _preferences->matchPhrase;
        content = content.trimmed();
        qDebug() << Q_FUNC_INFO << "Emitting message received with content '" << content << "'";
        emit messageReceived(content);

        if (match == content) {
            qDebug() << Q_FUNC_INFO << "Message matched passphrase";
            _displayAlarm->activate();
        }
    }
}

QString
MessageListener::findMessageContent(const QDBusMessage &msg) const {
    foreach (QVariant variantArg, msg.arguments()) {
        qDebug() << Q_FUNC_INFO << "Processing next argument";
        const QDBusArgument arg = variantArg.value<QDBusArgument>();
        arg.beginArray();
        while (!arg.atEnd()) {
            arg.beginMap();
            while (!arg.atEnd()) {
                QString key;
                QVariant value;

                arg.beginMapEntry();
                arg >> key >> value;
                arg.endMapEntry();

                qDebug() << Q_FUNC_INFO << "Extracted key" << key << "and value" << value;
                if (key == DBUS_ENTRY_WITH_MESSAGE) {
                    qDebug() << "Found what was looked for";

                    QString message = value.toString();
                    return message;
                }
            }
            arg.endMap();
        }
        arg.endArray();
    }
    return QString();
}
