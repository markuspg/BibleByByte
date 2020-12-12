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

#ifndef BBB_BOOKENUM_H
#define BBB_BOOKENUM_H

#include <QMetaType>

enum class EBibleBook : unsigned int {
    Gen,
    Ex,
    Lev,
    Num,
    Deut,
    Josh,
    Judg,
    Ruth,
    Frst_Sam,
    Scnd_Sam,
    Frst_Kings,
    Scnd_Kings,
    Frst_Chron,
    Scnd_Chron,
    Ezra,
    Neh,
    Est,
    Job,
    Ps,
    Prov,
    Eccles,
    Song,
    Isa,
    Jer,
    Lam,
    Ezek,
    Dan,
    Hos,
    Joel,
    Amos,
    Obad,
    Jonah,
    Mic,
    Nah,
    Hab,
    Zeph,
    Hag,
    Zech,
    Mal,
    Matt,
    Mark,
    Luke,
    John,
    Acts,
    Rom,
    Frst_Cor,
    Scnd_Cor,
    Gal,
    Eph,
    Phil,
    Col,
    Frst_Thess,
    Scnd_Thess,
    Frst_Tim,
    Scnd_Tim,
    Titus,
    Philem,
    Heb,
    James,
    Frst_Pet,
    Scnd_Pet,
    Frst_John,
    Scnd_John,
    Thrd_John,
    Jude,
    Rev,

    BOOK_QTY
};
Q_DECLARE_METATYPE(EBibleBook)

#endif // BBB_BOOKENUM_H
