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
#include <QDebug>

#include "qmlbackend.h"

QmlBackend::QmlBackend(ControlClient *controlClient, QObject *parent) :
    QObject(parent), _controlClient(controlClient), _daemonActive(false), _daemonRunning(false)
{
    connect(_controlClient, SIGNAL(activeChanged(bool)), this, SLOT(daemonActiveChanged(bool)));
    connect(_controlClient, SIGNAL(started()), this, SLOT(daemonStarted()));
    connect(_controlClient, SIGNAL(stopped()), this, SLOT(daemonStopped()));
    connect(_controlClient, SIGNAL(matchPhraseChanged(const QString &)), this, SLOT(matchPhraseChanged(const QString &)));

    _initDaemonState();
}

void
QmlBackend::_initDaemonState() {
    _daemonActive = _controlClient->isActive();
    _matchPhrase = _controlClient->matchPhrase();
    if (_controlClient->lastError() != 0) {
        qDebug("QmlBackend::_initDaemonState: isActive resulted in DBus error type %d", _controlClient->lastError());
        _daemonActive = false;
        _daemonRunning = false;
    } else {
        _daemonRunning = true;
    }
}

bool
QmlBackend::isActive() const {
    return _daemonActive;
}

void
QmlBackend::setActive(bool isActive) {
    qDebug() << Q_FUNC_INFO << "Set active" << isActive;
    _controlClient->setActive(isActive);
}

bool
QmlBackend::daemonRunning() const {
    return _daemonRunning;
}

void
QmlBackend::daemonActiveChanged(bool active) {
    if (active != _daemonActive) {
        _daemonActive = active;
        qDebug() << Q_FUNC_INFO << "Emitting activeChanged" << active;
        emit activeChanged();
    }
}

void
QmlBackend::daemonStarted() {
    qDebug() << Q_FUNC_INFO;
    _initDaemonState();
    emit daemonRunningChanged();
    emit activeChanged();
}

void
QmlBackend::daemonStopped() {
    qDebug() << Q_FUNC_INFO;
    _initDaemonState();
    emit daemonRunningChanged();
    emit activeChanged();
}

void
QmlBackend::setMatchPhrase(const QString &matchPhrase) {
    qDebug() << Q_FUNC_INFO << "Set active" << matchPhrase;
    _controlClient->setMatchPhrase(matchPhrase);
}

void
QmlBackend::matchPhraseChanged(const QString &matchPhrase) {
    if (matchPhrase != _matchPhrase) {
        _matchPhrase = matchPhrase;
        qDebug() << Q_FUNC_INFO << "Emitting matchPhraseChanged" << matchPhrase;
        emit matchPhraseChanged();
    }
}
