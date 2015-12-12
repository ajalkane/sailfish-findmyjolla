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
#include <QSettings>
#include <QUuid>

#include "configuration.h"

#define APP "harbour-FindMyJolla"

Configuration::Configuration()
{
}

void
Configuration::writePreferences(const Preferences &p) {
    qDebug() << Q_FUNC_INFO;

    // So wrong by the API specifications, but so right by the end results (no, I don't like doing it this way)
    QSettings s(APP, "preferences");
    s.clear();
    s.setValue("isActive", p.isActive);
    s.setValue("matchPhrase", p.matchPhrase);
}

void
Configuration::readPreferences(Preferences &p) {
    // So wrong by the API specifications, but so right by the end results (no, I don't like doing it this way)
    QSettings s(APP, "preferences");
    p.isActive = s.value("isActive", true).toBool();
    p.matchPhrase = s.value("matchPhrase").toString();
}
