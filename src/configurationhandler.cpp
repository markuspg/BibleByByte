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

/*!
 * \brief Struct representing relevant data of a configuration option
 */
struct ConfOpt {
    constexpr ConfOpt(ConfigurationHandler::EConfigOptions argEnumVal,
                      const char* argName, const char* argDefaultVal) noexcept :
        defaultVal{argDefaultVal}, enumVal{argEnumVal}, name{argName}
    {
    }

    //! The configuration option's default value
    const char* const defaultVal = nullptr;
    //! The enumerator of the configuration option
    const ConfigurationHandler::EConfigOptions enumVal
        = ConfigurationHandler::EConfigOptions::AAA_INVALID;
    //! The name of the configuration option
    const char* const name = nullptr;
};

constexpr std::array<ConfOpt, 2> configOpts{
    ConfOpt{ConfigurationHandler::EConfigOptions::ACTIVE_MODULES,
            "active_modules", "BibleVerse"},
    ConfOpt{ConfigurationHandler::EConfigOptions::STORAGE_BACKEND,
            "storage_backend", "file"}};

// ConfigurationHandler --------------------------------------------------------

/*!
 * \brief Initialize a new ConfigurationHandler by reading the config file
 *
 * \param[in] argParent The parent QObject of the new instance
 * \exception ConfigException If reading the configuration file fails
 */
ConfigurationHandler::ConfigurationHandler(QObject* const argParent) :
    QObject{argParent},
    configFilePath{
        QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)
        + "/config.txt"}
{
    if (ReadConfigFile() == false) {
        throw ConfigException{};
    }
}

/*!
 * \brief Retrieve the value of a particular configuration option
 *
 * \param[in] argConfOpt An enumerator denoting the option whose value shall be
 * queried
 * \return The value of the configuration option if it could be retrieved
 *
 * \exception ConfigException If the option could not be found
 * \exception std::out_of_range If there exists no value for the option
 */
QString
    ConfigurationHandler::GetConfigValue(const EConfigOptions argConfOpt) const
{
    // find the configuration option belonging to the enum value
    const auto res = std::find_if(configOpts.cbegin(), configOpts.cend(),
                                  [&argConfOpt](const ConfOpt& argOptData) {
                                      return argOptData.enumVal == argConfOpt;
                                  });

    // throw an exception if the enum value could not be found
    if (res == configOpts.cend()) {
        qWarning() << "Queried config option"
                   << static_cast<std::underlying_type_t<EConfigOptions>>(
                          argConfOpt)
                   << "seems not to exist";
        throw ConfigException{};
    }

    return optsAndVals.at(res->name);
}

/*!
 * \brief Read the configuration file and update the internal cache
 * \return true on success or false otherwise
 */
bool ConfigurationHandler::ReadConfigFile()
{
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

/*!
 * \brief Set the value of a particular configuration option
 *
 * \param[in] argConfOpt An enumerator denoting the option whose value shall be
 * queried
 * \param[in] argVal The value the configuration option shall be set to
 *
 * \exception ConfigException If the option could not be found
 */
void ConfigurationHandler::SetConfigValue(const EConfigOptions argConfVal,
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
                   << static_cast<std::underlying_type<EConfigOptions>::type>(
                          argConfVal)
                   << "seems not to exist";
        throw ConfigException{};
    }

    if (optsAndVals[res->name] != argVal) {
        // update the configuration option's value if it got changed
        optsAndVals.at(res->name) = argVal;
        configMustBeSynced = true;
    }
}

/*!
 * \brief Force the cached configuration values being written to storage
 *
 * This function is not implemented yet and returns false always.
 *
 * \return Always false
 */
bool ConfigurationHandler::SyncConfiguration() { return false; }

// ConfigurationHandler::ConfigException ---------------------------------------

ConfigurationHandler::ConfigException*
    ConfigurationHandler::ConfigException::clone() const
{
    return new ConfigException{*this};
}

void ConfigurationHandler::ConfigException::raise() const { throw *this; }
