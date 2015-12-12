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
#include <sailfishapp.h>

#include "appmaininit.h"

 #include "controlclient.h"
 #include "qmlbackend.h"

#ifdef JOLLA_STORE_CRIPPLED
#include "processcontrol.h"
#define DAEMON_PATH "/usr/bin/harbour-findjolla -d"
#endif

int
AppMainInit::main(int argc, char *argv[]) {
#ifdef JOLLA_STORE_CRIPPLED
    ProcessControl daemonControl(DAEMON_PATH);
    daemonControl.startIfNotRunning();
#endif

    qDebug() << Q_FUNC_INFO << "Starting app";
    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
    QScopedPointer<QQuickView> view(SailfishApp::createView());

    ControlClient controlClient;
    QmlBackend qmlBackend(&controlClient);

    view->rootContext()->setContextProperty("backend", &qmlBackend);
//    view->setSource(SailfishApp::pathTo("qml/app/harbour-ringingrestorer.qml"));
    view->setSource(SailfishApp::pathTo("qml/findjolla.qml"));

    view->show();
    return app->exec();
}
