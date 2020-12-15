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

#ifndef VERSECHECKWDGT_H
#define VERSECHECKWDGT_H

#include "../../abstractcheckwdgt.h"
#include "../../singleton.h"

namespace Ui {
class VerseCheckWdgt;
} // namespace Ui

class VerseCheckWdgt :
    public AbstractCheckWdgt,
    public BibleByByte::Singleton<VerseCheckWdgt>
{
    Q_OBJECT

public:
    explicit VerseCheckWdgt(QWidget* argParent = nullptr);
    ~VerseCheckWdgt() override;

    void ShowData() override;

private:
    void SetDataToCheckInternal(
        const AbstractDataTypeSharedPtr& argData) override;
    void ShowCheckedDataWdgt(bool argDisplayData) override;

    Ui::VerseCheckWdgt* const ui = nullptr;
};

#endif // VERSECHECKWDGT_H
