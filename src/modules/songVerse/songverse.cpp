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

#include "songverse.h"

SongVerse::SongVerse(const QString& argSongName,
                     const unsigned short argSongVerseNo,
                     const QString& argSongVerseText) :
    AbstractDataType{EModIds::SongVerse},
    songName{argSongName},
    songVerseNo{argSongVerseNo},
    songVerseText{argSongVerseText}
{
}

QString SongVerse::GetIdentifier() const
{
    return songName + "_" + QString::number(songVerseNo);
}
