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

#include "verse.h"

#include <QDebug>
#include <QObject>

Verse::Verse(const int argBookIdx, const unsigned short argChapterNo,
             const unsigned short argVerseNo, const QString& argText,
             const ll::Level argCurrLvl) :
    AbstractDataType{EModIds::BibleVerse},
    book{&(bookTitles.at(static_cast<BookTitleInfos::size_type>(argBookIdx)))},
    chapterNo{argChapterNo},
    currLvl{argCurrLvl},
    verseNo{argVerseNo},
    text{argText}
{
}

Verse::Verse(const BookTitleInfoPtr argBook, const unsigned short argChapterNo,
             const unsigned short argVerseNo, const QString& argText,
             const ll::Level argCurrLvl) :
    AbstractDataType{EModIds::BibleVerse},
    book{argBook},
    chapterNo{argChapterNo},
    currLvl{argCurrLvl},
    verseNo{argVerseNo},
    text{argText}
{
}

QString Verse::GetBook() const
{
    if (book == nullptr) {
        qWarning() << "Text of not initialized Verse instance got requested";
        return QString{};
    }
    return QObject::tr(book->prettyTitle);
}

QByteArray Verse::GetData() const { return text.toUtf8(); }

QString Verse::GetIdentifier() const
{
    return QString{book->technicalTitle} + "_" + QString::number(chapterNo)
           + "-" + QString::number(verseNo);
}
