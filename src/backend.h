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

#ifndef BBB_BACKEND_H
#define BBB_BACKEND_H

#ifdef QML_APP
#include "abstractdatatype.h"
#endif // QML_APP

#include <QObject>

class AbstractStorageBackend;
class ConfigurationHandler;

class Backend : public QObject
{
    Q_OBJECT
#ifdef QML_APP
    Q_PROPERTY(int savedVerses READ GetSavedVerses() NOTIFY SavedVersesChanged)
    Q_PROPERTY(QString checkedBook READ GetCheckedBook() NOTIFY CheckedBookChanged)
    Q_PROPERTY(int checkedChapterNo READ GetCheckedChapterNo() NOTIFY CheckedChapterNoChanged)
    Q_PROPERTY(int checkedVerseNo READ GetCheckedVerseNo() NOTIFY CheckedVerseNoChanged)
    Q_PROPERTY(QString checkedVerseText READ GetCheckedVerseText() NOTIFY CheckedVerseTextChanged)
#endif // QML_APP

public:
    Backend(QObject *argParent = nullptr);

#ifdef QML_APP
    QString GetCheckedBook() const { return currCheckedBook; }
    int GetCheckedChapterNo() const noexcept { return currCheckedChapterNo; }
    int GetCheckedVerseNo() const noexcept { return currCheckedVerseNo; }
    QString GetCheckedVerseText() const { return currCheckedVerseText; }
#endif // QML_APP
    ConfigurationHandler* GetConfigHndlr() const noexcept { return configHndlr; }
#ifdef QML_APP
    int GetSavedVerses() const noexcept { return savedVersesQty; }
#endif // QML_APP
    AbstractStorageBackend* GetStorageBcknd() const noexcept { return storageBackend; }
    void Initialize();
#ifdef QML_APP
    Q_INVOKABLE void saveVerse(int argBookIdx, int argChapterNo,
                               int argVerseNo, const QString &argVerseText);

public slots:
    void requestNextVerse();
    void verseAnsweredRightly();
    void verseAnsweredWrongly();

signals:
    void CheckedBookChanged();
    void CheckedChapterNoChanged();
    void CheckedVerseNoChanged();
    void CheckedVerseTextChanged();
    void SavedVersesChanged();
#endif // QML_APP

private:
    ConfigurationHandler *const configHndlr = nullptr;
#ifdef QML_APP
    QString currCheckedBook;
    int currCheckedChapterNo = 0;
    int currCheckedVerseNo = 0;
    QString currCheckedVerseText;
    AbstractDataTypeSharedPtr currDataItem;
    unsigned int savedVersesQty = 0u;
#endif // QML_APP
    AbstractStorageBackend *const storageBackend = nullptr;

#ifdef QML_APP
private slots:
    void RetrieveNewVerse(const AbstractDataTypeSharedPtr &argDataPtr);
    void VerseGotSuccessfullySaved();
#endif // QML_APP
};

#endif // BBB_BACKEND_H
