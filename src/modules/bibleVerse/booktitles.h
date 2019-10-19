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

#ifndef BOOKTITLES_H
#define BOOKTITLES_H

#include "bookenum.h"

#include <QtGlobal>

#include <array>

struct BookTitleInfo {
    constexpr BookTitleInfo() = default;
    constexpr BookTitleInfo(EBibleBook argEnumVal,
                            const char * const argPrettyTitle,
                            const char * const argAbbreviation,
                            const char * const argTechnicalTitle) :
        enumVal(argEnumVal),
        prettyTitle(argPrettyTitle),
        abbreviation(argAbbreviation),
        technicalTitle(argTechnicalTitle)
    {
    }

    const EBibleBook enumVal
        = static_cast<EBibleBook>(
            std::numeric_limits<std::underlying_type<EBibleBook>::type>::max());
    const char * const prettyTitle = nullptr;
    const char * const abbreviation = nullptr;
    const char * const technicalTitle = nullptr;
};
Q_DECLARE_METATYPE(BookTitleInfo)

using BookTitleInfos = std::array<BookTitleInfo, 66>;
static constexpr BookTitleInfos bookTitles{
    BookTitleInfo{EBibleBook::Gen, QT_TR_NOOP("Genesis"),
                  QT_TR_NOOP("Gen."), "01_gen"},
    BookTitleInfo{EBibleBook::Ex, QT_TR_NOOP("Exodus"),
                  QT_TR_NOOP("Ex."), "02_ex"},
    BookTitleInfo{EBibleBook::Lev, QT_TR_NOOP("Leviticus"),
                  QT_TR_NOOP("Lev."), "03_lev"},
    BookTitleInfo{EBibleBook::Num, QT_TR_NOOP("Numbers"),
                  QT_TR_NOOP("Num."), "04_num"},
    BookTitleInfo{EBibleBook::Deut, QT_TR_NOOP("Deuteronomy"),
                  QT_TR_NOOP("Deut."), "05_deut"},
    BookTitleInfo{EBibleBook::Josh, QT_TR_NOOP("Joshua"),
                  QT_TR_NOOP("Josh."), "06_josh"},
    BookTitleInfo{EBibleBook::Judg, QT_TR_NOOP("Judges"),
                  QT_TR_NOOP("Judg."), "07_judg"},
    BookTitleInfo{EBibleBook::Ruth, QT_TR_NOOP("Ruth"),
                  QT_TR_NOOP("Ruth"), "08_ruth"},
    BookTitleInfo{EBibleBook::Frst_Sam, QT_TR_NOOP("1 Samuel"),
                  QT_TR_NOOP("1 Sam."), "09_frst-sam"},
    BookTitleInfo{EBibleBook::Scnd_Sam, QT_TR_NOOP("2 Samuel"),
                  QT_TR_NOOP("2 Sam."), "10_scnd-sam"},
    BookTitleInfo{EBibleBook::Frst_Kings, QT_TR_NOOP("1 Kings"),
                  QT_TR_NOOP("1 Kings"), "11_frst-kings"},
    BookTitleInfo{EBibleBook::Scnd_Kings, QT_TR_NOOP("2 Kings"),
                  QT_TR_NOOP("2 Kings"), "12_scnd-kings"},
    BookTitleInfo{EBibleBook::Frst_Chron, QT_TR_NOOP("1 Chronicles"),
                  QT_TR_NOOP("1 Chron."), "13_frst-chron"},
    BookTitleInfo{EBibleBook::Scnd_Chron, QT_TR_NOOP("2 Chronicles"),
                  QT_TR_NOOP("2 Chron."), "14_scnd-chron"},
    BookTitleInfo{EBibleBook::Ezra, QT_TR_NOOP("Ezra"),
                  QT_TR_NOOP("Ezra"), "15_ezra"},
    BookTitleInfo{EBibleBook::Neh, QT_TR_NOOP("Nehemiah"),
                  QT_TR_NOOP("Neh."), "16_neh"},
    BookTitleInfo{EBibleBook::Est, QT_TR_NOOP("Esther"),
                  QT_TR_NOOP("Est."), "17_est"},
    BookTitleInfo{EBibleBook::Job, QT_TR_NOOP("Job"),
                  QT_TR_NOOP("Job"), "18_job"},
    BookTitleInfo{EBibleBook::Ps, QT_TR_NOOP("Psalms"),
                  QT_TR_NOOP("Ps."), "19_ps"},
    BookTitleInfo{EBibleBook::Prov, QT_TR_NOOP("Proverbs"),
                  QT_TR_NOOP("Prov."), "20_prov"},
    BookTitleInfo{EBibleBook::Eccles, QT_TR_NOOP("Ecclesiastes"),
                  QT_TR_NOOP("Eccles."), "21_eccles"},
    BookTitleInfo{EBibleBook::Song, QT_TR_NOOP("Song of Solomon"),
                  QT_TR_NOOP("Song"), "22_song"},
    BookTitleInfo{EBibleBook::Isa, QT_TR_NOOP("Isaiah"),
                  QT_TR_NOOP("Isa."), "23_isa"},
    BookTitleInfo{EBibleBook::Jer, QT_TR_NOOP("Jeremiah"),
                  QT_TR_NOOP("Jer."), "24_jer"},
    BookTitleInfo{EBibleBook::Lam, QT_TR_NOOP("Lamentations"),
                  QT_TR_NOOP("Lam."), "25_lam"},
    BookTitleInfo{EBibleBook::Ezek, QT_TR_NOOP("Ezekiel"),
                  QT_TR_NOOP("Ezek."), "26_ezek"},
    BookTitleInfo{EBibleBook::Dan, QT_TR_NOOP("Daniel"),
                  QT_TR_NOOP("Dan."), "27_dan"},
    BookTitleInfo{EBibleBook::Hos, QT_TR_NOOP("Hosea"),
                  QT_TR_NOOP("Hos."), "28_hos"},
    BookTitleInfo{EBibleBook::Joel, QT_TR_NOOP("Joel"),
                  QT_TR_NOOP("Joel"), "29_joel"},
    BookTitleInfo{EBibleBook::Amos, QT_TR_NOOP("Amos"),
                  QT_TR_NOOP("Amos"), "30_amos"},
    BookTitleInfo{EBibleBook::Obad, QT_TR_NOOP("Obadiah"),
                  QT_TR_NOOP("Obad."), "31_obad"},
    BookTitleInfo{EBibleBook::Jonah, QT_TR_NOOP("Jonah"),
                  QT_TR_NOOP("Jonah"), "32_jonah"},
    BookTitleInfo{EBibleBook::Mic, QT_TR_NOOP("Micah"),
                  QT_TR_NOOP("Mic."), "33_mic"},
    BookTitleInfo{EBibleBook::Nah, QT_TR_NOOP("Nahum"),
                  QT_TR_NOOP("Nah."), "34_nah"},
    BookTitleInfo{EBibleBook::Hab, QT_TR_NOOP("Habakkuk"),
                  QT_TR_NOOP("Hab."), "35_hab"},
    BookTitleInfo{EBibleBook::Zeph, QT_TR_NOOP("Zephaniah"),
                  QT_TR_NOOP("Zeph."), "36_zeph"},
    BookTitleInfo{EBibleBook::Hag, QT_TR_NOOP("Haggai"),
                  QT_TR_NOOP("Hag."), "37_hag"},
    BookTitleInfo{EBibleBook::Zech, QT_TR_NOOP("Zechariah"),
                  QT_TR_NOOP("Zech."), "38_zech"},
    BookTitleInfo{EBibleBook::Mal, QT_TR_NOOP("Malachi"),
                  QT_TR_NOOP("Mal."), "39_mal"},
    BookTitleInfo{EBibleBook::Matt, QT_TR_NOOP("Matthew"),
                  QT_TR_NOOP("Matt."), "40_matt"},
    BookTitleInfo{EBibleBook::Mark, QT_TR_NOOP("Mark"),
                  QT_TR_NOOP("Mark"), "41_mark"},
    BookTitleInfo{EBibleBook::Luke, QT_TR_NOOP("Luke"),
                  QT_TR_NOOP("Luke"), "42_luke"},
    BookTitleInfo{EBibleBook::John, QT_TR_NOOP("John"),
                  QT_TR_NOOP("John"), "43_john"},
    BookTitleInfo{EBibleBook::Acts, QT_TR_NOOP("Acts"),
                  QT_TR_NOOP("Acts"), "44_acts"},
    BookTitleInfo{EBibleBook::Rom, QT_TR_NOOP("Romans"),
                  QT_TR_NOOP("Rom."), "45_rom"},
    BookTitleInfo{EBibleBook::Frst_Cor, QT_TR_NOOP("1 Corinthians"),
                  QT_TR_NOOP("1 Cor."), "46_frst-cor"},
    BookTitleInfo{EBibleBook::Scnd_Cor, QT_TR_NOOP("2 Corinthians"),
                  QT_TR_NOOP("2 Cor."), "47_scnd-cor"},
    BookTitleInfo{EBibleBook::Gal, QT_TR_NOOP("Galatians"),
                  QT_TR_NOOP("Gal."), "48_gal"},
    BookTitleInfo{EBibleBook::Eph, QT_TR_NOOP("Ephesians"),
                  QT_TR_NOOP("Eph."), "49_eph"},
    BookTitleInfo{EBibleBook::Phil, QT_TR_NOOP("Philippians"),
                  QT_TR_NOOP("Phil."), "50_phil"},
    BookTitleInfo{EBibleBook::Col, QT_TR_NOOP("Colossians"),
                  QT_TR_NOOP("Col."), "51_col"},
    BookTitleInfo{EBibleBook::Frst_Thess, QT_TR_NOOP("1 Thessalonians"),
                  QT_TR_NOOP("1 Thess."), "52_frst-thess"},
    BookTitleInfo{EBibleBook::Scnd_Thess, QT_TR_NOOP("2 Thessalonians"),
                  QT_TR_NOOP("2 Thess."), "53_scnd-thess"},
    BookTitleInfo{EBibleBook::Frst_Tim, QT_TR_NOOP("1 Timothy"),
                  QT_TR_NOOP("1 Tim."), "54_frst-tim"},
    BookTitleInfo{EBibleBook::Scnd_Tim, QT_TR_NOOP("2 Timothy"),
                  QT_TR_NOOP("2 Tim."), "55_scnd-tim"},
    BookTitleInfo{EBibleBook::Titus, QT_TR_NOOP("Titus"),
                  QT_TR_NOOP("Titus"), "56_titus"},
    BookTitleInfo{EBibleBook::Philem, QT_TR_NOOP("Philemon"),
                  QT_TR_NOOP("Philem."), "57_philem"},
    BookTitleInfo{EBibleBook::Heb, QT_TR_NOOP("Hebrews"),
                  QT_TR_NOOP("Heb."), "58_heb"},
    BookTitleInfo{EBibleBook::James, QT_TR_NOOP("James"),
                  QT_TR_NOOP("James"), "59_james"},
    BookTitleInfo{EBibleBook::Frst_Pet, QT_TR_NOOP("1 Peter"),
                  QT_TR_NOOP("1 Pet."), "60_frst-pet"},
    BookTitleInfo{EBibleBook::Scnd_Pet, QT_TR_NOOP("2 Peter"),
                  QT_TR_NOOP("2 Pet."), "61_scnd-pet"},
    BookTitleInfo{EBibleBook::Frst_John, QT_TR_NOOP("1 John"),
                  QT_TR_NOOP("1 John"), "62_frst-john"},
    BookTitleInfo{EBibleBook::Scnd_John, QT_TR_NOOP("2 John"),
                  QT_TR_NOOP("2 John"), "63_scnd-john"},
    BookTitleInfo{EBibleBook::Thrd_John, QT_TR_NOOP("3 John"),
                  QT_TR_NOOP("3 John"), "64_thrd-john"},
    BookTitleInfo{EBibleBook::Jude, QT_TR_NOOP("Jude"),
                  QT_TR_NOOP("Jude"), "65_jude"},
    BookTitleInfo{EBibleBook::Rev, QT_TR_NOOP("Revelation"),
                  QT_TR_NOOP("Rev."), "66_rev"}};
using BookTitleInfoPtr = const BookTitleInfos::value_type*;
Q_DECLARE_METATYPE(BookTitleInfoPtr)

#endif // BOOKTITLES_H
