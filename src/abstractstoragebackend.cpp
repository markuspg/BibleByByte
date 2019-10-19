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

#include "abstractstoragebackend.h"

IOException* IOException::clone() const
{
    return new IOException{*this};
}

void IOException::raise() const
{
    throw *this;
}

AbstractStorageBackend::AbstractStorageBackend(QObject *const argParent) :
    QObject{argParent}
{
}

void AbstractStorageBackend::MoveDataOneLevelDown(AbstractDataTypeSharedPtr argData)
{
    const MoveResult res{MoveData(argData, false)};
    if (res.errorOccurred == true) {
        emit DataMovingFailed();
        return;
    }

    if (res.moveHappened == true) {
        cache.ItemGotMoved(argData->GetType(), res.prevLevel,
                           res.newLevel);
    }

    RetrieveRandomData();
}

void AbstractStorageBackend::MoveDataOneLevelUp(AbstractDataTypeSharedPtr argData)
{
    const MoveResult res{MoveData(argData, true)};
    if (res.errorOccurred == true) {
        emit DataMovingFailed();
        return;
    }

    if (res.moveHappened == true) {
        cache.ItemGotMoved(argData->GetType(), res.prevLevel,
                           res.newLevel);
    }

    RetrieveRandomData();
}

void AbstractStorageBackend::SaveData(const AbstractDataTypeSharedPtr &argData)
{
    if (SaveDataInternally(argData) == true) {
        cache.InsertNewItem(argData->GetType());
        // emit a new item if this is the first ever saved data item
        if (Q_UNLIKELY(noItemSavedYet == true)) {
            // if this was the first saved item, the cache should be '1' now
            if (cache.GetTotalStoredItemsQty() == 1) {
                RetrieveRandomData();
            }
            noItemSavedYet = false;
        }
        emit DataSavingSucceeded();
        return;
    }

    emit DataSavingFailed();
}
