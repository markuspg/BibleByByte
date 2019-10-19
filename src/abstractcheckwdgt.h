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

#ifndef ABSTRACTCHECKWDGT_H
#define ABSTRACTCHECKWDGT_H

#include "abstractdatatype.h"

#include <QWidget>

class AbstractCheckWdgt : public QWidget
{
    Q_OBJECT

public:
    explicit AbstractCheckWdgt(QWidget *argParent = nullptr);

    void SetDataToCheck(const AbstractDataTypeSharedPtr &argData);
    virtual void ShowData() = 0;

protected:
    virtual void SetDataToCheckInternal(const AbstractDataTypeSharedPtr &argData) = 0;
    /*!
     * \brief ShowCheckedDataWdgt shows or hides the widget containing the data in question
     * \param argDisplayData True, if the widget shall be visible, false otherwise
     */
    virtual void ShowCheckedDataWdgt(bool argDisplayData) = 0;
};

#endif // ABSTRACTCHECKWDGT_H
