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

#include "backend.h"
#include "configurationhandler.h"
#include "filestoragebackend.h"
#include "sqlitestoragebackend.h"
#ifdef QML_APP
#include "modules/bibleVerse/verse.h"

#include <QDebug>
#endif // QML_APP

Backend::Backend(QObject *const argParent) :
    QObject(argParent),
    configHndlr(new ConfigurationHandler),
    storageBackend(configHndlr->GetConfigValue(
                       ConfigurationHandler::ECV::STORAGE_BACKEND) == "file"
                   ? reinterpret_cast<AbstractStorageBackend*>(new FileStorageBackend)
                   : reinterpret_cast<AbstractStorageBackend*>(new SqliteStorageBackend))
{
    configHndlr->setParent(this);
    storageBackend->setParent(this);

#ifdef QML_APP
    connect(storageBackend, &AbstractStorageBackend::DataSavingSucceeded,
            this, &Backend::VerseGotSuccessfullySaved);
    connect(storageBackend, &AbstractStorageBackend::DataRetrievalSucceeded,
            this, &Backend::RetrieveNewVerse);
#endif // QML_APP
}

void Backend::Initialize()
{
    storageBackend->RetrieveRandomData();
}

#ifdef QML_APP
void Backend::requestNextVerse()
{
    storageBackend->RetrieveRandomData();
}

void Backend::RetrieveNewVerse(const AbstractDataTypeSharedPtr &argDataPtr)
{
    currDataItem = argDataPtr;
    const auto ptr = std::dynamic_pointer_cast<Verse>(currDataItem);
    if (ptr) {
        const auto tmpBook = ptr->GetBook();
        if (tmpBook != currCheckedBook) {
            currCheckedBook = tmpBook;
            emit CheckedBookChanged();
        }
        const auto tmpChapterNo = ptr->GetChapterNo();
        if (tmpChapterNo != currCheckedChapterNo) {
            currCheckedChapterNo = tmpChapterNo;
            emit CheckedChapterNoChanged();
        }
        const auto tmpVerseNo = ptr->GetVerseNo();
        if (tmpVerseNo != currCheckedVerseNo) {
            currCheckedVerseNo = tmpVerseNo;
            emit CheckedVerseNoChanged();
        }
        const auto tmpVerseText = ptr->GetText();
        if (tmpVerseText != currCheckedVerseText) {
            currCheckedVerseText = tmpVerseText;
            emit CheckedVerseTextChanged();
        }
    }
}

void Backend::saveVerse(const int argBookIdx, const int argChapterNo,
                        const int argVerseNo, const QString &argVerseText)
{
    // Filter invalid bible book indices
    if (bookTitles.size() <= static_cast<unsigned int>(argBookIdx)) {
        qWarning() << "Invalid book index given:" << argBookIdx;
    }

    // Filter invalid chapter and verse numbers
    if (((argChapterNo < 1) || argChapterNo > 150)
            || ((argVerseNo < 1) || argVerseNo > 176)) {
        qWarning() << "Invalid chapter or verse number given:"
                   << argChapterNo << argVerseNo;
        return;
    }

    storageBackend->SaveData(
                AbstractDataTypeSharedPtr{
                    new Verse(argBookIdx, argChapterNo,
                              argVerseNo, argVerseText, 0)});
}

void Backend::VerseGotSuccessfullySaved()
{
    ++savedVersesQty;
    emit SavedVersesChanged();
}

void Backend::verseAnsweredRightly()
{
    storageBackend->MoveDataOneLevelUp(currDataItem);
}

void Backend::verseAnsweredWrongly()
{
    storageBackend->MoveDataOneLevelDown(currDataItem);
}
#endif // QML_APP
