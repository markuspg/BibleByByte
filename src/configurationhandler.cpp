/*
 * Copyright 2019-2020 Markus Prasser
 *
 * This file is part of BibleByByte.
 *
 *  BibleByByte is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  BibleByByte is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with BibleByByte.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "configurationhandler.h"

#include <QDebug>
#include <QFile>
#include <QStandardPaths>

#include <algorithm>
#include <type_traits>

// ConfOpt ---------------------------------------------------------------------

struct ConfOpt {
    constexpr ConfOpt(ConfigurationHandler::EConfigValues argEnumVal,
                      const char* argName, const char* argDefaultVal) noexcept :
        defaultVal{argDefaultVal}, enumVal{argEnumVal}, name{argName}
    {
    }

    const char* const defaultVal = nullptr;
    const ConfigurationHandler::EConfigValues enumVal
        = ConfigurationHandler::EConfigValues::AAA_INVALID;
    const char* const name = nullptr;
};

constexpr std::array<ConfOpt, 2> configOpts{
    ConfOpt{ConfigurationHandler::EConfigValues::ACTIVE_MODULES,
            "active_modules", "BibleVerse"},
    ConfOpt{ConfigurationHandler::EConfigValues::STORAGE_BACKEND,
            "storage_backend", "file"}};

// ConfigurationHandler --------------------------------------------------------

ConfigurationHandler::ConfigurationHandler(QObject* const argParent) :
    QObject{argParent}
{
    if (ReadConfigFile() == false) {
        throw ConfigException{};
    }
}

QString
    ConfigurationHandler::GetConfigValue(const EConfigValues argConfVal) const
{
    // find the configuration option belonging to the enum value
    const auto res = std::find_if(configOpts.cbegin(), configOpts.cend(),
                                  [argConfVal](const ConfOpt& argOptData) {
                                      return argOptData.enumVal == argConfVal;
                                  });

    // throw an exception if the enum value could not be found
    if (res == configOpts.cend()) {
        qWarning() << "Queried config option"
                   << static_cast<std::underlying_type<EConfigValues>::type>(
                          argConfVal)
                   << "seems not to exist";
        throw ConfigException{};
    }

    return optsAndVals.at(res->name);
}

bool ConfigurationHandler::ReadConfigFile()
{
    const QString configFilePath{
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/"
        + configFileName};

    QFile confFile{configFilePath};
    // create the configuration file if it does not exist yet
    if (confFile.exists() == false) {
        if (confFile.open(QIODevice::Text | QIODevice::WriteOnly) == false) {
            qWarning() << "Failed to create and open new configuration file";
            return false;
        }
        confFile.close();
    }

    // attempt to open the configuration file
    if (confFile.open(QIODevice::ReadOnly | QIODevice::Text) == false) {
        qWarning() << "Failed to open configuration file for reading";
        return false;
    }

    qint64 readBytes = 0;
    // iterate over all lines of the file until it's read in its entirety
    while (readBytes < confFile.size()) {
        QByteArray buf(65536, '\0');

        // read the next line
        const auto nowReadBytes = confFile.readLine(buf.data(), buf.size());
        if (nowReadBytes == -1) {
            qWarning() << "Failed to read line from configuration file";
            return false;
        }
        readBytes += nowReadBytes;

        // interprete the line
        const QString confFileLine{QString{buf}.trimmed()};

        // skip empty lines
        if (confFileLine.isEmpty() == true) {
            continue;
        }

        // error if the line does not contain a '=' and is not a comment
        if ((confFileLine.contains('=') == false) && (confFileLine[0] != '#')) {
            qWarning() << "Malformed line";
            return false;
        }

        // skip empty lines
        if (confFileLine[0] == '#') {
            continue;
        }

        optsAndVals.emplace(confFileLine.left(confFileLine.indexOf('=')),
                            confFileLine.right(confFileLine.indexOf('=')));
    }

    // add default values to the map for missing options
    for (const auto& optData : configOpts) {
        if (optsAndVals.find(optData.name) == optsAndVals.end()) {
            optsAndVals.emplace(optData.name, optData.defaultVal);
        }
    }

    return true;
}

void ConfigurationHandler::SetConfigValue(const EConfigValues argConfVal,
                                          const QString& argVal)
{
    // find the configuration option belonging to the enum value
    const auto res = std::find_if(configOpts.cbegin(), configOpts.cend(),
                                  [argConfVal](const ConfOpt& argOptData) {
                                      return argOptData.enumVal == argConfVal;
                                  });

    // throw an exception if the enum value could not be found
    if (res == configOpts.cend()) {
        qWarning() << "Config option"
                   << static_cast<std::underlying_type<EConfigValues>::type>(
                          argConfVal)
                   << "seems not to exist";
        throw ConfigException{};
    }

    if (optsAndVals.at(res->name) != argVal) {
        // update the configuration option's value if it got changed
        optsAndVals.at(res->name) = argVal;
        configMustBeSynced = true;
    }
}

bool ConfigurationHandler::SyncConfiguration() { return false; }

// ConfigurationHandler::ConfigException ---------------------------------------

ConfigurationHandler::ConfigException*
    ConfigurationHandler::ConfigException::clone() const
{
    return new ConfigException{*this};
}

void ConfigurationHandler::ConfigException::raise() const { throw *this; }
