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

#include "abstractdatatype.h"
#include "modules/bibleVerse/verse.h"

#include <QDebug>
#include <QRegularExpression>

AbstractDataType::AbstractDataType(const EModIds argType) noexcept :
    type{argType}
{
}

AbstractDataTypeSharedPtr AbstractDataType::ParseFromData(
        const EModIds argMod, const ll::Level argLevel,
        const QString &argIdentifier, const QByteArray &argData)
{
    if (argMod == EModIds::BibleVerse) {
        // Retrieve the index of the book and its info structure
        const QStringRef bookNum{argIdentifier.leftRef(2)};
        bool convSucc = false;
        unsigned int bookIdx = bookNum.toUInt(&convSucc) - 1u;
        if (convSucc == false) {
            qWarning() << "Book index could not be extracted from identifier";
            return AbstractDataTypeSharedPtr{};
        }
        BookTitleInfoPtr bookTitleInfoPtr = &(bookTitles.at(bookIdx));

        // Split everything after the technical title to get chapter and verse
        const QString technicalTitle{bookTitles.at(bookIdx).technicalTitle};
        const QStringList splitRes{argIdentifier.mid(technicalTitle.size() + 1)
                                   .split(QRegularExpression{"[-]"})};
        if (splitRes.size() != 2) {
            qWarning() << "Invalid identifier passed into Verse parser";
            return AbstractDataTypeSharedPtr{};
        }

        convSucc = false;
        const unsigned short chapterNo{splitRes.at(0).toUShort(&convSucc)};
        if (convSucc == false) {
            qWarning() << "Failed to parse chapter number for Verse";
            return AbstractDataTypeSharedPtr{};
        }
        convSucc = false;
        const unsigned short verseNo{splitRes.at(1).toUShort(&convSucc)};
        if (convSucc == false) {
            qWarning() << "Failed to parse verse number for Verse";
            return AbstractDataTypeSharedPtr{};
        }
        const QString verseText{QString{argData}};

        return std::make_shared<Verse>(bookTitleInfoPtr, chapterNo, verseNo,
                                          argData, argLevel);
    } else {
        qWarning() << "Invalid module passed for data type parsing";
        return AbstractDataTypeSharedPtr{};
    }
    return AbstractDataTypeSharedPtr{};
}
