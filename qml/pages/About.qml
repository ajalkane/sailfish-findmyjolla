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
import QtMultimedia 5.0


Page {
    id: page

    SilicaFlickable {
        anchors.fill: parent

        contentHeight: column.height

        Column {
            id: column

            width: page.width
            spacing: Theme.paddingLarge

            PageHeader {
                //: Note to translators: application name should not be translated
                title: qsTr("About Find My Jolla")
            }

            Label {
                text: qsTr("(c) ajalkane & qt_junkie 2015")
                width: parent.width
            }

            Label {
                text: qsTr(
                    '<a href="https://github.com/ajalkane/sailfish-findmyjolla">Released under GPLv3</a>'
                    + '<p>'
                    + '<a href="https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=499LF83BBX5RY">'
                    + 'Please donate if you like this application</a>'
                )
                textFormat: Text.RichText
                wrapMode: Text.WordWrap
                width: parent.width
                font.pixelSize: Theme.fontSizeSmall

                onLinkActivated: {
                    Qt.openUrlExternally(link)
                }
            }
        }
    }
}


