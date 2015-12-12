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
#include "controlclient.h"

#define PM_PATH "/org/ajalkane/findmyjolla"
#define PM_SERVICE "org.ajalkane.findmyjolla"
#define PM_INTERFACE "org.ajalkane.findmyjolla"

ControlClient::ControlClient(QObject *parent) :
    QObject(parent), dbus_iface(NULL)
{
    dbus_iface = new QDBusInterface(PM_SERVICE, PM_PATH,
                                    PM_INTERFACE);

    connect(dbus_iface, SIGNAL(activeChanged(bool)), this, SIGNAL(activeChanged(bool)));
    connect(dbus_iface, SIGNAL(matchPhraseChanged(const QString &)), this, SIGNAL(matchPhraseChanged(const QString &)));
    connect(dbus_iface, SIGNAL(started()), this, SIGNAL(started()));
    connect(dbus_iface, SIGNAL(stopped()), this, SIGNAL(stopped()));
}

ControlClient::~ControlClient() {
    delete dbus_iface;
}

int
ControlClient::lastError() const {
    return dbus_iface->lastError().type();
}

bool
ControlClient::isActive() const {
    QDBusReply<bool> reply = dbus_iface->call("isActive");
    if (!reply.isValid()) {
        QDBusError e = reply.error();
        qDebug("isActive error %s %s %d", qPrintable(e.message()), qPrintable(e.name()), e.type());
    }
    return reply.value();
}


void
ControlClient::setActive(bool isActive) {
    /*QDBusReply<QList<Rule> > reply = */ dbus_iface->call("setActive", QVariant::fromValue(isActive));
    /*if (!reply.isValid()) {
        QDBusError e = reply.error();
        qDebug("updateRule error %s %s %d", qPrintable(e.message()), qPrintable(e.name()), e.type());
    }*/
}

QString
ControlClient::matchPhrase() const {
    QDBusReply<QString> reply = dbus_iface->call("matchPhrase");
    if (!reply.isValid()) {
        QDBusError e = reply.error();
        qDebug("isActive error %s %s %d", qPrintable(e.message()), qPrintable(e.name()), e.type());
    }
    return reply.value();
}


void
ControlClient::setMatchPhrase(const QString &matchPhrase) {
    /*QDBusReply<QList<Rule> > reply = */ dbus_iface->call("setMatchPhrase", QVariant::fromValue(matchPhrase));
    /*if (!reply.isValid()) {
        QDBusError e = reply.error();
        qDebug("updateRule error %s %s %d", qPrintable(e.message()), qPrintable(e.name()), e.type());
    }*/
}
