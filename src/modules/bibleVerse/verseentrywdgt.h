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

#ifndef VERSEENTRYWDGT_H
#define VERSEENTRYWDGT_H

#include "../../abstractentrywdgt.h"
#include "../../singleton.h"
#include "verse.h"

namespace Ui {
class VerseEntryWdgt;
} // namespace Ui

class VerseEntryWdgt :
    public AbstractEntryWdgt,
    public Singleton<VerseEntryWdgt>
{
    Q_OBJECT

public:
    explicit VerseEntryWdgt(QWidget* const argParent = nullptr);
    ~VerseEntryWdgt() override;

    void ClearAndPrepare() override;
    AbstractDataTypeSharedPtr GetDataPr() override;

private:
    Ui::VerseEntryWdgt* const ui = nullptr;

private slots:
    void OnDataChanged();
};

#endif // VERSEENTRYWDGT_H
