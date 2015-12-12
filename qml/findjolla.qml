/**********************************************************************
 * Copyright 2015 ajalkane & qt_junkie
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

import QtQuick 2.0
import Sailfish.Silica 1.0
import "pages"

ApplicationWindow
{
    id: root

//    property string matchTo

    initialPage: Component {
        FirstPage {
            onMatchToChanged: {
                console.log("Match to changed: " + matchTo)
                backend.matchPhrase = matchTo
//                root.matchTo = matchTo
            }
        }
    }
    cover: Qt.resolvedUrl("cover/CoverPage.qml")

//    Connections {
//        target: messageListener
//        onMessageReceived: {
//            console.log("Received message" + message)
//            var matchTo = root.matchTo.trim()
//            console.log("Match to " + matchTo)

//            if (message.trim() === matchTo) {
//                console.log("Trying to activate alarm")
//                displayAlarm.activate()
//            }
//        }
//    }

}


