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
#include "displayalarm.h"

#include <QProcess>
#include <QDebug>

#define TIMEDCLIENT "/usr/bin/timedclient-qt5"

DisplayAlarm::DisplayAlarm()
{
}

bool
DisplayAlarm::activate() const {
    QStringList args;

    args << "-bTITLE=button0"
         << "-eAPPLICATION=FindMyJolla;TITLE=Find My Jolla;ticker=0";

    if (!QProcess::startDetached(TIMEDCLIENT, args)) {
        qCritical() << "Failed starting " << TIMEDCLIENT;
        return false;
    }

    return true;
}
