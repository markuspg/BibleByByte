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

#ifndef ABSTRACTDATATYPE_H
#define ABSTRACTDATATYPE_H

#include "global_definitions.h"
#include "modules/helpers.h"

#include <QMetaType>

#include <memory>

class AbstractDataType;
using AbstractDataTypeSharedPtr = std::shared_ptr<AbstractDataType>;

class AbstractDataType
{
public:
    explicit AbstractDataType(EModIds argType) noexcept;
    virtual ~AbstractDataType() = default;

    virtual QByteArray GetData() const = 0;
    virtual QString GetIdentifier() const = 0;
    inline EModIds GetType() const noexcept;
    static AbstractDataTypeSharedPtr ParseFromData(EModIds argMod,
                                                   ll::Level argLevel,
                                                   const QString &argIdentifier,
                                                   const QByteArray &argData);

private:
    const EModIds type;
};
Q_DECLARE_METATYPE(AbstractDataTypeSharedPtr)

EModIds AbstractDataType::GetType() const noexcept { return type; }

#endif // ABSTRACTDATATYPE_H
