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

#ifndef ABSTRACTENTRYWDGT_H
#define ABSTRACTENTRYWDGT_H

#include "abstractdatatype.h"

#include <QWidget>

class AbstractEntryWdgt : public QWidget
{
    Q_OBJECT

public:
    explicit AbstractEntryWdgt(QWidget* const argParent = nullptr);

    /*!
     * \brief Clear the entry widget and prepare for next entry (e.g. increment
     * indices)
     */
    virtual void ClearAndPrepare() = 0;
    /*!
     * \brief GetDataPr returns a pointer to the data and otherwise an empty
     * shared pointer
     *
     * \return A shared pointer pointing to the data (or an empty one)
     */
    virtual AbstractDataTypeSharedPtr GetDataPr() = 0;

signals:
    /*!
     * \brief This signal tells the its containing widget that data is complete
     * for submission
     */
    void DataComplete();

protected:
    bool dataHasBeenCompleted = false;
};

#endif // ABSTRACTENTRYWDGT_H
