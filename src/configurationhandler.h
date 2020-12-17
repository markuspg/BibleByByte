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

#ifndef BBB_CONFIGURATIONHANDLER_H
#define BBB_CONFIGURATIONHANDLER_H

#include "singleton.h"

#include <QObject>

class ConfigurationHandler :
    public QObject,
    public BibleByByte::Singleton<ConfigurationHandler>
{
    Q_OBJECT

public:
    /*!
     * \brief Enumeration of all available configuration options
     */
    enum class EConfigOptions {
        //! Invalid enumerator
        AAA_INVALID,

        //! A comma separated list of the modules which shall be enabled
        ACTIVE_MODULES,
        //! The storage backend which shall be utilized
        STORAGE_BACKEND,
    };
    using ECV = EConfigOptions;

    explicit ConfigurationHandler(QObject* argParent = nullptr);

    QString GetConfigValue(EConfigOptions argConfOpt) const;
    void SetConfigValue(EConfigOptions argConfVal, const QString& argVal);
    bool SyncConfiguration();

private:
    /*!
     * \brief Exception which is being thrown on internal errors of the
     * ConfigurationHandler class
     */
    class ConfigException : public QException
    {
        ConfigException* clone() const override;
        void raise() const override;
    };

    bool ReadConfigFile();

    //! The path where the configuration file is being stored
    const QString configFilePath;
    //! true if the cached options have been updated and must be synced
    bool configMustBeSynced = false;
    //! Map of the cached configuration options and their values
    std::map<QString, QString> optsAndVals;
};

#endif // BBB_CONFIGURATIONHANDLER_H
