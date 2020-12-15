/*
 * Copyright 2019 Markus Prasser
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

#ifndef BBB_ABSTRACTDATATYPE_H
#define BBB_ABSTRACTDATATYPE_H

#include "global_definitions.h"
#include "modules/helpers.h"

#include <QMetaType>

#include <memory>

class AbstractDataType;
using AbstractDataTypeSharedPtr = std::shared_ptr<AbstractDataType>;

/*!
 * \brief The AbstractDataType class is the base class for all classes
 * responsible for representing a module's data items
 */
class AbstractDataType
{
public:
    virtual ~AbstractDataType() = default;

    /*!
     * \brief Retrieve the instance's data converted to a byte array
     * \return The data represented by the instance convered to a byte array
     */
    virtual QByteArray GetData() const = 0;
    /*!
     * \brief Retrieve a unique identifier representing the instance's data
     *
     * The identifier should be able to uniquely identify the instance. For an
     * instance of an hypothetical "Person" class this could be something like
     * "forename_lastname_<social_security_id>". The identifier should contain
     * no special characters (especially no '/' character) since it might be
     * used as file name by some storage backends.
     *
     * \return A unique identifier representing the instance's data
     */
    virtual QString GetIdentifier() const = 0;
    /*!
     * \brief Retrieve the id of the module the represented data belongs to
     * \return The module id the represented data belongs to
     */
    inline EModIds GetType() const noexcept;
    static AbstractDataTypeSharedPtr ParseFromData(EModIds argMod,
                                                   ll::Level argLevel,
                                                   const QString& argIdentifier,
                                                   const QByteArray& argData);

protected:
    explicit AbstractDataType(EModIds argType) noexcept;

private:
    const EModIds type = EModIds::INVALID;
};
Q_DECLARE_METATYPE(AbstractDataTypeSharedPtr)

EModIds AbstractDataType::GetType() const noexcept { return type; }

#endif // BBB_ABSTRACTDATATYPE_H
