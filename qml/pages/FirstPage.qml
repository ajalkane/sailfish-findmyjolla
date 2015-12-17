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

Page {
    id: page

    property alias matchTo : messageMatch.text

    // To enable PullDownMenu, place our content in a SilicaFlickable
    SilicaFlickable {
        anchors.fill: parent

        // PullDownMenu and PushUpMenu must be declared in SilicaFlickable, SilicaListView or SilicaGridView
        PullDownMenu {
            MenuItem {
                text: qsTr("About")
                onClicked: pageStack.push(Qt.resolvedUrl("About.qml"))
            }
        }

        // Tell SilicaFlickable the height of its content.
        contentHeight: column.height

        // Place our content in a Column.  The PageHeader is always placed at the top
        // of the page, followed by our content.
        Column {
            id: column

            width: page.width
            spacing: Theme.paddingLarge

            PageHeader {
                //: Note to translators: application name should not be translated
                title: qsTr("Find My Jolla")
            }

            Label {
                text: qsTr("When following message (SMS, IM) is received, trigger alarm")
                width: parent.width
                wrapMode:  Text.WordWrap
            }

            TextField {
                id: messageMatch
                placeholderText: qsTr("Message to match")
                width: parent.width
                onTextChanged: matchToChanged(text)
                Component.onCompleted: {
                    text = backend.matchPhrase
                }
            }

            Label {
                text: qsTr("You can close this application and alarm will work. If you reboot phone, you will need to start this application again for background process to be started.")

                wrapMode: Text.WordWrap
                width: parent.width
                font.pixelSize: Theme.fontSizeSmall
            }
        }
    }
}


