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

#ifndef SONGVERSE_H
#define SONGVERSE_H

#include "../../abstractdatatype.h"

#include <limits>

#include <QString>

class SongVerse : public AbstractDataType
{
public:
    SongVerse(const QString &argSongName, unsigned short argSongVerseNo,
              const QString &argSongVerseText);

    QByteArray GetData() const override { return songVerseText.toUtf8(); }
    QString GetIdentifier() const override;
    QString GetSongName() const { return songName; }
    unsigned short GetVerseNo() const noexcept { return songVerseNo; }
    QString GetVerseText() const { return songVerseText; }

private:
    const QString songName;
    const unsigned int songVerseNo = std::numeric_limits<unsigned int>::max();
    const QString songVerseText;
};

#endif // SONGVERSE_H
