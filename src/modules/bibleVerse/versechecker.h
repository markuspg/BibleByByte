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

#ifndef VERSECHECKER_H
#define VERSECHECKER_H

#include "../../abstractdatachecker.h"
#include "../../singleton.h"

class VerseChecker : public AbstractDataChecker, public Singleton<VerseChecker>
{
    Q_OBJECT

public:
    explicit VerseChecker(QWidget* const argParent = nullptr);
};

#endif // VERSECHECKER_H
