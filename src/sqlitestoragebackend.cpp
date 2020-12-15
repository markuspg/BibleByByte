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

#include "sqlitestoragebackend.h"

SqliteStorageBackend::SqliteStorageBackend(QObject* const argParent) :
    AbstractStorageBackend{argParent}
{
}

AbstractStorageBackend::MoveResult
    SqliteStorageBackend::MoveData(const AbstractDataTypeSharedPtr& argData,
                                   const bool argMoveLevelUp)
{
    Q_UNUSED(argData)
    Q_UNUSED(argMoveLevelUp)

    return MoveResult{true, false, std::numeric_limits<ll::Level>::max(),
                      std::numeric_limits<ll::Level>::max()};
}

void SqliteStorageBackend::RetrieveRandomData() { emit DataRetrievalFailed(); }

bool SqliteStorageBackend::SaveDataInternally(
    const AbstractDataTypeSharedPtr& argData)
{
    Q_UNUSED(argData)

    return false;
}

bool SqliteStorageBackend::UpdateCache() { return false; }
