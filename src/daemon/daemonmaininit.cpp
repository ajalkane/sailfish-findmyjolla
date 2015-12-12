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
#include <QtQuick>
#include <QtDebug>
#include <QCoreApplication>

#include "daemonmaininit.h"
#include "messagelistener.h"
#include "displayalarm.h"
#include "preferences.h"
#include "controlinterface.h"
#include "configuration.h"

int
DaemonMainInit::main(int argc, char *argv[]) {
    qDebug() << Q_FUNC_INFO << "Starting Find My Jolla daemon";

    QCoreApplication app(argc, argv);

    Preferences preferences;
    Configuration::readPreferences(preferences);
    ControlInterface interface(&preferences);

    if (interface.init()) {
        fprintf(stderr, "Exiting\n");
        return -1;
    }

    QScopedPointer<DisplayAlarm> displayAlarm(new DisplayAlarm);
    QScopedPointer<MessageListener> messageListener(new MessageListener(&preferences, displayAlarm.data()));

    return app.exec();
}
