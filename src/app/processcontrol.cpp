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
#include <QProcess>
#include <QThread>

#include "processcontrol.h"

ProcessControl::ProcessControl(QString processNameMatch, QObject *parent)
    : QObject(parent), _pathToBinary(processNameMatch)
{
}

bool
ProcessControl::startIfNotRunning() {
    qDebug() << Q_FUNC_INFO;
    if (!isRunning()) {
        bool returnValue = start();
        if (true) {
            qDebug() << Q_FUNC_INFO << "Sleeping a second to give daemon time to start";
            QThread::sleep(1);
        }
        return returnValue;
    }
    return true;
}

bool
ProcessControl::isRunning() {
    qDebug() << Q_FUNC_INFO;
    QStringList args;
    args << "-f" << _pathToBinaryMatch();
    int ret = QProcess::execute("pgrep", args);
    qDebug() << Q_FUNC_INFO << "return value " << ret << "which means running " << (ret == 0 ? true : false);
    return ret == 0 ? true : false;
}

bool
ProcessControl::start() {
    qDebug() << Q_FUNC_INFO;
    bool ret = QProcess::startDetached(_pathToBinary);
    qDebug() << Q_FUNC_INFO << "success " << ret;
    return ret;
}
